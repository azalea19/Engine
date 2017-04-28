-- Player --


local Player = 
{
	instanceid =0,
	boundingBox = { min = {x=0,y=0,z=0}, max = {x=0,y=0,z=0} },
	position = {x=0,y=0,z=0},
	direction = {x=0,y=0,z=0},
	camera = {},
	acceleration = {x=0,y=0,z=0}
}

Player.__index = Player

function Player:new(o)
	o = o or {}
	setmetatable(o, self)
	self.__index = self
	return o
end

function Player:setAABB(minx,maxx,miny,maxy,minz,maxz)
	printAPI.print("Setting player AABB...\n");
	
	self.boundingBox.min = {x=minx,y=miny,z=minz}
	self.boundingBox.max = {x=maxx,y=maxy,z=maxz}
end

function Player:BBToWorld()
	local newBB = {}
    newBB.min = luaVectorUtility.vec3_Sum(self.boundingBox.min,self.position,context.handle)
    newBB.max = luaVectorUtility.vec3_Sum(self.boundingBox.max,self.position,context.handle)

    return newBB
end

function Player:update()
	-- Start movement update
	self.position = cameraAPI.getPosition(camera0,context.handle)

	-- written by liz translated from maddys c++ code
	turnSpeed = 0.3
	if(inputManagerAPI.isKeyDown(SDL_SCANCODE_LSHIFT)) then
		moveSpeed = 0.2
	else
		moveSpeed = 0.1
	end
	gravitySpeed = 0.01
	--rotation
	origYaw = cameraAPI.getYaw(camera0,context.handle)
	origPitch = cameraAPI.getPitch(camera0,context.handle)
	
	deltaYaw =  - inputManagerAPI.mouseDeltaX() * turnSpeed
	--PrintVec3(deltaYaw)

	deltaPitch = -inputManagerAPI.mouseDeltaY() * turnSpeed
	--printAPI.print(deltaYaw .. "," .. deltaPitch .. "\n")

	cameraAPI.setYaw(camera0,origYaw + deltaYaw)
	cameraAPI.setPitch(camera0,origPitch+deltaPitch)

	--translation   
	oldPos = cameraAPI.getPosition(camera0,context.handle);
	forward = cameraAPI.forward(camera0,context.handle);
	right = cameraAPI.right(camera0,context.handle);
	up = cameraAPI.up(camera0,context.handle);

	translation = luaVectorUtility.vec3_CreateEmpty(context.handle)

	if inputManagerAPI.isKeyDown(SDL_SCANCODE_W) then
		translation = luaVectorUtility.vec3_Sum(translation,forward,context.handle)
	end

	if inputManagerAPI.isKeyDown(SDL_SCANCODE_A) then
		translation = luaVectorUtility.vec3_Subtract(translation,right,context.handle)
	end

	if inputManagerAPI.isKeyDown(SDL_SCANCODE_S) then
		translation = luaVectorUtility.vec3_Subtract(translation,forward,context.handle)
	end
	if inputManagerAPI.isKeyDown(SDL_SCANCODE_D) then
		translation = luaVectorUtility.vec3_Sum(translation,right,context.handle)
	end
	if debug then

		if inputManagerAPI.isKeyDown(SDL_SCANCODE_Q) then
			translation = luaVectorUtility.vec3_Sum(translation,up,context.handle)
		end

		if inputManagerAPI.isKeyDown(SDL_SCANCODE_Z) then
			translation = luaVectorUtility.vec3_Subtract(translation,up,context.handle)
		end
	end
	
	emptyvec = luaVectorUtility.vec3_CreateEmpty(context.handle)
	
	newPos = self.position
	
	--printAPI.print("Updating player location...\n")
	if not luaVectorUtility.vec3_Equals(translation,emptyvec) then
		translation = luaVectorUtility.vec3_Normalize(translation,context.handle)
	end

	translation = luaVectorUtility.vec3_ScalarMultiply(translation,moveSpeed,context.handle)
	translation.y = translation.y - gravitySpeed

	newPos = luaVectorUtility.vec3_Sum(oldPos,translation, context.handle)

	newPos.x = math.min(math.max(newPos.x, 0), terrainSizeX - 1)
	newPos.z = math.min(math.max(newPos.z, 0), terrainSizeY - 1)
	desiredHeight = GetHeightAtPoint(newPos.x, newPos.z) + 1.8

	newPos.y = math.max(newPos.y, desiredHeight)		
				
	cameraAPI.setPosition(camera0,newPos.x,newPos.y,newPos.z);  

	-- printAPI.print("Moving player bounding box...\n")
	self.position = newPos
	
	--PrintVec3s(self.boundingBox.min, self.boundingBox.max)

	--value = AABBBAPI.move(emptyv,emptyb,emptyc,context.handle)
		 
	--printAPI.print("Completed player update.\n")

	manyList = {}
	local currentGOs = world:GetGameObjects()

    for i = 1, world:GetGameObjectCount() do
		local bbo = currentGOs[i]:BBToWorld()
		if bbo ~= nil then
			manyList[i] = bbo
		else
			printAPI.print("nil aabb\n")
		end
    end


	self.position = islandCollisionAPI.resolve(self.position,self.boundingBox,manyList,world:GetGameObjectCount(),0.01,context.handle)
	
	cameraAPI.setPosition(camera0,self.position.x,self.position.y,self.position.z)
end

return Player
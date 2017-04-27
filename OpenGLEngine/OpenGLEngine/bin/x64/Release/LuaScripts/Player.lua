-- Player --


local Player = 
{
	instanceid =0,
	bbox = { min = {x=0,y=0,z=0}, max = {x=0,y=0,z=0} },
	pos = {x=0,y=0,z=0},
	lastpos = {x=0,y=0,z=0},
	dir = {x=0,y=0,z=0}
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

	
	self.bbox.min = {x=self.pos.x+minx,y=self.pos.y+miny,z=self.pos.z+minz}
	self.bbox.max = {x=self.pos.x+maxx,y=self.pos.y+maxy,z=self.pos.z+maxz}

	--[[
	{
	min = {pos.x+minx, pos.y+miny, pos.z+minz}, 
	max = {pos.x+maxx, pos.y+maxy, pos.z+maxz}
	}
	]]
	printAPI.print("Player AABB set.\n");

end

function Player:update()
	-- Start movement update
	--printAPI.print(1)
	--printAPI.print("Updating player.\n")
	self.pos = cameraAPI.getPosition(camera0,context.handle)

	-- written by liz translated from maddys c++ code
	turnSpeed = 0.3
	if(inputManagerAPI.isKeyDown(SDL_SCANCODE_LSHIFT)) then
	moveSpeed = 0.2
	else
	moveSpeed = 0.1
	end
	gravitySpeed = 1 
	--rotation
	origYaw = cameraAPI.getYaw(camera0,context.handle)
	origPitch = cameraAPI.getPitch(camera0,context.handle)
	
	deltaYaw =  - inputManagerAPI.mouseDeltaX() * turnSpeed
	--PrintVec3(deltaYaw)

	deltaPitch = -inputManagerAPI.mouseDeltaY() * turnSpeed
	--printAPI.print(deltaYaw .. "," .. deltaPitch .. "\n")

	cameraAPI.setYaw(camera0,origYaw + deltaYaw)
	cameraAPI.setPitch(camera0,origPitch+deltaPitch)
	--printAPI.print(2)

	--translation   

	oldPos = cameraAPI.getPosition(camera0,context.handle);
	forward = cameraAPI.forward(camera0,context.handle);
	right = cameraAPI.right(camera0,context.handle);
	up = cameraAPI.up(camera0,context.handle);

	translation = luaVectorUtility.vec3_CreateEmpty(context.handle)

	--printAPI.print(translation[1] .. translation[2] .. translation[3] .. "\n")
	--printAPI.print(3)

	if inputManagerAPI.isKeyDown(SDL_SCANCODE_W) then
		translation = luaVectorUtility.vec3_Sum(translation,forward,context.handle)
		--printAPI.print(translation[1] .. translation[2] .. translation[3] .. "\n")
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

	--printAPI.print("Updating player location...\n")
	
	newPos = self.pos
	
	--printAPI.print("Updating player location...\n")

		--printAPI.print(4)

	--if moving
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
				
	--printAPI.print(newPos.x .. "    " .. newPos.z .. "\n")	
	cameraAPI.setPosition(camera0,newPos.x,newPos.y,newPos.z);  

	-- Movement update finished

  -- printAPI.print("Moving player bounding box...\n")
	--printAPI.print(6)

	self.pos = newPos
	
	--PrintVec3s(self.bbox.min, self.bbox.max)

	--value = AABBBAPI.move(emptyv,emptyb,emptyc,context.handle)
	--printAPI.print(7)

	self.bbox = AABBAPI.move(self.bbox,self.lastpos,self.pos,context.handle)
	--printAPI.print(8)

	self.lastpos = self.pos
		 
	--printAPI.print("Completed player update.\n")

	manyList = {}
    anumRows = 0
    for k,v in next, gameObjects do
        anumRows = anumRows + 1
    end
	--printAPI.print("rows " .. anumRows)

    for i = 1, anumRows do
		local bbo = gameObjects[i]["boundingbox"]
		if bbo ~= nil then
			manyList[i] = bbo
		else
			printAPI.print("nil aabb\n")

		end
    end
	--printAPI.print(9)

	self.pos = islandCollisionAPI.resolve(self.pos,self.bbox,manyList,anumRows,0.01,context.handle)
	--printAPI.print(9.1)
	
	cameraAPI.setPosition(camera0,self.pos.x,self.pos.y,self.pos.z)
	--printAPI.print(10)

end

return Player
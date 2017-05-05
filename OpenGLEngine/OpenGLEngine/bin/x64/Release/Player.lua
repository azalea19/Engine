local Player = {}
Player.__index = Player

function Player.new(newCam)
	instance = {
		instanceid =0,
		boundingBox = { min = {x=0,y=0,z=0}, max = {x=0,y=0,z=0} },
		position = {x=0,y=0,z=0},
		direction = {x=0,y=0,z=0},
		camera = newCam,
		velocity = luaVectorUtility.vec3_CreateEmpty(context.handle)
	}

	setmetatable(instance, Player)
	return instance
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
	-- written by liz translated from maddys c++ code
	turnSpeed = 0.3
	if(inputManagerAPI.isKeyDown(Sprint_Input)) then
		moveSpeed = 0.1
	else
		if(inputManagerAPI.isKeyDown(Walk_Input)) then
			moveSpeed = 0.025
		else
			moveSpeed = 0.05
		end
	end
	jumpHeight = 1
	gravitySpeed = 0.05
	terminalVelocity = -1
	friction = 0.8

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
		translation = luaVectorUtility.vec3_ScalarMultiply(translation,moveSpeed,context.handle)
		translation.y = 0
		self.velocity = luaVectorUtility.vec3_Sum(translation,self.velocity,context.handle)
	end

	if inputManagerAPI.isKeyDown(SDL_SCANCODE_A) then
		translation = luaVectorUtility.vec3_Subtract(translation,right,context.handle)
		translation = luaVectorUtility.vec3_ScalarMultiply(translation,moveSpeed,context.handle)
		translation.y = 0
		self.velocity = luaVectorUtility.vec3_Sum(translation,self.velocity,context.handle)
	end

	if inputManagerAPI.isKeyDown(SDL_SCANCODE_S) then
		translation = luaVectorUtility.vec3_Subtract(translation,forward,context.handle)
		translation = luaVectorUtility.vec3_ScalarMultiply(translation,moveSpeed,context.handle)
		translation.y = 0
		self.velocity = luaVectorUtility.vec3_Sum(translation,self.velocity,context.handle)
	end
	if inputManagerAPI.isKeyDown(SDL_SCANCODE_D) then
		translation = luaVectorUtility.vec3_Sum(translation,right,context.handle)
		translation = luaVectorUtility.vec3_ScalarMultiply(translation,moveSpeed,context.handle)
		translation.y = 0
		self.velocity = luaVectorUtility.vec3_Sum(translation,self.velocity,context.handle)
	end
	if debug then

		if inputManagerAPI.isKeyDown(SDL_SCANCODE_Q) then
			translation = luaVectorUtility.vec3_Sum(translation,up,context.handle)
			translation = luaVectorUtility.vec3_ScalarMultiply(translation,moveSpeed,context.handle)
			translation.y = 0
			self.velocity = luaVectorUtility.vec3_Sum(translation,self.velocity,context.handle)
		end

		if inputManagerAPI.isKeyDown(SDL_SCANCODE_Z) then
			translation = luaVectorUtility.vec3_Subtract(translation,up,context.handle)
			translation = luaVectorUtility.vec3_ScalarMultiply(translation,moveSpeed,context.handle)
			translation.y = 0
			self.velocity = luaVectorUtility.vec3_Sum(translation,self.velocity,context.handle)
		end
	end
	
	if(inputManagerAPI.isKeyDown(Jump_Input) and self.velocity == 0) then
		self.velocity.y = jumpHeight
	end

	emptyvec = luaVectorUtility.vec3_CreateEmpty(context.handle)
	
	newPos = self.position
	
	self.velocity.x = self.velocity.x * friction
	self.velocity.z = self.velocity.z * friction


	if(self.velocity.y < terminalVelocity) then
		self.velocity.y = terminalVelocity
	end

	--printAPI.print("Updating player location...\n")
	if not luaVectorUtility.vec3_Equals(self.velocity,emptyvec) then
		--self.velocity = luaVectorUtility.vec3_Normalize(self.velocity,context.handle)
	end
	--translation = luaVectorUtility.vec3_ScalarMultiply(translation,moveSpeed,context.handle)
	--translation.y = translation.y - gravitySpeed
	self.velocity.y = self.velocity.y - gravitySpeed
	printAPI.print(self.velocity.x .. "\n")
	newPos = luaVectorUtility.vec3_Sum(oldPos,self.velocity, context.handle)
	newPos.x = math.min(math.max(newPos.x, 0), terrainSizeX - 1)
	newPos.z = math.min(math.max(newPos.z, 0), terrainSizeY - 1)
	desiredHeight = GetHeightAtPoint(newPos.x, newPos.z) + 1.8
	newPos.y = math.max(newPos.y, desiredHeight)		
	if(newPos.y == desiredHeight) then
		self.velocity.y = 0
	end
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
	self.position = islandCollisionAPI.resolve(self.position,self:BBToWorld(),manyList,world:GetGameObjectCount(),0.01,context.handle)
	
	cameraAPI.setPosition(camera0,self.position.x,self.position.y,self.position.z)
end

return Player
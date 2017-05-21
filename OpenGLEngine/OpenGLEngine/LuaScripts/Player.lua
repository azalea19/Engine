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
	local turnSpeed = 0.3
	local moveSpeed = 2.5 * deltaTime
	if(inputManagerAPI.isKeyDown(Sprint_Input)) then
		moveSpeed = 5 * deltaTime
	else
		if(inputManagerAPI.isKeyDown(Walk_Input)) then
			moveSpeed = 1 * deltaTime
		end
	end
	local jumpHeight = 2
	local gravitySpeed = deltaTime * 4.9
	local terminalVelocity = -1
	local friction = 0.90

	--rotation
	origYaw = cameraAPI.getYaw(camera0,context.handle)
	origPitch = cameraAPI.getPitch(camera0,context.handle)
	
	deltaYaw =  - inputManagerAPI.mouseDeltaX() * turnSpeed
	--PrintVec3(deltaYaw)

	deltaPitch = -inputManagerAPI.mouseDeltaY() * turnSpeed
	--printAPI.print(deltaYaw .. "," .. deltaPitch .. "\n")

	cameraAPI.setYaw(camera0,origYaw + deltaYaw)
	cameraAPI.setPitch(camera0,origPitch+deltaPitch)

	 
	oldPos = cameraAPI.getPosition(camera0,context.handle);
	forward = cameraAPI.forward(camera0,context.handle);
	right = cameraAPI.right(camera0,context.handle);
	up = cameraAPI.up(camera0,context.handle);

	translation = luaVectorUtility.vec3_CreateEmpty(context.handle)

	if inputManagerAPI.isKeyDown(Forward_Input) then
		translation = luaVectorUtility.vec3_Sum(translation,forward,context.handle)
		translation.y = 0
	end

	if inputManagerAPI.isKeyDown(Left_Input) then
		translation = luaVectorUtility.vec3_Subtract(translation,right,context.handle)
		translation.y = 0
	end

	if inputManagerAPI.isKeyDown(Backward_Input) then
		translation = luaVectorUtility.vec3_Subtract(translation,forward,context.handle)
		translation.y = 0
	end
	if inputManagerAPI.isKeyDown(Right_Input) then
		translation = luaVectorUtility.vec3_Sum(translation,right,context.handle)
		translation.y = 0
	end
	if debug then

		if inputManagerAPI.isKeyDown(Ascend_Input) then
			translation = luaVectorUtility.vec3_Sum(translation,up,context.handle)
			translation.y = 0
		end

		if inputManagerAPI.isKeyDown(Descend_Input) then
			translation = luaVectorUtility.vec3_Subtract(translation,up,context.handle)
			translation.y = 0
		end
	end
	
	if(inputManagerAPI.isKeyDown(Jump_Input) and self.velocity.y == 0) then
		self.velocity.y = jumpHeight
	end

	emptyvec = luaVectorUtility.vec3_CreateEmpty(context.handle)
	
	newPos = self.position

	if not luaVectorUtility.vec3_Equals(translation,emptyvec) then
		translation = luaVectorUtility.vec3_Normalize(translation,context.handle)
		translation = luaVectorUtility.vec3_ScalarMultiply(translation,moveSpeed,context.handle)		
	end


	self.velocity.y = self.velocity.y - gravitySpeed

	newPos = luaVectorUtility.vec3_Sum(oldPos,translation, context.handle)
	newPos.y = newPos.y + self.velocity.y
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
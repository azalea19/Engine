dofile '../Assets/Scripts/Weapon.lua'

local Player = {}
Player.__index = Player

function Player.new(newCam,newCurrentHealth,newMaxHealth)
	instance = 
	{
        maxHealth = newMaxHealth,
	    currentHealth = newCurrentHealth,
		instanceid =0,
		boundingBox = { min = {x=0,y=0,z=0}, max = {x=0,y=0,z=0} },
		position = {x=0,y=0,z=0},
		direction = {x=0,y=0,z=0},
		camera = newCam,
		velocity = mmath.vec3_CreateEmpty(context.handle),
		lookRay = nil,
		lookTarget = nil,
		inDialogue = false,
		rangedWeaponEquipped = true, -- Whether the player is wielding a readied ranged weapon
		weapon = nil,
		lastTimeShot = nil, -- Last time player shot ranged weapon
	}

	setmetatable(instance, Player)
	return instance
end


function Player:getPosition()
	return self.position
end

function Player:takeDamage(dmg)
    debugLPrint("Player Taking damage " .. dmg .. "\n")
	self.currentHealth = self.currentHealth - dmg
	if(self.currentHealth <= 0) then
		self:die()
	end
end


function Player:die()
    printAPI.print("Player has died.")

    inMenu = true
    inGame = false
end


function Player:setPosition(newPos)
	self.position = newPos
	cameraAPI.setPosition(camera0,self.position.x,self.position.y,self.position.z)

end

function Player:setAABB(minx,maxx,miny,maxy,minz,maxz)
	printAPI.print("Setting player AABB...\n");
	
	self.boundingBox.min = {x=minx,y=miny,z=minz}
	self.boundingBox.max = {x=maxx,y=maxy,z=maxz}

end

function Player:BBToWorld()
	
	local newBB = {}
    newBB.min = mmath.vec3_Sum(self.boundingBox.min,self.position,context.handle)
    newBB.max = mmath.vec3_Sum(self.boundingBox.max,self.position,context.handle)

    return newBB
end

function Player:update()

	
	-- written by liz translated from maddys c++ code
	--printAPI.print("Updating player\n")
	local turnSpeed = 0.3
	local moveSpeed = 2.8 * deltaTime
	--printAPI.print("DeltaTime: " .. deltaTime .. "\n")
	if(inputManagerAPI.isKeyDown(Sprint_Input)) then
		moveSpeed = moveSpeed * 2
	else
		if(inputManagerAPI.isKeyDown(Walk_Input)) then
			moveSpeed = moveSpeed * 0.5
		end
	end
	local jumpHeight = 0.1
	local gravitySpeed = 0.003
	local terminalVelocity = -10
	local friction = 0.5
	local minimumSpeed = 0.001

	
	if(self.inDialogue == false) then
		--rotation
		origYaw = cameraAPI.getYaw(camera0,context.handle)
		origPitch = cameraAPI.getPitch(camera0,context.handle)
		
		deltaYaw =  - inputManagerAPI.mouseDeltaX() * turnSpeed
		deltaPitch = -inputManagerAPI.mouseDeltaY() * turnSpeed

		cameraAPI.setYaw(camera0,origYaw + deltaYaw)
		cameraAPI.setPitch(camera0,origPitch+deltaPitch)
		
		--translation  
		if(self.velocity.x < minimumSpeed and self.velocity.x > -1 * minimumSpeed) then
			self.velocity.x = 0
		end
		if(self.velocity.z < minimumSpeed and self.velocity.z > -1 * minimumSpeed) then
			self.velocity.z = 0
		end
		 
		oldPos = cameraAPI.getPosition(camera0,context.handle);
		forward = cameraAPI.forward(camera0,context.handle);
		right = cameraAPI.right(camera0,context.handle);
		up = cameraAPI.up(camera0,context.handle);

		translation = mmath.vec3_CreateEmpty(context.handle)

		if inputManagerAPI.isKeyDown(Forward_Input) then
			translation = mmath.vec3_Sum(translation,forward,context.handle)
			translation.y = 0
		end

		if inputManagerAPI.isKeyDown(Left_Input) then
			translation = mmath.vec3_Subtract(translation,right,context.handle)
			translation.y = 0
		end

		if inputManagerAPI.isKeyDown(Backward_Input) then
			translation = mmath.vec3_Subtract(translation,forward,context.handle)
			translation.y = 0
		end
		if inputManagerAPI.isKeyDown(Right_Input) then
			translation = mmath.vec3_Sum(translation,right,context.handle)
			translation.y = 0
		end
		if debug then

			if inputManagerAPI.isKeyDown(Ascend_Input) then
				translation = mmath.vec3_Sum(translation,up,context.handle)
				translation.y = 0
			end

			if inputManagerAPI.isKeyDown(Descend_Input) then
				translation = mmath.vec3_Subtract(translation,up,context.handle)
				translation.y = 0
			end
		end
		
		if(inputManagerAPI.isKeyDown(Jump_Input) and self.velocity.y == 0) then
			self.velocity.y = jumpHeight
		end

		emptyvec = mmath.vec3_CreateEmpty(context.handle)
		
		newPos = self.position

		
		if not mmath.vec3_Equals(translation,emptyvec) then
			translation = mmath.vec3_Normalize(translation,context.handle)
			translation = mmath.vec3_ScalarMultiply(translation,moveSpeed,context.handle)
			self.velocity = mmath.vec3_Sum(translation,self.velocity,context.handle)
		end
		self.velocity.x = self.velocity.x * friction
		self.velocity.z = self.velocity.z * friction

		self.velocity.y = self.velocity.y - gravitySpeed
		if(self.velocity.y < terminalVelocity) then
			self.velocity.y = terminalVelocity
		end

		--printAPI.print(math.sqrt(self.velocity.x * self.velocity.x + self.velocity.y * self.velocity.y + self.velocity.z * self.velocity.z) .. "\n")
		newPos = mmath.vec3_Sum(oldPos,self.velocity, context.handle)
		--newPos = oldPos
		newPos.x = math.min(math.max(newPos.x, 0), terrainSizeX - 1)
		newPos.z = math.min(math.max(newPos.z, 0), terrainSizeY - 1)
		desiredHeight = GetHeightAtPoint(newPos.x, newPos.z) + 1.8
		newPos.y = math.max(newPos.y, desiredHeight)		
		if(newPos.y == desiredHeight) then
			self.velocity.y = 0
		end

		self.position = newPos

    if createCollisionTree then
		  if collisionAPI.box_collidingInTree(self:BBToWorld()) then
			  self.velocity.y = 0
		  end


		  if self.boundingBox ~= nil then
			  self:setPosition( islandCollisionAPI.resolve(self.position,self:BBToWorld(),context.handle))
		  end
    end
		--printAPI.print(self.position.y .. "\n")
		cameraAPI.setPosition(camera0,self.position.x,self.position.y,self.position.z)
	end
end

return Player
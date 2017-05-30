dofile '../Assets/Scripts/Weapon.lua'
local Vector3 = dofile '../Assets/Scripts/Vector3.lua'

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
        trackTerrain = true,
		weapon = {},
		weaponID
	}

	setmetatable(instance, Player)
	return instance
end



function Player:setWeapon(newWeapon)
	for i=1,#weaponList do
		if(weaponList[i].id == newWeapon) then
			debugLPrint("Found weapon\n")
			self.weapon = weaponList[i]
		end
	end
	self.weaponID = newWeapon
end

function Player:getPosition()
	return self.position
end

function Player:takeDamage(dmg)
    debugLPrint("Player Taking damage " .. dmg .. "\n")
	self.currentHealth = self.currentHealth - dmg
    soundAPI.playSound("Gunshot",1)
	if(self.currentHealth <= 0) then
		self:die()
	end
end

function Player:die()
    printAPI.print("Player has died.")

    inMenu = true
	preCameraPos = player0:getPosition()
	--printVec3(preCameraPos)
	preCameraYaw = cameraAPI.getYaw(camera0,context.handle)
	preCameraPitch = cameraAPI.getPitch(camera0,context.handle)
			
	cameraAPI.setPosition(camera0,10,-1,30)
	cameraAPI.setYaw(camera0,0)
	cameraAPI.setPitch(camera0,0)
	changeMenu(0)
end


function Player:setPosition(newPos)
	self.position = newPos
	cameraAPI.setPosition(camera0,self.position.x,self.position.y + 1.8,self.position.z)

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

function Player:getYaw()
	return cameraAPI.getYaw(camera0,context.handle)
end

function Player:getPitch();
	return cameraAPI.getPitch(camera0,context.handle)
end

function Player:setYaw(newYaw)
	cameraAPI.setYaw(camera0,newYaw)
end

function Player:setPitch(newPitch);
	cameraAPI.setPitch(camera0,newPitch)
end

function Player:update()
   -- printVec3(self:getPosition())
	
	-- written by liz translated from maddys c++ code
	--printAPI.print("Updating player\n")
	local turnSpeed = 0.3
	local moveSpeed = 2.8 * deltaTime
	--printAPI.print("DeltaTime: " .. deltaTime .. "\n")
	if(inputManagerAPI.isKeyDown(Sprint_Input)) then
		moveSpeed = moveSpeed * 8
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
		 
		oldPos = self.position
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

		debugPrint("Delta Time:"..deltaTime .. "\n")
		newPos = mmath.vec3_Sum(oldPos,self.velocity, context.handle)
		newPos.x = math.min(math.max(newPos.x, 0), wsTerrainSize)
		newPos.z = math.min(math.max(newPos.z, 0), wsTerrainSize)
		desiredHeight = GetHeightAtPoint(newPos.x, newPos.z)
		newPos.y = math.max(newPos.y, desiredHeight)		
		if(newPos.y == desiredHeight) then
			self.velocity.y = 0
		end
		cameraAPI.setPosition(camera0,newPos.x,newPos.y,newPos.z);  
		self.position = newPos
      
        debugPrint("Resolving player collisions...\n")


        if createCollisionTree then
		      if collisionAPI.box_collidingInTree(self:BBToWorld()) then
			      self.velocity.y = 0
		      end


		      if self.boundingBox ~= nil then
			      self:setPosition( islandCollisionAPI.resolve(self.position,self:BBToWorld(),context.handle))
		      end
        end


		--printAPI.print(self.position.y .. "\n")

	end
    
	cameraAPI.setPosition(camera0,self.position.x,self.position.y + 1.8,self.position.z)
    -- Fill bounding box/collision data for use
	local goList = {} -- list of gameobjects with bounding boxes
	local listCount =0 -- number in these list
			
	local currentGOs = world:GetGameObjects()

	for i = 1, world:GetGameObjectCount() do
		if(currentGOs == nil) then
		debugPrint("Warning: Tried to check collisions, but World's GameObjects is nil\n")
		else
			
			debugPrint(world:GetGameObjectCount() .. " game objects in scene to check AABBs\n")
			debugPrint(currentGOs[i].name .. "is name of current object\n")	
						
			if currentGOs[i].displayNameOnLook then
				goList[i] = currentGOs[i]
				listCount = listCount + 1
			end
		end
	end

    debugPrint("Setting player ray\n")
	
	self.lookRay = {pos = cameraAPI.getPosition(camera0, context.handle), dir = cameraAPI.forward(camera0,context.handle)}
	
	debugPrint("Checking ray collisions\n")
	
	if(debugdetail) then
		printAPI.print("Ray data: ")
	end

	self.lookTarget =  nil
	lookAtText = " "

	local lookAtIndex = 0;
	local lookAtDist = 99999999;
	--printAPI.print("Object count " ..listCount .. '\n')
	for i=1,listCount, 1 do
		local dist = collisionAPI.rayOnObject(self.lookRay, goList[i].id);
		if((dist > 0) and (dist < lookAtDist)) then
			lookAtIndex = i
			lookAtDist = dist
		end
	end

	for i=1,listCount, 1 do
		if lookAtIndex == i then
			goList[i].playerLookAt = true
			self.lookTarget =  goList[i]
			if goList[i].displayNameOnLook  then		
				lookAtText = goList[i].name
			end
		else
			goList[i].playerLookAt = false
		end
	end

	if(self.lookTarget) then
		--printAPI.print(lookAtDist .. '\n')
	end

	if self.lookTarget == nil then
		self.inDialogue = false
    end
end

return Player
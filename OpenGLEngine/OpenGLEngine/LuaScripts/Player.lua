-- Player --
local Player = 
{
	instanceid =0,
	bbox = { min = {x=0,y=0,z=0}, max = {x=0,y=0,z=0} },
	pos = {x=0,y=0,z=0},
	lastpos = {x=0,y=0,z=0}
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

	--printAPI.print("Updating player.\n")
	self.pos = cameraAPI.getPosition(camera0,context.handle)
	-- written by liz translated from maddys c++ code
	turnSpeed = 0.3
	moveSpeed = 0.3
	  
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

	--printAPI.print(translation[1] .. translation[2] .. translation[3] .. "\n")

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
		newPos.y = oldPos.y
	if not luaVectorUtility.vec3_Equals(translation,emptyvec) then
   
		translation = luaVectorUtility.vec3_Normalize(translation,context.handle)
		newPos = luaVectorUtility.vec3_Sum(oldPos,translation, context.handle)
		alterSpeed = moveSpeed
		climbSpeed = 1
		loop = true
		--while loop do
			translation = luaVectorUtility.vec3_ScalarMultiply(translation,alterSpeed,context.handle)
			newPos = luaVectorUtility.vec3_Sum(oldPos,translation, context.handle)
			desiredHeight = GetHeightAtPoint(newPos.x, newPos.z) + 5
			dif = desiredHeight - oldPos.y
			if(dif == 0) then
				newPos.y = oldPos.y
				loop = false
				printAPI.print("Stable Y\n")
			else
				if(dif > climbSpeed) then
					alterSpeed = alterSpeed - 0.1
					printAPI.print("Diff: " .. desiredHeight .. "\n" .. "climbSpeed: " .. oldPos.y .. "\n")
				else
					if(desiredHeight  <  oldPos.y ) then
						if(desiredHeight + moveSpeed >=  oldPos.y) then
							newPos.y = desiredHeight
							printAPI.print("fall to point\n")
							loop = false
						else
							newPos.y = oldPos.y - moveSpeed
							loop = false
							printAPI.print("fall\n")
						end
					else
						if (dif <= moveSpeed) then
							--printAPI.print("climb \n")
							desiredHeight = GetHeightAtPoint(newPos.x, newPos.z) + 5
							newPos.y = desiredHeight
							loop = false
						end
					end
				end
				if(alterSpeed <= 0) then
					loop = false
					printAPI.print("tooSteep\n")
					alterSpeed = 1
					translation = luaVectorUtility.vec3_ScalarMultiply(translation,alterSpeed,context.handle)
					newPos = luaVectorUtility.vec3_Sum(oldPos,translation, context.handle)
					desiredHeight = GetHeightAtPoint(newPos.x, newPos.z) + 5
					newPos.y = desiredHeight
					loop = false
				end
			end
		--end
	else
		desiredHeight = GetHeightAtPoint(oldPos.x, oldPos.z) + 5
		dif = desiredHeight - oldPos.y
		printAPI.print("NotMoving\n")
		if(dif == 0) then
			newPos.y = oldPos.y
		else
			if(desiredHeight  <  oldPos.y ) then
				if(desiredHeight + moveSpeed >=  oldPos.y) then
					newPos.y = desiredHeight
					printAPI.print("fall to point\n")
					loop = false
				else
					newPos.y = oldPos.y - moveSpeed
					loop = false
					printAPI.print("fall\n")
				end
			else
				if (dif <= moveSpeed) then
					printAPI.print("climb \n")
					desiredHeight = GetHeightAtPoint(newPos.x, newPos.z) + 5
					newPos.y = desiredHeight
					loop = false
				end
			end
		end
	end
	printAPI.print(newPos.x .. "\n")	
	cameraAPI.setPosition(camera0,newPos.x,newPos.y,newPos.z);  

	-- Movement update finished

  -- printAPI.print("Moving player bounding box...\n")

	self.pos = cameraAPI.getPosition(camera0,context.handle)
	
	--PrintVec3s(self.bbox.min, self.bbox.max)

	--value = AABBBAPI.move(emptyv,emptyb,emptyc,context.handle)

	self.bbox = AABBAPI.move(self.bbox,self.lastpos,self.pos,context.handle)
	
	self.lastpos = self.pos
		 
	--printAPI.print("Completed player update.\n")

	manyList = {}
	manyList[1] = plantBBox
	manyList[2] = plantBBox
	count = 2

	self.pos = islandCollisionAPI.resolve(self.pos,self.bbox,manyList,count,0.01,context.handle)
	cameraAPI.setPosition(camera0,self.pos.x,self.pos.y,self.pos.z)

end

return Player
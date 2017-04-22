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

	if not luaVectorUtility.vec3_Equals(translation,emptyvec) then
   
		translation = luaVectorUtility.vec3_Normalize(translation,context.handle)
		translation = luaVectorUtility.vec3_ScalarMultiply(translation,moveSpeed,context.handle)

		newPos = luaVectorUtility.vec3_Sum(oldPos,translation, context.handle)

		newPos.y = GetHeightAtPoint(newPos.x, newPos.z) + 5
		cameraAPI.setPosition(camera0,newPos.x,newPos.y,newPos.z);  
	else
		--printAPI.print("Player has not moved.\n")

	end 
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

	--[[
	errorBBox = {min = self.bbox.min, max = self.bbox.max}
	errorBBox.min.x =  errorBBox.min.x * 0.9
	errorBBox.min.y =  errorBBox.min.y * 0.9
	errorBBox.min.z =  errorBBox.min.z * 0.9
	errorBBox.max.x =  errorBBox.max.x * 0.9
	errorBBox.max.y =  errorBBox.max.y * 0.9
	errorBBox.max.z =  errorBBox.max.z * 0.9

	PrintVec3s(errorBBox.min,self.bbox.min)
	printAPI.print("+")
	PrintVec3s(errorBBox.max,self.bbox.max)
	printAPI.print("\n")
	]]
	--PrintVec3s(self.bbox.min,self.bbox.max)
	--printAPI.print("\n")
	collides = islandCollisionAPI.checkAnyCollision(self.bbox,manyList,count)
	
	if collides then
	   --printAPI.print("Collision! Resolved to: ")
	   self.pos = islandCollisionAPI.resolve(self.pos,self.bbox,manyList,count,2,context.handle)
	   cameraAPI.setPosition(camera0,self.pos.x,self.pos.y,self.pos.z)

	   --PrintVec3(self.pos)
	end
end

return Player
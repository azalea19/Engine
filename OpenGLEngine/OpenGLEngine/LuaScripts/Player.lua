local Player = {}
Player.__index = Player

function Player.new()
	local instance = {}
	instance.id = 0

	setmetatable(instance, Player)
	return instance
end

function Player:update()
	-- written by liz translated from maddys c++ code
	turnSpeed = 0.3
	moveSpeed = 0.5

  --[[
	--rotation
	origYaw = cameraAPI.getYaw(camera0)
	origPitch = cameraAPI.getPitch(camera0)
	mouseX = inputManagerAPI.mouseDeltaX
	--printAPI.print(tostring(mouseX).."\n")
	
	deltaYaw =  - mouseX * turnSpeed
  
	deltaPitch = -1 *inputManagerAPI.mouseDeltaY * turnSpeed
	cameraAPI.setYaw(originalYaw + deltaYaw)
	cameraAPI.setPitch(originalPitch+deltaPitch)
	  

	--translation   
	

	MOVE_SPEED = 1
]]

	oldPos = cameraAPI.getPosition(camera0);
	forward = cameraAPI.forward(camera0);
	right = cameraAPI.right(camera0);

	translation = { x=0, y=0, z=0 };


	if inputManagerAPI.isKeyDown(SDL_SCANCODE_W) then
		translation = luaVectorUtility.addVector(translation,forward)
	end

	--[[
	if inputManagerAPI.isKeyDown(SDL_SCANCODE_A) then
		translation = luaVectorUtility.subtractVector(translation,right)
	end


	if inputManagerAPI.isKeyDown(SDL_SCANCODE_S) then
		translation = luaVectorUtility.subtractVector(translation,forward)
	end
	if inputManagerAPI.isKeyDown(SDL_SCANCODE_D) then
		translation = luaVectorUtility.addVector(translation,right)
	end
	]]
		--[[
	if not luaVectorUtility.equals(translation,luaVectorUtility.emptyVec3) then


		translation = luaVectorUtility.normalize(translation.x,translation.y,translation.z)
		translation = luaVectorUtility.multiplyFloat(translation.x,translation.y,translation.z,MOVE_SPEED)

		
		newPos = luaVectorUtility.addVector(oldPos,translation)

		cameraAPI.setPosition(camera0,newPos.x,newPos.y,newPos.z);
	  

	end  ]]
	
end

return Player
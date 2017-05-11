
-- todo needs some work. NPC should inherit from this class, but most functionality is in NPC that should be in both.

local gameObject = {}
gameObject.__index = gameObject

function gameObject.new(newName, newModel, newPos, newDir, newScale, newAnim)


	instanceID = luaObjInstManager.addNewInstance(newModel)

	local instance = 
	{
		model = newModel,
		direction = newDir,
		name = newName,
		id = instanceID,
		scale = newScale,
		animation = newAnim,
		boundingBox = { min ={x=0,y=0,z=0}, max={x=0,y=0,z=0} }
	}	
	
	setmetatable(instance, gameObject)
	
	if(newPos.y == 0) then
		newPos.y = GetHeightAtPoint(newPos.x , newPos.z) +10
	end

	objectInstanceAPI.setTranslation(instanceID,newPos.x,newPos.y,newPos.z)
	objectInstanceAPI.setOrientation(instanceID,newDir.x,newDir.y,newDir.z)
	objectInstanceAPI.setScale(instanceID,newScale.x,newScale.y,newScale.z)
	objectInstanceAPI.setAnimation(instanceID,0)
	renderManagerAPI.addObject(instanceID)
	
	local abox = AABBAPI.getAABB(instanceID, context.handle)
		
	abox.min = mmath.vec3_Multiply(abox.min,newScale,context.handle)
	abox.max = mmath.vec3_Multiply(abox.max,newScale,context.handle)
	
	boundingBox = abox
	
	
	
	return instance
end


function gameObject:setPosition(pos)
	objectInstanceAPI.setTranslation(self.id,pos.x,pos.y,pos.z)
end

function gameObject:getPosition()
    return objectInstanceAPI.getTranslation(self.id,context.handle)
end


function gameObject:BBToWorld()
	local newBB = {}

	--printAPI.print("Getting BB to world... ")
	
    newBB.min = mmath.vec3_Sum(self.boundingBox.min,self:getPosition(),context.handle)
    newBB.max = mmath.vec3_Sum(self.boundingBox.max,self:getPosition(),context.handle)
	--printAPI.print("Got BB to world.")
    return newBB
end

function gameObject:Update()
	--printAPI.print("Updating gameobject " .. self.id .. "\n")
end

function gameObject:getPos()
	return gameObject.position
end

function gameObject:getDir()
	return gameObject.direction
end

function gameObject:getScale()
	return gameObject.scale
end

function gameObject:getAnim()
	return gameObject.animation
end

function gameObject:getID()
	return gameObject.id
end

function gameObject:getName()
	return gameObject.name
end

function gameObject:getModel()
	return gameObject.model
end

return gameObject

local gameObject = {}
gameObject.__index = gameObject

function gameObject.new(newName, newModel, newPos, newDir, newScale, newAnim, newID)
	local instance = {}	
	
	instance.model = newModel
	instance.position = newPos
	instance.direction = newDir
	instance.name = newName
	instance.id = newID
	instance.scale = newScale
	instance.animation = newAnim
	instance.boundingBox = {}


	setmetatable(instance, gameObject)

	return instance
end

function gameObject:BBToWorld()
	local newBB = {}
    newBB.min = luaVectorUtility.vec3_Sum(self.boundingBox.min,self.position,context.handle)
    newBB.max = luaVectorUtility.vec3_Sum(self.boundingBox.max,self.position,context.handle)

    return newBB
end

function gameObject:Update()
	return self.id
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
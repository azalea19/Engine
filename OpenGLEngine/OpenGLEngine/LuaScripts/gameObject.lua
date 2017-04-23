
local gameObject = {}
gameObject.__index = character
--The gameObject class, contains the data stored by all game objects
function gameObject.new(newName, newModel, newPos, newDir, newScale, newAnim, newID)
	local instance = {}	
	
	instance.model = newModel
	instance.position = newPos
	instance.direction = newDir
	instance.name = newName
	instance.id = newID
	instance.scale = newScale
	instance.animation = newAnim
	setmetatable(instance, gameObject)

	return instance
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
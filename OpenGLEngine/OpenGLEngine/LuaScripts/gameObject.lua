
local gameObject = {}
gameObject.__index = character

function gameObject.new(newName, newModel, newPos, newDir, newBBox, newScale, newAnim, newID)
	local instance = {}	
	setmetatable(instance, gameObject)
	instance.model = newModel
	instance.boundingBox = newBBox
	instance.position = newPos
	instance.direction = newDir
	instance.name = newName
	instance.id = newID
	instance.scale = newScale
	instance.animation = newAnim

	return instance
end

function gameObject:getModel()
	return self.model
end

function gameObject:getMaxHealth()
	return gameObject.maxHealth
end

function gameObject:getCurrentHealth()
	return gameObject.currentHealth
end

function gameObject:outOfHealth()
	if gameObject.currentHealth < 0 then
		return true
	else
		return false
	end
end


return gameObject
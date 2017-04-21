gameObject = {}
gameObject.__index = character

function gameObject.new(newName, newModel, newPos, newDir, newBBox, newID)
	local instance = {
		model = newModel,
		boundingBox = newBBox,
		position = newPos,
		direction = newDir,
		name = newName,
		id = newID
	}
	setmetatable(instance, gameObject)
	return instance
end

function gameObject:getType()
	return gameObject.type
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

npc = {}
npc.__index = npc
	
function npc.new(newName, newModel, newPos, newDir, newBBox, newID, newHealth, newCharacterName)
	local instance = {
		model = newModel,
		boundingBox = newBBox,
		position = newPos,
		direction = newDir,
		maxHealth = newHealth,
		currentHealth = newHealth,
		type = newType,
		name = newName,
		id = newID,
		characterName = newCharacterName
	}
	setmetatable(instance, npc)
	return instance
end

setmetatable(npc,{__index = character})

function npc:getName()
	return npc.name
end



AABoundingBox = {}

function AABoundingBox.new(NewMinX, NewMaxX, NewMinY, NewMaxY, NewMinZ, NewMaxZ)
	local instance = {
		minX = NewMinX,
		minY = NewMinY,
		minZ = NewMinZ,
		maxX = NewMaxX,
		maxY = NewMaxY,
		maxZ = NewMaxZ
	}
	setmetatable(instance, AABoundingBox)
	return instance
	
end



Vector3 = {}

function Vector3.new(x, y, z)
	local instance = {
		X = x,
		Y = y,
		Z = z
	}
	setmetatable(instance, Vector3)
	return instance
end
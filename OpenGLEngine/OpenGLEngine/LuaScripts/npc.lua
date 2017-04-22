local gameObject = require 'LuaScripts/gameObject'

local npc = {}
npc.__index = npc
	
function npc.new(newName, newModel, newPos, newDir, newBBox, newScale, newAnim, newID, newCurrentHealth, newMaxHealth, newCharacterName)
	local instance = {
		model = newModel,
		boundingBox = newBBox,
		position = newPos,
		direction = newDir,
		maxHealth = newMaxHealth,
		currentHealth = newCurrentHealth,
		type = newType,
		name = newName,
		id = newID,
		characterName = newCharacterName,
		scale = newScale,
		animation = newAnim
	}
	setmetatable(instance, npc)
	return instance
end

setmetatable(npc,{__index = gameObject})

return npc
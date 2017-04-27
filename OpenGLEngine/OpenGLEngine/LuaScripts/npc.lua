local gameObject = require 'LuaScripts/gameObject'
--local gameObject = require 'gameObject'

local npc = {}
npc.__index = npc
	
function npc.new(newName, newModel, newPos, newDir, newScale, newAnim, newID, newCurrentHealth, newMaxHealth, newCharacterName)
	local instance = {}
	
	instance.model = newModel
	instance.position = newPos
	instance.direction = newDir
	instance.maxHealth = newMaxHealth
	instance.currentHealth = newCurrentHealth
	instance.type = newType
	instance.name = newName
	instance.id = newID
	instance.characterName = newCharacterName
	instance.scale = newScale
	instance.animation = newAnim
	instance.alive = true
	
	setmetatable(instance, npc)

	return instance
end

function npc:Update()
	if self.alive == true then
		self.currentHealth = self.currentHealth - 1
		if(self.currentHealth <= 0) then
			--self:Die()
		end
	end
end

function npc:Die()
	
	renderManagerAPI.removeObject(self.id)
	renderManagerAPI.removeObject(self.id)
	--luaObjInstManager.deleteInstance(self.id)
	--self = nil
	self.alive = false
end

setmetatable(npc,{__index = gameObject})

return npc
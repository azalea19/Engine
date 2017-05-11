local gameObject = require 'LuaScripts/gameObject'
--local gameObject = require 'gameObject'

local npc = {}
npc.__index = gameObject

	-- todo What are the expected values/types for these parameters?
function npc.new(newName, newModel, newPos, newDir, newScale, newAnim, newCurrentHealth, newMaxHealth, newCharacterName)
	
	
	local instance = gameObject.new(newName,newModel,newPos,newDir,newScale,newAnim)
	

	instance.dialogue = nil
	instance.maxHealth = newMaxHealth
	instance.currentHealth = newCurrentHealth
	instance.type = newType
	instance.characterName = newCharacterName
	instance.alive = true
    instance.hostileToPlayer = false
    instance.seenPlayer = false
    instance.alertedToPlayer = false
    instance.state = idle -- Function to call for to the players state
    instance.moveSpeed = 0.1

	setmetatable(instance, { __index = gameObject } )

	setmetatable(instance, npc)
	
	return instance
end

function npc:makeIdle()
	self.state = idle
end

function npc:idle()
	printAPI.print("Idling...")
    if (self.hostileToPlayer and self.seenPlayer) then
        self.state = npc:chasing()
    end
end

function npc:chasing()

    self:setPosition(MoveTowards(self.position,player0.position,self.moveSpeed * deltaTime))

end

function npc:setDialogue(dial)
	self.dialogue = dial
end


function npc:test()

end

function npc:setDialogue(dial)
	self.dialogue = dial
end
--[[
function npc:Talk(topic)
    if(topic.questEvent) then
        questManager.check()
    end
end
]]

function npc:Update()
	if self.alive == true then
		self.currentHealth = self.currentHealth - 1
		if(self.currentHealth <= 0) then
			--self:Die()
		end
	end
	
	self.state()
end

function npc:Die()
	
	renderManagerAPI.removeObject(self.id)
	renderManagerAPI.removeObject(self.id)
	--luaObjInstManager.deleteInstance(self.id)
	--self = nil
	self.alive = false
end

function npc:SetDialogue(dial)
	self.dialogue = dial
end

--setmetatable(npc,{__index = gameObject})

return npc
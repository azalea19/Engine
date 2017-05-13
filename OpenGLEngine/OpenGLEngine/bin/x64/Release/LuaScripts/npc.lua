local gameObject = require 'LuaScripts/gameObject'
require 'LuaScripts/3DUtility'
--local gameObject = require 'gameObject'

local npc = {}
npc.__index = npc

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
    instance.state = nil -- Function to call for to the players state
    instance.moveSpeed = 0.1

	--printAPI.print("Testing NPC instantiate bounding box: " .. instance.boundingBox.min.x .. "\n")
	--setmetatable(instance, { __index = gameObject } )

	setmetatable(instance, npc)
	
	return instance
end

	setmetatable(npc,{__index = gameObject})


function idle(anpc)
	debugPrint("NPC is Idling... ")
    if (anpc.hostileToPlayer and anpc.seenPlayer) then
        anpc.state = chasing
    end
end

function chasing(anpc)
	debugPrint("NPC is Chasing... ")
	if player0 ~= nil then
		anpc:setPosition(MoveTowards(anpc:getPosition(),player0.position,anpc.moveSpeed))
	else
		printAPI.print("Warning: Player is nil\n")
	end
end
function npc:makeIdle()
	printAPI.print("Made NPC idle.")
	self.state = idle
end
function npc:makeChasing()
	debugPrint("Made NPC chase... ")
	self.state = chasing
	debugPrint("Success\n")

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
	if self.state ~= nil then
		debugPrint("Running NPC state...")
		self.state(self)
	end
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
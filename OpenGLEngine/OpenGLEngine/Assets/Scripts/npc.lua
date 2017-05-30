local gameObject = dofile '../Assets/Scripts/gameObject.lua'
dofile '../Assets/Scripts/3DUtility.lua'
local Weapon = dofile '../Assets/Scripts/Weapon.lua'

--local gameObject = require 'gameObject'

local npc = {}
npc.__index = npc

player = player0

	-- todo What are the expected values/types for these parameters?
function npc.new(strID, newName, newModel, newPos, newDir, newScale, newAnim, newCurrentHealth, newMaxHealth)
	
	
	local instance = gameObject.new(strID, newName,newModel,newPos,newDir,newScale,newAnim)
	printAPI.print(strID.." hp "..newCurrentHealth .."/"..newMaxHealth.."\n")

	instance.dialogue = nil
	instance.maxHealth = newMaxHealth
	instance.currentHealth = newCurrentHealth
	instance.type = newType
	instance.alive = true
    instance.hostileToPlayer = false
    instance.seenPlayer = false
    instance.alertedToPlayer = false
    instance.state = nil -- Function to call for to the players state
    instance.moveSpeed = 1
	instance.objType = "NPC"
	instance.hearDist = 10
	instance.lookAngleDeg = 45
    instance.weapon = Weapon.new("melee","melee",10,100,100)
    instance.hurtAnim = nil
    instance.timeHurtAnimTriggered = 0
    printAPI.print(instance.currentHealth.."\n")

	--printAPI.print("Testing NPC instantiate bounding box: " .. instance.boundingBox.min.x .. "\n")
	--setmetatable(instance, { __index = gameObject } )

	setmetatable(instance, npc)
	
	return instance
end

	setmetatable(npc,{__index = gameObject})

function idle(anpc)
	debugPrint("NPC is Idling... ")
	
	if(anpc.seenPlayer) then
        if (anpc.hostileToPlayer) then
    	    debugPrint("NPC state changed to chasing during idle. ")
            anpc.state = chasing
        else
            anpc.state = looking
        end
    end
    
    
    
    debugPrint("NPC idling complete.\n")
end


function chasing(anpc)
	debugPrint("NPC is Looking at player... ")
    anpc:lookAt(player0.position)

end

function chasing(anpc)
	debugPrint("NPC is Chasing... ")

    --printAPI.print(anpc.currentHealth.."\n")

	if player0 ~= nil then
		anpc:setPosition(MoveTowards(anpc:getPosition(),player0.position,anpc.moveSpeed))
		debugPrint("Looking at player position.\n")
		anpc:lookAt(player0.position)

        if(anpc.weapon ~= nil) then
            if(Distance(anpc:getPosition(),player0:getPosition()) < anpc.weapon.range) then
            	debugPrint("Ready to attack.\n")

                anpc.weapon:attack(player0)
            end
        end
        
        --printAPI.print("Got distance~!")
        


	else
		printAPI.print("Warning: Player is nil\n")
	end
end
function npc:takeDamage(mydmg)
    --debugLPrint(self.currentHealth .. " hp remains\n")

    if (self.hurtAnim~= nil) then
    	debugLPrint("NPC playing hurt anim ".."\n")
        self.timeHurtAnimTriggered = time
        self:setAnimation(self.hurtAnim)
    end

	debugLPrint("NPC Taking damage " .. mydmg .. "\n")
	self.currentHealth = self.currentHealth - mydmg
    debugLPrint(self.currentHealth .. " hp remains\n")
	if(self.currentHealth <= 0) then
		self:die()
	end
end

function npc:die()
	debugLPrint("NPC death.\n")
	self.alive = false
	questManager:check(KILL,self)

	currentScene:RemoveInstance(self)
	--self.updating = false
	--self.visible = false
	-- You will not be able to check if this specific instance is dead/properties of later on, but you could check if it exists in the scene or not.
	-- Todo possibly store past gameobjects in the scene as well as current gameobjects, so this data can be accessed if needed.
end

function npc:makeIdle()
	printAPI.print("Made NPC idle.")
	self.state = idle
end

function npc:makeChasing()
	debugLPrint("Making NPC chase... ")
	self.state = chasing
	debugLPrint("Chase success\n")

end


function npc:readTopics()
	local str = {}
	local length = 0
	if self.dialogue ~= nil then
		for i=1,self.dialogue.topicCount do
			local topic = self.dialogue.topics[i]
			local topicName
			if topic.name~= nil then
				topicName = topic.name
			else
				topicName = topic.id
			end
			length = length + 1
			str[length] = topicName

		end
		return str,length
	end
	return nil,0
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


    if self.animation == self.hurtAnim then
        if self.timeHurtAnimTriggered < (timeAPI.elapsedTimeMs() + 100) then
            self:setAnimation(self.defaultAnim)
            printAPI.print("Swapping back")
        end
    end

	if self.alive == true then
		--self.currentHealth = self.currentHealth - 1
		if(self.currentHealth <= 0) then
			self:Die()
		end
	end
	
	if (AngleDiffDeg(self:getForward(),Direction(player0:getPosition(),self:getPosition()) ) <= self.lookAngleDeg) then
		self.seenPlayer = true
	end

    if (Distance(self:getPosition(), player0:getPosition()) <= self.hearDist) then
		self.seenPlayer = true
	end
	
	if self.state ~= nil then
		debugPrint("Running NPC state...")
		self.state(self)
		local an ={ x=self:getPosition().x, y = GetHeightAtPoint(self:getPosition().x , self:getPosition().z), z = self:getPosition().z}
		self:setPosition(an)

	end
	
	
end

function npc:Die()
	
	--renderManagerAPI.removeObject(self.id)
	--renderManagerAPI.removeObject(self.id)
	--luaObjInstManager.deleteInstance(self.id)
	--self = nil
	self.alive = false
end

function npc:SetDialogue(dial)
	self.dialogue = dial
end

--setmetatable(npc,{__index = gameObject})

return npc
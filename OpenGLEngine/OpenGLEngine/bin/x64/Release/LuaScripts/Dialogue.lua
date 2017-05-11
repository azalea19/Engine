require 'LuaScripts/QuestManager'


Dialogue = {}
Dialogue.__index = Dialogue

function Dialogue.new()
	instance = 
	{
		topics = {},
		topicCount = 1
	}

	setmetatable(instance, Dialogue)
	return instance
end

function Dialogue:addTopic(newTopic)
	printAPI.print("Setting Dialogue...\n");
	self.topics[newTopic.id] = newTopic
	self.topicCount = self.topicCount+1
	
end

Topic = {}
Topic.__index = Topic

function Topic.new(topicID)
	instance = 
	
	{
		id = topicID,
		textLines = {},
		size=0,
		questEvent = false, -- Is the topic a quest event? If so, when it is read it should trigger a QuestManager status check.
		unlockReq = nil, -- Unlock Requirements, set this to a bool check method to see if topic is available.
		hasRead = false, -- Whether the player has read this topic in the dialogue
		deleteOnRead = false -- Whether the topic becomes unavailable once the player reads it
	}

	setmetatable(instance, Topic)
	return instance
end

function Topic:setLines(iLines)
	printAPI.print("Filling Topic lines...\n");
	for i=1,#iLines do -- To length of lines
		self.textLines[i] = iLines[i]
		self.size = self.size + 1
	end
	
end

function Topic:getLine(ind)

	return (tostring(self.textLines[ind]))
end

function DialogueTest()
local questStages = {}

--questStages[1] = new QuestStage(KILL,Enemy01,nil)
questStages[1] = QuestStage.new(TALK,NPC01,"BobQuest1")
--questStages[3] = new QuestStage(GET,Item01,nil)

quest = Quest:new(questStages,1)

end

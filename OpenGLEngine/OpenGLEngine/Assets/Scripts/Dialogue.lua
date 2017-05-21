dofile '../Assets/Scripts/QuestManager.lua'


Dialogue = {}
Dialogue.__index = Dialogue

function Dialogue.new()
	instance = 
	{
		topics = {},
		topicCount = 0,
	}

	setmetatable(instance, Dialogue)
	return instance
end

function Dialogue:addTopic(newTopic)
	printAPI.print("Setting Dialogue...\n");
	self.topicCount = self.topicCount+1
	self.topics[self.topicCount] = newTopic	
end

Topic = {}
Topic.__index = Topic

function Topic.new(topicID, topicName)
	instance = 
	
	{
		id = topicID, -- ID for finding this topic in the list
		name = topicName, -- Name of topic visible to player
		textLines = {}, -- The lines of text in this topic
		size=0, -- Number of lines of text
		questEvent = false, -- Is the topic a quest event? If so, when it is read it should trigger a QuestManager status check. 
		unlockReq = nil, -- Unlock Requirements, set this to a QuestManager check (stages complete) to see if topic is available. 
		isAvailable = true,
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
end

-- QUEST MANAGER
QuestManager = {}
QuestManager.__index = QuestManager
	
function QuestManager.new()
	local instance = {}
	instance.quests = nil
	instance.questNum = 1
	
	setmetatable(instance, QuestManager)

	return instance
end

function QuestManager:check()
	
	
	
	
end

-- Expects Quest as param
function QuestManager:addQuest(newQuest)
	self.quests[questNum] = newQuest
	self.questNum = self.questNum + 1
end

-- QUEST
Quest = {}
Quest.__index = Quest

-- Expects table of QuestStage as param
function Quest.new(questStages, iEndStage)
	local instance = {}
	instance.endStage = iEndStage
	instance.stages = questStages

	setmetatable(instance, Quest)

	return instance
end

-- Quest stage actions
KILL = 0
TALK = 1
GET = 2

-- QUEST STAGE
QuestStage = {}
QuestStage.__index = QuestStage
	
function QuestStage.new(myAction, myTarget, myExtraInfo)
	local instance = {}
	instance.action = myAction
	instance.target = myTarget
	instance.extraInfo = myExtraInfo
	instance.isComplete = false

	setmetatable(instance, QuestStage)

	return instance
end

function QuestManagerTest()
local questStages = {}

--questStages[1] = new QuestStage(KILL,Enemy01,nil)
questStages[1] = QuestStage.new(TALK,NPC01,"BobQuest1")
--questStages[3] = new QuestStage(GET,Item01,nil)

quest = Quest:new(questStages,1)

end



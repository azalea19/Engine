-- Quest stage actions
KILL = 0
TALK = 1
GET = 2

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

-- Checks whether the action that was performed updated any quests.
function QuestManager:check(action,target,extraInfo)
	for i=0,questNum do
		for a=0,quests[i].stageCount do
			thisStage = quests[i].stages[a]
			if(action==thisStage.action and target == thisStage.target and extraInfo == thisStage.extraInfo) then
				thisStage.isComplete = true
				printAPI.print("You completed quest stage: " .. thisStage.name)
				
				if(quests[i]:isComplete()) then
				printAPI.print("You completed quest: " .. quests[i].name)
				end
			end
		end
	end
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
function Quest.new(name,questStages, iEndStage)
	local instance = {}
	instance.name = name -- Name of quest, assume visible to player.
	instance.endStage = iEndStage
	instance.stages = questStages
	instance.stageCount = 0

	setmetatable(instance, Quest)

	return instance
end

function Quest:isComplete()
	for i=0,stageCount do
		if(stages[i].isComplete == false) then
			return false
		end
	end
	return true
end



-- QUEST STAGE
QuestStage = {}
QuestStage.__index = QuestStage
	
function QuestStage.new(name, myAction, myTargetName myExtraInfo)
	local instance = {}
	instance.name = name -- Name of quest stage, assume visible to player.
	instance.action = myAction
	instance.target = myTarget
	instance.targetName = myTargetName
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

	local quest = Quest:new(questStages,1)

end



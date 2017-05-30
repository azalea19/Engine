-- Quest stage actions
KILL = 0
TALK = 1
GET = 2

-- QUEST MANAGER
QuestManager = {}
QuestManager.__index = QuestManager
	
function QuestManager.new()
	local instance = {}
	instance.quests = {}
	
	setmetatable(instance, QuestManager)

	return instance
end

-- Checks whether the action that was performed updated any quests.
function QuestManager:check(action,target,extraInfo)
	for i=1,#self.quests do
		if(self.quests[i]~= nil) then
		printAPI.print("Checking quest "..i .. "\n")

			for a=1,#self.quests[i].stages do
				thisStage = self.quests[i].stages[a]

                if(thisStage.extraInfo ~= nil) then
                    debugLPrint("QUEST STAGE DATA: " .. thisStage.action .. " " .. thisStage.target .. " " .. thisStage.extraInfo .. "\n")

                 else
                    debugLPrint("QUEST STAGE DATA: " .. thisStage.action .. " " .. thisStage.target .. "\n")

                end

                if(extraInfo == nil) then
                	debugLPrint(action .. " " .. target.stringID .. "\n")

                else
                	debugLPrint(action .. " " .. target.stringID .. " " .. extraInfo .. "\n")

                end

                if(thisStage.name == "ObsGetQuest") then
                            saveAllToCurrentSave()
                        end
                        if(thisStage.name == "ObsGetTech") then
                            saveAllToCurrentSave()
                        end
                        if(thisStage.name == "ObsReturn") then
                            saveAllToCurrentSave()
                        end
                        if(thisStage.name == "AirGetQuest") then

                            saveAllToCurrentSave()
                        end
                        if(thisStage.name == "AirKillBoss") then
                            saveAllToCurrentSave()
                        end
				
				if(action==thisStage.action and target.stringID == thisStage.target and extraInfo == thisStage.extraInfo) then
                	printAPI.print("You completed quest stage: " .. thisStage.name .. " But it still may be already complete.\n")

					if(thisStage.isComplete == false) then
						self.quests[i].stages[a].isComplete = true
						printAPI.print("You completed quest stage: " .. thisStage.name .. "\n")

                        if(thisStage.name == "ObsGetTech" or thisStage.id == "AirKillBoss") then
						    ShowMessageBox("You completed quest stage " .. thisStage.name .. "\n")
                        end



                        --[[diag:addTopic(greeting)
    diag:addTopic(quest1)
    diag:addTopic(quest2)
    diag:addTopic(quest1return)
    diag:addTopic(quest2return)
    diag:addTopic(teleport1)
    diag:addTopic(teleport2)]]

                         
						if(self.quests[i]:isComplete()) then
							printAPI.print("You completed quest: " .. self.quests[i].name .. "\n")
                           	--ShowMessageBox("You completed quest: " .. self.quests[i].name .. "\n")

						end
					end
				end
			end
		else
		printAPI.print(i-1 .. " " .. self.quests[i-1].name)
		printAPI.print(" Was last quest. Next, ".. i.. "was Nil quest tried to access\n")
		end
	end
end

-- Expects Quest as param
function QuestManager:addQuest(newQuest)
	self.quests[#self.quests +1] = newQuest


    --printAPI.print(newQuestnewQuest.targetName .. " " .. newQuest.
end

function QuestManager:getQuest(questName)
    for i=1,#self.quests do
		if(self.quests[i].name == questName) then
			return self.quests[i]
		end
	end
end

function QuestManager:doesQuestExist(questName)
	for i=1,#self.quests do
		if(self.quests[i].name == questName) then
			return true
		end
	end
	
	return false
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

	setmetatable(instance, Quest)

	return instance
end

function Quest:getStage(stageName)
    for i=0,#instance.stages do
        if (instance.stages[i].name == stageName) then
            return instance.stages[i]
        end
    end
end
function Quest:isComplete()
	for i=1,#self.stages-1 do
		debugLPrint("Checking Quests ... ")

		if(self.stages[i].isComplete == false) then
				debugLPrint("a stage is incomplete\n")
			return false
		end
	end
	return true
end

function Quest:getSize()
	return #self.stages
end

-- QUEST STAGE
QuestStage = {}
QuestStage.__index = QuestStage
	
function QuestStage.new(name, myAction, myTargetName, myExtraInfo)
	local instance = {}
	instance.name = name -- Name of quest stage, assume visible to player.
	instance.action = myAction
	instance.target = myTargetName
	instance.extraInfo = myExtraInfo or "none"
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



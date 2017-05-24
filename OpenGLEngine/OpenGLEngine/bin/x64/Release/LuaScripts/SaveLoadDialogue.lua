require 'LuaScripts/FileIO'
require 'LuaScripts/Dialogue'

function LoadTopics(filePath, fileType)
	local outputData = {}
	local fileData= read(filePath, ',')
	local numRows = 0

	for k,v in next, fileData do 
		numRows = numRows + 1
	end
	
	local i = 1
	while i <= numRows do
		local nSpeakerName = fileData[i][1]
		local nTopicID = fileData[i][2]
		local nTopicName = fileData[i][3]
		local nDeleteOnRead = fileData[i][4]
		local nQuestEvent = fileData[i][5]
		local nTextLinesCount = fileData[i][6]
		local nUnlockRequirementCount = fileData[i][7]
		
		local nUnlockRequirements = {}

		for k = 1, nUnlockRequirementCount do
			local t = {}
			t.nUnlockRequirementQuest = fileData[i + k][1]
			t.nUnlockRequirementStage = fileData[i + k][2]
			table.insert(nUnlockRequirements, t)
		end
		
		local nTextLines = {}
		
		for l = 1, nTextLinesCount do
			nTextLines[l] = fileData[i + nUnlockRequirementCount + l][1]
		end
		
		local nTopic = Topic.new(nTopicID,nTopicName)
		nTopic:setLines(nTextLines)
		nTopic.size = nTextLinesCount
		nTopic.questEvent = nQuestEvent
		nTopic.unlockReq = nUnlockRequirements
		nTopic.deleteOnRead = nDeleteOnRead
		
		local nDialogue = Dialogue.new()
		nDialogue:addTopic(nTopic)
		
		local go = world:FindObject(nSpeakerName)
		if go ~= false then
			if go.dialogue == nil then
				go:SetDialogue(nDialogue)
			else
				go.dialogue:addTopic(nTopic)
			end
		end
		
		i = i + nTextLinesCount + nUnlockRequirementCount + 1
	end
	
	printAPI.print(numRows .. ' lines loaded.\n')
	
	return outputData
end

function LoadQuests(filePath, fileType)
	local outputData = {}
	local fileData= read(filePath, ',')
	local numRows = 0

	for k,v in next, fileData do 
		numRows = numRows + 1
	end
	
	local i = 1
	while i <= numRows do
		local nQuestName = fileData[i][1]
		local nEndStage = fileData[i][2]
		local nStageCount = fileData[i][3]
		
		local Stages = {}

		for k = 1, nStageCount do
			local t = {}
			t = QuestStage.new(fileData[i + k][1], fileData[i + k][2], fileData[i + k][3], fileData[i + k][4])
			table.insert(Stages, t)
		end
		
		local nQuest = Quest.new(nQuestName,Stages, nEndStage)
		
		questManager:addQuest(nQuest)
		
		i = i + nStageCount + 1
	end
	
	printAPI.print(numRows .. ' lines loaded.\n')
	
	return outputData
end

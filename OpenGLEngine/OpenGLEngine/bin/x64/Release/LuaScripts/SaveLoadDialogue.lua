require 'LuaScripts/FileIO'
require 'LuaScripts/Dialogue'

function LoadTopics(filePath, fileType)
	local outputData = {}
	local fileData= read(filePath, ',')
	local numRows = 0

	for k,v in next, fileData do 
		numRows = numRows + 1
	end
	for i = 1, numRows do
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
			nTextLines[l] = fileData[i + nUnlockRequirementCount + l]
		end
		
		local nTopic = Topic.new(nTopicID,nTopicName)
		nTopic:setLines(nTextLines)
		nTopic.size = nTextLinesCount
		nTopic.questEvent = nQuestEvent
		nTopic.unlockReq = nUnlockRequirements
		nTopic.deleteOnRead = nDeleteOnRead
		
		table.insert(outputData, nTopic)
		numRows = numRows + nTextLinesCount + nUnlockRequirementCount
	end
	


	printAPI.print(numRows .. ' lines loaded.\n')
	
	return outputData
end


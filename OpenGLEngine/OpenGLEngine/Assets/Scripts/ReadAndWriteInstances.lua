--[[local Vector3 = require 'Vector3'
local gameObject = require 'gameObject'
local AABoundingBox = require 'AABoundingBox'
local npc = require 'npc'
local Player = require 'Player'
require 'FileIO'
]]
local Vector3 = dofile '../Assets/Scripts/Vector3.lua'
local Weapon = dofile '../Assets/Scripts/Weapon.lua'
local gameObject = dofile '../Assets/Scripts/gameObject.lua'
local AABoundingBox = dofile '../Assets/Scripts/AABoundingBox.lua'
local npc = dofile '../Assets/Scripts/npc.lua'
local Player = dofile '../Assets/Scripts/Player.lua'
dofile '../Assets/Scripts/FileIO.lua'
dofile '../Assets/Scripts/Dialogue.lua'

function SaveInstances(filePath, data, fileType)
	local numRows = 0
	local total = 0
	local saveTable = {}
	local saveString = ""
	
	for k,v in next, data do 
		numRows = numRows + 1
	end

	clearFile(filePath)

	for i = 1, numRows do
		if(fileType == "gameObject") then
			if data[i]["currentHealth"] == nil then
				total = total + 1
				saveTable[#saveTable + 1] =  data[i]["stringID"] 
				saveTable[#saveTable + 1] =  "," 
				saveTable[#saveTable + 1] =  data[i]["name"] 
				saveTable[#saveTable + 1] =  "," 
				saveTable[#saveTable + 1] =  data[i]["model"]
				saveTable[#saveTable + 1] =  "," 
				saveTable[#saveTable + 1] =  data[i]:getPosition().x
				saveTable[#saveTable + 1] =  ","
				saveTable[#saveTable + 1] =  data[i]:getPosition().y
				saveTable[#saveTable + 1] =  ","
				saveTable[#saveTable + 1] =  data[i]:getPosition().z
				saveTable[#saveTable + 1] =  ","
				saveTable[#saveTable + 1] =  data[i]["direction"]["x"]
				saveTable[#saveTable + 1] =  ","
				saveTable[#saveTable + 1] =  data[i]["direction"]["y"]
				saveTable[#saveTable + 1] =  ","
				saveTable[#saveTable + 1] =  data[i]["direction"]["z"]
				saveTable[#saveTable + 1] =  ","
				saveTable[#saveTable + 1] =  data[i]["scale"]["x"]
				saveTable[#saveTable + 1] =  ","
				saveTable[#saveTable + 1] =  data[i]["scale"]["y"]
				saveTable[#saveTable + 1] =  ","
				saveTable[#saveTable + 1] =  data[i]["scale"]["z"]
				saveTable[#saveTable + 1] =  ","
				saveTable[#saveTable + 1] =  data[i]["animation"]
				saveTable[#saveTable + 1] =  "\n"
			end
		else
			if(fileType == "npc") then
				if data[i]["currentHealth"] ~= nil then
					total = total + 1
					saveTable[#saveTable + 1] =  data[i]["stringID"] 
					saveTable[#saveTable + 1] =  "," 
					saveTable[#saveTable + 1] =  data[i]["name"] 
					saveTable[#saveTable + 1] =  "," 
					saveTable[#saveTable + 1] =  data[i]["model"]
					saveTable[#saveTable + 1] =  "," 
					saveTable[#saveTable + 1] =  data[i]:getPosition().x
					saveTable[#saveTable + 1] =  ","
					saveTable[#saveTable + 1] =  data[i]:getPosition().y
					saveTable[#saveTable + 1] =  ","
					saveTable[#saveTable + 1] =  data[i]:getPosition().z
					saveTable[#saveTable + 1] =  ","
					saveTable[#saveTable + 1] =  data[i]["direction"]["x"]
					saveTable[#saveTable + 1] =  ","
					saveTable[#saveTable + 1] =  data[i]["direction"]["y"]
					saveTable[#saveTable + 1] =  ","
					saveTable[#saveTable + 1] =  data[i]["direction"]["z"]
					saveTable[#saveTable + 1] =  ","
					saveTable[#saveTable + 1] =  data[i]["scale"]["x"]
					saveTable[#saveTable + 1] =  ","
					saveTable[#saveTable + 1] =  data[i]["scale"]["y"]
					saveTable[#saveTable + 1] =  ","
					saveTable[#saveTable + 1] =  data[i]["scale"]["z"]
					saveTable[#saveTable + 1] =  ","
					saveTable[#saveTable + 1] =  data[i]["animation"]
					saveTable[#saveTable + 1] =  ","
					saveTable[#saveTable + 1] =  data[i]["currentHealth"]
					saveTable[#saveTable + 1] =  ","
					saveTable[#saveTable + 1] =  data[i]["maxHealth"]
					--saveTable[#saveTable + 1] =  ","
					--saveTable[#saveTable + 1] =  data[i]["characterName"]
					saveTable[#saveTable + 1] =  "\n"
				end
			end
		end
	end
	
	saveString = table.concat(saveTable)
	write(filePath, saveString)

	if(fileType == "gameObject") then
		printAPI.print(total .. ' game objects saved.\n')
	else
		if(fileType == "npc") then
			printAPI.print(total .. ' NPCs saved.\n')
		end
	end	
end

function LoadInstances(filePath, fileType)
	local outputData = {}
	local n, instanceID, objPos, dir, sca
	local fileData= read(filePath, ',')
	local numRows = 0

	for k,v in next, fileData do 
		numRows = numRows + 1
	end
	for i = 1, numRows do
		--instanceID = luaObjInstManager.addNewInstance(fileData[i][2])

		objpos = Vector3.new(fileData[i][4], fileData[i][5], fileData[i][6])
		dir = Vector3.new(fileData[i][7], fileData[i][8], fileData[i][9])
		sca = Vector3.new(fileData[i][10], fileData[i][11], fileData[i][12])
		anim = fileData[i][13]

		
		local stringID = fileData[i][1]
			
		if(fileType == "gameObject") then
			n = gameObject.new(stringID, fileData[i][2],fileData[i][3], objpos, dir, sca, anim)
			
		else
			if(fileType == "npc") then
			
				n = npc.new(stringID, fileData[i][2],fileData[i][3], objpos, dir, sca, anim, fileData[i][13], fileData[i][14])
			end
		end
		
		table.insert(outputData, n)
		
	end
	
	if(fileType == "gameObject") then
		printAPI.print(numRows .. ' game objects loaded.\n')
	else
		if(fileType == "npc") then
			printAPI.print(numRows .. ' NPCs loaded.\n')
		end
	end	
	
	return outputData
end

function loadWeapons(filePath)	--data is an array of weapons
	local outputData = {}
	local fileData= read(filePath, ',')
	local numRows = 0

	for k,v in next, fileData do 
		numRows = numRows + 1
	end
	
	local i = 1
	while i <= numRows do
		local nWeaponID = fileData[i][1]
		local nName = fileData[i][2]
		local nDamage = fileData[i][3]
		local nInterval = fileData[i][4]
		local nRange = fileData[i][5]
		
		local newWeapon = Weapon.new(nWeaponID, nName, nDamage, nInterval, nRange)
		
		table.insert(outputData, newWeapon)
		
		i = i + 1
	end
	
	printAPI.print(numRows .. ' weapons loaded.\n')
	
	return outputData
end

function savePlayer(filePath, data)
	local numRows = 0

	local saveTable = {}
	local saveString = ""

	clearFile(filePath)

	saveTable[#saveTable + 1] =  data.position.x 
	saveTable[#saveTable + 1] =  "," 
	saveTable[#saveTable + 1] =  data.position.y
	saveTable[#saveTable + 1] =  "," 
	saveTable[#saveTable + 1] =  data.position.z
	saveTable[#saveTable + 1] =  "," 
	saveTable[#saveTable + 1] =  data:getYaw()
	saveTable[#saveTable + 1] =  "," 
	saveTable[#saveTable + 1] =  data:getPitch()
	saveTable[#saveTable + 1] =  "," 
	saveTable[#saveTable + 1] =  data.currentHealth
	saveTable[#saveTable + 1] =  "," 
	saveTable[#saveTable + 1] =  data.weapon
	
	saveString = table.concat(saveTable)
	write(filePath, saveString)
	
	printAPI.print('Player saved.\n')
end

function saveWeapons(filePath, data)	--data is a array of weapons
	local saveTable = {}
	local saveString = ""

	clearFile(filePath)
	
	for i = 1, #data do
		saveTable[#saveTable + 1] =  data.id
		saveTable[#saveTable + 1] =  "," 
		saveTable[#saveTable + 1] =  data.name
		saveTable[#saveTable + 1] =  "," 
		saveTable[#saveTable + 1] =  data.damage
		saveTable[#saveTable + 1] =  "," 
		saveTable[#saveTable + 1] =  data.shootInterval
		saveTable[#saveTable + 1] =  "," 
		saveTable[#saveTable + 1] =  data.range
		saveTable[#saveTable + 1] =  "\n" 
	end
	
	saveString = table.concat(saveTable)
	write(filePath, saveString)
	
	printAPI.print(#data .. 'Weapons saved.\n')
end

function loadPlayer(filePath, player)	--player is a ref to the player
	local fileData= read(filePath, ',')

	pos = {x=fileData[1][1],y=fileData[1][2],z=fileData[1][3]}

	player:setPosition(pos)
	player:setYaw(fileData[1][4])
	player:setPitch(fileData[1][5])
	player.currentHealth = fileData[1][6]
	player.weapon = fileData[1][7]
	
	printAPI.print('Player loaded.\n')
end

function SaveQuests(filePath, data)
	local numRows = 0
	local total = 0
	local saveTable = {}
	local saveTableTwo = {}
	local saveString = ""

	clearFile(filePath)
--questManager.quests[1].name
	for i = 1, #data.quests do
		total = total + 1
		saveTable[#saveTable + 1] =  data.quests[i]["name"] 
		saveTable[#saveTable + 1] =  "," 
		saveTable[#saveTable + 1] =  data.quests[i]["endStage"] 
		saveTable[#saveTable + 1] =  "," 
		saveTable[#saveTable + 1] =  data.quests[i]:getSize()
		saveTable[#saveTable + 1] =  "\n" 
		
		local Stages = {}

		for k = 1, data.quests[i]:getSize()  do
			saveTable[#saveTable + 1] =  data.quests[i]["stages"][k].name
			saveTable[#saveTable + 1] =  "," 
			saveTable[#saveTable + 1] =  data.quests[i]["stages"][k].action
			saveTable[#saveTable + 1] =  "," 
			saveTable[#saveTable + 1] =  data.quests[i]["stages"][k].targetName
			saveTable[#saveTable + 1] =  "," 
			saveTable[#saveTable + 1] =  data.quests[i]["stages"][k].extraInfo
			saveTable[#saveTable + 1] =  "," 
			if(data.quests[i]["stages"][k].isComplete)then
				saveTable[#saveTable + 1] =  1
			else
				saveTable[#saveTable + 1] =  0
			end
			saveTable[#saveTable + 1] =  "\n" 
		end
	end
	
	saveString = table.concat(saveTable)
	write(filePath, saveString)
	
	printAPI.print(#data.quests .. ' quests saved.\n')
end

function LoadTopics(filePath)
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

function LoadQuests(filePath)
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
			t.isComplete = fileData[i + k][5]
			table.insert(Stages, t)
		end
		
		local nQuest = Quest.new(nQuestName,Stages, nEndStage)
		
		questManager:addQuest(nQuest)
		
		i = i + nStageCount + 1
	end
	
	printAPI.print(numRows .. ' lines loaded.\n')
	
	return outputData
end
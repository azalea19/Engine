local Vector3 = require 'LuaScripts/Vector3'
local gameObject = require 'LuaScripts/gameObject'
local AABoundingBox = require 'LuaScripts/AABoundingBox'
local npc = require 'LuaScripts/npc'
local Player = require 'LuaScripts/Player'
require 'LuaScripts/FileIO'

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
			if gameObjects[i]["currentHealth"] == nil then
				total = total + 1
				saveTable[#saveTable + 1] =  gameObjects[i]["name"] 
				saveTable[#saveTable + 1] =  "," 
				saveTable[#saveTable + 1] =  gameObjects[i]["model"]
				saveTable[#saveTable + 1] =  "," 
				saveTable[#saveTable + 1] =  gameObjects[i]["position"]["x"]
				saveTable[#saveTable + 1] =  ","
				saveTable[#saveTable + 1] =  gameObjects[i]["position"]["y"]
				saveTable[#saveTable + 1] =  ","
				saveTable[#saveTable + 1] =  gameObjects[i]["position"]["z"]
				saveTable[#saveTable + 1] =  ","
				saveTable[#saveTable + 1] =  gameObjects[i]["direction"]["x"]
				saveTable[#saveTable + 1] =  ","
				saveTable[#saveTable + 1] =  gameObjects[i]["direction"]["y"]
				saveTable[#saveTable + 1] =  ","
				saveTable[#saveTable + 1] =  gameObjects[i]["direction"]["z"]
				saveTable[#saveTable + 1] =  ","
				saveTable[#saveTable + 1] =  gameObjects[i]["scale"]["x"]
				saveTable[#saveTable + 1] =  ","
				saveTable[#saveTable + 1] =  gameObjects[i]["scale"]["y"]
				saveTable[#saveTable + 1] =  ","
				saveTable[#saveTable + 1] =  gameObjects[i]["scale"]["z"]
				saveTable[#saveTable + 1] =  ","
				saveTable[#saveTable + 1] =  gameObjects[i]["animation"]
				saveTable[#saveTable + 1] =  "\n"
			end
		else
			if(fileType == "npc") then
				if gameObjects[i]["currentHealth"] ~= nil then
					total = total + 1
					saveTable[#saveTable + 1] =  gameObjects[i]["name"] 
					saveTable[#saveTable + 1] =  "," 
					saveTable[#saveTable + 1] =  gameObjects[i]["model"]
					saveTable[#saveTable + 1] =  "," 
					saveTable[#saveTable + 1] =  gameObjects[i]["position"]["x"]
					saveTable[#saveTable + 1] =  ","
					saveTable[#saveTable + 1] =  gameObjects[i]["position"]["y"]
					saveTable[#saveTable + 1] =  ","
					saveTable[#saveTable + 1] =  gameObjects[i]["position"]["z"]
					saveTable[#saveTable + 1] =  ","
					saveTable[#saveTable + 1] =  gameObjects[i]["direction"]["x"]
					saveTable[#saveTable + 1] =  ","
					saveTable[#saveTable + 1] =  gameObjects[i]["direction"]["y"]
					saveTable[#saveTable + 1] =  ","
					saveTable[#saveTable + 1] =  gameObjects[i]["direction"]["z"]
					saveTable[#saveTable + 1] =  ","
					saveTable[#saveTable + 1] =  gameObjects[i]["scale"]["x"]
					saveTable[#saveTable + 1] =  ","
					saveTable[#saveTable + 1] =  gameObjects[i]["scale"]["y"]
					saveTable[#saveTable + 1] =  ","
					saveTable[#saveTable + 1] =  gameObjects[i]["scale"]["z"]
					saveTable[#saveTable + 1] =  ","
					saveTable[#saveTable + 1] =  gameObjects[i]["animation"]
					saveTable[#saveTable + 1] =  ","
					saveTable[#saveTable + 1] =  gameObjects[i]["currentHealth"]
					saveTable[#saveTable + 1] =  ","
					saveTable[#saveTable + 1] =  gameObjects[i]["maxHealth"]
					saveTable[#saveTable + 1] =  ","
					saveTable[#saveTable + 1] =  gameObjects[i]["characterName"]
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
	printAPI.print("Loading instances")

	local fileData= read(filePath, ',')
	local numRows = 0

	for k,v in next, fileData do 
		numRows = numRows + 1
	end
	for i = 1, numRows do
		instanceID = luaObjInstManager.addNewInstance(fileData[i][2])

		objpos = Vector3.new(fileData[i][3], fileData[i][4], fileData[i][5])
		dir = Vector3.new(fileData[i][6], fileData[i][7], fileData[i][8])
		sca = Vector3.new(fileData[i][9], fileData[i][10], fileData[i][11])
		if(fileData[i][12] == 1) then
			anim = 1
		else
			anim = 0
		end

		if(fileType == "gameObject") then
			n = gameObject.new(fileData[i][1], fileData[i][2], objpos, dir, sca, anim, instanceID)
		else
			if(fileType == "npc") then
				n = npc.new(fileData[i][1], fileData[i][2], objpos, dir, sca, anim, instanceID, fileData[i][13], fileData[i][14], fileData[i][15])
			end
		end
		
		table.insert(gameObjects, n)
		objectInstanceAPI.setTranslation(instanceID,objpos.x,objpos.y,objpos.z)
		objectInstanceAPI.setOrientation(instanceID,dir.x,dir.y,dir.z)
		objectInstanceAPI.setScale(instanceID,sca.x,sca.y,sca.z)
		objectInstanceAPI.setAnimation(instanceID,0)
		renderManagerAPI.addObject(instanceID)
	end
	
	if(fileType == "gameObject") then
		printAPI.print(numRows .. ' game objects loaded.\n')
	else
		if(fileType == "npc") then
			printAPI.print(numRows .. ' NPCs loaded.\n')
		end
	end	
	printAPI.print("Loaded instances")

end

local Vector3 = require 'LuaScripts/Vector3'
local gameObject = require 'LuaScripts/gameObject'
local AABoundingBox = require 'LuaScripts/AABoundingBox'
local npc = require 'LuaScripts/npc'
local Player = require 'LuaScripts/Player'
require 'LuaScripts/FileIO'
--This file handles saving and loadinge gameObjects
--This function saves all gameObjects of a specific type to the specified path
function SaveInstances(filePath, data, fileType)
	local total = 0
	local numRows = 0
	--get the total number of gameObjects
	for k,v in next, data do 
		numRows = numRows + 1
	end
	--delete all contents in the current saveFile if it exists
	clearFile(filePath)

	--for every game object
	for i = 1, numRows do
	--write out data in this format if a gameObject was chosen
		if(fileType == "gameObject") then
		--check whether the current object is a gameObject
			if gameObjects[i]["currentHealth"] == nil then
				//saves all data to a csv
				total = total + 1
				write(filePath, gameObjects[i]["name"])
				write(filePath, ",")
				
				write(filePath, gameObjects[i]["model"])
				write(filePath, ",")
				
				write(filePath, gameObjects[i]["position"]["X"])
				write(filePath, ",")
				write(filePath, gameObjects[i]["position"]["Y"])
				write(filePath, ",")
				write(filePath, gameObjects[i]["position"]["Z"])
				write(filePath, ",")
				
				write(filePath, gameObjects[i]["direction"]["X"])
				write(filePath, ",")
				write(filePath, gameObjects[i]["direction"]["Y"])
				write(filePath, ",")
				write(filePath, gameObjects[i]["direction"]["Z"])
				write(filePath, ",")
				
				write(filePath, gameObjects[i]["scale"]["X"])
				write(filePath, ",")
				write(filePath, gameObjects[i]["scale"]["Y"])
				write(filePath, ",")
				write(filePath, gameObjects[i]["scale"]["Z"])
				write(filePath, ",")
				
				if(gameObjects[i]["animation"] == true) then
					ani = 1
				else
					ani = 0
				end
				write(filePath, ani)
				write(filePath, "\n")
			end
		else
			--if the desired type is an npc, print data in this format
			if(fileType == "npc") then
				--check if this game object is an npc
				if gameObjects[i]["currentHealth"] ~= nil then
				--output all data to csv file
					total = total + 1
					write(filePath, gameObjects[i]["name"])
					write(filePath, ",")
					
					write(filePath, gameObjects[i]["model"])
					write(filePath, ",")
					
					write(filePath, gameObjects[i]["position"]["X"])
					write(filePath, ",")
					write(filePath, gameObjects[i]["position"]["Y"])
					write(filePath, ",")
					write(filePath, gameObjects[i]["position"]["Z"])
					write(filePath, ",")
					
					write(filePath, gameObjects[i]["direction"]["X"])
					write(filePath, ",")
					write(filePath, gameObjects[i]["direction"]["Y"])
					write(filePath, ",")
					write(filePath, gameObjects[i]["direction"]["Z"])
					write(filePath, ",")
					
					write(filePath, gameObjects[i]["scale"]["X"])
					write(filePath, ",")
					write(filePath, gameObjects[i]["scale"]["Y"])
					write(filePath, ",")
					write(filePath, gameObjects[i]["scale"]["Z"])
					write(filePath, ",")
					
					if(gameObjects[i]["animation"] == true) then
						ani = 1
					else
						ani = 0
					end
					write(filePath, ani)
					write(filePath, ",")
					
					write(filePath, gameObjects[i]["currentHealth"])
					write(filePath, ",")
					write(filePath, gameObjects[i]["maxHealth"])
					write(filePath, ",")
					write(filePath, gameObjects[i]["characterName"])
					write(filePath, "\n")
				end
			end
		end
	end
	--tell the user how may objects were saved
	if(fileType == "gameObject") then
		printAPI.print(total .. ' game objects saved.\n')
	else
		if(fileType == "npc") then
			printAPI.print(total .. ' NPCs saved.\n')
		end
	end	
end

--load a csv file and convert that data into object instances
function LoadInstances(filePath, fileType)
	local fileData= read(filePath, ',')
	local numRows = 0

	--get the number of game objects
	for k,v in next, fileData do 
		numRows = numRows + 1
	end
	--for every game object stored in csv
	for i = 1, numRows do
	--create a new instance and get the handle
		instanceID = luaObjInstManager.addNewInstance(fileData[i][2])
		--get data specific to this instance
		objpos = Vector3.new(fileData[i][3], fileData[i][4], fileData[i][5])
		dir = Vector3.new(fileData[i][6], fileData[i][7], fileData[i][8])
		sca = Vector3.new(fileData[i][9], fileData[i][10], fileData[i][11])
		if(fileData[i][12] == 1) then
			anim = 1
		else
			anim = 0
		end
		--if the object is a gameObject do this
		if(fileType == "gameObject") then
			n = gameObject.new(fileData[i][1], fileData[i][2], objpos, dir, sca, anim, instanceID)
		else
			--if its an npc do this
			if(fileType == "npc") then
				n = npc.new(fileData[i][1], fileData[i][2], objpos, dir, sca, anim, instanceID, fileData[i][13], fileData[i][14], fileData[i][15])
			end
		end
		
		--insert this instance into the list of game objects
		table.insert(gameObjects, n)
		--set up the object in the object instance api
		objectInstanceAPI.setTranslation(instanceID,objpos.X,objpos.Y,objpos.Z)
		objectInstanceAPI.setOrientation(instanceID,dir.X,dir.Y,dir.Z)
		objectInstanceAPI.setScale(instanceID,sca.X,sca.Y,sca.Z)
		objectInstanceAPI.setAnimation(instanceID,0)
		renderManagerAPI.addObject(instanceID)
	end
	
	
	--tell the user how many objects were loaded
	if(fileType == "gameObject") then
		printAPI.print(numRows .. ' game objects loaded.\n')
	else
		if(fileType == "npc") then
			printAPI.print(numRows .. ' NPCs loaded.\n')
		end
	end	
end

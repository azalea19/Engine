local Vector3 = require 'LuaScripts/Vector3'
local gameObject = require 'LuaScripts/gameObject'

local Scene = {}
Scene.__index = Scene

-- todo change capitalisation

function Scene.new(newSceneName, newPlayerStartPos, newPlayerStartDir)
	local instance = {
		name = newSceneName,
		objects = {},
		terrainID = 0,
		playerStartPos = newPlayerStartPos,
		playerStartDir = newPlayerStartDir,
	}
	
	setmetatable(instance,Scene)
	
	return instance
end

function Scene:SetTerrain(newTerrainID)
	self.terrainID = newTerrainID
end

function Scene:Update()
	
end

function Scene:GetTerrainID()
	return self.terrainID
end

function Scene:AddInstances(data)
	if(self:GetGameObjectCount() <= 0) then
		self.objects = data
	else
		for i = 1,#data do
			table.insert(self.objects, data[i])
		end
	end
end

function Scene:RemoveInstance(data)
	for i=1,#self.objects do
		if(self.objects[i].stringID == data.stringID) then
			debugLPrint("Removed object " .. data.stringID .." from scene.\n")
			table.remove(self.objects,i)
			return true
		end
	end
	debugLPrint("Could not remove ".. data.stringID .." from scene - it does not exist.")
	return false
end

function Scene:AddInstance(data)
	table.insert(self.objects, data)
end

function Scene:RemoveInstances()
	for i = 1,self:GetGameObjectCount() do
		self.objects[i] = nil
	end
end

function Scene:GetGameObjectCount()
	return #self.objects
end

function Scene:SpawnRandomObjects(type, rotationMod, scale, amount)
	for k = 0, amount do
		local xRand = math.random(5, terrainSizeX - 5)
		local zRand = math.random(5, terrainSizeY - 5)
		local xRotRand = math.random(360)
		local yRand = GetHeightAtPoint(xRand , zRand)
		local tempID = luaObjInstManager.addNewInstance(type)
		local objPosTemp = Vector3.new(xRand, yRand, zRand )
		local dirTemp = Vector3.new(xRotRand, 0, 0)

		local item = gameObject.new(type, type, objPosTemp, dirTemp, scale, 0, tempID)
		--[[
		objectInstanceAPI.setTranslation(tempID, xRand, yRand, zRand)
		objectInstanceAPI.setOrientation(tempID, xRotRand, rotationMod["y"], rotationMod["z"])
		objectInstanceAPI.setScale(tempID,scale.x,scale.y,scale.z)
		objectInstanceAPI.setAnimation(tempID,0)
		renderManagerAPI.addObject(tempID)


        local nscale = objectInstanceAPI.getScale(tempID, context.handle)
        local abox = AABBAPI.getAABB(tempID, context.handle)
		--printAPI.print(abox.min.x .. " " .. abox.min.y .. " " .. abox.min.z .. " " .. abox.max.x .. " " .. abox.max.y .. " " .. abox.max.z .. "\n")
		abox.min = mmath.vec3_Multiply(abox.min,nscale,context.handle)
		abox.max = mmath.vec3_Multiply(abox.max,nscale,context.handle)
		item["boundingBox"] = abox
		]]
		table.insert(self.objects, item)
	end
end

return Scene
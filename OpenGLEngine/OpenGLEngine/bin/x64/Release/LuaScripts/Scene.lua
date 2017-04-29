local Vector3 = require 'LuaScripts/Vector3'
local gameObject = require 'LuaScripts/gameObject'

local Scene = {}
Scene.__index = Scene

function Scene.new(newSceneName, newSceneTerrain, newPlayerStartPos, newPlayerStartDir)
	local instance = {
		name = newSceneName,
		objects = {},
		terrainID = newSceneTerrain,
		playerStartPos = newPlayerStartPos,
		playerStartDir = newPlayerStartDir,
	}
	
	setmetatable(instance,Scene)
	
	return instance
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

function Scene:AddInstance(data)
	table.insert(self.objects, data)
end

function Scene:RemoveInstances()
	for i = 1,self:GetGameObjectCount() do
		self.objects[i] = nil
	end
end

function Scene:SetupInstances()
	for i = 1, self:GetGameObjectCount() do
		if(self.objects[i]["position"]["y"] == 0) then
			self.objects[i]["position"]["y"] = GetHeightAtPoint(self.objects[i]["position"]["x"] , self.objects[i]["position"]["z"]) + 10
		end
        local gid = self.objects[i]["id"]

		objectInstanceAPI.setTranslation(self.objects[i]["id"],self.objects[i]["position"]["x"],self.objects[i]["position"]["y"],self.objects[i]["position"]["z"])
        local nscale = objectInstanceAPI.getScale(gid, context.handle)
        local abox = AABBAPI.getAABB(gid, context.handle)
		
		abox.min = luaVectorUtility.vec3_Multiply(abox.min,nscale,context.handle)
		abox.max = luaVectorUtility.vec3_Multiply(abox.max,nscale,context.handle)

        self.objects[i]["boundingBox"] = abox
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
		objectInstanceAPI.setTranslation(tempID, xRand, yRand, zRand)
		objectInstanceAPI.setOrientation(tempID, xRotRand, rotationMod["y"], rotationMod["z"])
		objectInstanceAPI.setScale(tempID,scale.x,scale.y,scale.z)
		objectInstanceAPI.setAnimation(tempID,0)
		renderManagerAPI.addObject(tempID)


        local nscale = objectInstanceAPI.getScale(tempID, context.handle)
        local abox = AABBAPI.getAABB(tempID, context.handle)
		printAPI.print(abox.min.x .. " " .. abox.min.y .. " " .. abox.min.z .. " " .. abox.max.x .. " " .. abox.max.y .. " " .. abox.max.z .. "\n")
		abox.min = luaVectorUtility.vec3_Multiply(abox.min,nscale,context.handle)
		abox.max = luaVectorUtility.vec3_Multiply(abox.max,nscale,context.handle)
		item["boundingBox"] = abox
		table.insert(self.objects, item)
	end
end

return Scene

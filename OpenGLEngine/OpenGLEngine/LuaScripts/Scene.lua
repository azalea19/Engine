local Scene = {}
Scene.__index = Scene

function Scene.new(newSceneName, newSceneTerrain, newPlayerStartPos, newPlayerStartDir)
	local instance = {
		name = newSceneName,
		objects = {},
		terrain = newSceneTerrain,
		playerStartPos = newPlayerStartPos,
		playerStartDir = newPlayerStartDir,
		gameObjectCount = 0
	}
	
	setmetatable(instance,Scene)
	
	return instance
end

function Scene:Update()
	
end

function Scene:GetTerrainID()
	return self.terrain["id"]
end

function Scene:AddInstances(data)
	local numRows = 0
	for k,v in next, gameObjects do 
		numRows = numRows + 1
	end

	for i = 1,numRows do
		table.insert(self.objects, data[i])
		self.gameObjectCount = self.gameObjectCount + 1
	end
end

function Scene:RemoveInstances(data)
	for i = 1,self.gameObjectCount do
		self.objects[i] = nil
		self.gameObjectCount = self.gameObjectCount - 1
	end
end

function Scene:SetupInstances()
	for i = 1, self.gameObjectCount do
		if(self.objects[i]["position"]["y"] == 0) then
			self.objects[i]["position"]["y"] = GetHeightAtPoint(self.objects[i]["position"]["x"] , self.objects[i]["position"]["z"])
		end
        local gid = self.objects[i]["id"]

		objectInstanceAPI.setTranslation(self.objects[i]["id"],self.objects[i]["position"]["x"],self.objects[i]["position"]["y"],self.objects[i]["position"]["z"])
        local nscale = objectInstanceAPI.getScale(gid, context.handle)
        local nloc = objectInstanceAPI.getTranslation(gid, context.handle)
        local abox = AABBAPI.getAABB(gid, context.handle)
        self.objects[i]["boundingbox"] = BBToLocal(abox,nscale,nloc)
    end
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

		item = gameObject.new(type, type, objPosTemp, dirTemp, scale, 0, tempID)
		objectInstanceAPI.setTranslation(tempID, xRand, yRand, zRand)
		objectInstanceAPI.setOrientation(tempID, xRotRand, rotationMod["y"], rotationMod["z"])

        local nscale = objectInstanceAPI.getScale(tempID, context.handle)
        local nloc = objectInstanceAPI.getTranslation(tempID, context.handle)
        local abox = AABBAPI.getAABB(tempID, context.handle)
        item["boundingbox"] = BBToLocal(abox,nscale,nloc)
		table.insert(self.objects, item)
		self.gameObjectCount = self.gameObjectCount + 1
	end
end

return Scene

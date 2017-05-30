
local World = {}
World.__index = World

function World.new(newPlayer)
	local instance = {
		Player = newPlayer,
		scenes = {},
		currentScene = 1
	}    
	  
	setmetatable(instance,World)
	return instance
end
	
function World:enterScene(sceneToEnter)
	for i = 1, #self.scenes do
		if(self.scenes[i]["name"] == sceneToEnter) then
			self.currentScene = i
            playerInScene = i
            printAPI.print("Successfuly changed scenes\n")
		end
	end
end

function World:FindObject(name)
	for i=1,#self.scenes do
	local tmp = self.scenes[i]:FindInstance(name)
		if(tmp ~= false) then
			debugLPrint("Found object " .. name .." in scene.\n")
			return tmp
		end
	end
	return false
end

function World:Update()

end
	
function World:GetScene()
	return self.scenes[self.currentScene]
end

function World:GetSceneSpecific(sce)
	for i=1,#self.scenes do
	    if(sce == self.scenes.name) then
		    return self.scenes[i]
	    end
	end
end

function World:AddScene(newScene)
	self.scenes[#self.scenes + 1] = newScene
end

function World:GetGameObjects()
	return self.scenes[self.currentScene]["objects"]
end

function World:GetCheckpoints()
	return self.scenes[self.currentScene]["checkpoints"]
end

function World:AddCheckpoints(data)
	self.scenes[self.currentScene]:AddCheckpoints(data)
end

function World:AddCheckpoint(newCheckpoint)
	self.scenes[self.currentScene]:AddCheckpoint(newCheckpoint)
end

function World:AddInstances(data)
	self.scenes[self.currentScene]:AddInstances(data)
end

function World:AddInstance(newInstance)
	self.scenes[self.currentScene]:AddInstance(newInstance)
end

function World:RemoveInstances()
	self.scenes[self.currentScene]:RemoveInstances()
end

function World:GetTerrainID()
	return self.scenes[self.currentScene]:GetTerrainID()
end

function World:GetGameObjectCount()
	debugPrint("Getting game object count... ")
	a = self.scenes[self.currentScene]:GetGameObjectCount()
	debugPrint("Success\n")
	return a
end

function World:SetupInstances()
	self.scenes[self.currentScene]:SetupInstances()
end

return World


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
            printAPI.print("Successfuly changed scenes\n")
		end
	end
end

function World:Update()

end
	
function World:GetScene()
	return self.scenes[self.currentScene]
end

function World:AddScene(newScene)
	self.scenes[#self.scenes + 1] = newScene
end

function World:GetGameObjects()
	return self.scenes[self.currentScene]["objects"]
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

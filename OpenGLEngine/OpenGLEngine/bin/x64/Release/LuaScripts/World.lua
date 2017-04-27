
local World = {}
World.__index = World

function World.new(newPlayer, newScene)
	local instance = {
		Player = newPlayer,
		scenes = newScene,
		currentScene = 1
	}    
	  
	setmetatable(instance,World)
	return instance
end
	
function World:enterScene(sceneToEnter)
	for i = 1, #self.scenes do
		if(self.scenes[i]["name"] == sceneToEnter) then
			currentScene = i
		end
	end
end

function World:Update()

end
	
function World:AddScene(newScene)
	table.insert(self.scenes, newScene)
end

function World:GetGameObjects()
	return self.scenes[currentScene]["objects"]
end

function World:AddInstances(data)
	self.scenes[currentScene]:AddInstances(data)
end

function World:RemoveInstances()
	self.scenes[currentScene]:RemoveInstances()
end

function World:GetTerrainID()
	return self.scenes[currentScene]:GetTerrainID()
end

function World:GetGameObjectCount()
	return self.scenes[currentScene]["gameObjectCount"]
end

return World

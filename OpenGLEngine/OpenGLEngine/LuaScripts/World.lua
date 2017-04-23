
local World = {}
World.__index = World

function World.new(newPlayer, newScenes)
	local instance = {
	Player = newPlayer,
	scenes = newScenes,
	currentScene = 1}      
	setmetatable(instance,World)
	
	return instance
end
	
function World:enterScene(sceneToEnter)
	currentScene = sceneToEnter
end

function World:Update()

end
	
return World

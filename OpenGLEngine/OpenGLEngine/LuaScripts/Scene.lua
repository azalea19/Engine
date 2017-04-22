local Scene = {}
Scene.__index = Scene

function Scene.new(newSceneName, newSceneObjects, newSceneTerrain, newPlayerStartPos)
	local instance = {
	name = newSceneName,
	objects = newSceneObjects,
	terrain = newSceneTerrain,
	playerStartPos = newPlayerStartPos}
	
	setmetatable(instance,Scene)
	
	return instance
end

function Scene:Update()
	
end

return Scene

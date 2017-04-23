local Scene = {}
Scene.__index = Scene
--A scene, contains all objects, terrain and relevant data specific to this scene
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

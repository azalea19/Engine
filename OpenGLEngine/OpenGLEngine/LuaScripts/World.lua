

World =
{
	function World:create(balance)
	   local world = {}      
	   setmetatable(acnt,World) 
	   return world
	end

	local player =

	
	bodies = {}
	
	scenes = {}
	
	function world:enterScene(sceneToEnter)
	end
	
	function world:loadSceneFromFile(sceneFile) return 'sceneIndex'
	newScene
	newScene.id = scenes.count
	end
}

Scene =
{
	local id

	function Scene:addRigidBody
	
	end

	function Scene:create()
	   local scene = {}             -- our new object
	   setmetatable(scene,World)  -- make Account handle lookup
	   return acnt
	end

	end
		
}


RigidBody =
{
local id
}
InteractableBody = RigidBody:New()
NPCBody = InteractableBody:New()
PickUpBody = InteractableBody:New()



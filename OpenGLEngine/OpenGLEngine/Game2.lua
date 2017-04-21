function Run()
	Initialize()
	GameLoop()
	Finalize()
end

function LoadAPIs()
	GetAPI(context.handle, 'printAPI', 'printAPI')
	GetAPI(context.handle, 'objectInstanceAPI', 'objectInstanceAPI')
	--GetAPI(context.handle, 'luaInstanceManager', 'luaInstanceManager')
	GetAPI(context.handle, 'printAPI', 'printAPI')
	GetAPI(context.handle, 'modelLibraryAPI', 'modelLibraryAPI')
	GetAPI(context.handle, 'renderManagerAPI', 'renderManagerAPI')
	GetAPI(context.handle, 'mainAPI', 'mainAPI')
	[[
	GetAPI(context.handle, 'instanceFileLoaderAPI', 'mainAPI')
	GetAPI(context.handle, 'luaInstanceFileLoaderManager', 'mainAPI')
	]]
end

function Initialize()
	LoadAPIs()
	
	printAPI.print('Initializing...\n')
	mainAPI.initialise()
	--modelLibraryAPI.addModel("Plant","Assets/Models/SmallPlant/SmallPlant.obj",false)
	--plant01 = objectInstanceAPI.AddNewInstance("Plant")

	
	[[
	scene01 = Scene.create()
	
	instanceLoader = luaInstanceFileLoaderManager.AddNewInstance()
	
	for int i=0,i<instanceFileLoaderAPI.fileLength,i++
		objectHandle = instanceFileLoaderAPI.readFromLoadedFile(instanceLoader, i) -- Adds this instance from the file to lua instance manager. Object instance can be referenced by objectHandle using the objectInstanceAPI. Also sets translation, scale and animation state from file.
		scene01.addRigidBody(objectHandle)
		--objectInstanceAPI.SetTranslation(objectHandle,)
		
		
		
	end
	
	]]
end

function GameLoop()
	while true do
		Update()
		Render()
		--if count == 10 then
			--return
		--end
	end
end

function Finalize()
	printAPI.print('Finalizing...\n')
end

function Update()
	count = (count or 0) + 1
	mainAPI.update()
end

function Render()
	printAPI.print('count = ')
	printAPI.print(count)
	printAPI.print('\n')
	mainAPI.render()
end

Run()

[[
World =
{
	function World:create()
	   local world = {}      
	   setmetatable(world,World) 
	   return world
	end

	local player =

	
	bodies = {}
	
	scenes = {}
	
	function world:enterScene(sceneToEnter)
	end
	
	function world:loadNewSceneFromFile(sceneFile) return 'sceneIndex'
		newScene
		newScene.id = scenes.count
	end
}

Scene =
{
	local id

	local instances
	local instCount = 0
	
	function Scene:addRigidBody(instHandle)
		instances[instCount] = instHandle
		instCount += 1
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


--InteractableBody = RigidBody:New()
--NPCBody = InteractableBody:New()
--PickUpBody = InteractableBody:New()

]]


function Run()
	Initialize()
	GameLoop()
	Finalize()
end

function LoadAPIs()
	GetAPI(context.handle, 'printAPI', 'printAPI')
	GetAPI(context.handle, 'objectInstanceAPI', 'objectInstanceAPI')
	GetAPI(context.handle, 'luaInstanceManager', 'luaInstanceManager')
	GetAPI(context.handle, 'printAPI', 'printAPI')
	GetAPI(context.handle, 'modelLibraryAPI', 'modelLibraryAPI')
	GetAPI(context.handle, 'renderManagerAPI', 'renderManagerAPI')
	GetAPI(context.handle, 'mainAPI', 'mainAPI')
	GetAPI(context.handle, 'instanceFileLoaderAPI', 'mainAPI')
	GetAPI(context.handle, 'luaInstanceFileLoaderManager', 'mainAPI')

end

function Initialize()
	--scen = Scene.new()
	LoadAPIs()
	
	
	
	printAPI.print('Initializing...\n')
	mainAPI.initialise()
	modelLibraryAPI.addModel("Plant","Assets/Models/SmallPlant/SmallPlant.obj",false)
	plant01 = luaInstanceManager.addNewInstance("Plant")
	objectInstanceAPI.setTranslation(plant01,10,10,10)
	plant01 = luaInstanceManager.addNewInstance("Plant")
	objectInstanceAPI.setTranslation(plant01,0,0,0)

	
	--
	
	--[[
	instanceLoader = luaInstanceFileLoaderManager.AddNewInstance()
	instanceFileLoaderAPI.loadNewSceneFromFile(instanceLoader,"test")
	
	for i=0,instanceFileLoaderAPI.getFileLength(instanceLoader) do
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
	--printAPI.print('count = ')
	--printAPI.print(count)
	--printAPI.print('\n')
	mainAPI.render()
end

Run()

-- World --
World = 
{
	player = {},
	scenes = {},
	sceneCount = 0
}

	function World:new(o)-- return 'createdWorld'
		o = o or {}  
	    setmetatable(o,World) 
	    return o
	end
	
	
	
	function World:enterScene(sceneToEnter)
	end

	
	function World:loadNewSceneFromFile(sceneFile) return 'sceneIndex'
		--newScene.id = sceneCount
		--sceneCount = sceneCount+1
	end
	
-- Scene --
Scene =
{}
--[[
	id,00
	instances = {},
	instCount = 0
]]
	
--	Scene.__index = Scene
	
	function Scene.new()
		local self = setmetatable({}, MyClass)
		return self
	end
	--[[
	function Scene:new(scene)
	   scene = scene or {}     
	   setmetatable(scene,self)
	   self.__index = self
	   return scene
	end
	]]

	--[[
	function Scene.addRigidBody(instHandle)
		--instHandle = instHandle or {}
		instances[instCount] = instHandle
		instCount = instCount + 1
	end
	]]
	
	
	
	
	
	
	
	
	
RigidBody =
{
id
}

function RigidBody:new(o)-- return 'createdWorld'
		o = o or {}  
	    setmetatable(o,RigidBody) 
	    return o
	end
	
InteractableBody = RigidBody:New()
NPCBody = InteractableBody:New()
PickUpBody = InteractableBody:New()
	
--[[

	

	

	local player = {}

	
	bodies = {}
	
	scenes = {}
	
	function world:enterScene(sceneToEnter)
	end
	
	function world:loadNewSceneFromFile(sceneFile) return 'sceneIndex'
		--newScene
		newScene.id = scenes.count
	end




]]
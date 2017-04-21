

SDL_SCANCODE_W = 26
SDL_SCANCODE_A = 4

SDL_SCANCODE_S = 22
SDL_SCANCODE_D = 7
SDL_SCANCODE_ESCAPE = 41


	
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
	GetAPI(context.handle, 'inputManagerAPI', 'inputManagerAPI')
    GetAPI(context.handle, 'luaVectorUtility', 'luaVectorUtility')
    GetAPI(context.handle, 'engineAPI', 'engineAPI')
    GetAPI(context.handle, 'cameraAPI', 'cameraAPI')
    GetAPI(context.handle, 'timeAPI', 'timeAPI')

end

--[[
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

		
-- Bodies --

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
	
	]]
-- Scene --
Scene =
{	id,
	instances = {},
	instCount = 0
}
	
	function Scene:new(o)
		o = o or {}
		local self = setmetatable({}, Scene)
		self.__index = self
		return self
	end

	function Scene.addRigidBody(instHandle)
		--instances[instCount] = instHandle
		--instCount = instCount + 1
	end
	
-- Player --


Player =
{	
}
	
	function Player:new(o)
		o = o or {}
		local self = setmetatable({}, Player)
		self.__index = self
		return self
	end

	function Player.update()
	
	    -- written by liz translated from maddys c++ code
	    turnSpeed = 0.3
	    moveSpeed = 0.5
	    camera0 = cameraManager.getInstance(0)
	
        --rotation
	    origYaw = cameraAPI.getYaw(camera0)
	    origPitch = cameraAPI.getPitch(camera0)
	    deltaYaw = -inputManagerAPI.mouseDeltaX * turnSpeed
	    deltaPitch = -inputManagerAPI.mouseDeltaY * turnSpeed
	    cameraAPI.setYaw(originalYaw + deltaYaw)
	    cameraAPI.setPitch(originalPitch+deltaPitch)

        --translation   
	    oldPos = cameraAPI.getPosition(camera0);
	    forward = cameraAPI.forward(camera0);
	    right = cameraAPI.right(camera0);
	    translation = { x=0, y=0, z=0 };
	
        MOVE_SPEED = 1
    
    
	
	    if inputManagerAPI.isKeyDown(SDL_SCANCODE_W) then
        	translation = luaVectorUtility.addVector(translation,forward)
        end

        if inputManagerAPI.isKeyDown(SDL_SCANCODE_A) then
        	translation = luaVectorUtility.subtractVector(translation,right)
        end


	    if inputManagerAPI.isKeyDown(SDL_SCANCODE_S) then
        	translation = luaVectorUtility.subtractVector(translation,forward)
        end
	    if inputManagerAPI.isKeyDown(SDL_SCANCODE_D) then
        	translation = luaVectorUtility.addVector(translation,right)
        end
        
        if not luaVectorUtility.equals(translation.x,translation.y,translation.z,0,0,0) then

            translation = luaVectorUtility.normalize(translation.x,translation.y,translation.z)
            translation = luaVectorUtility.multiplyFloat(translation.x,translation.y,translation.z,MOVE_SPEED)

            
            newPos = luaVectorUtility.addVector(oldPos,translation)

            cameraAPI.setPosition(camera0,newPos.x,newPos.y,newPos.z);

        end
        

	end
	


function Initialize()
	
	LoadAPIs()
	
	
	
	printAPI.print('Initializing...\n')

    printAPI.print('Initialising engine...\n')

	engineAPI.Create(0);
	engineAPI.Initialise(1024,728);

    printAPI.print('Initialising objects...\n')

	modelLibraryAPI.addModel("Plant","Assets/Models/SmallPlant/SmallPlant.obj",false)
	modelLibraryAPI.addModel("Bob","Assets/Models/Bob/bob.md5mesh",false)
	plant01 = luaInstanceManager.addNewInstance("Plant")
	objectInstanceAPI.setTranslation(plant01,10,10,10)

	plant02 = luaInstanceManager.addNewInstance("Plant")
	objectInstanceAPI.setTranslation(plant02,0,0,0)

    renderManagerAPI.addObject(plant01)
    renderManagerAPI.addObject(plant02)


    printAPI.print('Initialising scene...\n')


	scene01 = Scene:new()

    printAPI.print('Initialising player...\n')

	
	player = Player.new()

    printAPI.print('Initialising camera...\n')

    camera0 = cameraAPI.addNewInstance()

    

    --[[
	
	instanceLoader = luaInstanceFileLoaderManager.addNewInstance()
	instanceFileLoaderAPI.loadFile(instanceLoader,'test')
	for i=0,instanceFileLoaderAPI.getFileLength(instanceLoader)-1 do
		objectHandle = instanceFileLoaderAPI.readFromLoadedFile(instanceLoader, i) -- Adds this instance from the file to lua instance manager. Object instance can be referenced by objectHandle using the objectInstanceAPI. Also sets translation, scale and animation state from file.
		
        
        --scene01.addRigidBody(objectHandle)
		--objectInstanceAPI.SetTranslation(objectHandle,)
	end
    ]]
end

function GameLoop()
	run = true
	while run do
    	--printAPI.print('Running game loop...\n')

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

function TestInputAPI()
	--printAPI.print('Testing input...\n')

	e = inputManagerAPI.isKeyDown(8)
	if e then
		printAPI.print("e")
		objectInstanceAPI.setTranslation(plant01,0,0,0)

	end

    esc = inputManagerAPI.isKeyDown(SDL_SCANCODE_ESCAPE)
	if esc then
		printAPI.print("Quitting - pressed Esc.\n")
        run = false
	end

end


function Update()

    engineAPI.BeginUpdate()

    inputManagerAPI.update();

	--Lua update here
    count = (count or 0) + 1
	--run = mainAPI.update()
	
	TestInputAPI()

    --player.Update();


	engineAPI.EndUpdate();
	
end



function Render()
	--printAPI.print('count = ')
	--printAPI.print(count)
	--printAPI.print('\n')
	--mainAPI.render()

    engineAPI.BeginRender()

    printAPI.print("Getting time...\n");

    time = timeAPI.elapsedTimeMs()

    printAPI.print("Getting world matrix...\n");

    worldMatrix = luaVectorUtility.mat4_CreateIdentity(context.handle)

    printAPI.print("Getting view matrix...\n");

    viewMatrix = cameraAPI.getViewMatrix(camera0, context.handle)

    printAPI.print("Getting projection matrix...\n");

    projectionmatrix = cameraAPI.getProjectionMatrix(camera0, context.handle)

    
    printAPI.print("Rendering...\n");

    --renderManagerAPI.renderFromCamera(camera0,time)
	--Lua render here

    
    printAPI.print("Render Successful\n");

    engineAPI.EndRender()

end

Run()


	

	
	
	
	
	

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
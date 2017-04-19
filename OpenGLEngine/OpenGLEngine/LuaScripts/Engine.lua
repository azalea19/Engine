

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
	GetAPI(context.handle, 'engineAPI', 'engineAPI')
end

function Initialize()
	
	LoadAPIs()
	
	printAPI.print('Initializing...\n')
	
	engineAPI.Create(0);
	engineAPI.Initialise(1024,728);

	scene = CreateScene();	
end

function GameLoop()
	while true do
		Update()
		Render()		
	end
end

function Finalize()
	printAPI.print('Finalizing...\n')
end

function Update()
	engineAPI.BeginUpdate()

	--Lua update here

	engineAPI.EndUpdate();
end

function Render()
	engineAPI.BeginRender()


	--Lua render here

    engineAPI.EndRender()
end

--Creates a terrain object
function CreateTerrain()

	local terrain = {}
	terrain["ground"] = luaInstanceManager.AddNewInstance("ground")
	terrain["trees"] = {}

	for i=1, 10, 1 do 
		terrain["trees"][i] = luaInstanceManager.AddNewInstance("tree")
		objectInstanceAPI.SetTranslation(terrain["trees"][i], i,0,i)
	end

	return terrain
end


function LoadAssets()
	modelLibraryAPI.AddModel("ground","ground.obj",false)
	modelLibraryAPI.AddModel("tree","tree.obj", false)
end

function CreateScene()
	local scene = {}
	scene["terrain"] = CreateTerrain()
	scene["NPCS"] = {}
	--scene.NPCS[1] = objectInstance
	--scene["player"] = CreatePlayer()
end

function CreatePlayer()

	local player = {}
	player["position"] = CreateVec3()
end

function CreateVec3(x,y,z)
	local vec3 = {}
	vec3["x"] = x;
	vec3["y"] = y;
	vec3["z"] = z;
	return vec3
end

Run()
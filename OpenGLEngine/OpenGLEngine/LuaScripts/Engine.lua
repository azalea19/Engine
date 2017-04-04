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
	GetAPI(context.handle, 'instanceFileLoaderAPI', 'instanceFileLoaderAPI')
	GetAPI(context.handle, 'luaInstanceFileLoaderManager', 'luaInstanceFileLoaderManager')
end

function Initialize()
	
	LoadAPIs()
	
	printAPI.print('Initializing...\n')
	
	engineAPI.Create(0);
	engineAPI.Initialise(1024,728);
	
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

Run()
function Run()
	Initialize()
	GameLoop()
	Finalize()
end

function LoadAPIs()
	GetAPI(context.handle, 'printAPI', 'printAPI')
	GetAPI(context.handle, 'objectInstanceAPI', 'objectInstanceAPI')
	GetAPI(context.handle, 'printAPI', 'printAPI')
	GetAPI(context.handle, 'modelLibraryAPI', 'modelLibraryAPI')
	GetAPI(context.handle, 'renderManagerAPI', 'renderManagerAPI')
	GetAPI(context.handle, 'mainAPI', 'mainAPI')
end

function Initialize()
	LoadAPIs()
	--
	printAPI.print('Initializing...\n')
	mainAPI.initialise()
	--modelLibraryAPI.addModel("Plant","Assets/Models/SmallPlant/SmallPlant.obj",false)
	--plant01 = objectInstanceAPI.AddNewInstance("Plant")
	
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
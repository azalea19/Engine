function Run()
	Initialize()
	GameLoop()
	Finalize()
end

function LoadAPIs()
	GetAPI(context.handle, 'printAPI', 'printAPI')
end

function Initialize()
	LoadAPIs()
	printAPI.print('Initializing...\n')
end

function GameLoop()
	while true do
		Update()
		Render()
		if count == 10 then
			return
		end
	end
end

function Finalize()
	printAPI.print('Finalizing...\n')
end

function Update()
	count = (count or 0) + 1
end

function Render()
	printAPI.print('count = ')
	printAPI.print(count)
	printAPI.print('\n')
end

Run()
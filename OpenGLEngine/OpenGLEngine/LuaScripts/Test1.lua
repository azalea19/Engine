Scene =
{}
	
	function Scene:new(o)
		o = o or {}
		local self = setmetatable({}, MyClass)
		self.__index = self
		return self
	end
	
function Run()
	Initialize()
	GameLoop()
	Finalize()
end

function Initialize()
	scene01 = Scene:new()
end

function GameLoop()
	while true do
		Update()
		Render()
	end
end

function Finalize()
end

function Update()
end

function Render()
end

Run()


local Vector3 = dofile '../Assets/Scripts/Vector3.lua'
local gameObject = dofile '../Assets/Scripts/gameObject.lua'
local AABoundingBox = dofile '../Assets/Scripts/AABoundingBox.lua'
local npc = dofile '../Assets/Scripts/npc.lua'
Player = dofile '../Assets/Scripts/Player.lua'
local Scene = dofile '../Assets/Scripts/Scene.lua'
local World = dofile '../Assets/Scripts/World.lua'
dofile '../Assets/Scripts/GameWorld.lua'
dofile  '../Assets/Scripts/Load.lua'

dofile '../Assets/Scripts/Dialogue.lua'
dofile '../Assets/Scripts/FileIO.lua'
dofile '../Assets/Scripts/ReadAndWriteData.lua'
dofile '../Assets/Scripts/Terrain.lua'
dofile '../Assets/Scripts/Controls.lua'
dofile '../Assets/Scripts/QuestManager.lua'

OPEN_GL = 0

debug = false
debugdetail = false

createCollisionTree = true


time = 0
lastTime = 0
deltaTime = 0

BoxYaw = 0;


-- Detailed debug print. For when you want to display value constantly in update and will pause to find it.
function debugPrint(string)
    if debugdetail then
        printAPI.print(string)
    end
end

-- Limited debug print. For prints that will not occur constantly in update, such as when a button is pressed.
function debugLPrint(string)
    if debug then
        printAPI.print(string)
    end
end

function Run()
	Initialize()
	GameLoop()
	Finalize()
end


function Initialize()

	LoadAPIs()
	printAPI.print('Initializing...\n')
    printAPI.print('Initialising engine...\n')

	engineAPI.Create(OPEN_GL);
	wireindex = 1

	printAPI.print('Creating...\n')
	engineAPI.Initialise(1280,720);

	printAPI.print('Loading Assets...\n')
	
	LoadAssets()
	CreateTown()

  objectInstanceAPI.setAnimation(BobTest, 0);
  --objectInstanceAPI.setAnimationSection(BobTest, 0, 5)
  objectInstanceAPI.setAnimationSpeed(BobTest, 2)
  objectInstanceAPI.setBaseTransform(BobTest, Vector3.new(0, 0, 0), 180, -90, 0, Vector3.new(1, 1, 1))

end

function GameLoop()
	run = true
	while run do
		Update()
		Render()
	end
end

function Finalize()
	printAPI.print('Finalizing...\n')
end

function Update()

	for updateIndex = 1, 1, 1 do

	    engineAPI.BeginUpdate()
		lastTime = time
		time = timeAPI.elapsedTimeMs()
		deltaTime = time - lastTime

		local quitIn = inputManagerAPI.isKeyDown(Exit_Input)
		if quitIn then
			printAPI.print("Quitting - pressed input to quit.\n")
			quitting = true
		end
    
		if(quitting) then
			if inputManagerAPI.isMousePressedLeft() then
				run = false
			end
		end

		local helpIn = inputManagerAPI.isKeyDown(Help_Input)
		if helpIn then
			helpMenu = true
		end

		if helpMenu then
			if inputManagerAPI.isMousePressedLeft() then
				helpMenu = false
			end
		end

		if(inputManagerAPI.isKeyPressed(Wireframe_Input)) then
			if(wireindex ==0) then
				wireindex =1
			else
				wireindex =0
			end
		end

		player0:update();
		
		engineAPI.EndUpdate()
	end
	

    objectInstanceAPI.lookAt(BobTest, Vector3.new(0, 1, 0), player0:getPosition())

    objectInstanceAPI.setOrientation(BoxTest, BoxYaw, 0, 0)
    collisionAPI.createCollisionTree(collidableObjects);
    BoxYaw = BoxYaw + 0.2

	
end

font1path = "../Assets/Fonts/WesternBangBang.otf"
white = {x=0,y=0,z=0}
textPos =  {x=0,y=0,z=0}

function Render()
    renderManagerAPI.beginRender()

    renderManagerAPI.setFillMode(wireindex)

    if(quitting) then
        display2DAPI.drawFullScreen("../Assets/Images/faces.png")
    else
		if(helpMenu) then
			display2DAPI.drawFullScreen("../Assets/Images/rules.png")
		else

			
			local i
			for i = 1, #collidableObjects - 1, 1 do
				renderManagerAPI.renderObject(camera0,time,collidableObjects[i], 1);
			end

			
			local i
			for i = 1, #terrainChunks, 1 do
				renderManagerAPI.renderObject(camera0,time,terrainChunks[i], 1);
			end

			renderManagerAPI.renderObject(camera0,time,gunShop, 1)	
			renderManagerAPI.renderObject(camera0,time,titan, 1)		
			renderManagerAPI.renderObject(camera0,time,skybox, 0)
			
			--[[
<<<<<<< HEAD
			renderManagerAPI.renderObject(camera0,time,BobTest,1)
=======
      renderManagerAPI.renderObject(camera0,time,BobTest,1)
      renderManagerAPI.renderObject(camera0, time, BoxTest, 1)
>>>>>>> b3d3b0fccebfe4a05f738eaf3a5bda086432277e
]]
			renderManagerAPI.present(camera0)

			--display2DAPI.drawText(64,font1path,"Damn it feels good to be a gangsta.",textPos, white, 1,1280,720)


		end
	end
    renderManagerAPI.endRender()
end

local status, err = pcall(Run)
if not status then
	--printAPI.print(err)
    --read(1)
end

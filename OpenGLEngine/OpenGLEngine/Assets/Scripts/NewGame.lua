--[[local Vector3 = require 'Vector3'
local gameObject = require 'gameObject'
local AABoundingBox = require 'AABoundingBox'
local npc = require 'npc'
local Player = require 'Player'
local Scene = require 'Scene'
local World = require 'World'
require 'FileIO'
require 'ReadAndWriteInstances'
require 'Terrain'
]]--

local Vector3 = dofile '../Assets/Scripts/Vector3.lua'
local gameObject = dofile '../Assets/Scripts/gameObject.lua'
local AABoundingBox = dofile '../Assets/Scripts/AABoundingBox.lua'
local npc = dofile '../Assets/Scripts/npc.lua'
local Player = dofile '../Assets/Scripts/Player.lua'
local Scene = dofile '../Assets/Scripts/Scene.lua'
local World = dofile '../Assets/Scripts/World.lua'

--local QuestManager = require '../Assets/Scripts/QuestManager'
dofile '../Assets/Scripts/Dialogue.lua'
dofile '../Assets/Scripts/FileIO.lua'
dofile '../Assets/Scripts/ReadAndWriteInstances.lua'
dofile '../Assets/Scripts/Terrain.lua'
dofile '../Assets/Scripts/Controls.lua'
dofile '../Assets/Scripts/QuestManager.lua'

OPEN_GL = 0

debug = false
debugdetail = false


time = 0
lastTime = 0
deltaTime = 0


collidableObjects = {}


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


function LoadAPIs()
	GetAPI(context.handle, 'objectInstanceAPI', 'objectInstanceAPI')
	GetAPI(context.handle, 'luaObjInstManager', 'luaObjectInstanceManager')
	GetAPI(context.handle, 'printAPI', 'printAPI')
	GetAPI(context.handle, 'modelLibraryAPI', 'modelLibraryAPI')
	GetAPI(context.handle, 'renderManagerAPI', 'renderManagerAPI')
	GetAPI(context.handle, 'inputManagerAPI', 'inputManagerAPI')
    GetAPI(context.handle, 'mmath', 'luaVectorUtility')
    GetAPI(context.handle, 'engineAPI', 'engineAPI')
    GetAPI(context.handle, 'cameraAPI', 'cameraAPI')
    GetAPI(context.handle, 'timeAPI', 'timeAPI')
    GetAPI(context.handle, 'terrainAPI', 'terrainAPI')
    GetAPI(context.handle, 'AABBAPI', 'AABBAPI')
    GetAPI(context.handle, 'islandCollisionAPI', 'islandCollisionAPI')
    GetAPI(context.handle, 'display2DAPI', 'display2DAPI')
    GetAPI(context.handle, 'collisionAPI', 'collisionAPI')
end

	
function LoadAssets()

	printAPI.print('Loading Models...\n')
	modelLibraryAPI.addModel("Airship","../Assets/Models/Airship/airship.lwo",false)
	modelLibraryAPI.addModel("Skybox","../Assets/Models/SkyBox/skybox.obj",false)
	modelLibraryAPI.addModel("Bob","../Assets/Models/Alfred.obj",false)
	modelLibraryAPI.addModel("Cactus","../Assets/Models/Cactus1/cactus.obj",false)
	modelLibraryAPI.addModel("Crate","../Assets/Models/Crate/crate.obj",false)
	modelLibraryAPI.addModel("GunShop","../Assets/Models/GunsShop/GunsShop.obj",false)

	printAPI.print('Loading Terrain...\n')

    hMapPath = "../Assets/HeightMaps/flatmap.png"
    terrainSizeX = 1024
    terrainSizeY = 1024
    heightMapSize = 257
    heightMapHeight = 0


	terrainHeightData = terrainAPI.generateTerrain(terrainSizeX, terrainSizeY, heightMapSize, heightMapHeight, hMapPath , "../Assets/Models/Terrain/Terrain.obj", context.handle)	
	modelLibraryAPI.addModel("Terrain","../Assets/Models/Terrain/Terrain.obj",false)
	
end

function Initialize()

	LoadAPIs()
	printAPI.print('Initializing...\n')
    printAPI.print('Initialising engine...\n')

	engineAPI.Create(OPEN_GL);
	wireindex =0

	printAPI.print('Creating...\n')
	engineAPI.Initialise(1280,720);

	printAPI.print('Loading Assets...\n')
	LoadAssets()


    printAPI.print("Initialising text...\n")

	printAPI.print('Initialising terrain...\n')
	Terrain01 = luaObjInstManager.addNewInstance("Terrain")


	objectInstanceAPI.setTranslation(Terrain01,0,0,0)


	skybox = luaObjInstManager.addNewInstance("Skybox")
	objectInstanceAPI.setTranslation(skybox, 0,0,0)
	objectInstanceAPI.setScale(skybox, 1000,1000,1000)

	gunShop = luaObjInstManager.addNewInstance("GunShop")
	objectInstanceAPI.setTranslation(gunShop, 80,0,80)
	objectInstanceAPI.setScale(gunShop, .01,.01,.01)
	
	local x
	local y
	for y = 1, 8, 1 do		
		for x = 1, 8, 1 do
			--cactus = luaObjInstManager.addNewInstance("Cactus")
			--objectInstanceAPI.setTranslation(cactus,100 + x*5,0,100 + y*5)
			--objectInstanceAPI.setOrientation(cactus, 45,0,0)
			--objectInstanceAPI.setScale(cactus, 0.1, 0.1, 0.1)
			--collidableObjects[#collidableObjects + 1] = cactus
		end
	end
	
	collidableObjects[#collidableObjects + 1] = gunShop
	collidableObjects["length"] = #collidableObjects
	
    printAPI.print('Initialising camera...\n')
    camera0 = cameraAPI.addNewInstance()
    cameraAPI.setPosition(camera0,terrainSizeX / 2, 30, terrainSizeY / 2)


    printAPI.print('Initialising player...\n')
	player0 = Player:new(camera0)
	cameraAPI.setPosition(camera0,100,0,100)
    player0:setAABB(-0.5,0.5,-1.8,0,-0.5,0.5) 

	collisionAPI.createCollisionTree(collidableObjects);

   
	
	printAPI.print('Initialization finished.\n')

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
	
	if collisionAPI.box_collidingInTree(player0:BBToWorld()) then
		printAPI.print(' Collision \n')
	else
		printAPI.print(' Not collision \n')
	end
	
	engineAPI.EndUpdate()
	
end

font1path = "../Assets/Fonts/verdanab.ttf"
white = {x=1,y=1,z=1}
textPos =  {x=0,y=0,z=0}

function Render()
    renderManagerAPI.beginRender()

    renderManagerAPI.setFillMode(wireindex)

    if(quitting) then
        display2DAPI.drawFullScreen("faces.png")
    else
		if(helpMenu) then
			display2DAPI.drawFullScreen("rules.png")
		else

			local i
			for i = 1, #collidableObjects - 1, 1 do
				renderManagerAPI.renderObject(camera0,time,collidableObjects[i], 1);
			end
			
			renderManagerAPI.renderObject(camera0,time,gunShop, 1)
			renderManagerAPI.renderObject(camera0,time,Terrain01, 1)
			renderManagerAPI.renderObject(camera0,time,skybox, 0)
			renderManagerAPI.present(camera0)

			 display2DAPI.drawText(10,font1path,"Damn it feels good to be a gangsta.",textPos, white, 1,1280,720 )


		end
	end
    renderManagerAPI.endRender()
end

local status, err = pcall(Run)
if not status then
	printAPI.print(err)
    read(1)
end

local Vector3 = require 'LuaScripts/Vector3'
local gameObject = require 'LuaScripts/gameObject'
local AABoundingBox = require 'LuaScripts/AABoundingBox'
local npc = require 'LuaScripts/npc'
local Player = require 'LuaScripts/Player'
local Scene = require 'LuaScripts/Scene'
local World = require 'LuaScripts/World'
require 'LuaScripts/FileIO'
require 'LuaScripts/ReadAndWriteInstances'
require 'LuaScripts/Terrain'

OPEN_GL = 0

gameObjects = {}
debug = true
terrainSizeX = 1000
terrainSizeY = 1000
heightMapSize = 512
heightMapHeight = 50

--SDL ScanCode list: https://wiki.libsdl.org/SDLScancodeLookup
SDL_SCANCODE_W = 26
SDL_SCANCODE_A = 4
SDL_SCANCODE_P = 19
SDL_SCANCODE_S = 22
SDL_SCANCODE_E = 8
SDL_SCANCODE_D = 7
SDL_SCANCODE_ESCAPE = 41
SDL_SCANCODE_Q = 20
SDL_SCANCODE_Z = 29
SDL_SCANCODE_LSHIFT = 225

function Run()
	Initialize()
	GameLoop()
	Finalize()
end

function LoadAPIs()
	GetAPI(context.handle, 'printAPI', 'printAPI')
	GetAPI(context.handle, 'objectInstanceAPI', 'objectInstanceAPI')
	GetAPI(context.handle, 'luaObjInstManager', 'luaObjectInstanceManager')
	GetAPI(context.handle, 'printAPI', 'printAPI')
	GetAPI(context.handle, 'modelLibraryAPI', 'modelLibraryAPI')
	GetAPI(context.handle, 'renderManagerAPI', 'renderManagerAPI')
	GetAPI(context.handle, 'inputManagerAPI', 'inputManagerAPI')
    GetAPI(context.handle, 'luaVectorUtility', 'luaVectorUtility')
    GetAPI(context.handle, 'engineAPI', 'engineAPI')
    GetAPI(context.handle, 'cameraAPI', 'cameraAPI')
    GetAPI(context.handle, 'timeAPI', 'timeAPI')
    GetAPI(context.handle, 'terrainAPI', 'terrainAPI')
    GetAPI(context.handle, 'AABBAPI', 'AABBAPI')
    GetAPI(context.handle, 'islandCollisionAPI', 'islandCollisionAPI')
    GetAPI(context.handle, 'display2DAPI', 'display2DAPI')

end

function PrintVec3(veca)
    printAPI.print(veca.x .. "," .. veca.y .. "," .. veca.z .. "\n")
end

function PrintVec3s(vecc,vecb)
    printAPI.print(vecc.x .. "," .. vecc.y .. "," .. vecc.z .. " // " .. vecb.x .. "," .. vecb.y .. "," .. vecb.z .. " ")
end
	
function LoadAssets()

	modelLibraryAPI.addModel("Plant","Assets/Models/SmallPlant/SmallPlant.obj",false)
	
	printAPI.print('plant loaded\n')

	modelLibraryAPI.addModel("Bob","Assets/Models/Bob/bob.md5mesh",false)
	terrainHeightData = terrainAPI.generateTerrain(terrainSizeX, terrainSizeY, heightMapSize, heightMapHeight, "Assets/HeightMaps/hmap.png", "Assets/Models/Terrain/Terrain.obj", context.handle)
		
	printAPI.print('terrain loaded\n')

	modelLibraryAPI.addModel("Terrain","Assets/Models/Terrain/Terrain.obj",false)
	
	
end

function Initialize()
	LoadAPIs()
	printAPI.print('Initializing...\n')
    printAPI.print('Initialising engine...\n')

	engineAPI.Create(OPEN_GL);
		
	printAPI.print('Creating...\n')

	engineAPI.Initialise(1280,720);

	printAPI.print('Loading Assets...\n')
	LoadAssets()
	
    printAPI.print('Initialising objects...\n')

	LoadInstances("SaveData/GO_Data.csv", "gameObject")
	LoadInstances("SaveData/NPC_Data.csv", "npc")
	
	Terrain01 = luaObjInstManager.addNewInstance("Terrain")
	objectInstanceAPI.setTranslation(Terrain01,0,0,0)
    
	giantPlant = luaObjInstManager.addNewInstance("Plant")
	objectInstanceAPI.setTranslation(giantPlant,100,20,100)
    objectInstanceAPI.setScale(giantPlant,10,10,10)

    printAPI.print('Initialising AABBs...\n')

    plantScale = objectInstanceAPI.getScale(giantPlant, context.handle)
    plantLoc = objectInstanceAPI.getTranslation(giantPlant, context.handle)

    plantBBox = AABBAPI.getAABB(giantPlant, context.handle)
    printAPI.print(plantScale.x .. "\n")
    plantBBox.min = luaVectorUtility.vec3_Multiply(plantBBox.min,plantScale,context.handle)
    plantBBox.min = luaVectorUtility.vec3_Sum(plantBBox.min,plantLoc,context.handle)
    plantBBox.max = luaVectorUtility.vec3_Multiply(plantBBox.max,plantScale,context.handle)
    plantBBox.max = luaVectorUtility.vec3_Sum(plantBBox.max,plantLoc,context.handle)

    -- plantBBox.min = objectInstanceAPI.getScale(giantPlant)
    -- plantBBox.max *= objectInstanceAPI.getScale(giantPlant)
    -- plantBBox.max *= objectInstanceAPI.getScale(giantPlant)

    --printAPI.print('Initialising scene...\n')
	--scene01 = Scene:new()

    printAPI.print('Initialising camera...\n')
    camera0 = cameraAPI.addNewInstance()
    cameraAPI.setPosition(camera0,terrainSizeX / 2, 30, terrainSizeY / 2)

    printAPI.print('Initialising rendermanager...\n')
    renderManagerAPI.initialise()

    printAPI.print('Initialising player...\n')
	player0 = Player:new()
    player0:setAABB(-5,5,-50,50,-5,5) -- Y values higher than X and Z so the player doesn't jump above things with the island collisions. -- todo reduce if we implement jumping

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

    --Lua update here
    --printAPI.print("Getting time...\n");
    time = timeAPI.elapsedTimeMs()
	
    esc = inputManagerAPI.isKeyDown(SDL_SCANCODE_ESCAPE)
	if esc then
		printAPI.print("Quitting - pressed input to quit.\n")

        quitting = true
        --run = false
	end
	
	if inputManagerAPI.isKeyDown(SDL_SCANCODE_P) then
		SaveInstances("SaveData/GO_Save.csv", gameObjects, "gameObject")
		SaveInstances("SaveData/NPC_Save.csv", gameObjects, "npc")
	end
	
	local numRows = 0
	for k,v in next, gameObjects do 
		numRows = numRows + 1
	end

	for i = 1, numRows do
		if gameObjects[i]["currentHealth"] ~= nil then
			gameObjects[i]:Update()
			if gameObjects[i]["alive"] == false then
				gameObjects[i] = nil
			end
		end
	end

    player0:update();
	engineAPI.EndUpdate();
end


function Render()
    renderManagerAPI.beginRender()
    --Lua render here

    --printAPI.print("Getting world matrix...\n");

    worldMatrix = luaVectorUtility.mat4_CreateIdentity(context.handle)

    --printAPI.print("Getting view matrix...\n");

    viewMatrix = cameraAPI.getViewMatrix(camera0, context.handle)

    --printAPI.print("Getting projection matrix...\n");

    projectionmatrix = cameraAPI.getProjectionMatrix(camera0, context.handle)
    
    --printAPI.print("Rendering...\n");

    --renderManagerAPI.render(worldMatrix,viewMatrix,projectionMatrix,time)
    --renderManagerAPI.renderFromCamera(camera0,time)
	renderManagerAPI.renderObject(camera0,time,Terrain01)
	renderManagerAPI.renderObject(camera0,time,giantPlant)
	renderManagerAPI.present()
    display2DAPI.drawFullScreen("faces.png")
    --printAPI.print("Render Successful\n");

    renderManagerAPI.endRender()
end

local status, err = pcall(Run)
if not status then
	printAPI.print(err)
end

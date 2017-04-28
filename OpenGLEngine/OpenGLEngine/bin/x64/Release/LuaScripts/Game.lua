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
]]
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
world = {}
debug = true
terrainSizeX = 1024
terrainSizeY = 1024
heightMapSize = 1024
heightMapHeight = 100

--SDL ScanCode list: https://wiki.libsdl.org/SDLScancodeLookup
SDL_SCANCODE_W = 26
SDL_SCANCODE_A = 4
SDL_SCANCODE_P = 19
SDL_SCANCODE_S = 22
SDL_SCANCODE_E = 8
SDL_SCANCODE_H = 11
SDL_SCANCODE_D = 7
SDL_SCANCODE_K = 14
SDL_SCANCODE_L = 15
SDL_SCANCODE_ESCAPE = 41
SDL_SCANCODE_Q = 20
SDL_SCANCODE_Z = 29
SDL_SCANCODE_X = 27
SDL_SCANCODE_M = 16
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
	printAPI.print('Loading Models...\n')
	modelLibraryAPI.addModel("Plant","Assets/Models/SmallPlant/SmallPlant.obj",false)
	--modelLibraryAPI.addModel("Horse","Assets/Models/Horse/horse.3ds",false)
	--modelLibraryAPI.addModel("Drone","Assets/Models/Drone/PA_drone.fbx",false)
	--modelLibraryAPI.addModel("Bomber","Assets/Models/Bomber/PA_ArchlightBomber.fbx",false)
	--modelLibraryAPI.addModel("DropPod","Assets/Models/DropPod/PA_DropPod.fbx",false)
	--modelLibraryAPI.addModel("Tank","Assets/Models/Tank/PA_ArchfireTank.fbx",false)
	--modelLibraryAPI.addModel("Warrior","Assets/Models/Warrior/PA_Warrior.fbx",false)
	--modelLibraryAPI.addModel("Rabbit","Assets/Models/Rabbit/rabbit.fbx",false)
	--modelLibraryAPI.addModel("Spider","Assets/Models/Spider/spider.fbx",false)
	--modelLibraryAPI.addModel("Cactus1","Assets/Models/DesertPlants/Cactus/cactus_01.FBX",false)BROKEN
	--modelLibraryAPI.addModel("Cactus2","Assets/Models/DesertPlants/Cactus/cactus_02.FBX",false)BROKEN
	--modelLibraryAPI.addModel("Cactus3","Assets/Models/DesertPlants/Cactus/cactus_01.FBX",false)BROKEN
	modelLibraryAPI.addModel("Rock","Assets/Models/Rocks/Boulder/Rock.obj",false)
	--modelLibraryAPI.addModel("Stone","Assets/Models/Rocks/SmallRock/stone.fbx",false)BROKEN
	modelLibraryAPI.addModel("Airship","Assets/Models/Airship/airship.lwo",false)
	--modelLibraryAPI.addModel("Cart","Assets/Models/Cart/Ox_Cart_FBX.fbx",false)
	--modelLibraryAPI.addModel("Saloon","Assets/Models/Saloon/saloon exterior-interior.obj",false)
	modelLibraryAPI.addModel("Bob","Assets/Models/Alfred.obj",false)
	modelLibraryAPI.addModel("Cactus","Assets/Models/Cactus1/cactus.obj",false)

	printAPI.print('Loading Terrain...\n')
	terrainHeightData = terrainAPI.generateTerrain(terrainSizeX, terrainSizeY, heightMapSize, heightMapHeight, "Assets/HeightMaps/testmap.png", "Assets/Models/Terrain/Terrain.obj", context.handle)	
	modelLibraryAPI.addModel("Terrain","Assets/Models/Terrain/Terrain.obj",false)

	printAPI.print('Loading Skybox...\n')
	modelLibraryAPI.addModel("Skybox","Assets/Models/SkyBox/skybox.obj",false)
end



function BBToLocal(bb,scalea,loca)
    bb.min = luaVectorUtility.vec3_Multiply(bb.min,scalea,context.handle)
    bb.min = luaVectorUtility.vec3_Sum(bb.min,loca,context.handle)
    bb.max = luaVectorUtility.vec3_Multiply(bb.max,scalea,context.handle)
    bb.max = luaVectorUtility.vec3_Sum(bb.max,loca,context.handle)

    if bb == null then
        printAPI.print('ERROR Tried to get null local AABB\n')
    end

    return bb
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

	printAPI.print('Initialising terrain...\n')
	skybox = luaObjInstManager.addNewInstance("Skybox")
	objectInstanceAPI.setTranslation(skybox, 0,0,0);
	objectInstanceAPI.setScale(skybox, 1000,1000,1000)
	Terrain01 = luaObjInstManager.addNewInstance("Terrain")
	objectInstanceAPI.setTranslation(Terrain01,0,0,0)

    printAPI.print('Initialising camera...\n')
    camera0 = cameraAPI.addNewInstance()
    cameraAPI.setPosition(camera0,terrainSizeX / 2, 30, terrainSizeY / 2)

    printAPI.print('Initialising rendermanager...\n')
    renderManagerAPI.initialise()

    printAPI.print('Initialising player...\n')
	player0 = Player:new()
	cameraAPI.setPosition(camera0,0,0,0)
    player0:setAABB(-0.5,0.5,-1.8,0,-0.5,0.5) 

	printAPI.print('Initialising Scenes...\n')
	local GOData = LoadInstances("SaveData/GO_Data.csv", "gameObject")
	local NPCData = LoadInstances("SaveData/NPC_Data.csv", "npc")
	local startPos = Vector3.new(0,0,0)
	local startDir = Vector3.new(0,0,0)
	scene = Scene.new("Level1", Terrain01, startPos, startDir)
	scene:AddInstances(GOData)
	scene:AddInstances(NPCData)
	scene:SetupInstances()
	local a = Vector3.new(0,0,0)
	local b = Vector3.new(1,1,1)
	scene:SpawnRandomObjects("Bob", a, b,100)
	world = World.new(player0)
	world:AddScene(scene)

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

    time = timeAPI.elapsedTimeMs()

    local quitIn = inputManagerAPI.isKeyDown(SDL_SCANCODE_X)
	if quitIn then
		printAPI.print("Quitting - pressed input to quit.\n")
        quitting = true
    end
    
    if(quitting) then
        if inputManagerAPI.isMousePressedLeft() then
            run = false
        end
    end

    local helpIn = inputManagerAPI.isKeyDown(SDL_SCANCODE_M)
	if helpIn then
        helpMenu = true
    end

    if helpMenu then
        if inputManagerAPI.isMousePressedLeft() then
            helpMenu = false
        end
    end

    if(inputManagerAPI.isKeyPressed(SDL_SCANCODE_K)) then
        if(wireindex ==0) then
            wireindex =1
        else
            wireindex =0
        end
    end

	e = inputManagerAPI.isKeyPressed(SDL_SCANCODE_E)
	if e then
		local newX = player0["position"]["x"] 
		local newZ = player0["position"]["z"]
		local newY = GetHeightAtPoint(newX , newZ)
		local xRotRand = math.random(360)
		local tempID = luaObjInstManager.addNewInstance("Bob")
		local objPosTemp = Vector3.new(newX, newY, newZ )
		local dirTemp = Vector3.new(xRotRand, 0, 0)
		local scaTemp = Vector3.new(1, 1, 1)

		local item = gameObject.new("Bob", "Bob", objPosTemp, dirTemp, scaTemp, 0, tempID)

		objectInstanceAPI.setTranslation(tempID, newX, newY, newZ)
		objectInstanceAPI.setOrientation(tempID,dirTemp.x,dirTemp.y,dirTemp.z)
		objectInstanceAPI.setScale(tempID,scaTemp.x,scaTemp.y,scaTemp.z)
		objectInstanceAPI.setAnimation(tempID,0)

		local nscale = objectInstanceAPI.getScale(tempID, context.handle)

        local abox = AABBAPI.getAABB(tempID, context.handle)
		abox.min = luaVectorUtility.vec3_Multiply(abox.min,nscale,context.handle)
		abox.max = luaVectorUtility.vec3_Multiply(abox.max,nscale,context.handle)
		item["boundingBox"] = abox

		world:AddInstance(item)
		renderManagerAPI.addObject(tempID)
	end

	if inputManagerAPI.isKeyPressed(SDL_SCANCODE_P) then
		local currentGOs = world:GetGameObjects()
		SaveInstances("SaveData/GO_Save.csv", world:GetGameObjects(), "gameObject")
		SaveInstances("SaveData/NPC_Save.csv", world:GetGameObjects(), "npc")
	end

	if inputManagerAPI.isKeyPressed(SDL_SCANCODE_L) then
		local currentScene = world:GetScene()

		currentScene:RemoveInstances()

		player0["position"]["x"] = 500
		player0["position"]["z"] = 500
		player0["position"]["y"] = GetHeightAtPoint(500 , 500)
		cameraAPI.setPosition(camera0,player0["position"]["x"],player0["position"]["y"],player0["position"]["z"]); 

		printAPI.print('Initialising objects...\n')
		local GOData = LoadInstances("SaveData/GO_Save.csv", "gameObject")
		local NPCData = LoadInstances("SaveData/NPC_Save.csv", "npc")

		world:AddInstances(GOData)
		world:AddInstances(NPCData)
		world:SetupInstances()
	end

	local currentGOs = world:GetGameObjects()
	for i = 1, world:GetGameObjectCount() do
		local a = currentGOs[i]:Update()
	end

    player0:update();
	engineAPI.EndUpdate();
end

function Render()
    renderManagerAPI.beginRender()

    renderManagerAPI.setFillMode(wireindex)

    if(quitting) then
        display2DAPI.drawFullScreen("faces.png")
    else
		if(helpMenu) then
			display2DAPI.drawFullScreen("rules.png")
		else
			local currentGOs = world:GetGameObjects()
			for i = 1, world:GetGameObjectCount() do
				renderManagerAPI.renderObject(camera0,time,currentGOs[i]["id"], 1)
			end

			local currentTerrainID = world:GetTerrainID()
			renderManagerAPI.renderObject(camera0,time,currentTerrainID, 1)

			--renderManagerAPI.render(worldMatrix,viewMatrix,projectionMatrix,time)
			--renderManagerAPI.renderFromCamera(camera0,time)
			--renderManagerAPI.renderObject(camera0,time,Terrain01, 1)
			renderManagerAPI.renderObject(camera0,time,skybox, 0)
			--renderManagerAPI.renderObject(camera0,time,cactus, 1)
			renderManagerAPI.present(camera0)
		end
	end

    renderManagerAPI.endRender()
end

local status, err = pcall(Run)
if not status then
	printAPI.print(err)
    read(1)
end

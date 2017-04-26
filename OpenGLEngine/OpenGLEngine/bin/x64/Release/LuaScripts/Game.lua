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

	terrainHeightData = terrainAPI.generateTerrain(terrainSizeX, terrainSizeY, heightMapSize, heightMapHeight, "Assets/HeightMaps/testmap.png", "Assets/Models/Terrain/Terrain.obj", context.handle)

	--terrainHeightData = terrainAPI.generateTerrain(terrainSizeX, terrainSizeY, heightMapSize, heightMapHeight, "Assets/HeightMaps/hmap.png", "Assets/Models/Terrain/Terrain.obj", context.handle)

		
	printAPI.print('terrain loaded\n')

	modelLibraryAPI.addModel("Terrain","Assets/Models/Terrain/Terrain.obj",false)


	
	printAPI.print('skybox loaded\n')

	modelLibraryAPI.addModel("Skybox","Assets/Models/SkyBox/skybox.obj",false)
	
	printAPI.print('cactus loaded\n')

	modelLibraryAPI.addModel("Cactus1","Assets/Models/Cactus1/cactus.obj",false)

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
	
    printAPI.print('Initialising objects...\n')
	LoadInstances("SaveData/GO_Data.csv", "gameObject")
	LoadInstances("SaveData/NPC_Data.csv", "npc")

	printAPI.print('Data Loaded...\n')
	local numRows = 0
	for k,v in next, gameObjects do 
		numRows = numRows + 1
        end

	for i = 1, numRows do
		if(gameObjects[i]["position"]["Y"] == 0) then
			gameObjects[i]["position"]["Y"] = GetHeightAtPoint(gameObjects[i]["position"]["X"] , gameObjects[i]["position"]["Z"])
		end
        local gid = gameObjects[i]["id"]

		objectInstanceAPI.setTranslation(gameObjects[i]["id"],gameObjects[i]["position"]["X"],gameObjects[i]["position"]["Y"],gameObjects[i]["position"]["Z"])
	
        local nscale = objectInstanceAPI.getScale(gid, context.handle)
        local nloc = objectInstanceAPI.getTranslation(gid, context.handle)
        local abox = AABBAPI.getAABB(gid, context.handle)
        gameObjects[i]["boundingbox"] = BBToLocal(abox,nscale,nloc)

        -- Set uniform scale for the NPCs
        --[[
        if(gameObjects[i]["model"]=="Bob") then
            --objectInstanceAPI.setRotation(gameObjects[i]["id"],0,-90,0)
            --objectInstanceAPI.setScale(gameObjects[i]["id"],1,1,1)
            objectInstanceAPI.setTranslation(gameObjects[i]["id"],nloc.x,nloc.y+2,nloc.z)
        end
        ]]
    end
    printAPI.print('Data Loaded...\n')


	for k = 0, 50 do
		local xRand = math.random(5, terrainSizeX - 5)
		local zRand = math.random(5, terrainSizeY - 5)
		local xRotRand = math.random(360)
		local yRand = GetHeightAtPoint(xRand , zRand)
		local tempID = luaObjInstManager.addNewInstance("Plant")
		local objPosTemp = Vector3.new(xRand, yRand, zRand )
		local dirTemp = Vector3.new(xRotRand, 0, 0)
		local scaTemp = Vector3.new(1, 1, 1)

		item = gameObject.new("Plant", "Plant", objPosTemp, dirTemp, scaTemp, 0, tempID)
        
		objectInstanceAPI.setTranslation(tempID, xRand, yRand, zRand)

        
        local nscale = objectInstanceAPI.getScale(tempID, context.handle)
        local nloc = objectInstanceAPI.getTranslation(tempID, context.handle)
        local abox = AABBAPI.getAABB(tempID, context.handle)

        item["boundingbox"] = BBToLocal(abox,nscale,nloc)

		table.insert(gameObjects, item)
	end

        	printAPI.print('Data Loaded...\n')

	skybox = luaObjInstManager.addNewInstance("Skybox")
	objectInstanceAPI.setTranslation(skybox, 0,0,0);
	objectInstanceAPI.setScale(skybox, 1000,1000,1000)
        	printAPI.print('Data Loaded...\n')

	cactus = luaObjInstManager.addNewInstance("Cactus1")
	objectInstanceAPI.setTranslation(cactus, 15,45,15)
	printAPI.print('Initialising terrain...\n')

	Terrain01 = luaObjInstManager.addNewInstance("Terrain")
	objectInstanceAPI.setTranslation(Terrain01,0,0,0)
    
    printAPI.print('Initialising AABBs...\n')

    printAPI.print('Initialising camera...\n')
    camera0 = cameraAPI.addNewInstance()
    cameraAPI.setPosition(camera0,terrainSizeX / 2, 30, terrainSizeY / 2)

    printAPI.print('Initialising rendermanager...\n')
    renderManagerAPI.initialise()

    printAPI.print('Initialising player...\n')
	player0 = Player:new()
	cameraAPI.setPosition(camera0,0,0,0)
    player0:setAABB(-0.5,0.5,-1.8,0,-0.5,0.5) 

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
    --printAPI.print("Updating...\n");
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
        --printAPI.print("helpmenu1...\n");

    local helpIn = inputManagerAPI.isKeyDown(SDL_SCANCODE_M)
	if helpIn then
        helpMenu = true
    end
            --printAPI.print("helpmenu2...\n");

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
		local newX = player0["pos"]["x"] 
		local newZ = player0["pos"]["z"]
		local newY = GetHeightAtPoint(newX , newZ)
		local xRotRand = math.random(360)
		local tempID = luaObjInstManager.addNewInstance("Bob")
		local objPosTemp = Vector3.new(newX, newY, newZ )
		local dirTemp = Vector3.new(xRotRand, 270, 0)
		local scaTemp = Vector3.new(0.1, 0.1, 0.1)

		local item = gameObject.new("Bob", "Bob", objPosTemp, dirTemp, scaTemp, 0, tempID)



		local nscale = objectInstanceAPI.getScale(tempID, context.handle)
        local nloc = objectInstanceAPI.getTranslation(tempID, context.handle)
        local abox = AABBAPI.getAABB(tempID, context.handle)
		item["boundingbox"] = BBToLocal(abox,nscale,nloc)

		table.insert(gameObjects, item)
		objectInstanceAPI.setTranslation(tempID, newX, newY, newZ)
		objectInstanceAPI.setOrientation(tempID,dirTemp.X,dirTemp.Y,dirTemp.Z)
		objectInstanceAPI.setScale(tempID,scaTemp.X,scaTemp.Y,scaTemp.Z)
		objectInstanceAPI.setAnimation(tempID,0)
		renderManagerAPI.addObject(tempID)


	end
    
                --printAPI.print("p..\n");

	if inputManagerAPI.isKeyPressed(SDL_SCANCODE_P) then
		SaveInstances("SaveData/GO_Save.csv", gameObjects, "gameObject")
		SaveInstances("SaveData/NPC_Save.csv", gameObjects, "npc")
	end

                --printAPI.print("l..\n");
                

	if inputManagerAPI.isKeyPressed(SDL_SCANCODE_L) then
		local numRows = 0
		for k,v in next, gameObjects do 
			numRows = numRows + 1
		end

		for i = 1, numRows do
			 gameObjects[i] = nil
		end

		player0["pos"]["x"] = 500
		player0["pos"]["z"] = 500
		player0["pos"]["y"] = GetHeightAtPoint(500 , 500)

		printAPI.print('Initialising objects...\n')
		LoadInstances("SaveData/GO_Save.csv", "gameObject")
		LoadInstances("SaveData/NPC_Save.csv", "npc")

		for k,v in next, gameObjects do 
			numRows = numRows + 1
		end

		for i = 1, numRows do
			if(gameObjects[i]["position"]["Y"] == 0) then
				gameObjects[i]["position"]["Y"] = GetHeightAtPoint(gameObjects[i]["position"]["X"] , gameObjects[i]["position"]["Z"])
			end
			local gid = gameObjects[i]["id"]

			objectInstanceAPI.setTranslation(gameObjects[i]["id"],gameObjects[i]["position"]["X"],gameObjects[i]["position"]["Y"],gameObjects[i]["position"]["Z"])
	
			local nscale = objectInstanceAPI.getScale(gid, context.handle)
			local nloc = objectInstanceAPI.getTranslation(gid, context.handle)
			local abox = AABBAPI.getAABB(gid, context.handle)
			gameObjects[i]["boundingbox"] = BBToLocal(abox,nscale,nloc)
		end
	end


    --printAPI.print("checkdeath..\n");

	
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

        --printAPI.print("playerupdate..\n");

    player0:update();
	engineAPI.EndUpdate();
        --printAPI.print("update complete..\n");


end


function Render()
    renderManagerAPI.beginRender()
    
    --printAPI.print("Rendering...\n");

    renderManagerAPI.setFillMode(wireindex)

	local numRows = 0
	for k,v in next, gameObjects do 
		numRows = numRows + 1
	end
	for i = 1, numRows do
		renderManagerAPI.renderObject(camera0,time,gameObjects[i]["id"], 1)
	end

    
	renderManagerAPI.renderObject(camera0,time,Terrain01, 1)

    --renderManagerAPI.render(worldMatrix,viewMatrix,projectionMatrix,time)
    --renderManagerAPI.renderFromCamera(camera0,time)
	renderManagerAPI.renderObject(camera0,time,Terrain01, 1)
	renderManagerAPI.renderObject(camera0,time,skybox, 0)
	--renderManagerAPI.renderObject(camera0,time,cactus, 1)
	renderManagerAPI.present(camera0)

    if(quitting) then
        display2DAPI.drawFullScreen("faces.png")
    end

    if(helpMenu) then
        display2DAPI.drawFullScreen("rules.png")
    end
    --printAPI.print("Render Successful\n");

    renderManagerAPI.endRender()
end

local status, err = pcall(Run)
if not status then
	printAPI.print(err)
    read(1)
end

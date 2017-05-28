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

<<<<<<< HEAD
--GetAPI(context.handle, 'printAPI', 'printAPI')
=======
>>>>>>> 36947cce270eff9264ef4a438bd106f1a7a57b9e
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
dofile '../Assets/Scripts/ReadAndWriteData.lua'
dofile '../Assets/Scripts/Terrain.lua'
dofile '../Assets/Scripts/Controls.lua'
dofile '../Assets/Scripts/QuestManager.lua'
dofile '../Assets/Scripts/Menu.lua'

OPEN_GL = 0

gameObjects = {}
world = {}
debug = true
debugdetail = false
loadSmallTestTerrain = true

time = 0
lastTime = 0
deltaTime = 0


function Run()
	Initialize()
	GameLoop()
	Finalize()
end

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

	--modelLibraryAPI.addModel("Plant","../Assets/Models/SmallPlant/SmallPlant.obj",false)
	--modelLibraryAPI.addModel("Horse","../Assets/Models/Horse/horse.3ds",false)
	--modelLibraryAPI.addModel("Drone","../Assets/Models/Drone/PA_drone.fbx",false)
	--modelLibraryAPI.addModel("Bomber","../Assets/Models/Bomber/PA_ArchlightBomber.fbx",false)
	--modelLibraryAPI.addModel("DropPod","../Assets/Models/DropPod/PA_DropPod.fbx",false)
	--modelLibraryAPI.addModel("Tank","../Assets/Models/Tank/PA_ArchfireTank.fbx",false)
	--modelLibraryAPI.addModel("Warrior","../Assets/Models/Warrior/PA_Warrior.fbx",false)
	--modelLibraryAPI.addModel("Rabbit","../Assets/Models/Rabbit/rabbit.fbx",false)
	--modelLibraryAPI.addModel("Spider","../Assets/Models/Spider/spider.fbx",false)
	--modelLibraryAPI.addModel("Cactus1","../Assets/Models/DesertPlants/Cactus/cactus_01.FBX",false)BROKEN
	--modelLibraryAPI.addModel("Cactus2","../Assets/Models/DesertPlants/Cactus/cactus_02.FBX",false)BROKEN
	--modelLibraryAPI.addModel("Cactus3","../Assets/Models/DesertPlants/Cactus/cactus_01.FBX",false)BROKEN

    modelLibraryAPI.addModel("Warrior","../Assets/Models/Characters/PA_SciFiCombatants/PA_SciFiCombatants/_Imported3D/Characters/lizabc.FBX",false)
    modelLibraryAPI.addModel("CaveDoor","../Assets/Models/Liz_Dungeons/CAVEDOOR.obj",false)

    modelLibraryAPI.addModel("Dungeon1Interior","../Assets/Models/Liz_Dungeons/Dungeon1Interior.obj",false)
    modelLibraryAPI.addModel("Dungeon1InteriorEntrance","../Assets/Models/Liz_Dungeons/Dungeon1InteriorEntrance.obj",false)

    modelLibraryAPI.addModel("btnContinue",.."/Assets/Models/UI/continue.obj",false)
    modelLibraryAPI.addModel("btnNewGame",.."/Assets/Models/UI/newgame.obj",false)
    modelLibraryAPI.addModel("btnLoad",.."/Assets/Models/UI/load.obj",false)
    modelLibraryAPI.addModel("btnSave",.."/Assets/Models/UI/save.obj",false)
    modelLibraryAPI.addModel("btnGame1",.."/Assets/Models/UI/game1.obj",false)
    modelLibraryAPI.addModel("btnGame2",.."/Assets/Models/UI/game2.obj",false)
    modelLibraryAPI.addModel("btnGame3",.."/Assets/Models/UI/game3.obj",false)
    modelLibraryAPI.addModel("WhiteCube",.."/Assets/Models/UI/whiteCube.obj",false)



	modelLibraryAPI.addModel("Rock","../Assets/Models/Rocks/Boulder/Rock.obj",false)
	--modelLibraryAPI.addModel("Stone","../Assets/Models/Rocks/SmallRock/stone.fbx",false)BROKEN

	modelLibraryAPI.addModel("Airship","../Assets/Models/Airship/airship.lwo",false)
	modelLibraryAPI.addModel("Skybox","../Assets/Models/SkyBox/skybox.obj",false)
	modelLibraryAPI.addModel("Bob","../Assets/Models/Alfred.obj",false)
	modelLibraryAPI.addModel("Cactus","../Assets/Models/Cactus1/cactus.obj",false)

	printAPI.print('Loading Terrain...\n')

    if loadSmallTestTerrain then
        hMapPath = "../Assets/HeightMaps/heightmap.png"
        terrainSizeX = 1024
        terrainSizeY = 1024
        heightMapSize = 257
        heightMapHeight = 100
    else
        hMapPath = "../Assets/HeightMaps/testmap.png"
        terrainSizeX = 1024
        terrainSizeY = 1024
        heightMapSize = 1024
        heightMapHeight = 100
    end



	terrainHeightData = terrainAPI.generateTerrain(terrainSizeX, terrainSizeY, heightMapSize, heightMapHeight, hMapPath , "../Assets/Models/Terrain/Terrain.obj", context.handle)	
	modelLibraryAPI.addModel("Terrain","../Assets/Models/Terrain/Terrain.obj",false)

	printAPI.print('Loading Skybox...\n')

end



function BBToLocal(bb,scalea,loca)
    bb.min = mmath.vec3_Multiply(bb.min,scalea,context.handle)
    bb.min = mmath.vec3_Sum(bb.min,loca,context.handle)
    bb.max = mmath.vec3_Multiply(bb.max,scalea,context.handle)
    bb.max = mmath.vec3_Sum(bb.max,loca,context.handle)

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
	wireindex = 1

	printAPI.print('Creating...\n')
	engineAPI.Initialise(1280,720);

	printAPI.print('Loading Assets...\n')
	LoadAssets()


    printAPI.print("Initialising text...\n")
    lookAtText = " "
    dialogueText = " "
    dInMenu = false
    dCurrentTopic = nil
    dCurrentLine = 0



    -- Initialise scene objects
	printAPI.print('Initialising Scenes...\n')
	local GOData = LoadInstances("../SaveData/GO_Data.csv", "gameObject")
	local NPCData = LoadInstances("../SaveData/NPC_Data.csv", "npc")
	local startPos = Vector3.new(0,0,0)
	local startDir = Vector3.new(0,0,0)
	scene = Scene.new("Level1", Terrain01, startPos, startDir)

    scene2 = Scene.new("Level2", Terrain01, startPos, startDir)


	scene:AddInstances(GOData)
	scene:AddInstances(NPCData)

    
    local loc = {x=20,y=0,z=20}
    local scale = {x=1,y=1,z=1}
    local dir = {x=0,y=1,z=0}


    Dungeon1Door = gameObject.new("Dungeon1Door","Cave Door to The Observatory","CaveDoor",loc,dir,scale,0)
    scene:AddInstance(Dungeon1Door)

    loc = {x=0,y=0,z=0}
    Dungeon1Intr = gameObject.new("Dungeon1","The Observatory","Dungeon1Interior",loc,dir,scale,0)
    scene2:AddInstance(Dungeon1Intr);

    Dungeon1IntrDoor = gameObject.new("Dungeon1IntrDoor","The Observatory","Dungeon1InteriorEntrance",loc,dir,scale,0)
    scene2:AddInstance(Dungeon1IntrDoor);


    

    currentScene = scene

	local a = Vector3.new(0,0,0)
	local b = Vector3.new(1,1,1)

    loc = {x=40,y=0,z=40}
    scale = {x=10,y=10,z=10}
    dir = {x=0,y=1,z=0}

    local emptyVec = mmath.vec3_CreateEmpty(context.handle)

    NPC01 = npc.new("NPC01","Bob the Human","Warrior",loc,dir,scale,0,100,100)
    NPC01.hurtAnim = 4
    local upVector = {x=0,y=1,z=0}
    NPC01.upVector = upVector
    local diag = Dialogue.new()
    local topic01 = Topic.new("Greeting","Greeting")
    topic01.questEvent = true
    local topic02 = Topic.new("Quest1","Help find organs")

    local mylines = {}
    mylines[1] = "line 1\n"
    mylines[2] = "line 2\n"
    mylines[3] = "line 3\n"

    topic01:setLines(mylines)

    local mylines2 = {}
    mylines2[1] = "t2line 1\n"
    mylines2[2] = "t2line 2\n"
    mylines2[3] = "t2line 3\n"

    topic02:setLines(mylines2)

    diag:addTopic(topic01)
    diag:addTopic(topic02)

    NPC01.dialogue = diag
    NPC01:setDialogue(diag)

    NPC01:makeIdle()


    scene:AddInstance(NPC01) 


	--scene:SpawnRandomObjects("Bob", a, b,100)


    emptyVec = {x=0,y=0,z=0}
    scale = {x=10,y=10,z=10}
    

	world = World.new(player0)



	printAPI.print('Initialising terrain...\n')

	Terrain01 = luaObjInstManager.addNewInstance("Terrain")

	--wont work

	objectInstanceAPI.setTranslation(Terrain01,0,0,0)
	scene:SetTerrain(Terrain01)
	world:AddScene(scene)
    world:AddScene(scene2)

	skybox = luaObjInstManager.addNewInstance("Skybox")

	--wont work

	objectInstanceAPI.setTranslation(skybox, 0,0,0);

	--wont work

	objectInstanceAPI.setScale(skybox, 1000,1000,1000)

	--wont work

	--Wont work

    printAPI.print('Initialising camera...\n')
    camera0 = cameraAPI.addNewInstance()
    cameraAPI.setPosition(camera0,terrainSizeX / 2, 30, terrainSizeY / 2)

    printAPI.print('Initialising rendermanager...\n')
    --renderManagerAPI.initialise()

    printAPI.print('Initialising player...\n')
	player0 = Player:new(camera0,100,100)
	cameraAPI.setPosition(camera0,0,0,0)
	cameraAPI.setYaw(camera0,225)
	cameraAPI.setPitch(camera0,0)
    player0:setAABB(-0.5,0.5,-1.8,0,-0.5,0.5) 

	--test = luaObjInstManager.addNewInstance("Bob")

    -- Initialise weapon

    basicGun = Weapon.new("basicGun","Gun",1,1)
    player0:setWeapon(basicGun)

    
    --Initialise quests
    questManager = QuestManager.new()
    local stage1 = QuestStage.new("MeetBob",TALK,"NPC01","Greeting")
    local stage2 = QuestStage.new("GetQuest",TALK,"NPC01","Quest1")

    local stages = {stage1,stage2}
    local talkToBob = Quest.new("TalkToBob",stages,2)
    questManager:addQuest(talkToBob)
	LoadQuests("../SaveData/QUE_Data.csv")
	initMenu()
	
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

function StartDialogueTopic(playr,topicn)

    if(playr.inDialogue) then
        local topic = playr.lookTarget.dialogue.topics[topicn]
        if(topic ~= nil and topic.textLines ~= nil and topic.textLines[topicn] ~= nil) then
            dialogueText = topic.textLines[topicn]
            dCurrentTopic = topic
            dCurrentLine = 1
            dInMenu = false

            if topic.questEvent then
                questManager:check(TALK,playr.lookTarget,topic.id)
            end

        else
            debugLPrint("Could not start that topic.\n")
        end
    end
end

function Update()
	--printAPI.print("Update begun\n")

    engineAPI.BeginUpdate()
	lastTime = time
    time = timeAPI.elapsedTimeMs()
	deltaTime = time - lastTime
	
    if(quitting) then
        if inputManagerAPI.isMousePressedLeft() then
            run = false
        end
    end
	
	if(inputManagerAPI.isKeyPressed(Menu_Input)) then
        if(inMenu == false) then
            inMenu = true
			preCameraPos = player0:getPosition()
			printVec3(preCameraPos)
			preCameraYaw = cameraAPI.getYaw(camera0,context.handle)
			preCameraPitch = cameraAPI.getPitch(camera0,context.handle)
			
			cameraAPI.setPosition(camera0,0,10,0)
			cameraAPI.setYaw(camera0,180)
			cameraAPI.setPitch(camera0,0)
			changeMenu(0)
        else
            inMenu = false
			cameraAPI.setPosition(camera0,preCameraPos.x,preCameraPos.y,preCameraPos.z)
			cameraAPI.setYaw(camera0,preCameraYaw)
			cameraAPI.setPitch(camera0,preCameraPitch)
        end
    end
	
	if(inMenu) then
	
	else
    local quitIn = inputManagerAPI.isKeyDown(Exit_Input)
	if quitIn then
		printAPI.print("Quitting - pressed input to quit.\n")
        quitting = true
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

    --printAPI.print("Processing inputs\n")

	e = inputManagerAPI.isKeyPressed(Use_Input)
	if e then
        printAPI.print("Interacting.\n")

        
        if(player0.lookTarget ~= nil) then

            StartDialogue(player0.lookTarget)

            if(player0.lookTarget.stringID == "Dungeon1Door") then
                printAPI.print("Entering dungeon 1.\n")
                world:enterScene(scene2.name)
                player0.trackTerrain = true
                player0.position = {x=0,y=50,z=0}

                hMapPath = "../Assets/HeightMaps/flatmaphigh.png"
                terrainSizeX = 1024
                terrainSizeY = 1024
                heightMapSize = 256
                heightMapHeight = 35
	            terrainHeightData = terrainAPI.generateTerrain(terrainSizeX, terrainSizeY, heightMapSize, heightMapHeight, hMapPath , "../Assets/Models/Terrain/Terrain.obj", context.handle)	
	

            end
        end
        
        
	end

    if inputManagerAPI.isKeyPressed(QuickSlot1_Input) then

        StartDialogueTopic(player0,1)
        
    end
    if inputManagerAPI.isKeyPressed(QuickSlot2_Input) then

        StartDialogueTopic(player0,2)
        
    end
    if inputManagerAPI.isKeyPressed(QuickSlot3_Input) then

        StartDialogueTopic(player0,3)
        
    end
    if inputManagerAPI.isKeyPressed(QuickSlot4_Input) then

        StartDialogueTopic(player0,4)
        
    end
    if inputManagerAPI.isKeyPressed(QuickSlot5_Input) then

        StartDialogueTopic(player0,5)
        
    end
    if inputManagerAPI.isMousePressedLeft() then

        debugLPrint("Clicked LMB.\n")

        if(player0.inDialogue == false and player0.lookTarget ~= nil and player0.lookTarget.objType == "NPC") then
            if(player0.rangedWeaponEquipped and player0.lookTarget.hostileToPlayer) then
                    player0.weapon:attack(player0.lookTarget)
            
            end
        end




        if(player0.inDialogue == true and dInMenu == false) then
            if(dCurrentTopic.textLines[dCurrentLine+1] ~= nil) then
                dCurrentLine = dCurrentLine + 1
                dialogueText = dCurrentTopic.textLines[dCurrentLine]
                dInMenu = false

            else
                debugLPrint("Next line in topic is nil.\n")
                StartDialogue(player0.lookTarget)
            end
        else
            if(dInMenu) then
                    player0.inDialogue = false
            end
        end
    end

	if inputManagerAPI.isKeyPressed(Quicksave_Input) then
		local currentGOs = world:GetGameObjects()
		SaveInstances("../SaveData/GO_Save.csv", world:GetGameObjects(), "gameObject")
		SaveInstances("../SaveData/NPC_Save.csv", world:GetGameObjects(), "npc")
	end

	if inputManagerAPI.isKeyPressed(Quickload_Input) then
		local currentScene = world:GetScene()

		currentScene:RemoveInstances()

		player0["position"]["x"] = 500
		player0["position"]["z"] = 500
		player0["position"]["y"] = GetHeightAtPoint(500 , 500)
		cameraAPI.setPosition(camera0,player0["position"]["x"],player0["position"]["y"],player0["position"]["z"]); 

		printAPI.print('Initialising objects...\n')
		local GOData = LoadInstances("../SaveData/GO_Save.csv", "gameObject")
		local NPCData = LoadInstances("../SaveData/NPC_Save.csv", "npc")

		world:AddInstances(GOData)
		world:AddInstances(NPCData)
		world:SetupInstances()
	end

    if debug then

        if inputManagerAPI.isKeyPressed(SDL_SCANCODE_DELETE) then
            printAPI.print("Force quitting.\n")
            os.exit()

	    end
        if inputManagerAPI.isKeyPressed(TestInput1) then
            
            

	    end
    
        if inputManagerAPI.isKeyPressed(TestInput2) then
        
            TestChangeNPCState()

	    end
		
		if inputManagerAPI.isKeyPressed(TestInput3) then
		
		end
    
        if inputManagerAPI.isKeyPressed(TestInput3) then
            -- spawn bob
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
		    abox.min = mmath.vec3_Multiply(abox.min,nscale,context.handle)
		    abox.max = mmath.vec3_Multiply(abox.max,nscale,context.handle)
		    item["boundingBox"] = abox

		    world:AddInstance(item)
		    --renderManagerAPI.addObject(tempID)

	    end
    
        -- switch whether debug detail printing is on or off
        if inputManagerAPI.isKeyPressed(TestInput4) then
            if debugdetail == true then
                debugdetail = false
            else
                debugdetail = true
            end
	    end

    end

    
    --printAPI.print("Updating gameobjects\n")


	local currentGOs = world:GetGameObjects()
	for i = 1, world:GetGameObjectCount() do
        --printAPI.print(currentGOs[i].name .. "\n")
		local a = currentGOs[i]:Update()
	end
    --printAPI.print("Updating player\n")

    player0:update();
	end
	engineAPI.EndUpdate();
    --printAPI.print("Update complete\n")

end

font1path = "../Assets/Fonts/verdanab.ttf"
white = {x=1,y=1,z=1}


function TestChangeNPCState()
    printAPI.print("Test change NPC State.\n")
    NPC01:makeChasing()
end

function StartDialogue(npc)
    debugPrint("Starting Dialogue... ")
    if(npc ~= nil) then
        if(npc.dialogue ~= nil) then
    
            dInMenu= true
            local str = npc.name.."\n\nTopics: \n"
            local topics
            local count
            topics, count = npc:readTopics()
            for i=1,count do
                str = str .. topics[i]
            end

            dialogueText = str

            player0.inDialogue = true

            dCurrentTopic = nil
            debugPrint("Complete\n")
        else
            debugPrint("NPC has no dialogue.\n")
        end
    end
    



end

function Render()
    renderManagerAPI.beginRender()

    renderManagerAPI.setFillMode(wireindex)

    if(quitting) then
        display2DAPI.drawFullScreen("faces.png")
    else
		if(inMenu) then
			updateMenu()
			renderManagerAPI.renderObject(camera0,time,Background.id, 1)
			renderManagerAPI.renderObject(camera0,time,MouseObject.id, 1)
			if ButtonOne.active then
				renderManagerAPI.renderObject(camera0,time,ButtonOne.id, 1)
			end
			if ButtonTwo.active then
				renderManagerAPI.renderObject(camera0,time,ButtonTwo.id, 1)
			end
			if ButtonThree.active then
				renderManagerAPI.renderObject(camera0,time,ButtonThree.id, 1)
			end
			if BackButton.active then
				renderManagerAPI.renderObject(camera0,time,BackButton.id, 1)
			end
			if StartNewButton.active then
				renderManagerAPI.renderObject(camera0,time,StartNewButton.id, 1)
			end
			if ContinueButton.active then
				renderManagerAPI.renderObject(camera0,time,ContinueButton.id, 1)
			end
			if SaveButton.active then
				renderManagerAPI.renderObject(camera0,time,SaveButton.id, 1)
			end	
			if LoadButton.active then
				renderManagerAPI.renderObject(camera0,time,LoadButton.id, 1)
			end
			if ExitButton.active then
				renderManagerAPI.renderObject(camera0,time,ExitButton.id, 1)
			end
			renderManagerAPI.present(camera0)
		else
			if(helpMenu) then
				display2DAPI.drawFullScreen("rules.png")
			else

				-- Draw object
				local currentGOs = world:GetGameObjects()
				for i = 1, world:GetGameObjectCount() do
					if(currentGOs[i].visible) then
						renderManagerAPI.renderObject(camera0,time,currentGOs[i]["id"], 1)
					end
				end
				local currentTerrainID = world:GetTerrainID()
				renderManagerAPI.renderObject(camera0,time,currentTerrainID, 1)

				renderManagerAPI.renderObject(camera0,time,skybox, 0)
				renderManagerAPI.present(camera0)

				
				-- Draw UI text
				--display2DAPI.drawText(10,font1path,lookAtText,100,300,white)

				if(player0.inDialogue) then 
					--display2DAPI.drawText(10,font1path,dialogueText,200,300,white)
				end

			end
		end
	end


    renderManagerAPI.endRender()
end

local status, err = pcall(Run)
if not status then
	printAPI.print(err)
    read(1)
end

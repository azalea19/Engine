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
local Weapon = dofile '../Assets/Scripts/Weapon.lua'

--local QuestManager = require '../Assets/Scripts/QuestManager'
dofile '../Assets/Scripts/Dialogue.lua'
dofile '../Assets/Scripts/FileIO.lua'
dofile '../Assets/Scripts/ReadAndWriteData.lua'
dofile '../Assets/Scripts/Terrain.lua'
dofile '../Assets/Scripts/Controls.lua'
dofile '../Assets/Scripts/QuestManager.lua'
dofile '../Assets/Scripts/Menu.lua'
dofile '../Assets/Scripts/Load.lua'
dofile '../Assets/Scripts/GameWorld.lua'



OPEN_GL = 0

gameObjects = {}
world = {}
weaponList = {}
debug = true
debugdetail = false

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
    screenWidth = 1280
    screenHeight = 720
	engineAPI.Initialise(screenWidth,screenHeight);

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
	scene = Scene.new("Level1", startPos, startDir)
    scene2 = Scene.new("Level2", startPos, startDir)
	scene:AddInstances(GOData)
	scene:AddInstances(NPCData)
	for y = 1, worldWidthChunks, 1 do
		for x = 1, worldWidthChunks, 1 do
			--modelLibraryAPI.addModel("Terrain_" .. x .. "_" .. y,"../Assets/Models/Terrain/Terrain_" .. x .. "_" .. y .. ".obj",false)
			local terrainChunckID = luaObjInstManager.addNewInstance("Terrain_" .. x .. "_" .. y)
			objectInstanceAPI.setTranslation(terrainChunckID,(x - 1) * wsChunkSize,0,(y - 1) * wsChunkSize)
			objectInstanceAPI.setOrientation(terrainChunckID,0,0,0)
			objectInstanceAPI.setScale(terrainChunckID,1,1,1)
			objectInstanceAPI.setAnimation(terrainChunckID,0)
			table.insert(scene.terrainChunks, terrainChunckID)
		end
	end
    
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

    loc = {x=1100,y=0,z=1100}
    scale = {x=0.5,y=0.5,z=0.5}
    dir = {x=0,y=1,z=0}

    local emptyVec = mmath.vec3_CreateEmpty(context.handle)

    NPC01 = npc.new("NPC01","Bob the Human","Bob",loc,dir,scale,0,100,100)
    local anim = {"Section",0,5}
    local anim2 = {"Section",0,10}
    NPC01.defaultAnim = anim2
    NPC01.hurtAnim = {"Section",0,5}
    NPC01:setAnimation(anim2)
    objectInstanceAPI.setBaseTransform(NPC01.id, Vector3.new(0, 0.1, 0), 180, -90, 0, Vector3.new(1, 1, 1))

    --NPC01.hurtAnim = 4
    local upVector = {x=0,y=1,z=0}
    NPC01.upVector = upVector
    local diag = Dialogue.new()

    local quest1 = Topic.new("Quest1","I need my organs back")
    local mylines = {}
    mylines[1] = "Yes, yes, I know, it's terrible – having that foul industry stealing your organs and replacing them with barely-working, recycled pieces of scrap metal..."
    mylines[2] = "Listen, I can help you with your eyes – there's a nearby observatory that I hear has some equipment of interest to me, but it's far too dangerous to go myself."
    mylines[3] = "If you can bring back anything high-tech you find there, I'll happily repair your eyes."

    quest1:setLines(mylines)
    
    local greeting = Topic.new("Greeting","Greeting")
    local mylines2 = {}
    mylines2[1] = "Oh, it's you. I heard you came a long way to get here."

    greeting:setLines(mylines2)

    -- USE THE SCIFI BOX MODEL PLACE IT IN THE OBSERVATORY INTERIOR



    local quest1 = Topic.new("Quest1Return","I have something from the observatory.")
    local mylines = {}
    mylines[1] = "Yes, yes, I know, it's terrible – having that foul industry stealing your organs and replacing them with barely-working, recycled pieces of scrap metal..."
    mylines[2] = "Listen, I can help you with your eyes – there's a nearby observatory that I hear has some equipment of interest to me, but it's far too dangerous to go myself."
    mylines[3] = "If you can bring back anything high-tech you find there, I'll happily repair your eyes."

    quest1:setLines(mylines)

    local quest1return = Topic.new("Quest1Return","I have something from the observatory.")
    local mylines = {}
    mylines[1] = "Oh, excellent! Come right this way, I'll fix your eyes up for you."

    quest1return:setLines(mylines)
    

    local quest2 = Topic.new("Quest1Return","What about my lungs? My heart?")
    local mylines = {}
    mylines[1] = "You don't quit, do you... While you were gone, the nearby raiders tried to launch another attack. I am too busy helping these people to fix your faulty cybernetics."
    mylines[2] = "Look, the raiders came from an airship north of here. Tell you what, if you can kill their leader and force them to retreat, I'll happily repair the rest of your organs."

    quest2:setLines(mylines)
    

    local quest2return = Topic.new("Quest2Return","I killed their leader.")
    local mylines = {}
    mylines[1] = "What, really? Good on you! Excellent! Thank you so much! For a while at least, the people of this town will no longer have to suffer and fear when the next raid will come."
    mylines[2] = "Please, come with me, I'll fix the rest of your organs for you"

    quest2return:setLines(mylines)
    
    

    quest1.questEvent = true
    quest2.questEvent = true
    quest1return.questEvent = true
    quest2return.questEvent = true



    diag:addTopic(greeting)
    diag:addTopic(quest1)
    diag:addTopic(quest2)
    diag:addTopic(quest1return)
    diag:addTopic(quest2return)

    NPC01.dialogue = diag
    NPC01:setDialogue(diag)


    NPC01:makeIdle()


    scene:AddInstance(NPC01) 

    
    --Initialise quests
    questManager = QuestManager.new()
    local stage1 = QuestStage.new("ObsGetQuest",TALK,"NPC01","Quest1")
    local stage2 = QuestStage.new("ObsGetTech",GET,"ObsTech")
    local stage3 = QuestStage.new("ObsReturn",TALK,"NPC01","Quest1Return")

    local stage4 = QuestStage.new("AirGetQuest",TALK,"NPC01","Quest2")
    local stage5 = QuestStage.new("AirKillBoss",KILL,"Boss")
    local stage6 = QuestStage.new("AirReturn",TALK,"NPC01","Quest2Return")
    

    local stages = {stage1,stage2,stage3,stage4,stage5,stage6}
    local talkToBob = Quest.new("TalkToBob",stages,6)
    questManager:addQuest(talkToBob)

	LoadQuests("../SaveData/QUE_Data.csv")

    
    loc = {x=900,y=0,z=900}
    scale = {x=25,y=25,z=25}
    dir = {x=0,y=1,z=0}
    boss = npc.new("Boss","Boss","Warrior",loc,dir,scale,0,200,200)




    emptyVec = {x=0,y=0,z=0}
    scale = {x=10,y=10,z=10}
    

	world = World.new(player0)



	printAPI.print('Initialising terrain...\n')

	CreateTerrain(scene)
	CreateCactusField(scene)
	CreateTown(scene)

	--objectInstanceAPI.setTranslation(Terrain01,0,0,0)
	--scene:SetTerrain(Terrain01)
	world:AddScene(scene)
    world:AddScene(scene2)

	skybox = luaObjInstManager.addNewInstance("Skybox")
	objectInstanceAPI.setTranslation(skybox, 0,0,0);
	objectInstanceAPI.setScale(skybox, 10000,10000,10000)
	--function gameObject.new(strID, newName, newModel, newPos, newDir, newScale, newAnim)

	titan = gameObject.new("titan","Titan","Titan",Vector3.new(500,0,1500),Vector3.new(0,0,0),Vector3.new(1,1,1),0)
	scene:AddInstance(titan)

    printAPI.print('Initialising camera...\n')
    camera0 = cameraAPI.addNewInstance()
    --cameraAPI.setPosition(camera0,terrainSizeX / 2, 30, terrainSizeY / 2)

    printAPI.print('Initialising rendermanager...\n')
    --renderManagerAPI.initialise()

    printAPI.print('Initialising player...\n')
	player0 = Player:new(camera0,100,100)

	player0:setPosition(Vector3.new(1000,0,1000))

    gun = gameObject.new("gun","Pistol","Pistol",player0.position,Vector3.new(0,0,0),Vector3.new(0.001,0.001,0.001),0)
    bullet = gameObject.new("bullet","Bullet","Bullet",Vector3.new(0,0,0),Vector3.new(0,0,0),Vector3.new(0.05,0.05,0.05),0)

    scene:AddInstance(gun)
    scene:AddInstance(bullet)



	--cameraAPI.setYaw(camera0,225)
	--cameraAPI.setPitch(camera0,0)
    player0:setAABB(-0.5,0.5,-1.8,0,-0.5,0.5) 

	--test = luaObjInstManager.addNewInstance("Bob")

    -- Initialise weapon

    basicGun = Weapon.new("basicGun","Gun",1,1)
	table.insert(weaponList,basicGun);
	
    player0:setWeapon("basicGun")

    


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
			--printVec3(preCameraPos)
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
                    --if(player0.weapon:attack(player0.lookTarget)) then
                        FireBullet()
                    --end
            
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
		--local currentGOs = world:GetGameObjects()
		saveAllToCurrentSave()
		--SaveInstances("../SaveData/GO_Save.csv", world:GetGameObjects(), "gameObject")
		--SaveInstances("../SaveData/NPC_Save.csv", world:GetGameObjects(), "npc")
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
		loadWeapons("../SaveData/WEAPON_Data.csv")
		loadPlayer("../SaveData/PLAYER_Data.csv", player0)
		questManager = QuestManager.new()
		LoadQuests("../SaveData/QUE_Data.csv")
		LoadTopics("../SaveData/DIA_Data.csv")
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

            --[[
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
            ]]

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
        --printAPI.print("Current GO: "..currentGOs[i].name .. "\n")
		local a = currentGOs[i]:Update()
	end
    --printAPI.print("Updating player\n")

    player0:update();
	end
	engineAPI.EndUpdate();
    --printAPI.print("Update complete\n")

    bullet:setPosition(MoveTowards(bullet:getPosition(),mmath.vec3_Sum(mmath.vec3_ScalarMultiply(cameraAPI.forward(camera0,context.handle), 1000,context.handle) ,player0:getPosition(),context.handle),10*deltaTime))

    gun:setPosition(player0.position)
    local pos = mmath.vec3_ScalarMultiply(cameraAPI.forward(camera0,context.handle),2,context.handle)
    local sum = mmath.vec3_Sum(player0.position, pos,context.handle)
    gun:lookAt(cameraAPI.forward(camera0,context.handle))


end

function FireBullet()

    local pos = mmath.vec3_ScalarMultiply(cameraAPI.forward(camera0,context.handle),2,context.handle)
    local sum = mmath.vec3_Sum(player0.position, pos,context.handle)
    bullet:setPosition(sum)
    bullet:lookAt(cameraAPI.forward(camera0,context.handle))

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
				--local currentTerrainID = world:GetTerrainID()


				local i
			for i = 1, #scene.terrainChunks, 1 do
				renderManagerAPI.renderObject(camera0,time,scene.terrainChunks[i], 1);
			end



				--renderManagerAPI.renderObject(camera0,time,currentTerrainID, 1)

				renderManagerAPI.renderObject(camera0,time,skybox, 0)
				renderManagerAPI.present(camera0)

				
				-- Draw UI text --DrawTextLua(int size, string const& filePath, string const& text, LuaRef pos, LuaRef color, int centered, int screenWidth, int screenHeight)
				display2DAPI.drawText(10,font1path,lookAtText,{x=100,y=300},white,0,screenWidth,screenHeight)

				if(player0.inDialogue) then 
					display2DAPI.drawText(10,font1path,dialogueText,{x=200,y=300},white,0,screenWidth,screenHeight)
				end

                hpDisplay = "Health: ".. player0.currentHealth .. " / " .. player0.maxHealth
                display2DAPI.drawText(10,font1path,hpDisplay,{x=400,y=100},white,0,screenWidth,screenHeight)


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

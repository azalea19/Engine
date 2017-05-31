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

difficulty = 1

local Vector3 = dofile '../Assets/Scripts/Vector3.lua'
local gameObject = dofile '../Assets/Scripts/gameObject.lua'
local AABoundingBox = dofile '../Assets/Scripts/AABoundingBox.lua'
local npc = dofile '../Assets/Scripts/npc.lua'
local Player = dofile '../Assets/Scripts/Player.lua'
local Scene = dofile '../Assets/Scripts/Scene.lua'
local World = dofile '../Assets/Scripts/World.lua'
local Weapon = dofile '../Assets/Scripts/Weapon.lua'
local ParticleEmitter = dofile "../Assets/Scripts/ParticleEmitter.lua"
local WaterParticle = dofile "../Assets/Scripts/Particle.lua"

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


collisionObjects = {}
collisionsEnabled = true
collisionTreeCreated = false

gameObjects = {}
world = {}
weaponList = {}
debug = true
debugdetail = trfalseue
playerInScene = 1

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

function printVec3(veca)
    printAPI.print(veca.x .. "," .. veca.y .. "," .. veca.z .. "\n")
end

function printVec3After(string,veca)
    printAPI.print(string)
    printVec3(veca)

end

function printVec3s(vecc,vecb)
    printAPI.print(vecc.x .. "," .. vecc.y .. "," .. vecc.z .. " // " .. vecb.x .. "," .. vecb.y .. "," .. vecb.z .. "\n")
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

function InitScene1(goPath, npcPath, diff)

 -- Initialise scene objects
	printAPI.print('Initialising Scenes...\n')
	local GOData = LoadInstances(goPath, "gameObject",difficulty)
	local NPCData = LoadInstances(npcPath, "npc",difficulty)
	local startPos = Vector3.new(0,0,0)
	local startDir = Vector3.new(0,0,0)
	scene = Scene.new("Level1", startPos, startDir)
    
	scene:AddInstances(GOData)
	scene:AddInstances(NPCData)

    local loc = {x=1100,y=0,z=1000}
    local scale = {x=10,y=10,z=10}
    local dir = {x=0,y=1,z=0}

	if(scene:FindInstance("Dungeon1Door") == false) then

		loc = Vector3.new(1500,0,1500)
		scale = {x=0.1,y=0.1,z=0.1}
		obs = gameObject.new("Observatory","Observatory","COL_Observatory",loc,dir,scale,0)
		scene:AddInstance(obs)
	end

	currentScene = scene

	local a = Vector3.new(0,0,0)
	local b = Vector3.new(1,1,1)

	local loc = {x=1100,y=0,z=1100}
	local scale = {x=0.1,y=0.1,z=0.1}
	local dir = {x=0,y=1,z=0}

	local emptyVec = mmath.vec3_CreateEmpty(context.handle)

	if(scene:FindInstance("NPC01") == false) then
		NPC01 = npc.new("NPC01","Bob the Human","Bob",loc,dir,scale,0,100,100)
		local anim = {"Section",0,5}
		local anim2 = {"Section",0,10}
		NPC01.defaultAnim = anim2
		NPC01.hurtAnim = {"Section",0,5}
		NPC01:setAnimation(anim2)
		objectInstanceAPI.setBaseTransform(NPC01.id, Vector3.new(0, 0.1, 0), 180, -90, 0, Vector3.new(0.1, 0.1, 0.1))
		local upVector = {x=0,y=1,z=0}
		NPC01.upVector = upVector
		NPC01:makeIdle()
		scene:AddInstance(NPC01) 
	else
	    local bob = scene:FindInstance("NPC01")
		local anim = {"Section",0,5}
		local anim2 = {"Section",0,10}
		bob.defaultAnim = anim2
		bob.hurtAnim = {"Section",0,5}
		bob:setAnimation(anim2)
		objectInstanceAPI.setBaseTransform(bob.id, Vector3.new(0, 0.1, 0), 180, -90, 0, Vector3.new(0.1, 0.1, 0.1))
		local upVector = {x=0,y=1,z=0}
		bob.upVector = upVector
		bob:makeIdle()
	end

	if(scene:FindInstance("COLtitan") == false) then
		titan = gameObject.new("titan","Titan","COL_Titan",Vector3.new(500,0,1500),Vector3.new(0,0,0),Vector3.new(1,1,1),0)
	    objectInstanceAPI.setBaseTransform(titan.id, Vector3.new(0, -25, 0), 0, 0, 0, Vector3.new(1, 1, 1))
		scene:AddInstance(titan)
		local loc = {x=500,y=0,z=1500}
		local scale = {x=2,y=2,z=2}
		local dir = {x=0,y=1,z=0}
		local spid1 = npc.new("W1","Robot Mech","Warrior",loc,dir,scale,0,100,100)
	    scene:AddInstance(spid1)
		loc = {x=500,y=100,z=1500}
		local spid2 = npc.new("W1","Robot Mech","Warrior",loc,dir,scale,0,100,100)
	    scene:AddInstance(spid2)
	end
	
	
	local loc = {x=900,y=0,z=900}
	local scale = {x=25,y=25,z=25}
	local dir = {x=0,y=1,z=0}

	if(scene:FindInstance("Boss") == false) then

	    boss = npc.new("Boss","Boss","Warrior",loc,dir,scale,0,200,200)
	    debugLPrint("Changing robot mech")
	    boss.hostileToPlayer = true
	    boss:makeIdle()
	    objectInstanceAPI.setBaseTransform(boss.id, Vector3.new(0, 0, 0), 180, -90, 0, Vector3.new(1, 1, 1))
	    local anim = {"Section",0,1}
	    local anim2 = {"Section",1,2}
	    boss.defaultAnim = anim2
	    boss:setAnimation(anim2)

	    boss.hurtAnim = {"Section",0,5}
	    scene:AddInstance(boss)
	else
	    local oldBoss = scene:FindInstance("Boss")
	    debugLPrint("Changing robot mech")
	    oldBoss.hostileToPlayer = true
	    oldBoss:makeIdle()
	    objectInstanceAPI.setBaseTransform(oldBoss.id, Vector3.new(0, 0, 0), 180, -90, 0, Vector3.new(1, 1, 1))
	    local anim = {"Section",0,1}
	    local anim2 = {"Section",1,2}
	    oldBoss.defaultAnim = anim2
	    oldBoss:setAnimation(anim2)

	    oldBoss.hurtAnim = {"Section",0,5}
	    scene:AddInstance(boss)
	end
	
	FixRobots(scene)
end


function InitialiseCollisionTree()
	if collisionsEnabled then
		local currentGOs = scene:GetGameObjects()

		for i = 1, scene:GetGameObjectCount() do
			if currentGOs[i].collidable == true then
				table.insert(collisionObjects,currentGOs[i].id)
			end
		end
		printAPI.print("Number of collision objects " .. #collisionObjects .. '\n')
		collisionAPI.createCollisionTree(collisionObjects,#collisionObjects)
	end
	collisionTreeCreated = true
end


function FixRobots(thisScene)
    local currentGOs = scene:GetGameObjects()

	for i = 1, scene:GetGameObjectCount() do
		if(currentGOs[i].name == "Robot Mech") then
            debugLPrint("Changing robot mech")
            currentGOs[i].hostileToPlayer = true
            currentGOs[i]:makeIdle()
			currentGOs[i].collidable = false
            --current[i].setOrientation(Vector3.new(180, -90, 0))
            objectInstanceAPI.setBaseTransform(currentGOs[i].id, Vector3.new(0, 0, 0), 180, -90, 0, Vector3.new(1, 1, 1))
            local anim = {"Section",0,0.3}
            local anim2 = {"Section",1,2}
            currentGOs[i].defaultAnim = anim2
            currentGOs[i]:setAnimation(anim2)

            currentGOs[i].hurtAnim = {"Section",0,5}

        end
    end
end

function InitAirship()


	titan = gameObject.new("titan","Titan","COL_Titan",Vector3.new(500,0,1500),Vector3.new(0,0,0),Vector3.new(1,1,1),0)
	objectInstanceAPI.setTranslation(titan.id,500,GetHeightAtPoint(500,1500) - 15,1500)
	scene:AddInstance(titan)

    local loc = {x=500,y=0,z=1500}
    local scale = {x=2,y=2,z=2}
    local dir = {x=0,y=1,z=0}
    npc.new("W1","Robot Mech","Warrior",loc,dir,scale,0,100,100)
    loc = {x=500,y=100,z=1500}
    npc.new("W1","Robot Mech","Warrior",loc,dir,scale,0,100,100)
end


function InitScene2(pathNPC, diff)

    local loc = {x=100,y=100,z=100}
    local scale = {x=5,y=5,z=5}
    local dir = {x=0,y=1,z=0}
    --Dungeon1Intr = gameObject.new("Dungeon1","The Observatory","COL_Dungeon1Interior",loc,dir,scale,0)

    local NPCData = LoadInstances(pathNPC, "npc",difficulty)
	local startPos = Vector3.new(0,0,0)
	local startDir = Vector3.new(0,0,0)
	scene2 = Scene.new("Level2", startPos, startDir)
	

	
    scene2:AddInstances(NPCData);
    scene2:AddInstance(Dungeon1Intr);



    --obsTech = gameObject.new("ObsTech","The Observatory","ObsTech",loc,dir,scale,0)

    local currentGOs = scene2:GetGameObjects()

	for i = 1, scene2:GetGameObjectCount() do
		if(currentGOs[i].name == "Robot Mech") then
            debugLPrint("Changing robot mech")
            currentGOs[i].hostileToPlayer = true
            currentGOs[i]:makeIdle()
            objectInstanceAPI.setBaseTransform(currentGOs[i].id, Vector3.new(0, 0, 0), 180, -90, 0, Vector3.new(1, 1, 1))
            local anim = {"Section",0,5}
            local anim2 = {"Section",0,10}
            currentGOs[i].defaultAnim = anim2
            currentGOs[i]:setAnimation(anim2)
            currentGOs[i].hurtAnim = {"Section",0,5}
        end
    end
end

function InitQuests(quePath)

    diag = Dialogue.new()
	questManager = QuestManager.new()
	LoadQuests(quePath)

    greeting = Topic.new("Greeting","Greeting")
    local mylines2 = {}
    mylines2[1] = "Oh, it's you. I heard you came a long way to get here."

    greeting:setLines(mylines2)

    quest1 = Topic.new("Quest1","I need my organs back.")
    local mylines = {}
    mylines[1] = "Yes, yes, I know, it's terrible... having that foul industry stealing your organs and replacing them with barely-working, recycled pieces of scrap metal..."
    mylines[2] = "Listen, I can help you with your eyes... there's a nearby observatory that I hear has some equipment of interest to me, but it's far too dangerous to go myself."
    mylines[3] = "If you can bring back anything high-tech you find there, I'll happily repair your eyes."

    quest1:setLines(mylines)

    quest1return = Topic.new("Quest1Return","I have something from the observatory.")
    local mylines = {}
    mylines[1] = "Oh, excellent! Come right this way, I'll fix your eyes up for you."

    quest1return:setLines(mylines)
    

    quest2 = Topic.new("Quest2","What about my lungs? My heart?")
    local mylines = {}
    mylines[1] = "You don't quit, do you... While you were gone, the nearby raiders tried to launch another attack. I am too busy helping these people to fix your faulty cybernetics."
    mylines[2] = "Look, the raiders came from an airship north of here. Tell you what, if you can kill their leader and force them to retreat, I'll happily repair the rest of your organs."

    quest2:setLines(mylines)
    

    quest2return = Topic.new("Quest2Return","I killed their leader.")
    local mylines = {}
    mylines[1] = "What, really? Good on you! Excellent! Thank you so much! For a while at least, the people of this town will no longer have to suffer and fear when the next raid will come."
    mylines[2] = "Please, come with me, I'll fix the rest of your organs for you"

    quest2return:setLines(mylines)
    
    teleport1 = Topic.new("Teleport1","Can you take me to the observatory?")
    local mylines = {}
    mylines[1] = "Fine, I guess so."

    teleport1:setLines(mylines)
    
    teleport2 = Topic.new("Teleport2","Can you take me to the airship?")
    local mylines = {}
    mylines[1] = "Fine, I guess so."

    teleport2:setLines(mylines)


    quest1.questEvent = true
    quest2.questEvent = true
    quest1return.questEvent = true
    quest2return.questEvent = true
    greeting.questEvent = true

    

    diag:addTopic(greeting)
    diag:addTopic(quest1)
    diag:addTopic(quest2)
    diag:addTopic(quest1return)
    diag:addTopic(quest2return)
    diag:addTopic(teleport1)
    diag:addTopic(teleport2)


	local npc_01 = scene:FindInstance("NPC01")
    npc_01.dialogue = diag
    npc_01:setDialogue(diag)
    --[[
	if(questManager:doesQuestExist("TalkToBob") == false) then
		local stage1 = QuestStage.new("ObsGetQuest",TALK,"NPC01","Quest1")
		local stage2 = QuestStage.new("ObsGetTech",GET,"ObsTech")
		local stage3 = QuestStage.new("ObsReturn",TALK,"NPC01","Quest1Return")

		local stage4 = QuestStage.new("AirGetQuest",TALK,"NPC01","Quest2")
		local stage5 = QuestStage.new("AirKillBoss",KILL,"Boss")
		local stage6 = QuestStage.new("AirReturn",TALK,"NPC01","Quest2Return")
		
		local stages = {stage1,stage2,stage3,stage4,stage5,stage6}
		local talkToBob = Quest.new("TalkToBob",stages,6)
		questManager:addQuest(talkToBob)
	end
    ]]
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
    
    emptyVec = {x=0,y=0,z=0}
    scale = {x=10,y=10,z=10}
    scene = Scene.new("test", startPos, startDir)
    camera0 = cameraAPI.addNewInstance()
	--world = World.new(player0)
--    newGame("../SaveData/", 1)
--printAPI.print("2\n")


	printAPI.print('Initialising terrain...\n')
   
	skybox = luaObjInstManager.addNewInstance("Skybox")
	objectInstanceAPI.setTranslation(skybox, wsTerrainSize / 2,0, wsTerrainSize / 2);
	objectInstanceAPI.setScale(skybox, 3000,3000,3000)

    printAPI.print('Initialising camera...\n')
    --cameraAPI.setPosition(camera0,terrainSizeX / 2, 30, terrainSizeY / 2)

    printAPI.print('Initialising rendermanager...\n')
    InitPlayer()
    InitWeapon()
    --renderManagerAPI.initialise()

	initMenu()
    soundAPI.playSound("HappyHour",0)
    

    -- load menu
    inMenu = true
	preCameraPos = player0:getPosition()

	preCameraYaw = cameraAPI.getYaw(camera0,context.handle)
	preCameraPitch = cameraAPI.getPitch(camera0,context.handle)
			
	cameraAPI.setPosition(camera0,10,-1,30)
	cameraAPI.setYaw(camera0,0)
	cameraAPI.setPitch(camera0,0)
	changeMenu(0)

	--fountainEmitter = ParticleEmitter.new(WaterParticle, 5, Vector3.new(1000, 200, 1000), 0)
	
    printAPI.print('Initialization finished.\n')
end

function InitPlayer()

    printAPI.print('Initialising player...\n')
	player0 = Player.new(camera0,100,100)


	player0:setPosition(Vector3.new(1000,0,1000))

    gun = gameObject.new("gun","Pistol","Pistol",player0.position,Vector3.new(0,0,0),Vector3.new(0.01,0.01,0.01),0)
    gun.collidable = false
	bullet = gameObject.new("bullet","Bullet","Bullet",Vector3.new(0,0,0),Vector3.new(0,0,0),Vector3.new(0.05,0.05,0.05),0)
	bullet.collidable = false
    scene:AddInstance(gun)
    scene:AddInstance(bullet)

    player0:setAABB(-0.3,0.3,0,1.8,-0.3,0.3) 

end

function InitWeapon()
    basicGun = Weapon.new("basicGun","Gun",1,1)
	table.insert(weaponList,basicGun);
    player0:setWeapon("basicGun")
    
    gun = gameObject.new("gun","Pistol","Pistol",player0.position,Vector3.new(0,0,0),Vector3.new(0.01,0.01,0.01),0)
    bullet = gameObject.new("bullet","Bullet","Bullet",Vector3.new(0,0,0),Vector3.new(0,0,0),Vector3.new(0.05,0.05,0.05),0)

    scene:AddInstance(gun)
    scene:AddInstance(bullet)
    objectInstanceAPI.setBaseTransform(bullet.id, Vector3.new(0, 0, 0), -90, 90, 0, Vector3.new(1, 1, 1))
	bullet.displayNameOnLook = false
    objectInstanceAPI.setBaseTransform(gun.id, Vector3.new(0, 0, 0), 90, 0, 0, Vector3.new(1, 1, 1))
	gun.displayNameOnLook = false
    
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
        if(topic ~= nil and topic.textLines ~= nil and topic.textLines[1] ~= nil) then
            dialogueText = topic.textLines[1]
            dCurrentTopic = topic
            dCurrentLine = 1
            dInMenu = false

            if topic.questEvent then
                questManager:check(TALK,playr.lookTarget,topic.id)
            end

            if(topic.id == "Teleport1") then
                dInMenu = false
                debugLPrint("Closing dialogue - teleporting.\n")

                player0.inDialogue = false
                player0.position = Vector3.new(1200,0,1200)
            end
            if(topic.id == "Teleport2") then
                dInMenu = false
                debugLPrint("Closing dialogue - teleporting.\n")

                player0.inDialogue = false
                player0.position = Vector3.new(900,0,1100)
            end

        else
            debugLPrint("Could not start that topic.\n")
        end
    end
end

function Update()
	--printAPI.print("Update begun\n")
	for step = 1, 1, 1 do
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
				
				cameraAPI.setPosition(camera0,10,-1,30)
				cameraAPI.setYaw(camera0,0)
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
        end
    end

    if(awaitingMessageBox and player0.inDialogue == false) then
        awaitingMessageBox = false
        player0.inDialogue = true
        dialogueText = messageBoxStr
        dInMenu = true
    end
	
	if(inputManagerAPI.isKeyPressed(Menu_Input)) then
        if(inMenu == false) then
            inMenu = true
			preCameraPos = player0:getPosition()
			--printVec3(preCameraPos)
			preCameraYaw = cameraAPI.getYaw(camera0,context.handle)
			preCameraPitch = cameraAPI.getPitch(camera0,context.handle)
			
			cameraAPI.setPosition(camera0,10,-1,30)
			cameraAPI.setYaw(camera0,0)
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
	    e = inputManagerAPI.isKeyPressed(Use_Input)
	    if e then
            printAPI.print("Interacting.\n")
            if(player0.lookTarget ~= nil) then
                StartDialogue(player0.lookTarget)
                if(player0.lookTarget.stringID == "Dungeon1Door") then
                    MoveToDungeon1()
                end
                if(player0.lookTarget.stringID == "ObsTech") then
                    printAPI.print("Picked up quest item.\n")
                    questManager:check(GET,player0.lookTarget,"none")
                    world:RemoveInstance(player0.lookTarget)
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
        if inputManagerAPI.isKeyPressed(QuickSlot6_Input) then
            StartDialogueTopic(player0,6)
        end
        if inputManagerAPI.isKeyPressed(QuickSlot7_Input) then
            StartDialogueTopic(player0,7)
        end
        if inputManagerAPI.isKeyPressed(QuickSlot8_Input) then
            StartDialogueTopic(player0,8)
        end
        if inputManagerAPI.isKeyPressed(QuickSlot9_Input) then
            StartDialogueTopic(player0,9)
        end
        if inputManagerAPI.isMousePressedLeft() then
            debugLPrint("Clicked LMB.\n")
            if(player0.inDialogue == false and player0.lookTarget ~= nil and player0.lookTarget.objType == "NPC") then
                if(player0.rangedWeaponEquipped and player0.lookTarget.hostileToPlayer) then
                    if(player0.weapon:attack(player0.lookTarget)) then
                        FireBullet()
                    end
                end
            end
            if(player0.inDialogue == true and dInMenu == false) then
				debugLPrint("In dialogue...")
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
                    debugLPrint("Closing dialogue - clicked in main menu.\n")
                    player0.inDialogue = false
                end
            end
        end
	    if inputManagerAPI.isKeyPressed(Quicksave_Input) then
		    saveAllToCurrentSave()
	    end

			if inputManagerAPI.isKeyPressed(Quickload_Input) then
			    local currentScene = world:GetScene()

			    currentScene:RemoveInstances()

			    player0["position"]["x"] = 500
			    player0["position"]["z"] = 500
			    player0["position"]["y"] = GetHeightAtPoint(500 , 500)
			    cameraAPI.setPosition(camera0,player0["position"]["x"],player0["position"]["y"],player0["position"]["z"]); 

			    printAPI.print('Initialising objects...\n')
			    local GOData = LoadInstances("../SaveData/GO_Save.csv", "gameObject",difficulty)
			    local NPCData = LoadInstances("../SaveData/NPC_Save.csv", "npc",difficulty)

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
			    end
			
			    if inputManagerAPI.isKeyPressed(TestInput3) then
			    end
    
			    if inputManagerAPI.isKeyPressed(TestInput3) then
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
			local currentGOs = world:GetGameObjects()
			for i = 1, world:GetGameObjectCount() do
			    local a = currentGOs[i]:Update()
			    if(currentGOs[i]["currentHealth"] ~= nil) then
			        if(currentGOs[i]["justSeen"] == true and currentGOs[i]["hostileToPlayer"] == true) then
			            for k = 1, world:GetGameObjectCount() do
			                if(currentGOs[k]["currentHealth"] ~= nil and currentGOs[k].hostileToPlayer) then
			                    if(Distance(currentGOs[i]:getPosition(), currentGOs[k]:getPosition()) < currentGOs[k]["alertDist"]) then
			                        currentGOs[k]:makeChasing()
			                    end
			                end
			            end
			        end
			    end
			end
			player0:update();
			AdjustGunAndBullet()
		end
	end
	engineAPI.EndUpdate();
end

function SpawnBob()
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

function AdjustGunAndBullet()
    local playerPos = Vector3.new(player0.position.x,player0.position.y+1.8,player0.position.z)
    local closerpos = mmath.vec3_Sum(playerPos,mmath.vec3_ScalarMultiply(cameraAPI.forward(camera0,context.handle),1,context.handle),context.handle)
    closerpos.y = closerpos.y - 0.5
    local pos = mmath.vec3_Sum(playerPos,mmath.vec3_ScalarMultiply(cameraAPI.forward(camera0,context.handle),2,context.handle),context.handle)
     
    bullet:setPosition(MoveTowards(bullet:getPosition(),mmath.vec3_Sum(mmath.vec3_ScalarMultiply(cameraAPI.forward(camera0,context.handle), 1000,context.handle) ,playerPos,context.handle),100*deltaTime))

    gun:setPosition(closerpos)
    gun:lookAt(pos)
end

function MoveToDungeon1()

    printAPI.print("Entering dungeon 1.\n")
    world:enterScene(scene2.name)
    player0.trackTerrain = true
    player0.position = {x=100,y=150,z=100}

    
    --[[
    hMapPath = "../Assets/HeightMaps/flatmaphigh.png"
    terrainSizeX = 1024
    terrainSizeY = 1024
    heightMapSize = 256
    heightMapHeight = 35
	terrainHeightData = terrainAPI.generateTerrain(terrainSizeX, terrainSizeY, heightMapSize, heightMapHeight, hMapPath , "../Assets/Models/Terrain/Terrain.obj", context.handle)	
	]]
end

function FireBullet()

    local playerPos = Vector3.new(player0.position.x,player0.position.y+1.8,player0.position.z)

    local pos = mmath.vec3_ScalarMultiply(cameraAPI.forward(camera0,context.handle),2,context.handle)
    local sum = mmath.vec3_Sum(playerPos, pos,context.handle)
    bullet:setPosition(sum)
    bullet:lookAt(sum)
    soundAPI.playSound("Gunshot",1)



end

font1path = "../Assets/Fonts/WesternBangBang.otf"
black = {x=0,y=0,z=0}


function TestChangeNPCState()
    printAPI.print("Test change NPC State.\n")
    NPC01:makeChasing()
end

function StartDialogue(npc)
    debugLPrint("Starting Dialogue... ")
    if(npc ~= nil) then
        if(npc.dialogue ~= nil) then
            debugLPrint("Dialogue available.\n")
            dInMenu= true
            local str = npc.name.."Topics: "
            local topics
            local count
            topics, count = npc:readTopics()
            for i=1,count do
                if(topics[i]~= nil) then
                        npc.dialogue:getTopic("Quest1").active = false
                        npc.dialogue:getTopic("Quest1Return").active = false
                        npc.dialogue:getTopic("Quest2").active = false
                        npc.dialogue:getTopic("Quest2Return").active = false
                    -- enable quest1 if you have greeted bob
                    if(questManager.quests[1]:getStage("Greeting").isComplete) then
                        debugLPrint("Activating Quest1 \n")
                         npc.dialogue:getTopic("Quest1").active = true

                         if(questManager.quests[1]:getStage("ObsGetQuest").isComplete) then
                             debugLPrint("Disabling Quest1 \n")
                             npc.dialogue:getTopic("Quest1").active = false

                            -- enable return Quest 1 once quest done
                            if(questManager.quests[1]:getStage("ObsGetTech").isComplete) then
                                debugLPrint("Activating Quest1Return \n")
                                npc.dialogue:getTopic("Quest1Return").active = true

                                if(questManager.quests[1]:getStage("ObsReturn").isComplete) then
                                    debugLPrint("Removing Quest1Return \n")
                                    npc.dialogue:getTopic("Quest1Return").active = false

                                    debugLPrint("Adding Quest2\n")
                                    npc.dialogue:getTopic("Quest2").active = true

                                    -- disable quest2 once got
                                    if(questManager.quests[1]:getStage("AirGetQuest").isComplete) then
                                        debugLPrint("Disabling Quest2 \n")
                                        npc.dialogue:getTopic("Quest2").active = false
                                         -- enable return Quest 2 once quest done

                                        if(questManager.quests[1]:getStage("AirKillBoss").isComplete) then
                                            debugLPrint("Activating Quest2Return \n")
                                            npc.dialogue:getTopic("Quest2Return").active = true

                                            if(questManager.quests[1]:getStage("AirReturn").isComplete) then
                                                debugLPrint("Disabling Quest2Return \n")
                                                npc.dialogue:getTopic("Quest2Return").active = false
                                            end

                                        else
                                            debugLPrint("Disabling Quest2Return \n")
                                            npc.dialogue:getTopic("Quest2Return").active = false

                                        end
                                    end
                                end
                             end
                         end
                    else
                        debugLPrint("Disabling Quest1 \n")
                        npc.dialogue:getTopic("Quest1").active = false
                    end

                    

                    printAPI.print("TOPIC INFO" ..topics[i].name .. topics[i].id)
                     if(topics[i].active) then
                        str = str .. i ..". ".. topics[i].name .. " "
                    else
                        printAPI.print("Nil topic")
                    end
                end
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
        display2DAPI.drawFullScreen("../Assets/Images/faces.png")
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
			if ButtonEasy.active then
				renderManagerAPI.renderObject(camera0,time,ButtonEasy.id, 1)
			end
			if ButtonMedium.active then
				renderManagerAPI.renderObject(camera0,time,ButtonMedium.id, 1)
			end
			if ButtonHard.active then
				renderManagerAPI.renderObject(camera0,time,ButtonHard.id, 1)
			end
			renderManagerAPI.present(camera0)
		else
			if(helpMenu) then
				display2DAPI.drawFullScreen("../Assets/Images/rules.png")
			else

				-- Draw object
				local currentGOs = world:GetGameObjects()
				for i = 1, world:GetGameObjectCount() do
					if(currentGOs[i].visible) then
						renderManagerAPI.renderObject(camera0,time,currentGOs[i]["id"], 1)
					end
				end
				--local currentTerrainID = world:GetTerrainID()

                renderManagerAPI.renderObject(camera0,time,gun.id,1)
                renderManagerAPI.renderObject(camera0,time,bullet.id,1)


				local i
				for i = 1, #scene.terrainChunks, 1 do
					renderManagerAPI.renderObject(camera0,time,scene.terrainChunks[i], 1);
				end

				--renderManagerAPI.renderObject(camera0,time,currentTerrainID, 1)

				--fountainEmitter:render(camera0, time, 1)

				renderManagerAPI.renderObject(camera0,time,skybox, 0)
				renderManagerAPI.present(camera0)

				
				-- Draw UI text --DrawTextLua(int size, string const& filePath, string const& text, LuaRef pos, LuaRef color, int centered, int screenWidth, int screenHeight)
				
                if(player0.lookTarget ~= nil) then
                    display2DAPI.drawText(32,font1path,lookAtText,{x=100,y=300},black,0,screenWidth,screenHeight)

                end

				if(player0.inDialogue) then 
					display2DAPI.drawText(15,font1path,dialogueText,{x=200,y=200},black,0,screenWidth,screenHeight)
				end

                hpDisplay = "Health: ".. player0.currentHealth .. " / " .. player0.maxHealth
                display2DAPI.drawText(32,font1path,hpDisplay,{x=50,y=50},black,0,screenWidth,screenHeight)


			end
		end
	end
    renderManagerAPI.endRender()
end

function ShowMessageBox(string)
    awaitingMessageBox = true
    messageBoxStr = string
    
end

local status, err = pcall(Run)
if not status then
	printAPI.print(err)
    read(1)
end

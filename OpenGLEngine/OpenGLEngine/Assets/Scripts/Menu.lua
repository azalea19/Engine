local gameObject = dofile '../Assets/Scripts/gameObject.lua'

MenuButtons = {}
MenuButtonBoxes = {}
currentMenu = 0 -- 0MainMenu, 1SaveGame, 2LoadGame
currentSaveFile = 0
inMenu = false

function initMenu()
	-- Background
    local newPos = {x=100,y=0,z=10}
    local newScale = {x=1,y=1,z=1}
    local newDir = {x=0,y=1,z=0}
	Background = gameObject.new("Background", "Background", "Bob", newPos, newDir, newScale, newAnim)
	-- Start New, 0
    local newPos = {x=10,y=0,z=10}
    local newScale = {x=1,y=1,z=1}
    local newDir = {x=0,y=1,z=0}
    StartNewButton = gameObject.new("StartNewButton", "StartNewButton", "Bob", newPos, newDir, newScale, newAnim)
	StartNewButton.option = newGameButton -- initialise a new game
	StartNewButton.active = true
	-- Continue, 0
    local newPos = {x=20,y=0,z=10}
    local newScale = {x=1,y=1,z=1}
    local newDir = {x=0,y=1,z=0}
    ContinueButton = gameObject.new("ContinueButton", "ContinueButton", "Bob", newPos, newDir, newScale, newAnim)
	ContinueButton.option = continueGame -- loads the most recent save
	ContinueButton.active = true
	-- Load Game, 0
    local newPos = {x=30,y=0,z=10}
    local newScale = {x=1,y=1,z=1}
    local newDir = {x=0,y=1,z=0}
    LoadButton = gameObject.new("LoadButton", "LoadButton", "Bob", newPos, newDir, newScale, newAnim)
	LoadButton.option = loadGame -- go to load menu, show 3 slots and back button
	LoadButton.active = true
	-- Save Game, 0
    local newPos = {x=40,y=0,z=10}
    local newScale = {x=1,y=1,z=1}
    local newDir = {x=0,y=1,z=0}
    SaveButton = gameObject.new("SaveButton", "SaveButton", "Bob", newPos, newDir, newScale, newAnim)
	SaveButton.option = saveGame -- Go to save menu, show 3 slots and back button
	SaveButton.active = true
	-- Exit button, 0
    local newPos = {x=0,y=0,z=10}
    local newScale = {x=1,y=1,z=1}
    local newDir = {x=0,y=1,z=0}
    ExitButton = gameObject.new("ExitButton", "ExitButton", "Bob", newPos, newDir, newScale, newAnim)
	ExitButton.option = quitGame -- Exit game
	ExitButton.active = true
	-- Back Button, 1/2
    local newPos = {x=100,y=0,z=10}
    local newScale = {x=1,y=1,z=1}
    local newDir = {x=0,y=1,z=0}
    BackButton = gameObject.new("BackButton", "BackButton", "Bob", newPos, newDir, newScale, newAnim)
	BackButton.option = back -- go back to menu
	BackButton.active = false
	-- Button One, 1/2
    local newPos = {x=70,y=0,z=10}
    local newScale = {x=1,y=1,z=1}
    local newDir = {x=0,y=1,z=0}
    ButtonOne = gameObject.new("ButtonOne", "ButtonOne", "Bob", newPos, newDir, newScale, newAnim)
	ButtonOne.option = buttonOne -- set selected to 1
	ButtonOne.active = false
	-- Button Two, 1/2
    local newPos = {x=80,y=0,z=10}
    local newScale = {x=1,y=1,z=1}
    local newDir = {x=0,y=1,z=0}
    ButtonTwo = gameObject.new("ButtonTwo", "ButtonTwo", "Bob", newPos, newDir, newScale, newAnim)
	ButtonTwo.option = buttonTwo -- set selected to 2
	ButtonTwo.active = false
	-- Button Three, 1/2
    local newPos = {x=90,y=0,z=10}
    local newScale = {x=1,y=1,z=1}
    local newDir = {x=0,y=1,z=0}
    ButtonThree = gameObject.new("ButtonThree", "ButtonThree", "Bob", newPos, newDir, newScale, newAnim)
	ButtonThree.option = buttonThree -- set selected to 3
	ButtonThree.active = false
	-- Return button, 0 during game
    local newPos = {x=110,y=0,z=10}
    local newScale = {x=1,y=1,z=1}
    local newDir = {x=0,y=1,z=0}
    ReturnButton = gameObject.new("ReturnButton", "ReturnButton", "Bob", newPos, newDir, newScale, newAnim)
	ReturnButton.option = ReturnButton -- return to game
	ReturnButton.active = false
	-- Mouse cursor
    local newPos = {x=0,y=0,z=10}
    local newScale = {x=1,y=1,z=1}
    local newDir = {x=0,y=1,z=0}
	MouseObject = gameObject.new("MouseObject", "MouseObject", "Bob", newPos, newDir, newScale, newAnim)
	
	
	table.insert(MenuButtons, StartNewButton)
	table.insert(MenuButtons, ContinueButton)
	table.insert(MenuButtons, LoadButton)
	table.insert(MenuButtons, SaveButton)
	table.insert(MenuButtons, ExitButton)
	
	table.insert(MenuButtonBoxes, StartNewButton:BBToWorld())
	table.insert(MenuButtonBoxes, ContinueButton:BBToWorld())
	table.insert(MenuButtonBoxes, LoadButton:BBToWorld())
	table.insert(MenuButtonBoxes, SaveButton:BBToWorld())
	table.insert(MenuButtonBoxes, ExitButton:BBToWorld())
	
	totalButtons = 5
end

function updateMenu()
	local currentPos = MouseObject:getPosition()
	local newPos = {x=currentPos.x - (inputManagerAPI.mouseDeltaX() / 50),y=currentPos.y - (inputManagerAPI.mouseDeltaY() / 50),z=currentPos.z}
	printVec3(newPos)
	MouseObject:setPosition(newPos)

	if currentMenu == 0 then
		if(islandCollisionAPI.checkAnyCollision(MouseObject:BBToWorld(), MenuButtonBoxes, totalButtons)) then
			if(inputManagerAPI.isMousePressedLeft()) then
				local colIndex  = 1 + islandCollisionAPI.checkAnyCollisionGetIndex(MouseObject:BBToWorld(), MenuButtonBoxes, totalButtons)
				printAPI.print(colIndex)
				if  MenuButtons[colIndex].active then
					MenuButtons[colIndex].option()
				end
			end
		end
	end
	
	if currentMenu == 1 then
		if(islandCollisionAPI.checkAnyCollision(MouseObject:BBToWorld(), MenuButtonBoxes, totalButtons)) then
			if(inputManagerAPI.isMousePressedLeft()) then
				local colIndex  = 1 + islandCollisionAPI.checkAnyCollisionGetIndex(MouseObject:BBToWorld(), MenuButtonBoxes, totalButtons)
				if  MenuButtons[colIndex].active then
					MenuButtons[colIndex].option()
				end
			end
			
			if currentSaveFile == 1 then
				newGame("SaveOne")
				inMenu = false
			end
			if currentSaveFile == 2 then
				newGame("SaveTwo")
				inMenu = false
			end
			if currentSaveFile == 3 then
				newGame("SaveThree")
				inMenu = false
			end
		end
	end
	
	if currentMenu == 2 then
		if(islandCollisionAPI.checkAnyCollision(MouseObject:BBToWorld(), MenuButtonBoxes, totalButtons)) then
			if(inputManagerAPI.isMousePressedLeft()) then
				local colIndex  = 1 + islandCollisionAPI.checkAnyCollisionGetIndex(MouseObject:BBToWorld(), MenuButtonBoxes, totalButtons)
				if  MenuButtons[colIndex].active then
					MenuButtons[colIndex].option()
				end
			end
			
			if currentSaveFile == 1 then
				local tmp = world:GetGameObjects()
				SaveInstances(filePath, tmp, "gameObject")
				SaveInstances(filePath, tmp, "npc")
				SaveQuests(filePath, questManager.quests)
				currentMenu = 0
			end
			if currentSaveFile == 2 then
				local tmp = world:GetGameObjects()
				SaveInstances(filePath, tmp, "gameObject")
				SaveInstances(filePath, tmp, "npc")
				SaveQuests(filePath, questManager.quests)
				currentMenu = 0
			end
			if currentSaveFile == 3 then
				local tmp = world:GetGameObjects()
				SaveInstances(filePath, tmp, "gameObject")
				SaveInstances(filePath, tmp, "npc")
				SaveQuests(filePath, questManager.quests)
				currentMenu = 0
			end
		end
	end
	
	if currentMenu == 3 then
		if(islandCollisionAPI.checkAnyCollision(MouseObject:BBToWorld(), MenuButtonBoxes, totalButtons)) then
			if(inputManagerAPI.isMousePressedLeft()) then
				local colIndex  = 1 + islandCollisionAPI.checkAnyCollisionGetIndex(MouseObject:BBToWorld(), MenuButtonBoxes, totalButtons)
				if  MenuButtons[colIndex].active then
					MenuButtons[colIndex].option()
				end
			end
			
			if currentSaveFile == 1 then
				newGame("InitialData")
				inMenu = false
			end
			if currentSaveFile == 2 then
				newGame("InitialData")
				inMenu = false
			end
			if currentSaveFile == 3 then
				newGame("InitialData")
				inMenu = false
			end
		end
	end
end

function newGame(folder)
printAPI.print('Initialising Scenes...\n')
	-- Initialise objects
	local GOData = LoadInstances("../" .. folder .. "/GO_Data.csv", "gameObject")
	local NPCData = LoadInstances("../" .. folder .. "/NPC_Data.csv", "npc")
	local startPos = Vector3.new(0,0,0)
	local startDir = Vector3.new(0,0,0)
	scene = Scene.new("Level1", Terrain01, startPos, startDir)
	scene:AddInstances(GOData)
	scene:AddInstances(NPCData)
    currentScene = scene
	world = World.new(player0)

	Terrain01 = luaObjInstManager.addNewInstance("Terrain")
	objectInstanceAPI.setTranslation(Terrain01,0,0,0)
	scene:SetTerrain(Terrain01)
	world:AddScene(scene)
	LoadTopics("../InitialData/Topic_Data.csv")

	--Initialise camera
    printAPI.print('Initialising camera...\n')
    camera0 = cameraAPI.addNewInstance()
    cameraAPI.setPosition(camera0,terrainSizeX / 2, 30, terrainSizeY / 2)

	-- Initialise player
    printAPI.print('Initialising player...\n')
	player0 = Player:new(camera0)
	cameraAPI.setPosition(camera0,0,0,0)
    player0:setAABB(-0.5,0.5,-1.8,0,-0.5,0.5) 

    -- Initialise weapon
    basicGun = Weapon.new("basicGun","Gun",100,1)
    player0:setWeapon(basicGun)

    --Initialise quests
    questManager = QuestManager.new()
	LoadQuests("../" .. folder .. "/QUE_Data.csv")
    printAPI.print('Initialization finished.\n')
end

function newGameButton()
	ButtonOne.active = true
	ButtonTwo.active = true
	ButtonThree.active = true
	BackButton.active = true
	StartNewButton.active = false
	ContinueButton.active = false
	SaveButton.active = false
	LoadButton.active = false
	ExitButton.active = false
	
	currentMenu = 3
end

function loadGame()
	ButtonOne.active = true
	ButtonTwo.active = true
	ButtonThree.active = true
	BackButton.active = true
	StartNewButton.active = false
	ContinueButton.active = false
	SaveButton.active = false
	LoadButton.active = false
	ExitButton.active = false
	
	currentMenu = 2
end

function saveGame()
	ButtonOne.active = true
	ButtonTwo.active = true
	ButtonThree.active = true
	BackButton.active = true
	StartNewButton.active = false
	ContinueButton.active = false
	SaveButton.active = false
	LoadButton.active = false
	ExitButton.active = false
	
	currentMenu = 1
end

function back()
	currentMenu = 0
end

function quitGame()
	run = false
end

function buttonOne()
	currentSaveFile = 1
end

function buttonTwo()
	currentSaveFile = 2
end

function buttonThree()
	currentSaveFile = 3
end

function continueGame()
	
end

function ReturnButton()
	inMenu = false;
end
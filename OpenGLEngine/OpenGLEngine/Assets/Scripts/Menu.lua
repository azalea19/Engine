local Vector3 = dofile '../Assets/Scripts/Vector3.lua'
local gameObject = dofile '../Assets/Scripts/gameObject.lua'
local AABoundingBox = dofile '../Assets/Scripts/AABoundingBox.lua'
local npc = dofile '../Assets/Scripts/npc.lua'
local Player = dofile '../Assets/Scripts/Player.lua'
local Scene = dofile '../Assets/Scripts/Scene.lua'
local World = dofile '../Assets/Scripts/World.lua'

MenuButtons = {}
MenuButtonBoxes = {}
currentMenu = 1 -- 0MainMenu, 1SaveGame, 2LoadGame
currentSelectedSaveFile = 0
currentSaveFile = 0
inMenu = false
menuCount = 0
currentDifficulty = 1

function initMenu()
	-- Background
    local newPos = {x=0,y=1,z=40}
    local newScale = {x=5,y=5,z=0.01}
    local newDir = {x=0,y=1,z=0}
	Background = gameObject.new("Background", "Background", "Bob", newPos, newDir, newScale, newAnim)
	-- Start New, 0
    local newPos = {x=0,y=1,z=20}
    local newScale = {x=0.75,y=0.75,z=0.75}
    local newDir = {x=0,y=1,z=0}
    StartNewButton = gameObject.new("StartNewButton", "StartNewButton", "Bob", newPos, newDir, newScale, newAnim)
	StartNewButton.option = newGameButton -- initialise a new game
	StartNewButton.active = true
	-- Continue, 0
    local newPos = {x=5,y=1,z=20}
    local newScale = {x=0.75,y=0.75,z=0.75}
    local newDir = {x=0,y=1,z=0}
    ContinueButton = gameObject.new("ContinueButton", "ContinueButton", "Bob", newPos, newDir, newScale, newAnim)
	ContinueButton.option = continueGame -- loads the most recent save
	ContinueButton.active = true
	-- Load Game, 0
    local newPos = {x=10,y=1,z=20}
    local newScale = {x=0.75,y=0.75,z=0.75}
    local newDir = {x=0,y=1,z=0}
    LoadButton = gameObject.new("LoadButton", "LoadButton", "Bob", newPos, newDir, newScale, newAnim)
	LoadButton.option = loadGame -- go to load menu, show 3 slots and back button
	LoadButton.active = true
	-- Save Game, 0
    local newPos = {x=15,y=1,z=20}
    local newScale = {x=0.75,y=0.75,z=0.75}
    local newDir = {x=0,y=1,z=0}
    SaveButton = gameObject.new("SaveButton", "SaveButton", "Bob", newPos, newDir, newScale, newAnim)
	SaveButton.option = saveGame -- Go to save menu, show 3 slots and back button
	SaveButton.active = true
	-- Exit button, 0
    local newPos = {x=20,y=0,z=20}
    local newScale = {x=0.75,y=0.75,z=0.75}
    local newDir = {x=0,y=1,z=0}
    ExitButton = gameObject.new("ExitButton", "ExitButton", "Bob", newPos, newDir, newScale, newAnim)
	ExitButton.option = quitGame -- Exit game
	ExitButton.active = true
	-- Back Button, 1/2
    local newPos = {x=20,y=1,z=20}
    local newScale = {x=0.75,y=0.75,z=0.75}
    local newDir = {x=0,y=1,z=0}
    BackButton = gameObject.new("BackButton", "BackButton", "Bob", newPos, newDir, newScale, newAnim)
	BackButton.option = back -- go back to menu
	BackButton.active = false
	-- Button One, 1/2
    local newPos = {x=10,y=1,z=20}
    local newScale = {x=0.75,y=0.75,z=0.75}
    local newDir = {x=0,y=1,z=0}
    ButtonOne = gameObject.new("ButtonOne", "ButtonOne", "Bob", newPos, newDir, newScale, newAnim)
	ButtonOne.option = buttonOne -- set selected to 1
	ButtonOne.active = false
	-- Button Two, 1/2
    local newPos = {x=5,y=1,z=20}
    local newScale = {x=0.75,y=0.75,z=0.75}
    local newDir = {x=0,y=1,z=0}
    ButtonTwo = gameObject.new("ButtonTwo", "ButtonTwo", "Bob", newPos, newDir, newScale, newAnim)
	ButtonTwo.option = buttonTwo -- set selected to 2
	ButtonTwo.active = false
	-- Button Three, 1/2
    local newPos = {x=0,y=1,z=20}
    local newScale = {x=0.75,y=0.75,z=0.75}
    local newDir = {x=0,y=1,z=0}
    ButtonThree = gameObject.new("ButtonThree", "ButtonThree", "Bob", newPos, newDir, newScale, newAnim)
	ButtonThree.option = buttonThree -- set selected to 3
	ButtonThree.active = false
	-- Button Easy, 4
    local newPos = {x=10,y=1,z=20}
    local newScale = {x=0.75,y=0.75,z=0.75}
    local newDir = {x=0,y=1,z=0}
    ButtonEasy = gameObject.new("ButtonEasy", "ButtonEasy", "Bob", newPos, newDir, newScale, newAnim)
	ButtonEasy.option = buttonEasy -- set selected to 1
	ButtonEasy.active = false
	-- Button Medium, 4
    local newPos = {x=5,y=1,z=20}
    local newScale = {x=0.75,y=0.75,z=0.75}
    local newDir = {x=0,y=1,z=0}
    ButtonMedium = gameObject.new("ButtonMedium", "ButtonMedium", "Bob", newPos, newDir, newScale, newAnim)
	ButtonMedium.option = buttonMedium -- set selected to 2
	ButtonMedium.active = false
	-- Button Hard, 4
    local newPos = {x=0,y=1,z=20}
    local newScale = {x=0.75,y=0.75,z=0.75}
    local newDir = {x=0,y=1,z=0}
    ButtonHard = gameObject.new("ButtonHard", "ButtonHard", "Bob", newPos, newDir, newScale, newAnim)
	ButtonHard.option = buttonHard -- set selected to 3
	ButtonHard.active = false
	-- Return button, 0 during game
    local newPos = {x=25,y=1,z=20}
    local newScale = {x=0.75,y=0.75,z=0.75}
    local newDir = {x=0,y=1,z=0}
    ReturnButton = gameObject.new("ReturnButton", "ReturnButton", "Bob", newPos, newDir, newScale, newAnim)
	ReturnButton.option = ReturnButton -- return to game
	ReturnButton.active = false
	-- Mouse cursor
    local newPos = {x=0,y=1,z=20}
    local newScale = {x=0.2,y=0.2,z=0.2}
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
	MouseObject:setPosition(newPos)

	if currentMenu == 0 then
		if(islandCollisionAPI.checkAnyCollision(MouseObject:BBToWorld(), MenuButtonBoxes, totalButtons)) then
		
						local colIndex  = 1 + islandCollisionAPI.checkAnyCollisionGetIndex(MouseObject:BBToWorld(), MenuButtonBoxes, totalButtons)
				printAPI.print(MenuButtons[colIndex].name .. "\n")

			if(inputManagerAPI.isMousePressedLeft()) then
				local colIndex  = 1 + islandCollisionAPI.checkAnyCollisionGetIndex(MouseObject:BBToWorld(), MenuButtonBoxes, totalButtons)
				printAPI.print(MenuButtons[colIndex].name)
				if  MenuButtons[colIndex].active then
					MenuButtons[colIndex].option()
				end
				last = true
			end
		end
	else
		if currentMenu == 1 then
			if(islandCollisionAPI.checkAnyCollision(MouseObject:BBToWorld(), MenuButtonBoxes, totalButtons)) then
			
							local colIndex  = 1 + islandCollisionAPI.checkAnyCollisionGetIndex(MouseObject:BBToWorld(), MenuButtonBoxes, totalButtons)
					printAPI.print(MenuButtons[colIndex].name .. "\n")
					
				if(inputManagerAPI.isMousePressedLeft()) then
					local colIndex  = 1 + islandCollisionAPI.checkAnyCollisionGetIndex(MouseObject:BBToWorld(), MenuButtonBoxes, totalButtons)
					--if  MenuButtons[colIndex].active == true then
						printAPI.print("SUCC")
						MenuButtons[colIndex].option()
					--end
				--end
				
				if currentSelectedSaveFile == 1 then
					local tmp = world:GetGameObjects()
					SaveInstances("../Saves/Slot1/GO_Data.csv", tmp, "gameObject")
					SaveInstances("../Saves/Slot1/NPC_Data.csv", tmp, "npc")
					SaveQuests("../Saves/Slot1/QUE_Data.csv", questManager)
					savePlayer("../Saves/Slot1/QUE_PLAYER.csv", player0)
					saveWeapons("../Saves/Slot1/QUE_WEAPON.csv", weaponList)
					currentSaveFile = 1
					changeMenu(0)
				end
				if currentSelectedSaveFile == 2 then
					local tmp = world:GetGameObjects()
					SaveInstances("../Saves/Slot2/GO_Data.csv", tmp, "gameObject")
					SaveInstances("../Saves/Slot2/NPC_Data.csv", tmp, "npc")
					SaveQuests("../Saves/Slot2/QUE_Data.csv", questManager)
					savePlayer("../Saves/Slot2/QUE_PLAYER.csv", player0)
					saveWeapons("../Saves/Slot2/QUE_WEAPON.csv", weaponList)
					currentSaveFile = 2
					changeMenu(0)
				end
				if currentSelectedSaveFile == 3 then
					local tmp = world:GetGameObjects()
					SaveInstances("../Saves/Slot3/GO_Data.csv", tmp, "gameObject")
					SaveInstances("../Saves/Slot3/NPC_Data.csv", tmp, "npc")
					SaveQuests("../Saves/Slot3/QUE_Data.csv", questManager)
					savePlayer("../Saves/Slot3/QUE_PLAYER.csv", player0)
					saveWeapons("../Saves/Slot3/QUE_WEAPON.csv", weaponList)
					currentSaveFile = 3
					changeMenu(0)
				end
				
				end
			end
		else
			if currentMenu == 2 then
				if(islandCollisionAPI.checkAnyCollision(MouseObject:BBToWorld(), MenuButtonBoxes, totalButtons)) then
				
								local colIndex  = 1 + islandCollisionAPI.checkAnyCollisionGetIndex(MouseObject:BBToWorld(), MenuButtonBoxes, totalButtons)
						printAPI.print(MenuButtons[colIndex].name .. "\n")
				
					if(inputManagerAPI.isMousePressedLeft()) then
						local colIndex  = 1 + islandCollisionAPI.checkAnyCollisionGetIndex(MouseObject:BBToWorld(), MenuButtonBoxes, totalButtons)
						--if  MenuButtons[colIndex].active == true then
						printAPI.print("SUCC")
							MenuButtons[colIndex].option()
						--end
					--end
					if currentSelectedSaveFile == 1 then
						newGame("../Saves/Slot1/", 1)
						currentSaveFile = 1
						inMenu = false
					end
					if currentSelectedSaveFile == 2 then
						newGame("../Saves/Slot2/", 1)
						currentSaveFile = 2
						inMenu = false
					end
					if currentSelectedSaveFile == 3 then
						newGame("../Saves/Slot3/", 1)
						currentSaveFile = 3
						inMenu = false
					end

					end
				end
			else
				if currentMenu == 3 then
					if(islandCollisionAPI.checkAnyCollision(MouseObject:BBToWorld(), MenuButtonBoxes, totalButtons)) then
					
						local colIndex  = 1 + islandCollisionAPI.checkAnyCollisionGetIndex(MouseObject:BBToWorld(), MenuButtonBoxes, totalButtons)
						printAPI.print(MenuButtons[colIndex].name .. "\n")
					
						if(inputManagerAPI.isMousePressedLeft()) then
							local colIndex  = 1 + islandCollisionAPI.checkAnyCollisionGetIndex(MouseObject:BBToWorld(), MenuButtonBoxes, totalButtons)
							MenuButtons[colIndex].option()
						
							if currentSelectedSaveFile == 1 then
								newGame("../SaveData/", currentDifficulty)
								currentSaveFile = 1
								inMenu = false
							end
							if currentSelectedSaveFile == 2 then
								newGame("../SaveData/", currentDifficulty)
								currentSaveFile = 2
								inMenu = false
							end
							if currentSelectedSaveFile == 3 then
								newGame("../SaveData/", currentDifficulty)
								currentSaveFile = 3
								inMenu = false
							end
						end
					end
				else
					if currentMenu == 4 then
						if(islandCollisionAPI.checkAnyCollision(MouseObject:BBToWorld(), MenuButtonBoxes, totalButtons)) then
						
							local colIndex  = 1 + islandCollisionAPI.checkAnyCollisionGetIndex(MouseObject:BBToWorld(), MenuButtonBoxes, totalButtons)
							printAPI.print(MenuButtons[colIndex].name .. "\n")
						
							if(inputManagerAPI.isMousePressedLeft()) then
								local colIndex  = 1 + islandCollisionAPI.checkAnyCollisionGetIndex(MouseObject:BBToWorld(), MenuButtonBoxes, totalButtons)
								MenuButtons[colIndex].option()
							end
						end
					end	
				end
			end
		end
	end
end

function newGame(folder, difficulty)
	printAPI.print('Initialising Scenes...\n')
	local GOData = LoadInstances(folder .. "GO_Data.csv", "gameObject")
	local NPCData = LoadInstances(folder .. "NPC_Data.csv", "npc", difficulty)
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
	LoadTopics("../SaveData/DIA_Data.csv")

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
	
	loadWeapons(folder .. "WEAPON_Data.csv")
	loadPlayer(folder .. "PLAYER_Data.csv", player0)

    --Initialise quests
    questManager = QuestManager.new()
	LoadQuests("../Saves/Slot1/QUE_Data.csv")
    printAPI.print('Initialization finished.\n')
end

function newGameButton()
	printAPI.print("NewGame")
	changeMenu(4)
end

function changeMenu(num)
	currentSaveFile = 0
	if num == 0 then
		ButtonOne.active = false
		ButtonTwo.active = false
		ButtonThree.active = false
		ButtonEasy.active = false
		ButtonMedium.active = false
		ButtonHard.active = false
		BackButton.active = false
		StartNewButton.active = true
		ContinueButton.active = true
		SaveButton.active = true
		LoadButton.active = true
		ExitButton.active = true
		currentMenu = 0
		MenuButtons = {}
		MenuButtonsBox = {}
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
	if num == 1 then
		ButtonOne.active = true
		ButtonTwo.active = true
		ButtonThree.active = true
		BackButton.active = true
		StartNewButton.active = false
		ContinueButton.active = false
		SaveButton.active = false
		LoadButton.active = false
		ExitButton.active = false
		ButtonEasy.active = false
		ButtonMedium.active = false
		ButtonHard.active = false
		currentMenu = 1
		MenuButtons = {}
		MenuButtonsBox = {}
		table.insert(MenuButtons, ButtonOne)
		table.insert(MenuButtons, ButtonTwo)
		table.insert(MenuButtons, ButtonThree)
		table.insert(MenuButtons, BackButton)
		
		table.insert(MenuButtonBoxes, ButtonOne:BBToWorld())
		table.insert(MenuButtonBoxes, ButtonTwo:BBToWorld())
		table.insert(MenuButtonBoxes, ButtonThree:BBToWorld())
		table.insert(MenuButtonBoxes, BackButton:BBToWorld())
		totalButtons = 4
	end
	if num == 2 then
		ButtonOne.active = true
		ButtonTwo.active = true
		ButtonThree.active = true
		BackButton.active = true
		StartNewButton.active = false
		ContinueButton.active = false
		SaveButton.active = false
		LoadButton.active = false
		ExitButton.active = false
		ButtonEasy.active = false
		ButtonMedium.active = false
		ButtonHard.active = false
		currentMenu = 2
		MenuButtons = {}
		MenuButtonsBox = {}
		table.insert(MenuButtons, ButtonOne)
		table.insert(MenuButtons, ButtonTwo)
		table.insert(MenuButtons, ButtonThree)
		table.insert(MenuButtons, BackButton)
		
		table.insert(MenuButtonBoxes, ButtonOne:BBToWorld())
		table.insert(MenuButtonBoxes, ButtonTwo:BBToWorld())
		table.insert(MenuButtonBoxes, ButtonThree:BBToWorld())
		table.insert(MenuButtonBoxes, BackButton:BBToWorld())
		totalButtons = 4
	end
	if num == 3 then
		ButtonOne.active = true
		ButtonTwo.active = true
		ButtonThree.active = true
		BackButton.active = true
		StartNewButton.active = false
		ContinueButton.active = false
		SaveButton.active = false
		LoadButton.active = false
		ExitButton.active = false
		ButtonEasy.active = false
		ButtonMedium.active = false
		ButtonHard.active = false
		currentMenu = 3
		MenuButtons = {}
		MenuButtonsBox = {}
		table.insert(MenuButtons, ButtonOne)
		table.insert(MenuButtons, ButtonTwo)
		table.insert(MenuButtons, ButtonThree)
		table.insert(MenuButtons, BackButton)
		
		table.insert(MenuButtonBoxes, ButtonOne:BBToWorld())
		table.insert(MenuButtonBoxes, ButtonTwo:BBToWorld())
		table.insert(MenuButtonBoxes, ButtonThree:BBToWorld())
		table.insert(MenuButtonBoxes, BackButton:BBToWorld())
		totalButtons = 4
	end
	if num == 4 then
		ButtonOne.active = false
		ButtonTwo.active = false
		ButtonThree.active = false
		BackButton.active = true
		StartNewButton.active = false
		ContinueButton.active = false
		SaveButton.active = false
		LoadButton.active = false
		ExitButton.active = false
		ButtonEasy.active = true
		ButtonMedium.active = true
		ButtonHard.active = true
		currentMenu = 3
		MenuButtons = {}
		MenuButtonsBox = {}
		table.insert(MenuButtons, ButtonEasy)
		table.insert(MenuButtons, ButtonMedium)
		table.insert(MenuButtons, ButtonThree)
		table.insert(MenuButtons, ButtonHard)
		
		table.insert(MenuButtonBoxes, ButtonEasy:BBToWorld())
		table.insert(MenuButtonBoxes, ButtonMedium:BBToWorld())
		table.insert(MenuButtonBoxes, ButtonHard:BBToWorld())
		table.insert(MenuButtonBoxes, BackButton:BBToWorld())
		totalButtons = 4
	end

end

function buttonEasy()
	printAPI.print("Easy")
	currentDifficulty = 1
	changeMenu(3)
end

function buttonMedium()
	printAPI.print("Medium")
	currentDifficulty = 1.25
	changeMenu(3)
end

function buttonHard()
	printAPI.print("Hard")
	currentDifficulty = 1.5
	changeMenu(3)
end

function loadGame()
	printAPI.print("LoadGame")
	changeMenu(2)
end

function saveGame()
	printAPI.print("SaveGame")
	changeMenu(1)
end

function back()
	printAPI.print("Back")
	changeMenu(0)
end

function quitGame()
	printAPI.print("Quit")
	run = false
end

function buttonOne()
	printAPI.print("One")
	currentSelectedSaveFile = 1
end

function buttonTwo()
	printAPI.print("Two")
	currentSelectedSaveFile = 2
end

function buttonThree()
	printAPI.print("Three")
	currentSelectedSaveFile = 3
end

function continueGame()
	printAPI.print("Continue")
end

function ReturnButton()
	inMenu = false;
end
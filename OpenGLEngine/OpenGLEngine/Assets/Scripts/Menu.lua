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
currentSaveFile = 1
inMenu = true
menuCount = 0
currentDifficulty = 1
inGame = false

function initMenu()
	-- Background
    local newPos = {x=10,y=-1,z=0}
    local newScaleBG = {x=500,y=500,z=0.01}
    local newDir = {x=0,y=1,z=0}
	Background = gameObject.new("Background", "Background", "mainMenu", newPos, newDir, newScaleBG, newAnim)
	-- Start New, 0
    local newPos = {x=0,y=-1,z=12}
    local newScale = {x=2,y=2,z=2}
    local newDir = {x=0,y=1,z=0}
    StartNewButton = gameObject.new("StartNewButton", "StartNewButton", "btnNewGame", newPos, newDir, newScale, newAnim)
	StartNewButton.option = newGameButton -- initialise a new game
	StartNewButton.active = true
	-- Continue, 0
    local newPos = {x=5,y=-1,z=12}
    local newDir = {x=0,y=1,z=0}
    ContinueButton = gameObject.new("ContinueButton", "ContinueButton", "btnContinue", newPos, newDir, newScale, newAnim)
	ContinueButton.option = continueGame -- loads the most recent save
	ContinueButton.active = true
	-- Load Game, 0
    local newPos = {x=10,y=-1,z=12}
    local newDir = {x=0,y=1,z=0}
    LoadButton = gameObject.new("LoadButton", "LoadButton", "btnLoad", newPos, newDir, newScale, newAnim)
	LoadButton.option = loadGame -- go to load menu, show 3 slots and back button
	LoadButton.active = true
	-- Save Game, 0
    local newPos = {x=15,y=-1,z=12}
    local newDir = {x=0,y=1,z=0}
    SaveButton = gameObject.new("SaveButton", "SaveButton", "btnSave", newPos, newDir, newScale, newAnim)
	SaveButton.option = saveGame -- Go to save menu, show 3 slots and back button
	SaveButton.active = true
	-- Exit button, 0
    local newPos = {x=20,y=-1,z=12}
    local newDir = {x=0,y=1,z=0}
    ExitButton = gameObject.new("ExitButton", "ExitButton", "btnQuit", newPos, newDir, newScale, newAnim)
	ExitButton.option = quitGame -- Exit game
	ExitButton.active = true
	-- Back Button, 1/2
    local newPos = {x=0,y=-1,z=12}
    local newDir = {x=0,y=1,z=0}
    BackButton = gameObject.new("BackButton", "BackButton", "btnBack", newPos, newDir, newScale, newAnim)
	BackButton.option = back -- go back to menu
	BackButton.active = false
	-- Button One, 1/2
    local newPos = {x=10,y=-1,z=12}
    local newDir = {x=0,y=1,z=0}
    ButtonOne = gameObject.new("ButtonOne", "ButtonOne", "btnGame1", newPos, newDir, newScale, newAnim)
	ButtonOne.option = buttonOne -- set selected to 1
	ButtonOne.active = false
	-- Button Two, 1/2
    local newPos = {x=15,y=-1,z=12}
    local newDir = {x=0,y=1,z=0}
    ButtonTwo = gameObject.new("ButtonTwo", "ButtonTwo", "btnGame2", newPos, newDir, newScale, newAnim)
	ButtonTwo.option = buttonTwo -- set selected to 2
	ButtonTwo.active = false
	-- Button Three, 1/2
    local newPos = {x=20,y=-1,z=12}
    local newDir = {x=0,y=1,z=0}
    ButtonThree = gameObject.new("ButtonThree", "ButtonThree", "btnGame3", newPos, newDir, newScale, newAnim)
	ButtonThree.option = buttonThree -- set selected to 3
	ButtonThree.active = false
	-- Button Easy, 4
    local newPos = {x=10,y=-1,z=12}
    local newDir = {x=0,y=1,z=0}
    ButtonEasy = gameObject.new("ButtonEasy", "ButtonEasy", "btnEasy", newPos, newDir, newScale, newAnim)
	ButtonEasy.option = buttonEasy -- set selected to 1
	ButtonEasy.active = false
	-- Button Medium, 4
    local newPos = {x=15,y=-1,z=12}
    local newDir = {x=0,y=1,z=0}
    ButtonMedium = gameObject.new("ButtonMedium", "ButtonMedium", "btnMedium", newPos, newDir, newScale, newAnim)
	ButtonMedium.option = buttonMedium -- set selected to 2
	ButtonMedium.active = false
	-- Button Hard, 4
    local newPos = {x=20,y=-1,z=12}
    local newDir = {x=0,y=1,z=0}
    ButtonHard = gameObject.new("ButtonHard", "ButtonHard", "btnHard", newPos, newDir, newScale, newAnim)
	ButtonHard.option = buttonHard -- set selected to 3
	ButtonHard.active = false
	-- Return button, 0 during game
    local newPos = {x=25,y=-1,z=12}
    local newDir = {x=0,y=1,z=0}
    ReturnButton = gameObject.new("ReturnButton", "ReturnButton", "btnReturn", newPos, newDir, newScale, newAnim)
	ReturnButton.option = ReturnButton -- return to game
	ReturnButton.active = false
	-- Mouse cursor
    local newPos = {x=10,y=5,z=14}
    local newScale = {x=0.25,y=0.25,z=0.25}
    local newDir = {x=0,y=1,z=0}
	MouseObject = gameObject.new("MouseObject", "MouseObject", "whiteCube", newPos, newDir, newScale, newAnim)
	
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
    cameraAPI.setPosition(camera0,10,-1,30)
	cameraAPI.setYaw(camera0,0)
	cameraAPI.setPitch(camera0,0)

	local currentPos = MouseObject:getPosition()
    local newXPos = currentPos.x + (inputManagerAPI.mouseDeltaX() / 50)
    local newYPos = currentPos.y - (inputManagerAPI.mouseDeltaY() / 50)

    if(newXPos < -4) then
        newXPos = -4
    end
    if(newXPos > 25) then
        newXPos = 25
    end
    if(newYPos > 8) then
        newYPos = 8
    end
    if(newYPos < -8) then
        newYPos = -8
    end
    
    local newPos = {x=newXPos,y=newYPos,z=currentPos.z}
    MouseObject:setPosition(newPos)



--printAPI.print(currentPos.x .. "," .. currentPos.y .. "\n")
--printAPI.print(StartNewButton:BBToWorld().min.x .. "," .. StartNewButton:BBToWorld().min.y .. " " .. StartNewButton:BBToWorld().max.x .. "," .. StartNewButton:BBToWorld().max.y .. "\n\n")
	if(inputManagerAPI.isMousePressedLeft()) then
		local colIndex = 0
		for i = 1, #MenuButtons, 1 do
			if collisionAPI.objectCollidesWithObject(MouseObject.id, MenuButtons[i].id) then
				colIndex = i
			end
		end

		if(colIndex > 0) then
			printAPI.print(MenuButtons[colIndex].name .. "\n")
			if  MenuButtons[colIndex].active then
				MenuButtons[colIndex].option()
				if currentMenu == 0 then
				else
					if currentMenu == 1 then
						if currentSelectedSaveFile == 1 then
							currentSaveFile = 1
							currentSelectedSaveFile = 0
							saveAllToCurrentSave()
							changeMenu(0)
						end
						if currentSelectedSaveFile == 2 then
							currentSaveFile = 2
							currentSelectedSaveFile = 0
							saveAllToCurrentSave()
							changeMenu(0)
						end
						if currentSelectedSaveFile == 3 then
							currentSaveFile = 3
							currentSelectedSaveFile = 0
							saveAllToCurrentSave()
							changeMenu(0)
						end
					else
						if currentMenu == 2 then
							if currentSelectedSaveFile == 1 then
								newGame("../Saves/Slot1/", 1)
								currentSelectedSaveFile = 0
								currentSaveFile = 1
                                inGame = true
								inMenu = false
							end
							if currentSelectedSaveFile == 2 then
								newGame("../Saves/Slot2/", 1)
								currentSelectedSaveFile = 0
								currentSaveFile = 2
                                inGame = true
								inMenu = false
							end
							if currentSelectedSaveFile == 3 then
								newGame("../Saves/Slot3/", 1)
								currentSelectedSaveFile = 0
								currentSaveFile = 3
                                inGame = true
								inMenu = false
							end
						else
							if currentMenu == 3 then 					
								if currentSelectedSaveFile == 1 then
									newGame("../SaveData/", currentDifficulty)
									currentSelectedSaveFile = 0
									currentSaveFile = 1
                                    inGame = true
									inMenu = false
								end
								if currentSelectedSaveFile == 2 then
									newGame("../SaveData/", currentDifficulty)
									currentSelectedSaveFile = 0
									currentSaveFile = 2
                                    inGame = true
									inMenu = false
								end
								if currentSelectedSaveFile == 3 then
									newGame("../SaveData/", currentDifficulty)
									currentSelectedSaveFile = 0
									currentSaveFile = 3
                                    inGame = true
									inMenu = false
								end
							else
								if currentMenu == 4 then
								end	
							end
						end
					end
				end
			end
		end
	end
end

function newGame(folder, difficulty)
	local GOData = LoadInstances(folder .. "GO_Data.csv", "gameObject", difficulty)
	local NPCData = LoadInstances(folder .. "NPC_Data.csv", "npc", difficulty)
	local startPos = Vector3.new(0,0,0)
	local startDir = Vector3.new(0,0,0)
	
    printAPI.print("3\n")

	printAPI.print("4\n")
    InitScene1(folder .. "GO_Data.csv", folder .. "NPC_Data.csv", difficulty)
    InitScene2(folder .. "NPC_Data_Scene2.csv", difficulty)
    printAPI.print("5\n")

	CreateTerrain(scene)
	--CreateCactusField(scene)	--REMOVE AFTER DEFAULT SAVE SET UP
	--CreateTown(scene)			--REMOVE AFTER DEFAULT SAVE SET UP
	
	world = World.new(player0)
	world:AddScene(scene)
	world:AddScene(scene2)

    InitQuests(folder .. "QUE_Data.csv")

    printAPI.print("8\n")
	
	--LoadTopics("../SaveData/DIA_Data.csv")
	--Initialise camera
    camera0 = cameraAPI.addNewInstance()
	-- Initialise player
    InitPlayer()	
    InitWeapon()	
    -- Initialise weapo
	weaponList = {}
    printAPI.print("9\n")
	weaponList = loadWeapons(folder .. "WEAPON_Data.csv")
	loadPlayer(folder .. "PLAYER_Data.csv", player0)
    world.currentScene = playerInScene
    player0:setWeapon("basicGun")
    printAPI.print("10\n")
    gun = gameObject.new("gun","Pistol","Pistol",player0.position,Vector3.new(0,0,0),Vector3.new(0.01,0.01,0.01),0)
    bullet = gameObject.new("bullet","Bullet","Bullet",Vector3.new(0,0,0),Vector3.new(0,0,0),Vector3.new(0.05,0.05,0.05),0)
	InitialiseCollisionTree()
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
		ContinueButton.active = false
		SaveButton.active = true
		LoadButton.active = true
		ExitButton.active = true
		currentMenu = 0
		MenuButtons = {}
		MenuButtonsBox = {}

        totalButtons = 3

        if(inGame) then
            ReturnButton.active = false
        else
            ReturnButton.active = true
            table.insert(MenuButtons, ReturnButton)
            table.insert(MenuButtonBoxes, ReturnButton:BBToWorld())
            totalButtons = totalButtons +1
        end
        if(inGame) then
            SaveButton.active = true
            table.insert(MenuButtons, SaveButton)
            table.insert(MenuButtonBoxes, SaveButton:BBToWorld())
            totalButtons = totalButtons +1
        else
            SaveButton.active = false

        end

		table.insert(MenuButtons, StartNewButton)
		table.insert(MenuButtons, LoadButton)
		table.insert(MenuButtons, ExitButton)
		
		table.insert(MenuButtonBoxes, StartNewButton:BBToWorld())
		table.insert(MenuButtonBoxes, LoadButton:BBToWorld())
		
		table.insert(MenuButtonBoxes, ExitButton:BBToWorld())
		
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
        ReturnButton.active = false

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
        ReturnButton.active = false

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
        ReturnButton.active = false

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
        ReturnButton.active = false

		currentMenu = 4
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
	quitting = true
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
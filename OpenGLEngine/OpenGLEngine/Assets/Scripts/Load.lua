terrainHeightData = {}


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
	GetAPI(context.handle, 'soundAPI', 'soundAPI')
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
    modelLibraryAPI.addModel("Warrior","../Assets/Models/Characters/PA_SciFiCombatants/PA_SciFiCombatants/_Imported3D/Characters/lizabc.FBX",false)
    --modelLibraryAPI.addModel("COL_CaveDoor","../Assets/Models/Liz_Dungeons/CAVEDOOR.obj",false)
    --modelLibraryAPI.addModel("COL_Dungeon1Interior","../Assets/Models/Liz_Dungeons/Dungeon1Interior.obj",false)
    --modelLibraryAPI.addModel("COL_Dungeon1InteriorEntrance","../Assets/Models/Liz_Dungeons/Dungeon1InteriorEntrance.obj",false)
	modelLibraryAPI.addModel("COL_Rock","../Assets/Models/Rocks/Boulder/Rock.obj",false)
	modelLibraryAPI.addModel("Airship","../Assets/Models/Airship/airship.lwo",false)
	modelLibraryAPI.addModel("Skybox","../Assets/Models/SkyBox/skybox.obj",false)
	modelLibraryAPI.addModel("Bob","../Assets/Models/Bob/Bob.md5mesh",false)
	modelLibraryAPI.addModel("COL_Cactus","../Assets/Models/Cactus1/cactus.obj",false)
	modelLibraryAPI.addModel("COL_Crate","../Assets/Models/Crate/crate.obj",false)
	modelLibraryAPI.addModel("COL_Titan","../Assets/Models/Titan/Titan class II cargo ship landed.obj",false)
	modelLibraryAPI.addModel("COL_GunShop","../Assets/Models/GunsShop/GunsShop.obj",false)
    modelLibraryAPI.addModel("Pistol","../Assets/Models/pistol.obj",false)
    modelLibraryAPI.addModel("Bullet","../Assets/Models/Bullet.obj",false)
    modelLibraryAPI.addModel("btnNewGame","../Assets/Models/UI/newgame.obj",false)
    modelLibraryAPI.addModel("btnLoad","../Assets/Models/UI/load.obj",false)
    modelLibraryAPI.addModel("btnGame1","../Assets/Models/UI/game1.obj",false)
    modelLibraryAPI.addModel("btnGame2","../Assets/Models/UI/game2.obj",false)
    modelLibraryAPI.addModel("btnGame3","../Assets/Models/UI/game3.obj",false)
    modelLibraryAPI.addModel("btnBack","../Assets/Models/UI/back.obj",false)
    modelLibraryAPI.addModel("btnSave","../Assets/Models/UI/save.obj",false)
    modelLibraryAPI.addModel("btnReturn","../Assets/Models/UI/backToGame.obj",false)
    modelLibraryAPI.addModel("btnContinue","../Assets/Models/UI/continue.obj",false)
    modelLibraryAPI.addModel("btnQuit","../Assets/Models/UI/quit.obj",false)
    modelLibraryAPI.addModel("btnEasy","../Assets/Models/UI/easy.obj",false)
    modelLibraryAPI.addModel("btnMedium","../Assets/Models/UI/med.obj",false)
    modelLibraryAPI.addModel("btnHard","../Assets/Models/UI/hard.obj",false)
    modelLibraryAPI.addModel("whiteCube","../Assets/Models/UI/whitecube.obj",false)
    modelLibraryAPI.addModel("COL_Observatory","../Assets/Models/ObservatoryOutpost/ObservatoryOutpost_fin.obj",false)
	modelLibraryAPI.addModel("COL_FarmHouse","../Assets/Models/Farmhouse/farmhouse_obj.obj",false)
	modelLibraryAPI.addModel("COL_GeneralStore","../Assets/Models/GeneralStore/gs.obj",false)
	modelLibraryAPI.addModel("COL_Saloon","../Assets/Models/Saloon/saloon.obj",false)
	modelLibraryAPI.addModel("COL_Blacksmith","../Assets/Models/Blacksmith/bs.obj",false)
	--modelLibraryAPI.addModel("WaterWell","../Assets/Models/WaterWell/Fountain.obj",false)
    modelLibraryAPI.addModel("ObsTech","../Assets/Models/scifi box/scifibox.obj",false)


	soundAPI.addSound("HappyHour",'../Assets/Sounds/HappyHour.wav')
    soundAPI.addSound("Gunshot",'../Assets/Sounds/341255__jeremysykes__gunshot00.wav')
    soundAPI.addSound("Hit",'../Assets/Sounds/387434__blosche__hard-hit.wav')



	printAPI.print('Loading Terrain...\n')    
	--
	worldWidthChunks = 8
	--The world space size of a terrain chunk
	wsChunkSize = 256

	--The pixel width of a heightmap piece
	mapPieceSize = 257
	--The total pixel width of the heightmap
	totalMapSize = worldWidthChunks * (mapPieceSize-1) + 1
    
	--The total worldspace size of the terrain
	wsTerrainSize = totalMapSize - 1

	--The world space maximum height of the terrain
    heightScale = 50

	terrainHeightData = {}
	terrainHeightData["heightMap"] = {}
	terrainHeightData["alphaMap"] = {}

	local j
	for j = 1, 2057, 1 do
	terrainHeightData["heightMap"][j]= {}
	terrainHeightData["alphaMap"][j]= {}
	end

	local x
	local y
	for y = 1, worldWidthChunks, 1 do
		for x = 1, worldWidthChunks, 1 do
			--Get the terrain chunk data from the map piece		
			hmPath = "../Assets/HeightMaps/HM_Pieces/map_" .. x .. "_" .. y .. ".png"
			alphaMapPath = "../Assets/HeightMaps/AM_Pieces/map_" .. x .. "_" .. y .. ".png"

			terrainChunkData = terrainAPI.generateTerrain(wsChunkSize, wsChunkSize, mapPieceSize, heightScale, hmPath, alphaMapPath, "../Assets/Models/Terrain/Terrain_" .. x .. "_" .. y .. ".obj", context.handle)			
			--Iterate through the height data and add it to the main table of values
			for yy = 1, mapPieceSize, 1 do
				for xx = 1, mapPieceSize, 1 do
					terrainHeightData["heightMap"][(y-1)*(mapPieceSize-1) + yy][(x-1)*(mapPieceSize-1) + xx] = terrainChunkData["heightMap"][yy][xx]					
					terrainHeightData["alphaMap"][(y-1)*(mapPieceSize-1) + yy][(x-1)*(mapPieceSize-1) + xx] = terrainChunkData["alphaMap"][yy][xx]					
				end
			end
			printAPI.print('Chunk ')
			printAPI.print((y-1)*8 + x)
			printAPI.print('loaded. \n')
			--modelLibraryAPI.addModel("Terrain_" .. x .. "_" .. y,"../Assets/Models/Terrain/Terrain_" .. x .. "_" .. y .. ".obj",false)
		end
	end	

	for y = 1, worldWidthChunks, 1 do
		for x = 1, worldWidthChunks, 1 do
			modelLibraryAPI.addModel("Terrain_" .. x .. "_" .. y,"../Assets/Models/Terrain/Terrain_" .. x .. "_" .. y .. ".obj",false)
		end
	end
end


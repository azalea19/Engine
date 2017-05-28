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
end

function LoadAssets()

	printAPI.print('Loading Models...\n')

	--printAPI.print = function() end
	--modelLibraryAPI.addModel("Airship","../Assets/Models/Airship/airship.lwo",false)
	modelLibraryAPI.addModel("Skybox","../Assets/Models/SkyBox/skybox.obj",false)
	modelLibraryAPI.addModel("Bob","../Assets/Models/Bob/Bob.md5mesh",false)
	modelLibraryAPI.addModel("Cactus","../Assets/Models/Cactus1/cactus.obj",false)
	modelLibraryAPI.addModel("Crate","../Assets/Models/Crate/crate.obj",false)
	--modelLibraryAPI.addModel("Titan","../Assets/Models/Titan/Titan class II cargo ship landed.obj",false)
	modelLibraryAPI.addModel("GunShop","../Assets/Models/GunsShop/GunsShop.obj",false)
	--modelLibraryAPI.addModel("FarmHouse","../Assets/Models/Farmhouse/farmhouse_obj.obj",false)


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


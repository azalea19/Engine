
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
	modelLibraryAPI.addModel("TestObject","../Assets/Models/Crate/crate.obj",false)
	modelLibraryAPI.addModel("TestObject_Titan","../Assets/Models/Titan/Titan class II cargo ship landed.obj",false)
	modelLibraryAPI.addModel("TestObject_GunShop","../Assets/Models/GunsShop/GunsShop.obj",false)
	--modelLibraryAPI.addModel("FarmHouse","../Assets/Models/Farmhouse/farmhouse_obj.obj",false)


	printAPI.print('Loading Terrain...\n')

    hMapPath = "../Assets/HeightMaps/perlin_noise.png"
	alphaMapPath = "../Assets/HeightMaps/alphaMap.png"
    terrainSizeX = 1024
    terrainSizeY = 1024
    heightMapSize = 256
    heightMapHeight = 50


	terrainHeightData = terrainAPI.generateTerrain(terrainSizeX, terrainSizeY, heightMapSize, heightMapHeight, hMapPath, alphaMapPath, "../Assets/Models/Terrain/Terrain.obj", context.handle)	
	modelLibraryAPI.addModel("Terrain","../Assets/Models/Terrain/Terrain.obj",false)
end


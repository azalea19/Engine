local Vector3 = dofile '../Assets/Scripts/Vector3.lua'
local gameObject = dofile '../Assets/Scripts/gameObject.lua'


boundingbox = {}
collidableObjects = {}
terrainChunks ={}
objects = {}


function DealWith(instance,x,z,scaleX,scaleY,scaleZ,yaw,pitch,roll)
	local height = GetHeightAtPoint(x,z)
	objectInstanceAPI.setTranslation(instance, x,height,z)
	objectInstanceAPI.setScale(instance, scaleX,scaleY,scaleZ)
	objectInstanceAPI.setOrientation(instance,yaw,pitch,roll)
end

function CreateCactusField(myscene)
	local x	
	for x = 1, 256, 1 do
		local xRand = math.random(5, wsTerrainSize - 5)
		local zRand = math.random(5, wsTerrainSize - 5)
		local xRotRand = math.random(360)
		--DealWith(cactus, xRand,zRand, .1,.1,.1, 0, 0,0)
		local alphaVal = GetAlphaMapValue(xRand,zRand)
		printAPI.print(alphaVal)
		if alphaVal > 0 then		
			--collidableObjects[#collidableObjects + 1] = cactus
			cactus = gameObject.new("0","Cactus","Cactus",Vector3.new(xRand,0,zRand),Vector3.new(xRotRand,0,0), Vector3.new(.1,.1,.1),0)
			--function gameObject.new(strID, newName, newModel, newPos, newDir, newScale, newAnim)

			myscene:AddInstance(cactus)
		end
	end
end

function CreateTerrain(myscene)
	for y = 1, worldWidthChunks, 1 do
		for x = 1, worldWidthChunks, 1 do
			 local var= luaObjInstManager.addNewInstance("Terrain_" .. x .. "_" .. y)
			 terrainChunks[(y-1)*worldWidthChunks+x] = var
			objectInstanceAPI.setTranslation(terrainChunks[(y-1)*worldWidthChunks+x],(x-1)*wsChunkSize,0,(y-1)*wsChunkSize)		
		end
	end
	myscene.terrainChunks = terrainChunks
end

function CreateTown()

	printAPI.print("Initialising text...\n")
	printAPI.print('Initialising terrain...\n')
	Terrain01 = luaObjInstManager.addNewInstance("Terrain")
	objectInstanceAPI.setTranslation(Terrain01,0,0,0)
	
	skybox = luaObjInstManager.addNewInstance("Skybox")
	DealWith(skybox, 0,0, 1000,1000,1000, 0,0,0)

	gunShop = luaObjInstManager.addNewInstance("TestObject_Titan")
  objectInstanceAPI.setScale(gunShop, 1, 1, 1)
	objectInstanceAPI.setTranslation(gunShop, 200, GetHeightAtPoint(50, 50) - 10, 200)
  collidableObjects[#collidableObjects + 1] = gunShop

	 --function gameObject.new(strID, newName, newModel, newPos, newDir, newScale, newAnim)
	gunShop = gameObject.new("0","GunShop","GunShop",Vector3.new(1024,0,1029),Vector3.new(0,0,0), Vector3.new(.008,.008,.008),0)
	myscene:AddInstance(gunShop)

	farmHouse = gameObject.new("0","FarmHouse","FarmHouse",Vector3.new(1034,0,1024),Vector3.new(0,0,0), Vector3.new(.25,.25,.25),0)
	myscene:AddInstance(farmHouse)

	generalStore = gameObject.new("0","GeneralStore","GeneralStore",Vector3.new(1044,0,1020),Vector3.new(0,0,0), Vector3.new(.15,.15,.15),0)
	myscene:AddInstance(generalStore)
	
  BoxTest = luaObjInstManager.addNewInstance("TestObject");
  objectInstanceAPI.setTranslation(BoxTest, 50, GetHeightAtPoint(50, 50) + 10, 50)
  objectInstanceAPI.setScale(BoxTest, 20, 20, 20)
  collidableObjects[#collidableObjects + 1] = BoxTest

	--collidableObjects[#collidableObjects + 1] = gunShop

	--CreateCactusField()
	
    printAPI.print('Initialising camera...\n')
    camera0 = cameraAPI.addNewInstance()
    cameraAPI.setPosition(camera0,terrainSizeX / 2, 30, terrainSizeY / 2)

	saloon = gameObject.new("0","Saloon","Saloon",Vector3.new(1034,0,990),Vector3.new(0,0,0), Vector3.new(.1,.1,.1),0)
	myscene:AddInstance(saloon)

	blacksmith = gameObject.new("0","Blacksmith","Blacksmith",Vector3.new(1024,0,990),Vector3.new(0,0,0), Vector3.new(.06,.06,.06),0)
	myscene:AddInstance(blacksmith)

    printAPI.print('Initialising player...\n')
	player0 = Player:new(camera0)
	cameraAPI.setPosition(camera0,100,0,100)
    player0:setAABB(-0.4,0.4,0,1.8,-0.4,0.4) 

	waterwell = gameObject.new("0","WaterWell","WaterWell",Vector3.new(1124,0,1024),Vector3.new(0,0,0), Vector3.new(.001,.001,.001),0)
	myscene:AddInstance(waterwell)

  --if createCollisionTree then
	--  collisionAPI.createCollisionTree(collidableObjects);
  --end
	
	printAPI.print('Initialization finished.\n')
end

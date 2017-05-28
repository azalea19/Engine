local Vector3 = dofile '../Assets/Scripts/Vector3.lua'

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

function CreateCactusField()
	local x	
	for x = 1, 256, 1 do
		cactus = luaObjInstManager.addNewInstance("Cactus")
		local xRand = math.random(5, wsTerrainSize - 5)
		local zRand = math.random(5, wsTerrainSize - 5)
		local xRotRand = math.random(360)
		DealWith(cactus, xRand,zRand, .1,.1,.1, 0, 0,0)

		local alphaVal = GetAlphaMapValue(xRand,zRand)
		printAPI.print(alphaVal)
		if alphaVal > 0 then		
			collidableObjects[#collidableObjects + 1] = cactus
		end
	end
end

function CreateTerrain()
	for y = 1, worldWidthChunks, 1 do
		for x = 1, worldWidthChunks, 1 do
			terrainChunks[(y-1)*worldWidthChunks+x] = luaObjInstManager.addNewInstance("Terrain_" .. x .. "_" .. y)
			objectInstanceAPI.setTranslation(terrainChunks[(y-1)*worldWidthChunks+x],(x-1)*wsChunkSize,0,(y-1)*wsChunkSize)
		end
	end
end

function CreateTown()

	printAPI.print("Initialising text...\n")
	printAPI.print('Initialising terrain...\n')
	
	--Terrain01 = luaObjInstManager.addNewInstance("Terrain")
	--objectInstanceAPI.setTranslation(Terrain01,0,0,0)
	
	skybox = luaObjInstManager.addNewInstance("Skybox")
	DealWith(skybox, 0,0, 10000,10000,10000, 0,0,0)

	gunShop = luaObjInstManager.addNewInstance("GunShop")
	DealWith(gunShop, 0,0, .015,.015,.015, 0,0,0)

  BobTest = luaObjInstManager.addNewInstance("Bob");
  DealWith(BobTest, 100,150, 1,1,1, 0,0,0)

	titan = luaObjInstManager.addNewInstance("Titan")
	DealWith(titan, 50,50, 1,1,1, 0,0,0)

	collidableObjects[#collidableObjects + 1] = gunShop

	CreateTerrain()
	CreateCactusField()
	
    printAPI.print('Initialising camera...\n')
    camera0 = cameraAPI.addNewInstance()
    --cameraAPI.setPosition(camera0,wsChunkSize / 2, 30, wsChunkSize / 2)

    printAPI.print('Initialising player...\n')
	player0 = Player:new(camera0)
	player0:setPosition(Vector3.new(1000,0,1000))

	--cameraAPI.setPosition(camera0,100,0,100)
	--cameraAPI.setPosition(camera0,1,0,1)

    player0:setAABB(-0.1,0.1,-1.8,0,-0.1,0.1) 

	collidableObjects["length"] = #collidableObjects;

  if createCollisionTree then
	  collisionAPI.createCollisionTree(collidableObjects);
  end
	
	printAPI.print('Initialization finished.\n')

end

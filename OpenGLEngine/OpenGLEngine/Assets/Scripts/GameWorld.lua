boundingbox = {}
collidableObjects = {}

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
		local xRand = math.random(5, terrainSizeX - 5)
		local zRand = math.random(5, terrainSizeY - 5)
		local xRotRand = math.random(360)
		DealWith(cactus, xRand,zRand, .1,.1,.1, 0, 0,0)
		collidableObjects[#collidableObjects + 1] = cactus
	end
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

  BobTest = luaObjInstManager.addNewInstance("Bob");
  DealWith(BobTest, 100,150, 1,1,1, 0,0,0)

  BoxTest = luaObjInstManager.addNewInstance("TestObject");
  objectInstanceAPI.setTranslation(BoxTest, 50, GetHeightAtPoint(50, 50) + 10, 50)
  objectInstanceAPI.setScale(BoxTest, 20, 20, 20)
  collidableObjects[#collidableObjects + 1] = BoxTest

	--collidableObjects[#collidableObjects + 1] = gunShop

	--CreateCactusField()
	
    printAPI.print('Initialising camera...\n')
    camera0 = cameraAPI.addNewInstance()
    cameraAPI.setPosition(camera0,terrainSizeX / 2, 30, terrainSizeY / 2)


    printAPI.print('Initialising player...\n')
	player0 = Player:new(camera0)
	cameraAPI.setPosition(camera0,100,0,100)
    player0:setAABB(-0.4,0.4,0,1.8,-0.4,0.4) 

	collidableObjects["length"] = #collidableObjects;

  if createCollisionTree then
	  collisionAPI.createCollisionTree(collidableObjects);
  end
	
	printAPI.print('Initialization finished.\n')

end

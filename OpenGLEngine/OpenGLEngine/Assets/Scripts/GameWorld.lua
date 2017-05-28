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
	for x = 1, 2000, 1 do
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

	gunShop = luaObjInstManager.addNewInstance("GunShop")
	DealWith(gunShop, 0,0, .015,.015,.015, 0,0,0)

	collidableObjects[#collidableObjects + 1] = gunShop
	
	--ANIMATION
	--bob = luaObjInstManager.addNewInstance("Bob")
	--DealWith(bob, 0,0, 1,1,1, 0,-90,0)
	--objectInstanceAPI.setAnimation(bob,0)

	CreateCactusField()
	
    printAPI.print('Initialising camera...\n')
    camera0 = cameraAPI.addNewInstance()
    cameraAPI.setPosition(camera0,terrainSizeX / 2, 30, terrainSizeY / 2)


    printAPI.print('Initialising player...\n')
	player0 = Player:new(camera0)
	cameraAPI.setPosition(camera0,100,0,100)
    player0:setAABB(-0.1,0.1,-1.8,0,-0.1,0.1) 

	collidableObjects["length"] = #collidableObjects;
	collisionAPI.createCollisionTree(collidableObjects);
	
	printAPI.print('Initialization finished.\n')

end

-- todo needs some work. NPC should inherit from this class, but most functionality is in NPC that should be in both.

local gameObject = {}
gameObject.__index = gameObject

function gameObject.new(strID, newName, newModel, newPos, newDir, newScale, newAnim)

	instanceID = luaObjInstManager.addNewInstance(newModel)

	local instance = 
	{
		model = newModel, -- Name of model (must be accurate to load correctly)
		direction = newDir, -- Direction
		name = newName, -- Name of this object, assume visible to player
		stringID = strID, -- String ID for constant reference to this object despite saving and loading granting new object instance IDs. Pass in 0 to generate new unique ID (based on generated instance ID and time+date).
		id = instanceID, -- Unique Object Instance ID
		scale = newScale, -- Scale
		animation = newAnim, -- Current animation index
		boundingBox = { min ={x=0,y=0,z=0}, max={x=0,y=0,z=0} }, -- AABB for collisions
		playerLookAt = false, -- Is the player looking at the object
		displayNameOnLook = true,
		visible = true,
		objType = "GameObject",
        defaultAnim = newAnim
		
	}	
	instance.upVector = {x=0,y=1,z=0}

	if(instance.stringID == 0) then
		debugLPrint("Generating stringID for object: ")
		instance.stringID = instance.model .. instance.id .."-".. os.date("%x-%X")
		debugLPrint(instance.stringID .."\n")
	end
	
	setmetatable(instance, gameObject)
	
	if(newPos.y == 0) then
		newPos.y = GetHeightAtPoint(newPos.x , newPos.z)
	end

	objectInstanceAPI.setTranslation(instanceID,newPos.x,newPos.y,newPos.z)
	objectInstanceAPI.setOrientation(instanceID,newDir.x,newDir.y,newDir.z)
	objectInstanceAPI.setScale(instanceID,newScale.x,newScale.y,newScale.z)
	objectInstanceAPI.setAnimation(instanceID,0)
	--renderManagerAPI.addObject(instanceID)
	
	local abox = AABBAPI.getAABB(instanceID, context.handle)
	
	if abox ~= nil then
	
		abox.min = mmath.vec3_Multiply(abox.min,newScale,context.handle)
		abox.max = mmath.vec3_Multiply(abox.max,newScale,context.handle)
	else
		printAPI.print("Warning: Created object with nil aabb")
	end
	instance.boundingBox = abox
	
	--printVec3s(boundingBox.min,boundingBox.max)
	return instance
end

function gameObject:setAnimation(n)
    if tonumber (n) then
		printAPI.print("Setting basic int anim to ".. n .."\n")
        objectInstanceAPI.setAnimation(self.id,n)
        self.animation = n
    else
        if(n[1]=="Section") then
			printAPI.print("Setting section anim\n")
            objectInstanceAPI.setAnimationSection(self.id, n[2], n[3])
        end

    end
	
	objectInstanceAPI.setAnimationStartTime(self.id,timeAPI.elapsedTimeMs())


    
end
function gameObject:lookAt(npos)
    debugPrint("Looking at...")
	objectInstanceAPI.lookAt(self.id,self.upVector,npos)
    debugPrint("Look at complete.\n")
end


function gameObject:setPosition(pos)
	objectInstanceAPI.setTranslation(self.id,pos.x,pos.y,pos.z)
end
  
function gameObject:getPosition()
    return objectInstanceAPI.getTranslation(self.id,context.handle)
end

function gameObject:getForward()
	return objectInstanceAPI.forward(self.id,context.handle)
end


function gameObject:BBToWorld()

	--if (self.boundingBox ~= nil) then
		local newBB = {}
		--printAPI.print("Getting BB to world... ")
		
		newBB.min = mmath.vec3_Sum(self.boundingBox.min,self:getPosition(),context.handle)
		newBB.max = mmath.vec3_Sum(self.boundingBox.max,self:getPosition(),context.handle)
		--printAPI.print("Got BB to world.")
		
		--printVec3s(self.boundingBox.min,self.boundingBox.max)

		return newBB
	--else
		--return nil
	--end
	
end

function gameObject:Update()
	--printAPI.print("Updating gameobject " .. self.id .. "\n")
end

function gameObject:getPos()
	return gameObject.position
end

function gameObject:getDir()
	return gameObject.direction
end

function gameObject:setDir(newDir)
	objectInstanceAPI.setOrientation(self.id,newDir.x,newDir.y,newDir.z)
end

function gameObject:getScale()
	return gameObject.scale
end



function gameObject:setScale(newScale)
	objectInstanceAPI.setScale(instanceID,newScale.x,newScale.y,newScale.z)
end


function gameObject:getAnim()
	return gameObject.animation
end

function gameObject:getID()
	return gameObject.id
end

function gameObject:getName()
	return gameObject.name
end

function gameObject:getModel()
	return gameObject.model
end

return gameObject
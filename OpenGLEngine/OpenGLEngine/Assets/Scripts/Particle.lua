local Vector3 = dofile "../Assets/Scripts/Vector3.lua"

local Particle = {}
Particle.__index = Particle


function Particle.new(_particleEmitter, _time)
	instance = 
	{
		position = _particleEmitter.position,
		creationTime = _time,
		ttl = 5,
		velocity = Vector3.new(0.5, 0.5, 0.5),
		id = luaObjInstManager.addNewInstance("Bob")
	}
	objectInstanceAPI.setTranslation(instance.id, instance.position.x, instance.position.y, instance.position.z)
	objectInstanceAPI.setScale(instance.id, 100, 100, 100)
	return instance
end

function Particle:render(camera, time, enableLighting)
	renderManagerAPI.renderObject(camera,time,self.id, enableLighting)
end

function Particle:update(time)

	self.position.x = self.position.x + self.velocity.x
	self.position.y = self.position.y + self.velocity.y
	self.position.z = self.position.z + self.velocity.z
	objectInstanceAPI.setTranslation(self.id, self.position.x, self.position.y, self.position.z)

	self.velocity.y = self.velocity.y - 0.05

	local timeElapsed = time - self.creationTime

	printAPI.print("\n\n\n" .. timeElapsed .. "\n" .. self.ttl .. "\n\n\n")
	--if (timeElapsed > self.ttl) then
	--	return false
	--else
	--	return true
	--end
	return true
end

return Particle
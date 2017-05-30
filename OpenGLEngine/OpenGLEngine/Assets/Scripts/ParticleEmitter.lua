local ParticleEmitter = {}
ParticleEmitter.__index = ParticleEmitter


--_particleClas should be a class with :
    --new(_particleEmitter, time), _particleEmiiter is an arg primarily so the particle constructor has access to the emitters position
    --update(time) return false if the particle should be destroyed, true otherwise, this should update position of particle
    --render(camera, time, enableLighting)

function ParticleEmitter.new(_particleClass, _particlesPerSecond, _position, _time)
	instance = 
	{
		particleClass = _particleClass,
		particlesPerSecond = _particlesPerSecond,
		position = _position,
		startTime = _time,
		particlesCreated = 0,
		particlesDestroyed = 0,
		particlesAlive = 0,
		particles = {}
	}
	setmetatable(instance, ParticleEmitter)
	return instance
end


function ParticleEmitter:setPosition(newPos)
	self.position = newPos
end

function ParticleEmitter:render(camera, time, enableLighting)
	local p
	if(self.particlesCreated > self.particlesDestroyed) then
		for p = self.particlesDestroyed + 1, self.particlesCreated, 1 do
			self.particles[p]:render(camera, time, enableLighting)
		end
	end
end

function ParticleEmitter:update(time)
  --create new particles
  local timeElapsed = time - self.startTime
  local particlesExpected = timeElapsed * self.particlesPerSecond
  while math.floor(particlesExpected) > self.particlesCreated do
    self:addParticle(time)
  end

	local p
	if(self.particlesCreated > self.particlesDestroyed) then
		for p = self.particlesDestroyed + 1, self.particlesCreated, 1 do
			particle = self.particles[p]
			if particle:update(time) == false then
				self.particles[p] = nil
				self.particlesDestroyed = self.particlesDestroyed + 1
			end
		end
	end
end

function ParticleEmitter:addParticle(time)
  self.particles[self.particlesCreated + 1] = self.particleClass.new(self, time)
  self.particlesCreated = self.particlesCreated + 1
end

return ParticleEmitter
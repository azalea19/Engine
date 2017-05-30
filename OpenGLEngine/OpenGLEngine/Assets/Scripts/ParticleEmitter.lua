local Particle = dofile "../Assets/Scripts/Particle.lua"
local ParticleEmitter = {}
ParticleEmitter.__index = ParticleEmitter


--_particleClas should be a class with :
    --new(_particleEmitter, time), _particleEmiiter is an arg primarily so the particle constructor has access to the emitters position
    --update(time) return false if the particle should be destroyed, false otherwise, this should update position of particle
    --render(camera, time, enableLighting)

function ParticleEmitter.new(_particleClass, _particlesPerSecond, _particleTTL, _position, _time)
	instance = 
	{
    _particleClass
	  particlesPerSecond = _particlesPerSecond
    position = _position
    startTime = _time
    particlesCreated = 0
    particlesDestroyed = 0
    particlesAlive = 0
    particles = {}
	}
	setmetatable(instance, ParticleEmitter)
	return instance
end


function ParticleEmitter:setPosition(newPos)
	self.position = newPos
end

function ParticleEmitter:render(camera, time, enableLighting)
  local p;
  for p = particlesDestroyed + 1, particlesCreated, 1 do
    particles[p]:render(camera, time, enableLighting)
end

function ParticleEmitter:update(time)

  --create new particles
  local timeElapsed = time - startTime
  local particlesExpected = timeElapsed * particlesPerSecond
  while math.floor(particlesExpected) > particlesCreated do
    self:addParticle(time)
  end

  --Update particles and destroy any that need destroying
  while particlesDestroyed < particlesCreated and not (particles[particlesDestroyed + 1]:update(time)) do
    particles[particlesDestroyed + 1] = nil
    particlesDestroyed = particlesDestroyed + 1
  end
end

function ParticleEmitter:addParticle(time)
  particles[particlesCreated + 1] = particleClass.new(self, time)
end

return ParticleEmitter
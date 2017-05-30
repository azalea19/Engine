local Weapon = {}
Weapon.__index = Weapon


function Weapon.new(iid,iname,idmg,ishootInterval,irange)
	instance = 
	{
		id=iid,
		name=iname,
		damage = idmg,
		shootInterval = ishootInterval,
		range = irange or nil,
        lastTimeShot = 0,
        lastTimeOfAttack = 0
	}

	setmetatable(instance, Weapon)
	return instance
end

function Weapon:attack(myObj)

    debugLPrint("Weapon attacking ")
    if(self.lastTimeShot ==0 or self.lastTimeShot>= self.shootInterval) then
        debugLPrint("Weapon attack success")
    	myObj:takeDamage(self.damage)
        self.lastTimeShot = timeAPI.elapsedTimeMs()
        return true
    end
    return false


end

return Weapon
local Vector3 = {}

function Vector3.new(newX, newY, newZ)
	local instance = {
		x = newX,
		y = newY,
		z = newZ
	}

	setmetatable(instance, Vector3)
	return instance
end

return Vector3
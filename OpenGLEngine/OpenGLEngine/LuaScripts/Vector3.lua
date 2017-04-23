local Vector3 = {}
--A basic vector 3 class
function Vector3.new(x, y, z)
	local instance = {
		X = x,
		Y = y,
		Z = z
	}
	setmetatable(instance, Vector3)
	return instance
end

return Vector3
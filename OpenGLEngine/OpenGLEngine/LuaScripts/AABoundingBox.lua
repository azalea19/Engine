local AABoundingBox = {}
--A bounding box object, contains all data for an AABB
function AABoundingBox.new(NewMinX, NewMaxX, NewMinY, NewMaxY, NewMinZ, NewMaxZ)
	local instance = {
		minX = NewMinX,
		minY = NewMinY,
		minZ = NewMinZ,
		maxX = NewMaxX,
		maxY = NewMaxY,
		maxZ = NewMaxZ
	}
	setmetatable(instance, AABoundingBox)
	return instance
end

return AABoundingBox 
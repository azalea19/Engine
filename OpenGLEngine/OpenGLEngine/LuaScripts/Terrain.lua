function GetHeightAtPoint(x, y)
	if(x < 0) then
		x = 0
	end
	if(x > terrainSizeX) then
		x = terrainSizeX - 2
	end
	if(y < 0) then
		y = 0
	end
	if(y > terrainSizeY) then
		y = terrainSizeY - 2
	end
	xScale = terrainSizeX / heightMapSize
	yScale = terrainSizeY / heightMapSize

	xPixel = (x / terrainSizeX) * heightMapSize
	yPixel = (y / terrainSizeY) * heightMapSize
	BottomLeft = terrainHeightData[math.floor(xPixel) + 1][math.floor(yPixel) + 1]
	BottomRight = terrainHeightData[math.floor(xPixel) + 2][math.floor(yPixel) + 1]
	TopLeft = terrainHeightData[math.floor(xPixel) + 1][math.floor(yPixel) + 2]
	TopRight = terrainHeightData[math.floor(xPixel) + 2][math.floor(yPixel) + 2]
	if(x + y <= xPixel * xScale + yScale * yScale ) then
		z1 = TopLeft
		z2 = BottomRight
		z3 = BottomLeft
		x1 = (math.floor(xPixel) + 1) * xScale
		x2 = (math.floor(xPixel) + 2) * xScale
		x3 = (math.floor(xPixel) + 1) * xScale
		y1 = (math.floor(yPixel) + 2) * yScale
		y2 = (math.floor(yPixel) + 1) * yScale
		y3 = (math.floor(yPixel) + 1) * yScale

		first = ((y2 - y3) * (x - x3) + (x3 - x2) * (y - y3)) / ((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3))
		second = ((y3 - y1) * (x - x3) + (x1 - x3) * (y - y3)) / ((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3))
		third = 1 - first - second
		resultHeight = first * z1 + second * z2 + third * z3
	else
		z1 = TopLeft
		z2 = TopRight
		z3 = BottomRight
		x1 = (math.floor(xPixel) + 1) * xScale
		x2 = (math.floor(xPixel) + 2) * xScale
		x3 = (math.floor(xPixel) + 2) * xScale
		y1 = (math.floor(yPixel) + 2) * yScale
		y2 = (math.floor(yPixel) + 2) * yScale
		y3 = (math.floor(yPixel) + 1) * yScale

		first = ((y2 - y3) * (x - x3) + (x3 - x2) * (y - y3)) / ((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3))
		second = ((y3 - y1) * (x - x3) + (x1 - x3) * (y - y3)) / ((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3))
		third = 1 - first - second
		resultHeight = first * z1 + second * z2 + third * z3
	end
			--[[differenceInHeight = TopLeft - BottomLeft
		decimalPart = yPixel - math.floor(yPixel)
		changeBy = differenceInHeight * decimalPart
		leftSide = BottomLeft + changeBy

		differenceInHeight = TopRight - BottomRight
		decimalPart = yPixel - math.floor(yPixel)
		changeBy = differenceInHeight * decimalPart
		rightSide = BottomRight + changeBy

		differenceInHeight = leftSide - rightSide
		decimalPart = xPixel - math.floor(xPixel)
		changeBy = differenceInHeight * decimalPart
		resultHeight = leftSide + changeBy]]

	return resultHeight
end
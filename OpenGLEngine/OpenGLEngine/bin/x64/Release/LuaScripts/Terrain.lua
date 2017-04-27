function lerp(a, b, t)

	return a * (1-t) + b * t
end

function biLerp(p00, p10, p01, p11, tx,ty)
	local h0 = lerp(p00,p10,tx);
	local h1 = lerp(p01,p11,tx);

	return lerp(h0,h1,ty);
end

function mapRange(u1,u2,v1,v2, value)
	local lerpFactor = (value-u1)/(u2-u1)
	return lerp(v1,v2,lerpFactor)
end

function WSToHeightMapSpace(wsX,wsZ)
	local hmX = mapRange(0,terrainSizeX, 0.5, heightMapSize-0.5, wsX)
	local hmY = mapRange(0, terrainSizeY, 0.5, heightMapSize-0.5, wsZ)

	return hmX,hmY
end

function GetHeightAtPoint(x,y)
	--returned as floating value
	local hmX, hmY = WSToHeightMapSpace(x,y)
	hmX = hmX - 0.5	+ 1
	hmY = hmY - 0.5 + 1

	local sampleX = math.floor(hmX) 
	local sampleY = math.floor(hmY) 

	local lerpFactorX = hmX - sampleX
	local lerpFactorY = hmY - sampleY

	local h00 = terrainHeightData[sampleX][sampleY]
	local h10 = terrainHeightData[sampleX+1][sampleY]
    local h01 = terrainHeightData[sampleX][sampleY + 1]
	local h11 = terrainHeightData[sampleX + 1][sampleY + 1]	
	
	return biLerp(h00,h10, h01, h11, lerpFactorX,lerpFactorY)	
end


function GetHeightAtPointNathan(x, y)
	local z1, z2, z3, x1, x2, x3, y1, y2, y3, first, second, third, resultHeight

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

	local xScale = terrainSizeX / heightMapSize
	local yScale = terrainSizeY / heightMapSize

	local xPixel = (x / terrainSizeX) * heightMapSize - 1
	local yPixel = (y / terrainSizeY) * heightMapSize - 1

	local BottomLeft = terrainHeightData[math.floor(xPixel) + 1][math.floor(yPixel) + 1]
	local BottomRight = terrainHeightData[math.floor(xPixel) + 2][math.floor(yPixel) + 1]
	local TopLeft = terrainHeightData[math.floor(xPixel) + 1][math.floor(yPixel) + 2]
	local TopRight = terrainHeightData[math.floor(xPixel) + 2][math.floor(yPixel) + 2]
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
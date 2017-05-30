

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
	debugPrint("Getting world to heightmap space... ")

	local hmX = mapRange(0,wsTerrainSize, 0.5, totalMapSize-0.5, wsX)
	local hmY = mapRange(0, wsTerrainSize, 0.5, totalMapSize-0.5, wsZ)
	
	debugPrint("World to height map space: " .. hmX .." " .. hmY .. " ...")
	debugPrint("Complete gwths\n")

	return hmX,hmY
end

function GetHeightAtPoint(nx,ny)
debugPrint("Getting height at point... ")
--returned as floating value
local hmX, hmY = WSToHeightMapSpace(nx,ny)
hmX = hmX - 0.5	+ 1
hmY = hmY - 0.5 + 1

local sampleX = math.floor(hmX) 
local sampleY = math.floor(hmY) 

local lerpFactorX = hmX - sampleX
local lerpFactorY = hmY - sampleY

local h00 = terrainHeightData["heightMap"][sampleY][sampleX]
local h10 = terrainHeightData["heightMap"][sampleY][sampleX+1]
local h01 = terrainHeightData["heightMap"][sampleY + 1][sampleX]
local h11 = terrainHeightData["heightMap"][sampleY + 1][sampleX + 1]

local val = biLerp(h00,h10, h01, h11, lerpFactorX,lerpFactorY)	
debugPrint("Complete\n")
return val
end

function GetAlphaMapValue(nx,ny)

debugPrint("Getting alpha map value at point... ")
--returned as floating value
local hmX, hmY = WSToHeightMapSpace(nx,ny)
hmX = hmX - 0.5	+ 1
hmY = hmY - 0.5 + 1

local sampleX = math.floor(hmX) 
local sampleY = math.floor(hmY) 

local lerpFactorX = hmX - sampleX
local lerpFactorY = hmY - sampleY

local h00 = terrainHeightData["alphaMap"][sampleY][sampleX]
local h10 = terrainHeightData["alphaMap"][sampleY][sampleX+1]
local h01 = terrainHeightData["alphaMap"][sampleY + 1][sampleX]
local h11 = terrainHeightData["alphaMap"][sampleY + 1][sampleX + 1]
	
local val = biLerp(h00,h10, h01, h11, lerpFactorX,lerpFactorY)	
debugPrint("Complete\n")
return val
end

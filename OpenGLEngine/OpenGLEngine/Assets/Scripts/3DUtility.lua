

-- Distance between 2 given 3d points (vec3) - author Liz
function Distance(vec1,vec2)
    --printAPI.print("Getting Distance.")
	x2 = vec2.x
	x1 = vec1.x
	y1 = vec1.y
	y2 = vec2.y
	z1 = vec1.z
	z2 = vec2.z
    --printVec3s(vec1,vec2)

    local val = (math.sqrt(math.pow(x2 - x1,2) +math.pow(y2 - y1,2)+math.pow(z2 - z1,2)))

    --printAPI.print("Got distance.\n")

	return val
    --(x2 x1)2 + (y2 y1)2 + (z2 z1)2.
end

function Direction(vec1,vec2)
	return mmath.vec3_Normalize(mmath.vec3_Subtract(vec1,vec2,context.handle), context.handle)
end


function AngleDiffDeg(vec1,vec2)


	if(debugdetail) then
	printVec3s(vec1,vec2)
	end
	local dot = mmath.vec3_DotProduct(vec1,vec2)
	debugPrint("Dot product: " .. dot .. " // ")
	local angle = math.acos(dot)* 180 / 3.14
	debugPrint("Angle difference: " .. angle .. "\n")
	return angle 
end

-- Move from source (vec3) to dest (vec3) with the given increment (float) - author Liz
function MoveTowards(source,dest,increment)
	
	if(debugdetail) then
		printAPI.print("Moving towards...\n")
		printVec3After("Source: ",source)
		printVec3After("Dest: ",dest)
		printAPI.print("Increment: " .. increment .. "\n")
	end
	
  direction = Direction(dest,source)

  if Distance(source,dest) <= increment then
	  debugPrint("Complete.\n")
	  return dest
	end
	debugPrint("Getting direction * inc...\n")

	local mult = mmath.vec3_ScalarMultiply(direction,increment,context.handle)
	debugPrint("Getting final loc...\n")

	local am = mmath.vec3_Sum(source,mult,context.handle)
	debugPrint("Complete.\n")
	return am

    --[[
    
        public static void MoveTowards(GameObject2D obj, Vector2 dest, float step)
        {
            Vector2 direction = Vector2.Normalize(dest - obj.pos2D);
            obj.SetPos2D( obj.pos2D + direction * step);

            if (Distance(obj.pos2D, dest) <= step)
            {
                //Console.WriteLine(obj.pos2D.X + "," + obj.pos2D.Y);
                //Console.WriteLine(dest.X + "," + dest.Y);
                obj.SetPos2D(new Vector2(dest.X, dest.Y));

                PrintXnaVec(obj.pos2D);
            }
            
        }
    ]]

end


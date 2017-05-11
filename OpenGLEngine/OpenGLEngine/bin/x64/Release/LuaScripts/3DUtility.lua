-- Move from source (vec3) to dest (vec3) with the given increment (float) - author Liz
function MoveTowards(source,dest,increment)
    

    direction = luaVectorUtility.vec3_normalize(luaVectorUtility.vec3_subtract(dest,source))

    if(Distance(source,dest) <= increment
	{
		return dest
	}
	
	return mmath.vec3_sum(source,mmath.vec3_multiply(direction,increment))

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

-- Distance between 2 given 3d points (vec3) - author Liz
function Distance
	return (math.sqrt(math.pow(x2 - x1,2) +math.pow(y2 - y1,2)+math.pow(z2 - z1,2)))
    --(x2 x1)2 + (y2 y1)2 + (z2 z1)2.
end

#version 400

in vec2 TexCoord0;
layout (location = 0) out vec4 color;

uniform sampler2D inputTex0;
 
 
float uXPixelDistance = 1.0/1280.0;
 
float uYPixelDistance = 1.0/720.0;
 
const float jump = 1.0f;

uniform int blurRadius;
 
void main() 
{
    vec4 tempcolor = vec4(0, 0, 0, 0);
    vec2 point;
    int count = 0;
  
    // Calculate the total color intensity around the pixel
    // In this case we are calculating pixel intensity around 10 pixels
    for(float u = -blurRadius; u <= blurRadius ; u+=jump) 
	{
        for(float v = -blurRadius ; v <= blurRadius ; v+=jump) 
		{
            point.x = TexCoord0.x  + u * uXPixelDistance;
            point.y = TexCoord0.y  + v * uYPixelDistance;
             
            // If the point is within the range[0, 1]
            if (point.y >= 0.0f && point.x >= 0.0f &&
                point.y <= 1.0f && point.x <= 1.0f ) 
				{
					++count;
					tempcolor += texture2D(inputTex0, point.xy);
				}
        }
    }
     
    // Take the average intensity for the region
    tempcolor = tempcolor / float(count);
  
    color = vec4(tempcolor.xyz, 1.0f);
}



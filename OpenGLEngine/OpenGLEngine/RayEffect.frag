#version 400

in vec2 TexCoord0;
layout (location = 0) out vec3 color;

uniform sampler2D inputTex0;
uniform float exposure = 1.0;
uniform float decay = 0.97;
//uniform float density = 0.96;
uniform float density = 1.0;
uniform float weight = 1.0;
uniform vec2 lightPos;

const int NUM_SAMPLES = 200;

vec2 halfPixel = vec2(0.5/1280, 0.5/720);

float aspectRatio = 1280.0 / 720;

void main() 
{

	vec2 uvLightPos = (lightPos.xy + 1) * 0.5f;

	 if(any(greaterThan(uvLightPos.xy, vec2(1.5,1.5))) || any(lessThan(uvLightPos.xy, vec2(-0.5,-0.5))))
            discard;

   vec2 deltaTexCoord = uvLightPos - TexCoord0;
   vec2 tc = TexCoord0;
   deltaTexCoord *= 1.0 / float(NUM_SAMPLES) * density;
   float illuminationDecay = 1.0;

   float totalWeight = 0;

   for(int i=0; i < NUM_SAMPLES; i++)
   {
		tc += deltaTexCoord;
		vec2 fragToLight = uvLightPos - tc;
		fragToLight.x = fragToLight.x * aspectRatio;
		float distance = length(fragToLight) * 8;
		tc.x = clamp(tc.x, halfPixel.x, 1 - halfPixel.x);
		tc.y = clamp(tc.y, halfPixel.y, 1 - halfPixel.y);

		float s = texture2D(inputTex0, tc).x;

		if(s == 1)
			s = 2.0f / (1 + (distance * distance));

		s *= illuminationDecay;
		totalWeight += illuminationDecay;

		color += s;
		illuminationDecay *= decay;

		
   }

   color = color / totalWeight;

   color *= exposure;

   if(length(uvLightPos - TexCoord0) < 0.005)
   {
		color = vec3(1, 0, 0);
   }
   
}



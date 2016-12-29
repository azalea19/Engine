#ifndef Light_h__
#define Light_h__

#include "Types.h"
#include "MMath.h"

/**
* @file   Light.h
* @Author Maddisen Topaz
* @date   S2, 2016
* @brief  The various light structs.
*
* The light class contains the various light structs needed for various lighting.
*/


enum LightType : int
{
  LT_Ambient = 0,
  LT_Directional = 1,
  LT_Point = 2,
  LT_Spot = 3,
};

struct Light
{
  Light(LightType lightType, bool lightEnabled = true)
    :enabled(lightEnabled)
    , type(lightType)
  {
  }

	bool enabled;	
protected:
	LightType type;		
};

struct AmbientLight : public Light
{
  AmbientLight(vec3 const& lightColor = vec3(1.0f,1.0f,1.0f), bool lightEnabled = true)
    : Light(LT_Ambient, lightEnabled)
    , color(lightColor)
  {

  }
	vec3 color;		
};

struct DirectionalLight : public Light
{
  DirectionalLight(vec3 lightDirection, vec3 const& lightColor = vec3(1.0f, 1.0f, 1.0f), bool lightEnabled = true)
    : Light(LT_Directional, lightEnabled)
    , color(lightColor)
    , direction(lightDirection)
  {

  }
	vec3 color;	
	vec3 direction;		
};

struct PointLight : public Light
{
  PointLight(vec3 lightPosition, vec3 const& lightColor = vec3(1.0f, 1.0f, 1.0f), bool lightEnabled = true)
    : Light(LT_Point, lightEnabled)
    , color(lightColor)
    , position(lightPosition)
  {

  }

	vec3 color;		
	vec3 position;		
};

struct SpotLight : public Light 
{
  SpotLight(vec3 lightDirection, vec3 lightPosition, float attenuation, float angleInDegrees, vec3 const& lightColor = vec3(1.0f, 1.0f, 1.0f), bool lightEnabled = true)
    : Light(LT_Spot, lightEnabled)
    , color(lightColor)
    , direction(lightDirection)
    , position(lightPosition)
    , linearAttenuation(attenuation)
  {
    SetConeAngle(angleInDegrees);
  }

  void SetConeAngle(float angleInDegrees)
  {
    coneAngle = angleInDegrees;
    coneCosine = cos(DegToRad(angleInDegrees));
  }

  vec3 color;
  vec3 position;
  vec3 direction;
  float linearAttenuation;

private:

  float coneAngle;
  float coneCosine;

};



#endif

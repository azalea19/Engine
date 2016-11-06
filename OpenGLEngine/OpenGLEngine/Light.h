#ifndef Light_h__
#define Light_h__

#include "Types.h"

/**
* @file   Light.h
* @Author Maddisen Topaz
* @date   S2, 2016
* @brief  The various light structs.
*
* The light class conntains the various light structs needed for various lighting.
*/


enum LightType : int
{
	Ambient = 0,
	Directional = 1,
	Point = 2
};

struct Light
{
	bool enabled;	///< whether the light is enabled
protected:
	LightType type;		///< the type of light
};

struct AmbientLight : public Light
{
	vec3 colour;		///< the colour of the light
	float brightness;	///< the lights brightness
};

struct DirectionalLight : public Light
{
	vec3 colour;		///< the lights colour
	float brightness;	///< the lights brightness
	vec3 direction;		///< the lights direction
};

struct PointLight : public Light
{
	vec3 colour;		///< the lights colour
	float brightness;	///< the lights brightness
	vec3 position;		///< the lights posistion
};



#endif

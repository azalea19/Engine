#ifndef Random_h__
#define Random_h__

#include <stdlib.h>
#include <assert.h>


/**
* @file Random.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief
*
*/

float RandomFloat(float min, float max);

int RandomInt(int min, int max, bool includeMaxVal = false); //range : [min, max) or [min,max]




#endif // Random_h__

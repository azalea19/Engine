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
/// <summary>
/// Gets random float between min and max
/// </summary>
/// <param name="min">Min.</param>
/// <param name="max">Max.</param>
/// <returns>float</returns>
float RandomFloat(float min, float max);
/// <summary>
/// Gets random int between min and max
/// </summary>
/// <param name="min">Min.</param>
/// <param name="max">Max.</param>
/// <param name="includeMaxVal">Whether to include the max value</param>
/// <returns>float</returns>
int RandomInt(int min, int max, bool includeMaxVal = false); //range : [min, max) or [min,max]




#endif // Random_h__

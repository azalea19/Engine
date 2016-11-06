#ifndef MMath_h__
#define MMath_h__

/**
* @file   MMath.h
* @Author Maddisen Topaz
* @date   S2, 2016
* @brief  The math functions.
*
* The various math functions / constants.
*/


#define DegToRad(val) ((val) * 3.1416f / 180)
#define PI 3.1415962654
#define RadToDeg(val) ((val) * 180 / 3.1416f)

#define mMin(a,b) (((a) < (b)) ? (a) : (b))
#define mMax(a,b) (((a) > (b)) ? (a) : (b))
#define mClamp(val, min, max) mMin(mMax((val), (min)), (max))

//Linear interpolate.
#define mLerp(a,b,t) (a) * (1.f-(t)) + (b)*(t)

#endif
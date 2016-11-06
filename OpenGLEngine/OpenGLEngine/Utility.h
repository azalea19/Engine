#ifndef Utility_h__
#define Utility_h__

#include "Types.h"

/**
* @file   Utility.h
* @Author Maddisen Topaz, Elizabeth Haynes
* @date   S2, 2016
* @brief  The model loader.
*
* The utility file contains the various utility functions required for various classes.
*/


/**
* @brief Seperates strings at delimiter
*
* @param s - string
* @param delim - string delimiter
* @param elems - vector <string>
*
* @return void
*/
void split(const string &s, char delim, std::vector<string> &elems);


std::vector<string> split(const string &s, char delim);


/**
* @brief  
* See the following page for further explanation:
* http://eli.thegreenplace.net/2014/variadic-templates-in-c/
*/
template<typename T>
void  CreateVector(std::vector<T>& newVec)
{
}

template<typename T, typename ... Args>
void CreateVector(std::vector<T>& newVec, T val1, Args... args)
{
	newVec.push_back(val1);
	CreateVector(newVec, args...);
}
template<typename T, typename ... Args>
std::vector<T> CreateVector(T val1, Args... args)
{
	std::vector<T> newVec;
	newVec.push_back(val1);
	CreateVector(newVec, args...);
	return newVec;
}


#endif // Utility_h__

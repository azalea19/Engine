#ifndef Utility_h__
#define Utility_h__

#include "Types.h"

/**
* @file   Utility.h
* @Author Maddisen Topaz, Elizabeth Haynes
* @date   S1, 2017
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
/// <summary>
/// Creates the vector.
/// </summary>
/// <param name="newVec">The new vec.</param>
template<typename T>
void  CreateVector(std::vector<T>& newVec)
{
}

/// <summary>
/// Creates the vector.
/// </summary>
/// <param name="newVec">The new vec.</param>
/// <param name="val1">The val1.</param>
/// <param name="...args">The args.</param>
template<typename T, typename ... Args>
void CreateVector(std::vector<T>& newVec, T val1, Args... args)
{
	newVec.push_back(val1);
	CreateVector(newVec, args...);
}
/// <summary>
/// Creates the vector.
/// </summary>
/// <param name="val1">The val1.</param>
/// <param name="...args">The args.</param>
/// <returns></returns>
template<typename T, typename ... Args>
std::vector<T> CreateVector(T val1, Args... args)
{
	std::vector<T> newVec;
	newVec.push_back(val1);
	CreateVector(newVec, args...);
	return newVec;
}


/// <summary>
/// Vectors the concatenate.
/// </summary>
/// <param name="target">The target.</param>
/// <param name="source">The source.</param>
template<typename T>
void VectorConcatenate(std::vector<T>& target, std::vector<T> const& source)
{
	target.reserve(target.size() + source.size());
    for (int i = 0; i < source.size(); i++)
      target.push_back(source[i]);
}


string GetDirectoryFromFileName(string filename);


#endif // Utility_h__

#ifndef ModelLibrary_h__
#define ModelLibrary_h__

#include <unordered_map>
#include <string>
#include "Types.h"

/**
* @file   ModelLibrary.h
* @Author Maddisen Topaz
* @date   S2, 2016
* @brief  The model library.
*
* The model library contains all the models used in various scenes
*/

struct RenderableObject; 
struct ObjectInstance; 
struct ModelLibrary
{

	std::unordered_map<std::string, RenderableObject*> models; 


	void initModelLibrary();


	void addModel(std::string name, std::string path, bool normalized = false);

	
	ObjectInstance* getInstance(std::string name);


	static ModelLibrary* getLib();

};

#endif
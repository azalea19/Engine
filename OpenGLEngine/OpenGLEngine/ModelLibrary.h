#ifndef ModelLibrary_h__
#define ModelLibrary_h__

#include <unordered_map>
#include <string>
#include "Types.h"
#include "Singleton.h"

/**
* @file   ModelLibrary.h
* @Author Maddisen Topaz
* @date   S2, 2016
* @brief  The model library.
*
* The model library contains all the models used in various scenes
*/

class RenderableObject; 
class ObjectInstance; 

class ModelLibrary : public Singleton<ModelLibrary>
{
public:
	void InitModelLibrary();


	void AddModel(string const& name, string const& path, bool normalized = false);


	ObjectInstance* GetObjectInstance(string const& name) const;
private:

	std::unordered_map<string, RenderableObject*> models; 

};

#endif
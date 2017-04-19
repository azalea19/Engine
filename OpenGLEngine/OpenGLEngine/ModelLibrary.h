#ifndef ModelLibrary_h__
#define ModelLibrary_h__

#include <unordered_map>
#include <string>
#include "Types.h"
#include "Singleton.h"
#include "IModelLibrary.h"

/**
* @file   ModelLibrary.h
* @Author Maddisen Topaz
* @date   S2, 2016
* @brief  The model library.
*
* The model library contains all the models used in various scenes
*/

class IRenderableObject; 
class ObjectInstance; 

class ModelLibrary : public Singleton<ModelLibrary> , public IModelLibrary
{

public:

	virtual void Initialise() override;


	virtual void AddModel(string const& modelName, string const& path, bool normalized = false) override;


	virtual ObjectInstance* GetObjectInstance(string const& modelName) const override;


private:

	std::unordered_map<string, RenderableObject*> models; 

};

#endif
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
* @date   S1, 2017
* @brief  The model library.
*
* The model library contains all the models used in various scenes.
*/

class IRenderableObject; 
class ObjectInstance; 

class ModelLibrary : public Singleton<ModelLibrary> , public IModelLibrary
{

public:

  /// <summary>
  /// Initialises this instance.
  /// </summary>
  virtual void Initialise() override;


  /// <summary>
  /// Adds the model.
  /// </summary>
  /// <param name="modelName">Name of the model.</param>
  /// <param name="path">The path.</param>
  /// <param name="normalized">if set to <c>true</c> [normalized].</param>
  virtual void AddModel(string const& modelName, string const& path, bool normalized = false) override;


  /// <summary>
  /// Gets the object instance.
  /// </summary>
  /// <param name="modelName">Name of the model.</param>
  /// <returns></returns>
  virtual ObjectInstance* GetObjectInstance(string const& modelName) const override;


private:

  /// <summary>
  /// The models
  /// </summary>
  std::unordered_map<string, RenderableObject*> models;

};

#endif
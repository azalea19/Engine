#ifndef ModelLibrary_h__
#define ModelLibrary_h__

#include <unordered_map>
#include <string>
#include "Types.h"
#include "Singleton.h"
#include <memory>

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
class IEngine;


class ModelLibrary : public Singleton<ModelLibrary> 
{

public:

  /// <summary>
  /// Initialises this instance.
  /// </summary>
  static void Initialise(IEngine const *pEngine);


  /// <summary>
  /// Adds the model.
  /// </summary>
  /// <param name="modelName">Name of the model.</param>
  /// <param name="path">The path.</param>
  /// <param name="normalized">if set to <c>true</c> [normalized].</param>
  void AddModel(string const& modelName, string const& path, bool normalized = false);


  /// <summary>
  /// Gets the object instance.
  /// </summary>
  /// <param name="modelName">Name of the model.</param>
  /// <returns></returns>
  ObjectInstance* GetObjectInstance(string const& modelName) const;


private:

  /// <summary>
  /// The models
  /// </summary>
  std::unordered_map<string, IRenderableObject*> models;

  /// <summary>
  /// The engine
  /// </summary>
  IEngine const *m_pEngine;

};

#endif
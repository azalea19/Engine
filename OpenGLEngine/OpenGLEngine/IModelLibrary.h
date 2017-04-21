#ifndef IModelLibrary_h__
#define IModelLibrary_h__

#include "types.h"
#include "ObjectInstance.h"

/**
* @file IModelLibrary.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief An interface that allows the user to add functionality associated with a model library.
*
*/


class IModelLibrary
{

public:
 
  /// <summary>
  /// Initialises this instance.
  /// </summary>
  virtual void Initialise() = 0;

  /// <summary>
  /// Finalizes an instance of the <see cref="IModelLibrary" /> class.
  /// </summary>
  virtual ~IModelLibrary() = 0 {}


  /// <summary>
  /// Gets the object instance.
  /// </summary>
  /// <param name="modelName">Name of the model.</param>
  /// <returns>ObjectInstance</returns>
  virtual ObjectInstance* GetObjectInstance(string const& modelName) const = 0;

  /// <summary>
  /// Adds the model.
  /// </summary>
  /// <param name="modelName">Name of the model.</param>
  /// <param name="filePath">The file path.</param>
  /// <param name="normalised">if set to <c>true</c> [normalised].</param>
  virtual void AddModel(string const& modelName, string const& filePath, bool normalised) = 0;


};
#endif // IModelLibrary_h__

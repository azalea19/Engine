#ifndef Loader_h__
#define Loader_h__

#include "Types.h"

/**
* @file   Loader.h
* @Author Maddisen Topaz
* @date   S2, 2016
* @brief  The model loader.
*
* The loader takes an .obj file, parses the data and returns that data in the form of a pointer to a model
* See the following tutorial for information on the OBJ file format and laoding/parsing an OBJ:
* http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
*/

struct Model; ///< Stores loaded obj file as a model.


Model* loadObjFile(string filePath);


#endif // Loader_h__


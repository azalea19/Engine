#ifndef RenderableObject_h__
#define RenderableObject_h__


#include <stdio.h>
#include "Model.h"
#include "Loader.h"
#include "Texture.h"
#include "Types.h"

/**
* @file   RenderableObject.h
* @Author Maddisen Topaz
* @date   S2, 2016
* @brief  The renderable object struct.
*
* The renderable object struct takes a model and its data and transforms it in to something that can be rendered.
* It is a handle to the data on the video card representing a model.
*/

struct RenderSubObject
{
	uint32_t firstFace;	
	uint32_t faceCount;	
	GLint texture;		
};


struct RenderableObject
{
public:
	std::vector<RenderSubObject> subObjects;		


	RenderableObject(string modelPath, bool normalized = false);


	void GenerateSubObjects();


	int SubObjectCount();


	std::vector<glm::vec3> GetVertices(int subIndex);



	bool IsClimbable(int subIndex);

	
	bool generateBuffers();

	
	bool uploadBuffers();

	
	void UploadMVPMatrix(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, glm::mat4 modelMatrix);

	
	void Render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::mat4 modelMatrix);

	
	string GetModel() const { return model; }

	
	GLint GetTexture() const { return texture; }

	
	const Model & GetMyModel() const { return *myModel; }


	GLuint GetgVBO() const { return gVBO; }

	
	GLuint GetgUVBO() const { return gUVBO; }

private:

	string model;		
	GLint texture;		
	Model* myModel;		

	GLuint gVBO;		
	GLuint gUVBO;		
	GLuint gNBO;		


};


#endif // !ModelHandler_h__
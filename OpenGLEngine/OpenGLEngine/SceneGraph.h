#ifndef SceneGraph_h__
#define SceneGraph_h__

#include "Types.h"
#include "MCamera.h"

struct Node;
class UberShader;

class SceneGraph
{

public:

	SceneGraph(float fieldOfView, int screenWidth, int screenHeight, float nearPlane, float farPlane);
	~SceneGraph();

	void Initialise();

	UberShader* GetShader();

	void Render();

	void SetRoot(Node* root);


private:

	Node* m_root;
	UberShader* m_shader;

	mat4 m_modelMatrix;
	mat4 m_viewMatrix;
	mat4 m_projectionMatrix;

	float m_fov;
	int m_screenWidth;
	int m_screenHeight;
	float m_nearPlane;
	float m_farPlane;

	MCamera* cam;

};


#endif
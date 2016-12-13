#include "SceneGraph.h"
#include "MMath.h"
#include "Node.h"
#include "UberShader.h"

SceneGraph::SceneGraph(float fieldOfView, int screenWidth, int screenHeight, float nearPlane, float farPlane)
	: m_fov(fieldOfView)
	, m_screenWidth(screenWidth)
	, m_screenHeight(screenHeight)
	, m_nearPlane(nearPlane)
	, m_farPlane(farPlane)
{
	m_shader = new UberShader("uberShader", "uberShader.vert", "uberShader.frag");
}

SceneGraph::~SceneGraph()
{
}

void SceneGraph::Initialise()
{ 
	cam = new MCamera(m_fov, m_screenWidth, m_screenHeight, m_nearPlane, m_farPlane);
	m_projectionMatrix = cam->getProjectionMatrix();
	m_viewMatrix = cam->getViewMatrix();
}

UberShader * SceneGraph::GetShader()
{
	return m_shader;
}

void SceneGraph::Render()
{
	m_root->enter();
}

void SceneGraph::SetRoot(Node * root)
{
	m_root = root;
}

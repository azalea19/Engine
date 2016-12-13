#include "SkinnedMesh.h"

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices)

mat4 ASMat4ToGlm(const aiMatrix4x4& value)
{
	mat4 result;

	result[0][0] = value.a1; result[0][1] = value.a2; result[0][2] = value.a3; result[0][3] = value.a4;
	result[1][0] = value.b1; result[1][1] = value.b2; result[1][2] = value.b3; result[1][3] = value.b4;
	result[2][0] = value.c1; result[2][1] = value.c2; result[2][2] = value.c3; result[2][3] = value.c4;
	result[3][0] = value.d1; result[3][1] = value.d2; result[3][2] = value.d3; result[3][3] = value.d4;
	
	return result;
}


SkinnedMesh::SkinnedMesh()
{
	m_VAO = 0;
	memset(m_Buffers, 0, sizeof(GLuint)*NUM_VBs);
	m_NumBones = 0;
	m_pScene = NULL;
}

void SkinnedMesh::Destroy()
{
	if (m_Buffers[0] != 0)
	{
		glDeleteBuffers(NUM_VBs, m_Buffers);
	}

	if (m_VAO != 0)
	{
		glDeleteVertexArrays(1, &m_VAO);
		m_VAO = 0;
	}
}

SkinnedMesh::~SkinnedMesh()
{
	Destroy();
}


bool SkinnedMesh::LoadMesh(const string & filename)
{
	bool success = false;

	//Create the VAO
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	//Generate the buffers
	glGenBuffers(NUM_VBs, m_Buffers);
	m_pScene = m_importer.ReadFile(filename.c_str(), ASSIMP_LOAD_FLAGS);
	
	if (m_pScene)
	{		
		m_globalInverseTransform = ASMat4ToGlm(m_pScene->mRootNode->mTransformation.Inverse());
		success = InitFromScene(m_pScene, filename);
	}
	else
	{
		printf("Error parsing %s : %s", filename.c_str(), m_importer.GetErrorString());
	}

	//Make sure the VAO has not been changed from the outside
	glBindVertexArray(0);

	return success;
}

void SkinnedMesh::Render()
{
}

int SkinnedMesh::GetNumBones() const
{
	return 0;
}

void SkinnedMesh::BoneTransform(float timeInSeconds, std::vector<mat4>& transforms)
{
}

void SkinnedMesh::CalcInterpolatedScaling(aiVector3D & out, float animationTime, const aiNodeAnim * pNodeAnim)
{
}

void SkinnedMesh::CalcInterpolatedRotation(aiQuaternion & out, float animationTime, const aiNodeAnim * pNodeAnim)
{
}

void SkinnedMesh::CalcInterpolatedPosition(aiVector3D & out, float animationTime, const aiNodeAnim * pNodeAnim)
{
}

int SkinnedMesh::FindScaling(float animationTime, const aiNodeAnim * pNodeAnim)
{
	return 0;
}

int SkinnedMesh::FindRotation(float animationTime, const aiNodeAnim * pNodeAnim)
{
	return 0;
}

int SkinnedMesh::FindPosition(float animationTime, const aiNodeAnim * pNodeAnim)
{
	return 0;
}

const aiNodeAnim * SkinnedMesh::FindNodeAnim(const aiAnimation * pAnimation, const string nodeName)
{
	return nullptr;
}

void SkinnedMesh::ReadNodeHeirarchy(float animationTime, const aiNode * pNode, const mat4 & parentTransform)
{
}

bool SkinnedMesh::InitFromScene(const aiScene * pScene, const string & filename)
{
	m_subMeshes.resize(pScene->mNumMeshes);

	std::vector<vec3> positions;
	std::vector<vec3> normals;
	std::vector<vec3> textCoords;
	std::vector<VertexBoneData> bones;
	std::vector<int> indices;

	int numVertices = 0;
	int numIndices = 0;

	for (int i = 0; i < m_subMeshes.size(); i++)
	{
		m_subMeshes[i].materialIndex = pScene->mMeshes[i]->mMaterialIndex;
		m_subMeshes[i].numIndices = pScene->mMeshes[i]->mNumFaces * 3;
		m_subMeshes[i].baseVertex = numVertices;
		m_subMeshes[i].baseIndex = numIndices;

		numVertices += pScene->mMeshes[i]->mNumVertices;
		numIndices += m_subMeshes[i].numIndices;
	}

	//Initialise the meshes in the scene
	for (int i = 0; i < m_subMeshes.size(); i++)
	{
		const aiMesh* pAiMesh = pScene->mMeshes[i];
		InitMesh(i, pAiMesh, positions, normals, textCoords, bones, indices);
	}
}

void SkinnedMesh::InitMesh(int meshIndex, std::vector<vec3>* positions, std::vector<vec3>& normals, std::vector<vec2>& texCoords, std::vector<VertexBoneData>& bones, std::vector<int>& indices)
{
}

void SkinnedMesh::LoadBones(int meshIndex, const aiMesh * pAiMesh, std::vector<VertexBoneData>& bones)
{
}

bool SkinnedMesh::InitMaterials(const aiScene * pScene, const string & filename)
{
	return false;
}

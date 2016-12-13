#ifndef SkinnedMesh_h__
#define SkinnedMesh_h__

#include "Types.h"
#include "GL/glew.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postProcess.h"
#include <unordered_map>

//http://ogldev.atspace.co.uk/

//The maximum number of bones a vertex may be influenced by
#define NUM_BONES_PER_VERTEX 4

struct SubMesh
{
	//int firstFace;
	//int faceCount;
	//string texturePath;

	int numIndices;
	int baseVertex;
	int baseIndex;
	int materialIndex;

	SubMesh()
	{
		numIndices = 0;
		baseVertex = 0;
		baseIndex = 0;
		materialIndex = 0;
	}
};

struct Triangle
{
	uint32_t vIndex[3];
	uint32_t uvIndex[3];
	uint32_t normalIndex[3];
};

struct BoneInfo
{
	mat4 boneOffset;
	mat4 finalTransformation;

};

struct VertexBoneData
{
	int IDs[NUM_BONES_PER_VERTEX];
	float weights[NUM_BONES_PER_VERTEX];

	VertexBoneData()
	{
		memset(IDs, 0, sizeof(int)*NUM_BONES_PER_VERTEX);
		memset(weights, 0, sizeof(float)*NUM_BONES_PER_VERTEX);
	}

	void AddBoneData(int BoneID, float weight)
	{
		for (int i = 0; i < NUM_BONES_PER_VERTEX; i++)
		{
			if (weights[i] == 0)
			{
				IDs[i] = BoneID;
				weights[i] = weight;
				return;
			}
		}

		assert(0); // More bones than we have space for
	}
};

enum VB_TYPES 
{
	INDEX_BUFFER,
	POS_VB,
	NORMAL_VB,
	TEXCOORD_VB,
	BONE_VB,
	NUM_VBs //Gives back the number of buffer types (5)
};

class SkinnedMesh
{
	SkinnedMesh();

	~SkinnedMesh();

	void Destroy();

	bool LoadMesh(const string& filename);
	
	void Render();

	int GetNumBones() const;

	void BoneTransform(float timeInSeconds, std::vector<mat4>& transforms);

private:

	void CalcInterpolatedScaling(aiVector3D& out, float animationTime, const aiNodeAnim* pNodeAnim);
	void CalcInterpolatedRotation(aiQuaternion& out, float animationTime, const aiNodeAnim* pNodeAnim);
	void CalcInterpolatedPosition(aiVector3D& out, float animationTime, const aiNodeAnim* pNodeAnim);
	int FindScaling(float animationTime, const aiNodeAnim* pNodeAnim);
	int FindRotation(float animationTime, const aiNodeAnim* pNodeAnim);
	int FindPosition(float animationTime, const aiNodeAnim* pNodeAnim);
	
	const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const string nodeName);
	void ReadNodeHeirarchy(float animationTime, const aiNode* pNode, const mat4& parentTransform);
	bool InitFromScene(const aiScene* pScene, const string& filename);
	void InitMesh(int meshIndex, std::vector<vec3>* positions, std::vector<vec3>& normals, std::vector<vec2>& texCoords, std::vector<VertexBoneData>& bones, std::vector<int>& indices);
	void LoadBones(int meshIndex, const aiMesh* pAiMesh, std::vector<VertexBoneData>& bones);
	bool InitMaterials(const aiScene* pScene, const string& filename);
	
	GLuint m_VAO;
	GLuint m_Buffers[NUM_VBs];
	//A sub mesh contains the number of faces that use a particular texture
	std::vector<SubMesh> m_subMeshes;

	int m_NumBones;
	//Maps a bone name to its index
	std::unordered_map<string, int> m_boneMap;
	std::vector<BoneInfo> m_boneInfo;
	mat4 m_globalInverseTransform;

	const aiScene* m_pScene;
	Assimp::Importer m_importer;

};


#endif
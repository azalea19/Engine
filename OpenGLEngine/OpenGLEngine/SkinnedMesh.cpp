#include "SkinnedMesh.h"
#include "MMath.h"
#include "AssimpToGLM.h"

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_LimitBoneWeights )

#define POSITION_LOCATION    0
#define TEX_COORD_LOCATION   1
#define NORMAL_LOCATION      2
#define BONE_ID_LOCATION     3
#define BONE_WEIGHT_LOCATION 4


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
  

	printf(m_importer.GetErrorString());
	if (m_pScene)
	{		
		m_globalInverseTransform = ASToGLM(m_pScene->mRootNode->mTransformation.Inverse());
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
	glBindVertexArray(m_VAO);

	for (int i = 0; i < m_subMeshes.size(); i++)
		glDrawElementsBaseVertex(GL_TRIANGLES, m_subMeshes[i].numIndices, GL_UNSIGNED_INT, (void*)(sizeof(int) * m_subMeshes[i].baseIndex), m_subMeshes[i].baseVertex);

}

int SkinnedMesh::GetNumBones() const
{
	return 0;
}

void SkinnedMesh::BoneTransform(float timeInSeconds, std::vector<mat4>& transforms)
{
	mat4 identity;

	float ticksPerSec = (float)m_pScene->mAnimations[0]->mTicksPerSecond;
	
	if (ticksPerSec == 0)
	{
		ticksPerSec = 25.0f;
	}

	float timeInTicks = timeInSeconds * ticksPerSec;
	float animationTime = fmod(timeInTicks, (float)m_pScene->mAnimations[0]->mDuration);
	
	ReadNodeHeirarchy(animationTime, m_pScene->mRootNode, identity);
	transforms.resize(m_NumBones);

	for (int i = 0; i < m_NumBones; i++)
	{
		transforms[i] = m_boneInfo[i].finalTransformation;
	}
}

void SkinnedMesh::CalcInterpolatedScaling(aiVector3D & out, float animationTime, const aiNodeAnim * pNodeAnim)
{
	if (pNodeAnim->mNumScalingKeys == 1)
	{
		out = pNodeAnim->mScalingKeys[0].mValue;
		return;
	}

	int scalingIndex = FindScaling(animationTime, pNodeAnim);
	int nextScalingIndex = scalingIndex + 1;
	assert(nextScalingIndex < pNodeAnim->mNumScalingKeys);
	float deltaTime = (float)(pNodeAnim->mScalingKeys[nextScalingIndex].mTime - pNodeAnim->mScalingKeys[scalingIndex].mTime);
	float factor = animationTime - (float)pNodeAnim->mScalingKeys[scalingIndex].mTime / deltaTime;
	assert(factor >= 0.0f && factor <= 1.0f);
	const aiVector3D& start = pNodeAnim->mScalingKeys[scalingIndex].mValue;
	const aiVector3D& end = pNodeAnim->mScalingKeys[nextScalingIndex].mValue;
	out = mLerp(start, end, factor);
}

void SkinnedMesh::CalcInterpolatedRotation(aiQuaternion & out, float animationTime, const aiNodeAnim * pNodeAnim)
{
	if (pNodeAnim->mNumRotationKeys == 1)
	{
		out = pNodeAnim->mRotationKeys[0].mValue;
		return;
	}

	int rotationIndex = FindRotation(animationTime, pNodeAnim);
	int nextRotationIndex = rotationIndex + 1;
	assert(nextRotationIndex < pNodeAnim->mNumRotationKeys);
	float deltaTime = (float)(pNodeAnim->mRotationKeys[nextRotationIndex].mTime) - pNodeAnim->mRotationKeys[rotationIndex].mTime;
	float factor = (animationTime - (float)pNodeAnim->mRotationKeys[rotationIndex].mTime) / deltaTime;
	assert(factor >= 0.0f && factor <= 1.0f);
	const aiQuaternion& startRotQ = pNodeAnim->mRotationKeys[rotationIndex].mValue;
	const aiQuaternion& endRotQ = pNodeAnim->mRotationKeys[nextRotationIndex].mValue;
	aiQuaternion::Interpolate(out, startRotQ, endRotQ, factor);
	out = out.Normalize();
}

void SkinnedMesh::CalcInterpolatedPosition(aiVector3D & out, float animationTime, const aiNodeAnim * pNodeAnim)
{
	//mNumPositionKeys is the number of key frames a bone has
	if (pNodeAnim->mNumPositionKeys == 1)
	{
		out = pNodeAnim->mPositionKeys[0].mValue;
		return;
	}
	//Find the bone position at this time in the animation
	int positionIndex = FindPosition(animationTime, pNodeAnim);
	int nextPositionIndex = positionIndex + 1;
	//Check that we can get the next keyframe
	assert(nextPositionIndex < pNodeAnim->mNumPositionKeys);
	//Find the change in time since animations last fram and the next frame
	float deltaTime = (float)(pNodeAnim->mPositionKeys[nextPositionIndex].mTime - pNodeAnim->mPositionKeys[positionIndex].mTime);
	//Returns a value from 0 to 1 that is how from we are between first keyframe and second keyframe
	float factor = (animationTime - (float)(pNodeAnim->mPositionKeys[positionIndex].mTime) / deltaTime);
	assert(factor >= 0.0f && factor <= 1.0f);
	const aiVector3D& start = pNodeAnim->mPositionKeys[positionIndex].mValue;
	const aiVector3D& end = pNodeAnim->mPositionKeys[nextPositionIndex].mValue;
	//Returns an equivalent value between start to end from the value factor
	out = mLerp(start, end, factor);
}

int SkinnedMesh::FindScaling(float animationTime, const aiNodeAnim * pNodeAnim)
{
	assert(pNodeAnim->mNumScalingKeys > 0);

	for (int i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++) 
	{
		if (animationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime)
		{
			return i;
		}
	}

	assert(0);

	return 0;
}

int SkinnedMesh::FindRotation(float animationTime, const aiNodeAnim * pNodeAnim)
{
	for (int i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++)
	{
		if (animationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime)
		{
			return i;
		}
	}

	assert(0);

	return 0;
}

int SkinnedMesh::FindPosition(float animationTime, const aiNodeAnim * pNodeAnim)
{
	for (int i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++)
	{
		if (animationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime)
		{
			return i;
		}
	}
}

const aiNodeAnim * SkinnedMesh::FindNodeAnim(const aiAnimation * pAnimation, const string nodeName)
{
	//Return the keyframe data of a bone (nodeName is the bone name) from the specified animation 
	for (int i = 0; i < pAnimation->mNumChannels; i++)
	{
		const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];
		if (string(pNodeAnim->mNodeName.data) == nodeName)
		{
			return pNodeAnim;
		}
	}

	return nullptr;
}

void SkinnedMesh::ReadNodeHeirarchy(float animationTime, const aiNode * pNode, const mat4 & parentTransform)
{
	//bone name
	string nodeName = pNode->mName.data;
  
	const aiAnimation* pAnimation = m_pScene->mAnimations[0];
	

	mat4 nodeTransform = ASToGLM(pNode->mTransformation);
	//find the animation for that animation cycle for that bone
	const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, nodeName);

	if (pNodeAnim)
	{
		aiVector3D scaling;
		CalcInterpolatedScaling(scaling, animationTime, pNodeAnim);	
		mat4 scalingM = glm::scale(vec3(scaling.x, scaling.y, scaling.z));
		//mat4 scalingM;

		aiQuaternion rotationQ;
		CalcInterpolatedRotation(rotationQ, animationTime, pNodeAnim);
		mat4 rotationM = mat4(ASToGLM(rotationQ.GetMatrix()));
		//mat4 rotationM;

		aiVector3D translation;
		CalcInterpolatedPosition(translation, animationTime, pNodeAnim);
		mat4 translationM = glm::translate(vec3(translation.x, translation.y, translation.z));
		//mat4 translationM;

		//Combine the above transformations
		//nodeTransform = translationM * rotationM * scalingM;
		nodeTransform = translationM * rotationM * scalingM;
	}

	mat4 globalTransform = parentTransform * nodeTransform;
	//mat4 globalTransform = nodeTransform * parentTransform;

	if (m_boneMap.find(nodeName) != m_boneMap.end())
	{
		int boneIndex = m_boneMap[nodeName];
		m_boneInfo[boneIndex].finalTransformation = m_globalInverseTransform * globalTransform * m_boneInfo[boneIndex].boneOffset;
		//m_boneInfo[boneIndex].finalTransformation =  m_boneInfo[boneIndex].boneOffset * globalTransform * m_globalInverseTransform;
	}
  

	for (int i = 0; i < pNode->mNumChildren; i++)
	{
		ReadNodeHeirarchy(animationTime, pNode->mChildren[i], globalTransform);
	}
}

bool SkinnedMesh::InitFromScene(const aiScene * pScene, const string & filename)
{
	m_subMeshes.resize(pScene->mNumMeshes);

	std::vector<vec3> positions;
	std::vector<vec3> normals;
	std::vector<vec2> texCoords;
	std::vector<VertexBoneData> bones;
	std::vector<int> indices;

	int numVertices = 0;
	int numIndices = 0;

	//Count the number of verts and indices
	for (int i = 0; i < m_subMeshes.size(); i++)
	{
		m_subMeshes[i].materialIndex = pScene->mMeshes[i]->mMaterialIndex;
		m_subMeshes[i].numIndices = pScene->mMeshes[i]->mNumFaces * 3;
		m_subMeshes[i].baseVertex = numVertices;
		m_subMeshes[i].baseIndex = numIndices;

		numVertices += pScene->mMeshes[i]->mNumVertices;
		numIndices += m_subMeshes[i].numIndices;
	}

	//Reserve space in vectors for the vertex attributes and indices
	positions.reserve(numVertices);
	normals.reserve(numVertices);
	texCoords.reserve(numVertices);
	bones.resize(numVertices);
	indices.reserve(numVertices);

	//Initialise the meshes in the scene


	for (int i = 0; i < m_subMeshes.size(); i++)
	{
		const aiMesh* pAiMesh = pScene->mMeshes[i];
		InitMesh(i, pAiMesh, positions, normals, texCoords, bones, indices);
	}


	if (!InitMaterials(pScene, filename))
	{
		return false;
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[POS_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions[0])*positions.size(), &positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(POSITION_LOCATION);
	glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords[0])*texCoords.size(), &texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(TEX_COORD_LOCATION);
	glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, 0,0);

	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0])*normals.size(), &normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(NORMAL_LOCATION);
	glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[BONE_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bones[0])*bones.size(), &bones[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(BONE_ID_LOCATION);
	glVertexAttribIPointer(BONE_ID_LOCATION, 4, GL_INT, sizeof(VertexBoneData), (const GLvoid*)0);
	glEnableVertexAttribArray(BONE_WEIGHT_LOCATION);
	glVertexAttribPointer(BONE_WEIGHT_LOCATION, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (const GLvoid*)16);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Buffers[INDEX_BUFFER]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	return true;
}

void SkinnedMesh::InitMesh(int meshIndex, const aiMesh* pAiMesh, std::vector<vec3>& positions, std::vector<vec3>& normals, std::vector<vec2>& texCoords, std::vector<VertexBoneData>& bones, std::vector<int>& indices)
{
	const aiVector3D zeroVector(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < pAiMesh->mNumVertices; i++)
	{
		const aiVector3D* pPos = &(pAiMesh->mVertices[i]);
		const aiVector3D* pNormal = &(pAiMesh->mNormals[i]);
		const aiVector3D* pTexCoord = pAiMesh->HasTextureCoords(0) ? &(pAiMesh->mTextureCoords[0][i]) : &zeroVector;
		
		positions.push_back(vec3(pPos->x, pPos->y, pPos->z));
		normals.push_back(vec3(pNormal->x, pNormal->y, pNormal->z));
		texCoords.push_back(vec2(pTexCoord->x, pTexCoord->y));
	}

	LoadBones(meshIndex, pAiMesh, bones);

	for (int i = 0; i < pAiMesh->mNumFaces; i++)
	{
		const aiFace& face = pAiMesh->mFaces[i];
		assert(face.mNumIndices == 3);
		indices.push_back(face.mIndices[0]);
		indices.push_back(face.mIndices[1]);
		indices.push_back(face.mIndices[2]);
	}
}

void SkinnedMesh::LoadBones(int meshIndex, const aiMesh * pMesh, std::vector<VertexBoneData>& bones)
{
	for (int i = 0; i < pMesh->mNumBones; i++)
	{
		int boneIndex = 0;

		string boneName = pMesh->mBones[i]->mName.data;

		if (m_boneMap.find(boneName) == m_boneMap.end())
		{
			boneIndex = m_NumBones;
			m_NumBones++;
			BoneInfo bi;
			m_boneInfo.push_back(bi);
			m_boneInfo[boneIndex].boneOffset = ASToGLM(pMesh->mBones[i]->mOffsetMatrix);
			m_boneMap[boneName] = boneIndex;
      
		}
		else
		{
			boneIndex = m_boneMap[boneName];
		}

		for (int j = 0; j < pMesh->mBones[i]->mNumWeights; j++)
		{
			int vertexID = m_subMeshes[meshIndex].baseVertex + pMesh->mBones[i]->mWeights[j].mVertexId;
			float weight = pMesh->mBones[i]->mWeights[j].mWeight;
			bones[vertexID].AddBoneData(boneIndex, weight);
		}
	}
}

bool SkinnedMesh::InitMaterials(const aiScene * pScene, const string & filename)
{
	return true;
}

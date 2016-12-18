#include "NewMesh.h"
#include "assimp/scene.h"
#include "AssimpToGLM.h"
#include "mMath.h"

Mesh::Mesh()
  : m_name("")
  , m_bounds{ vec3{ 0, 0, 0 }, vec3{0, 0, 0} }
{
}

Mesh::Mesh(aiMesh const *pMesh, Bimap<string,int> const& boneLookup)
  : m_name(pMesh->mName.data)
{
  LoadTexCoords(pMesh);
  LoadVertices(pMesh);
  LoadNormals(pMesh);
  LoadVertexColours(pMesh);
  LoadIndices(pMesh);
  LoadBones(pMesh, boneLookup);
  LoadMaterial(pMesh);
  CalculateBounds();
}

string const& Mesh::GetName() const
{
  return m_name;
}

std::vector<vec2> const& Mesh::GetTexCoords(TextureType const& texType) const
{
  return m_texCoords[texType];
}

std::vector<vec3> const& Mesh::GetVertices() const
{
  return m_vertices;
}

std::vector<vec3> const& Mesh::GetNormals() const
{
  return m_normals;
}

std::vector<vec4> const& Mesh::GetVertexColours() const
{
  return m_vertexColours;
}

std::vector<int> const& Mesh::GetIndices() const
{
  return m_indices;
}

std::vector<VertexBoneIDs> const& Mesh::GetBoneIDs() const
{
  return m_boneIDs;
}

std::vector<VertexBoneWeights> const& Mesh::GetBoneWeights() const
{
  return m_boneWeights;
}

int const& Mesh::GetMaterialIndex() const
{
  return materialIndex;
}

mAABB const& Mesh::GetBounds() const
{
  return m_bounds;
}

void Mesh::LoadTexCoords(aiMesh const *pMesh)
{
  for (int uvChannel = 0; uvChannel < pMesh->GetNumUVChannels(); uvChannel++)
  {
    if (pMesh->HasTextureCoords(uvChannel))
    {
      m_texCoords[uvChannel].resize(pMesh->mNumVertices);
      for (int i = 0; i < pMesh->mNumVertices; i++)
      {
        vec3 uv = ASToGLM(pMesh->mTextureCoords[uvChannel][i]);
        m_texCoords[uvChannel][i] = vec2(uv.x, uv.y);
      }
    }
  }
}

void Mesh::LoadVertices(aiMesh const *pMesh)
{
  m_vertices.resize(pMesh->mNumVertices);
  for (int i = 0; i < pMesh->mNumVertices; i++)
    m_vertices[i] = ASToGLM(pMesh->mVertices[i]);
}

void Mesh::LoadNormals(aiMesh const * pMesh)
{
  m_normals.resize(pMesh->mNumVertices);
  for (int i = 0; i < pMesh->mNumVertices; i++)
    m_normals[i] = ASToGLM(pMesh->mNormals[i]);
}

void Mesh::LoadVertexColours(aiMesh const *pMesh)
{
  m_vertexColours.resize(pMesh->mNumVertices);
  for (int i = 0; i < pMesh->mNumVertices; i++)
    m_vertexColours[i] = ASToGLM(pMesh->mColors[0][i]);
}

void Mesh::LoadIndices(aiMesh const *pMesh)
{
  m_indices.resize(pMesh->mNumFaces * 3);
  for (int i = 0; i < pMesh->mNumFaces; i++)
  {
    m_indices[i * 3 + 0] = pMesh->mFaces[i].mIndices[0];
    m_indices[i * 3 + 1] = pMesh->mFaces[i].mIndices[1];
    m_indices[i * 3 + 2] = pMesh->mFaces[i].mIndices[2];
  }
}

int Mesh::GetNextWeightSlot(int vertexIndex)
{
  for (int i = 0; i < MAX_BONES_PER_VERTEX; i++)
  {
    if (m_boneWeights[vertexIndex].boneWeights[i] == 0)
    {
      return i;
    }
  }
  
  throw std::exception("Too many bones for vertex.");
}

void Mesh::LoadBones(aiMesh const *pMesh, Bimap<string,int> const& boneLookup)
{
  m_boneIDs.resize(pMesh->mNumVertices* MAX_BONES_PER_VERTEX);

  for (int i = 0; i < pMesh->mNumBones; i++)
  {
    string boneName = pMesh->mBones[i]->mName.data;
    int boneID = boneLookup.GetValue(boneName);

    for (int j = 0; j < pMesh->mBones[i]->mNumWeights; j++)
    {
      int pos = pMesh->mBones[i]->mWeights[j].mVertexId;
      int nextFree = GetNextWeightSlot(pos);
      m_boneIDs[pos].boneIDs[nextFree] = boneID;
      m_boneWeights[pos].boneWeights[nextFree] = pMesh->mBones[i]->mWeights[j].mWeight;
    }
  }
}

void Mesh::LoadMaterial(aiMesh const *pMesh)
{
  materialIndex = pMesh->mMaterialIndex;
}

void Mesh::CalculateBounds()
{
  m_bounds.min = vec3(FLT_MAX, FLT_MAX, FLT_MAX);
  m_bounds.max = vec3(-FLT_MAX, -FLT_MAX, -FLT_MAX);

  for (int i = 0; i < m_vertices.size(); i++)
  {
    m_bounds.min.x = mMin(m_bounds.min.x, m_vertices[i].x);
    m_bounds.min.y = mMin(m_bounds.min.y, m_vertices[i].y);
    m_bounds.min.z = mMin(m_bounds.min.z, m_vertices[i].z);

    m_bounds.max.x = mMax(m_bounds.max.x, m_vertices[i].x);
    m_bounds.max.y = mMax(m_bounds.max.y, m_vertices[i].y);
    m_bounds.max.z = mMax(m_bounds.max.z, m_vertices[i].z);
  }
}

int Mesh::GetVertexCount() const
{
  return m_vertices.size();
}

int Mesh::GetNormalCount() const
{
  return m_normals.size();
}

int Mesh::GetVertexColoursCount() const
{
  return m_vertexColours.size();
}

int Mesh::GetIndexCount() const
{
  return m_indices.size();
}

int Mesh::GetBoneIDCount() const
{
  return m_boneIDs.size();
}

int Mesh::GetBoneWeightCount() const
{
  return m_boneWeights.size();
}
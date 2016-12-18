#include "RenderableObject.h"
#include "Model.h"
#include "Mesh.h"
#include "ShaderLibrary.h"
#include "TextureLibrary.h"

enum Attribute_Location
{
  AL_Vertices,
  AL_TexCoords,
  AL_Normals,
  AL_BoneIDs,
  AL_BoneWeights,
};


RenderableObject::RenderableObject(string const& name, string const& filename)
  : m_VAO(0)
{
  memset(m_buffers, 0, sizeof(GLuint)* BT_NUM_BUFFERS);
  m_pModel = new Model(name, filename);
  Initialise();
}

RenderableObject::~RenderableObject()
{
  Destroy();
}

void RenderableObject::UpdateBones(float time)
{
	std::vector<glm::mat4> bones = m_pModel->GetBoneTransforms(0, time);
	ShaderLibrary::getLib()->currentShader()->transmitUniformArray("BONES", bones.data(), bones.size());
}

void RenderableObject::Initialise()
{

  std::vector<vec3> const& vertices = m_pModel->GetVertices();
  std::vector<int> const& indices = m_pModel->GetIndices();
  std::vector<vec3> const& normals = m_pModel->GetNormals();
  std::vector<vec2> const& texCoords = m_pModel->GetTexCoords();
  std::vector<VertexBoneIDs> const& boneIDs = m_pModel->GetBoneIDs();
  std::vector<VertexBoneWeights> const& boneWeights = m_pModel->GetBoneWeights();
  
  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);

  glGenBuffers(BT_NUM_BUFFERS, m_buffers);


  glBindBuffer(GL_ARRAY_BUFFER, m_buffers[BT_VERTEX_BUFFER]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0])*vertices.size(), &vertices[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(AL_Vertices);
  glVertexAttribPointer(AL_Vertices, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, m_buffers[BT_TEXCOORD_BUFFER]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords[0])*texCoords.size(), &texCoords[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(AL_TexCoords);
  glVertexAttribPointer(AL_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, m_buffers[BT_NORMAL_BUFFER]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0])*normals.size(), &normals[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(AL_Normals);
  glVertexAttribPointer(AL_Normals, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, m_buffers[BT_BONE_ID_BUFFER]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(boneIDs[0])*boneIDs.size(), &boneIDs[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(AL_BoneIDs);
  glVertexAttribIPointer(AL_BoneIDs, 4, GL_INT, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, m_buffers[BT_BONE_WEIGHT_BUFFER]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(boneWeights[0])*boneWeights.size(), &boneWeights[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(AL_BoneWeights);
  glVertexAttribPointer(AL_BoneWeights, 4, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[BT_INDEX_BUFFER]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

  glBindVertexArray(NULL);

}

void RenderableObject::Render(mat4 worldMatrix, mat4 viewMatrix, mat4 projectionMatrix, float time)
{
	UpdateBones(time);

  glBindVertexArray(m_VAO);

  for (int i = 0; i < m_pModel->GetMeshCount(); i++)
  {
    IndexRange const& range = m_pModel->GetMeshIndexRange(i);
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_2D, TextureLibrary::GetInstance().GetTexture(m_pModel->GetMeshTextureName(i, TT_Diffuse)));
    glDrawElementsBaseVertex(GL_TRIANGLES, range.indexCount, GL_UNSIGNED_INT, (void*)(sizeof(int)*range.firstIndexOffset), range.firstVertex);
  }

}

void RenderableObject::Destroy()
{
  if (m_buffers[0] != 0)
  {
    glDeleteBuffers(BT_NUM_BUFFERS, m_buffers);
  }

  if (m_VAO != 0)
  {
    glDeleteVertexArrays(1, &m_VAO);
    m_VAO = 0;
  }
}

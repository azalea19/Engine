#include "RenderableObject.h"
#include "Model.h"
#include "Mesh.h"
#include "ShaderLibrary.h"
#include "TextureLibrary.h"
#include "FrameBuffer.h"
#include "BloomEffect.h"
#include "FXAAEffect.h"
#include "Screen.h"
#include "InputManager.h"




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

void RenderableObject::UpdateAnimation(int animationIndex, float time)
{
  const Shader* shader = ShaderLibrary::getLib()->currentShader();
  if (m_pModel->HasAnimation() && animationIndex >= 0)
  {
    std::vector<glm::mat4> bones = m_pModel->GetBoneTransforms(animationIndex, time);
    ShaderLibrary::getLib()->currentShader()->transmitUniformArray("BONES", bones.data(), bones.size());
    shader->transmitUniform("ANIMATION_ENABLED", 1);
  }
  else
  {
    shader->transmitUniform("ANIMATION_ENABLED", 0);
  }


}

void RenderableObject::Initialise()
{
  std::vector<vec3> const& vertices = m_pModel->GetVertices();
  std::vector<int> const& indices = m_pModel->GetIndices();
  std::vector<vec3> const& normals = m_pModel->GetNormals();
  std::vector<vec2> const& texCoords = m_pModel->GetTexCoords();
  std::vector<VertexBoneIDs> const& boneIDs = m_pModel->GetBoneIDs();
  std::vector<VertexBoneWeights> const& boneWeights = m_pModel->GetBoneWeights();
  std::vector<vec4> const& vertexColours = m_pModel->GetVertexColours();
  
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

  glBindBuffer(GL_ARRAY_BUFFER, m_buffers[BT_VERTEX_COLOUR_BUFFER]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColours[0])*vertexColours.size(), &vertexColours[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(AL_VertexColours);
  glVertexAttribPointer(AL_VertexColours, 4, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[BT_INDEX_BUFFER]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);


  glBindVertexArray(NULL);

}

void RenderableObject::Render(mat4 worldMatrix, mat4 viewMatrix, mat4 projectionMatrix, DiffuseSource diffuseSource, int animationIndex, float time)
{
	UpdateAnimation(animationIndex, time);

  glBindVertexArray(m_VAO);
  for (int i = 0; i < m_pModel->GetMeshCount(); i++)
  {
    BindMaterial(i, diffuseSource);
    IndexRange const& range = m_pModel->GetMeshIndexRange(i);
    glDrawElementsBaseVertex(GL_TRIANGLES, range.indexCount, GL_UNSIGNED_INT, (void*)(sizeof(int)*range.firstIndexOffset), range.firstVertex);
  }
  glBindVertexArray(NULL);
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

void RenderableObject::BindMaterial(int meshIndex, DiffuseSource diffuseSource)
{
  const Shader* shader = ShaderLibrary::getLib()->currentShader();
  string diffuseTexture;
  switch (diffuseSource)
  {
    case DS_Texture:
      diffuseTexture = m_pModel->GetMeshTextureName(meshIndex, TT_Diffuse);
      glActiveTexture(GL_TEXTURE0 + TL_Diffuse);
      glBindTexture(GL_TEXTURE_2D, TextureLibrary::GetInstance().GetTexture(diffuseTexture));
      shader->transmitUniform("DIFFUSE_TEXTURE", int(TL_Diffuse));
      break;
    case DS_VertexColour:
    case DS_MeshColour:
      break;

  }
  shader->transmitUniform("DIFFUSE_SOURCE", int(diffuseSource));
}

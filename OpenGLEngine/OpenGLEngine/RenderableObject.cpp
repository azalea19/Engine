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

void RenderableObject::SetFillMode(FillMode fillMode) const
{
  switch (fillMode)
  {
    case FM_Line:
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      break;
    case FM_Fill:
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      break;
  }
}

void RenderableObject::UpdateAnimation(float time, int activeAnimation) const
{
  const IShader* shader = ShaderLibrary::GetInstance().CurrentShader();
  if (m_pModel->HasAnimation() && activeAnimation >= 0)
  {
    std::vector<glm::mat4> bones = m_pModel->GetBoneTransforms(activeAnimation, time);
	shader->TransmitUniformArray("BONES", bones.data(), bones.size());    
    shader->TransmitUniform("ANIMATION_ENABLED", 1);
  }
  else
  {
    shader->TransmitUniform("ANIMATION_ENABLED", 0);
  }
}

void RenderableObject::UploadMatrices(mat4 const& worldMatrix, mat4 const& viewMatrix, mat4 const& projectionMatrix) const
{
  const IShader* shader = ShaderLibrary::GetInstance().CurrentShader();

  if (shader->HasUniform("WORLD_MATRIX"))
    shader->TransmitUniform("WORLD_MATRIX", worldMatrix);

  if (shader->HasUniform("VIEW_MATRIX"))
    shader->TransmitUniform("VIEW_MATRIX", viewMatrix);

  if (shader->HasUniform("PROJECTION_MATRIX"))
    shader->TransmitUniform("PROJECTION_MATRIX", projectionMatrix);

  if (shader->HasUniform("INVERSE_WORLD_MATRIX"))
    shader->TransmitUniform("INVERSE_WORLD_MATRIX", glm::inverse(worldMatrix));

  if (shader->HasUniform("INVERSE_VIEW_MATRIX"))
    shader->TransmitUniform("INVERSE_VIEW_MATRIX", glm::inverse(viewMatrix));

  if (shader->HasUniform("INVERSE_PROJECTION_MATRIX"))
    shader->TransmitUniform("INVERSE_PROJECTION_MATRIX", glm::inverse(projectionMatrix));

  if (shader->HasUniform("WORLD_VIEW_PROJECTION_MATRIX"))
  {
    glm::mat4 wvp = projectionMatrix * viewMatrix * worldMatrix;
    shader->TransmitUniform("WORLD_VIEW_PROJECTION_MATRIX", wvp);
  }

  if (shader->HasUniform("CAMERA_POSITION"))
  {
	  vec4 cam =  inverse(viewMatrix) * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	  shader->TransmitUniform("CAMERA_POSITION", vec3(cam.x, cam.y, cam.z));
  }

}

void RenderableObject::Initialise()
{
  std::vector<vec3> const& vertices = m_pModel->GetVertices();
  std::vector<int> const& indices = m_pModel->GetIndices();
  std::vector<vec3> const& normals = m_pModel->GetNormals();
  std::vector<vec2> const& diffuseTexCoords = m_pModel->GetTexCoords(TT_Diffuse);
  std::vector<vec2> const& alphaTexCoords = m_pModel->GetTexCoords(TT_Alpha);
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

  glBindBuffer(GL_ARRAY_BUFFER, m_buffers[BT_DIFFUSE_TEXCOORD_BUFFER]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(diffuseTexCoords[0])*diffuseTexCoords.size(), &diffuseTexCoords[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(AL_DiffuseTexCoords);
  glVertexAttribPointer(AL_DiffuseTexCoords, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, m_buffers[BT_ALPHA_TEXCOORD_BUFFER]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(alphaTexCoords[0])*alphaTexCoords.size(), &alphaTexCoords[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(AL_AlphaTexCoords);
  glVertexAttribPointer(AL_AlphaTexCoords, 2, GL_FLOAT, GL_FALSE, 0, 0);

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

void RenderableObject::Render(mat4 const& worldMatrix, mat4 const& viewMatrix, mat4 const& projectionMatrix, float time, int animationIndex) const
{
  UploadMatrices(worldMatrix, viewMatrix, projectionMatrix);
  UpdateAnimation(time, animationIndex);
  IndexRange const& range = m_pModel->GetMeshIndexRange(boundMeshIndex);
  glDrawElementsBaseVertex(GL_TRIANGLES, range.indexCount, GL_UNSIGNED_INT, (void*)(sizeof(int)*range.firstIndexOffset), range.firstVertex);
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

int RenderableObject::GetAnimationCount() const
{
  return m_pModel->GetAnimationCount();
}

int RenderableObject::GetAnimationIndex(string const& animationName) const
{
  return m_pModel->GetAnimationIndex(animationName);
}

string const& RenderableObject::GetAnimationName(int animationIndex) const
{
  return m_pModel->GetAnimationName(animationIndex);
}

IMesh const& RenderableObject::GetMesh(int meshIndex) const
{
  return m_pModel->GetMesh(meshIndex);
}

int RenderableObject::GetMeshCount() const
{
  return m_pModel->GetMeshCount();
}

void RenderableObject::BindObject() const
{
  glBindVertexArray(m_VAO);
}

void RenderableObject::BindMesh(int meshIndex) const
{
  boundMeshIndex = meshIndex;
  BindMaterial(meshIndex);
}


void RenderableObject::BindMaterial(int meshIndex) const
{
  const IShader* shader = ShaderLibrary::GetInstance().CurrentShader();
  
    string diffuseTexture = m_pModel->GetMeshTextureName(meshIndex, TT_Diffuse);
    
    if (diffuseTexture != "Texture not supplied.")
    {
      glActiveTexture(GL_TEXTURE0 + TL_Diffuse);
      glBindTexture(GL_TEXTURE_2D, TextureLibrary::GetInstance().GetTexture(diffuseTexture));
      shader->TransmitUniform("DIFFUSE_MAP", int(TL_Diffuse));
      shader->TransmitUniform("DIFFUSE_SOURCE", int(DS_Texture));
    }
    else
    {
      shader->TransmitUniform("DIFFUSE_SOURCE", int(DS_VertexColour));
    }

    string alphaTexture = m_pModel->GetMeshTextureName(meshIndex, TT_Alpha);
    if (alphaTexture != "Texture not supplied.")
    {
      glActiveTexture(GL_TEXTURE0 + int(TL_Alpha));
      glBindTexture(GL_TEXTURE_2D, TextureLibrary::GetInstance().GetTexture(alphaTexture));
      shader->TransmitUniform("ALPHA_MAP", int(TL_Alpha));
      shader->TransmitUniform("USE_ALPHA_MAP", 1);
    }
    else
    {
      shader->TransmitUniform("USE_ALPHA_MAP", 0);
    }
}

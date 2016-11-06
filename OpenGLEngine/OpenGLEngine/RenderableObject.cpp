#include "RenderableObject.h"
#include "ShaderLibrary.h"
#include "Texture.h"

void RenderableObject::Render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::mat4 modelMatrix)
{

  const Shader* shader = ShaderLibrary::getLib()->currentShader();
  
  //enable depth testing
  glEnable(GL_DEPTH_TEST);

  //enable textures
  glEnable(GL_TEXTURE_2D);

  //enable shader program
  //glUseProgram(defaultProgram);

  if(shader->hasUniform("mvp"))
  {
	  UploadMVPMatrix(projectionMatrix, viewMatrix, modelMatrix);
  }
  if (shader->hasAttribute("position"))
  {
	  
	  //enables the use of "position" in the vertex shader
	  glEnableVertexAttribArray(shader->attribute("position"));

	  //sets gVBO as the current ARRAY_BUFFER
	  glBindBuffer(GL_ARRAY_BUFFER, gVBO);

	  //sets "position" to point to the current ARRAY_BUFFER
	  glVertexAttribPointer(shader->attribute("position"), 3, GL_FLOAT, GL_FALSE, 0, NULL);
  }
  if (shader->hasAttribute("uvIn"))
  {

	  //enables the use of "uvIn" in the vertex shader
	  glEnableVertexAttribArray(shader->attribute("uvIn"));;

	  //sets gUVBO as the current ARRAY_BUFFER
	  glBindBuffer(GL_ARRAY_BUFFER, gUVBO);

	  //sets "position" to point to the current ARRAY_BUFFER
	  glVertexAttribPointer(shader->attribute("uvIn"), 2, GL_FLOAT, GL_FALSE, 0, NULL);
  }
  if (shader->hasAttribute("normal"))
  {

	  //enables the use of "uvIn" in the vertex shader
	  glEnableVertexAttribArray(shader->attribute("normal"));;

	  //sets gUVBO as the current ARRAY_BUFFER
	  glBindBuffer(GL_ARRAY_BUFFER, gNBO);

	  //sets "position" to point to the current ARRAY_BUFFER
	  glVertexAttribPointer(shader->attribute("normal"), 3, GL_FLOAT, GL_FALSE, 0, NULL);
  }

  //////////TEXTURES/////////
  

  for (uint32_t i = 0; i < subObjects.size(); i++)
  {
	  if (shader->hasUniform("diffuse"))
	  {
		  //Set Texture unit 0 as the current texture unit
		  glActiveTexture(GL_TEXTURE0);

		  //bind our texture to the current texture unit
		  glBindTexture(GL_TEXTURE_2D, subObjects[i].texture);

		  //Set our sampler to sample the current texure unit
		  shader->transmitUniform("diffuse", 0);
	  }
	  glDrawArrays(GL_TRIANGLES, subObjects[i].firstFace * 3, subObjects[i].faceCount * 3);
  }

  if (shader->hasAttribute("position"))
  {
	  //disables use of "position" in the vertex shader
	  glDisableVertexAttribArray(shader->attribute("position"));
  }

  if (shader->hasAttribute("uvIn"))
  {
	  //disables use of "uvIn" in the vertex shader
	  glDisableVertexAttribArray(shader->attribute("uvIn"));
  }

  if (shader->hasAttribute("normal"))
  {
	  //disables use of "uvIn" in the vertex shader
	  glDisableVertexAttribArray(shader->attribute("normal"));
  }
}

void RenderableObject::UploadMVPMatrix(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, glm::mat4 modelMatrix)
{
	const Shader* shader = ShaderLibrary::getLib()->currentShader();
	if (shader->hasUniform("modelMatrix"))
	{
		shader->transmitUniform("modelMatrix", modelMatrix);
	}
	if (shader->hasUniform("viewMatrix"))
	{
		shader->transmitUniform("viewMatrix", viewMatrix);
	}
	if (shader->hasUniform("projectionMatrix"))
	{
		shader->transmitUniform("projectionMatrix", projectionMatrix);
	}

	if (shader->hasUniform("invModelMatrix"))
	{
		shader->transmitUniform("invModelMatrix", glm::inverse(modelMatrix));
	}
	if (shader->hasUniform("invViewMatrix"))
	{
		shader->transmitUniform("invViewMatrix", glm::inverse(viewMatrix));
	}
	if (shader->hasUniform("invProjectionMatrix"))
	{
		shader->transmitUniform("invProjectionMatrix", glm::inverse(projectionMatrix));
	}
	if (shader->hasUniform("normMatrix"))
	{
		shader->transmitUniform("normMatrix", glm::transpose(glm::inverse(modelMatrix)));
	}
	if (shader->hasUniform("campos"))
	{
		vec4 campos = glm::inverse(viewMatrix) * vec4(0, 0, 0, 1);
		shader->transmitUniform("campos", vec3(campos.x, campos.y, campos.z));
	}

	if (shader->hasUniform("mvp"))
	{
		glm::mat4 mvm = projectionMatrix * viewMatrix * modelMatrix;
		shader->transmitUniform("mvp", mvm);
	}

}

bool RenderableObject::uploadBuffers()
{
  std::vector<GLfloat> verts = myModel->GetVertexArray();
  std::vector<GLfloat> uvs = myModel->GetUVArray();
  std::vector<GLfloat> norms = myModel->GetNormalArray();

  glBindBuffer(GL_ARRAY_BUFFER, gVBO);
  glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(GLfloat), verts.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindBuffer(GL_ARRAY_BUFFER, gUVBO);
  glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(GLfloat), uvs.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindBuffer(GL_ARRAY_BUFFER, gNBO);
  glBufferData(GL_ARRAY_BUFFER, norms.size() * sizeof(GLfloat), norms.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  return true;
}

bool RenderableObject::generateBuffers()
{
  glGenBuffers(1, &gVBO);
  glGenBuffers(1, &gUVBO);
  glGenBuffers(1, &gNBO);
  return true;
}

std::vector<glm::vec3> RenderableObject::GetVertices(int subIndex)
{
  return myModel->GetVertexArray(subIndex);
}

int RenderableObject::SubObjectCount()
{
  return myModel->subObjects.size();
}

void RenderableObject::GenerateSubObjects()
{
  for (uint32_t i = 0; i < myModel->subObjects.size(); i++)
  {
    TextureData& object = myModel->subObjects[i];
    GLint tex = 0;
    tex = loadImage(object.texturePath.c_str());
    subObjects.push_back({ object.firstFace, object.faceCount, tex });
  }
}

RenderableObject::RenderableObject(string modelPath, bool normalized)
{
  myModel = loadObjFile(modelPath);

  if (normalized)
  {
	  myModel->Normalize();
  }

  myModel->GenerateSmoothNormals();

  generateBuffers();
  GenerateSubObjects();
  uploadBuffers();

}

bool RenderableObject::IsClimbable(int subIndex)
{
	return myModel->IsClimbable(subIndex);
}
/*
void RenderableObject::RemoveVertices()
{

	std::vector<triangle> triVec;
	myModel->faces = triVec;

	std::vector<glm::vec3> vec3Vec;
	myModel->normals = vec3Vec;
	myModel->vertices = vec3Vec;

	std::vector<glm::vec2> vec2Vec;
	myModel->uvs = vec2Vec;

	std::vector<TextureData> subObjVec;
	myModel->subObjects = subObjVec;

	
}*/
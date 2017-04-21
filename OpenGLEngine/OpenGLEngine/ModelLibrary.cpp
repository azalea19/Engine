#include "ModelLibrary.h"
#include "RenderableObject.h"
#include "ObjectInstance.h"
#include "IEngine.h"

void ModelLibrary::Initialise(IEngine* pEngine)
{
  ModelLibrary::GetInstance().m_pEngine = pEngine;
}

void ModelLibrary::AddModel(string const& name, string const& path, bool normalized)
{
  IRenderableObject* newObject = m_pEngine->CreateRenderableObject(name, path);
	models.emplace(name, newObject);
}

ObjectInstance* ModelLibrary::GetObjectInstance(string const& name) const
{
	return new ObjectInstance(models.at(name));
}

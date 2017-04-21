#include "ModelLibrary.h"
#include "RenderableObject.h"
#include "ObjectInstance.h"


void ModelLibrary::Initialise()
{
}

void ModelLibrary::AddModel(string const& name, string const& path, bool normalized)
{
	RenderableObject *newObject = new RenderableObject(name, path);
	models.emplace(name, newObject);
}

ObjectInstance* ModelLibrary::GetObjectInstance(string const& name) const
{
	return new ObjectInstance(models.at(name));
}

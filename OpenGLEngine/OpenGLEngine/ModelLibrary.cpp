#include "ModelLibrary.h"
#include "RenderableObject.h"
#include "ObjectInstance.h"

static ModelLibrary modelLib;

void ModelLibrary::initModelLibrary()
{

}

void ModelLibrary::addModel(std::string name, std::string path, bool normalized)
{
	RenderableObject *newObject = new RenderableObject(path, normalized);
	models.emplace(name, newObject);
}

ObjectInstance* ModelLibrary::getInstance(std::string name)
{
	return new ObjectInstance(models[name]);
}

ModelLibrary* ModelLibrary::getLib()
{
	return &modelLib;
}
#include "Loader.h"
#include "Model.h"
#include "Utility.h"
#include <stdio.h>
#include <windows.h>

struct Material;
std::vector<Material> parseMtlFile(string mtlPath);
//Face contains vertexIndex/textureIndex/normalIndex

struct Material
{
	string Name;
	string TexturePath;
};

Model* loadObjFile(string filePath)
{
  FILE* obj = NULL;

  fopen_s(&obj, filePath.c_str(), "rb");
  DWORD WINAPI GetLastError(void);
  

  if (obj == NULL)
  {
    printf("Could not open file %s.", filePath.c_str());
    return NULL;
  }

  Model* pModel = new Model();
  std::vector<Material> materials;

  char temp[1024];
  while (fgets(temp, 1024, obj))
  {
	if (strncmp(temp, "usemtl ", 7) == 0)
	{
		int i = strlen(temp) - 1;
		while (!isalpha(temp[i]))
		{
			temp[i] = NULL;
			i--;
		}

		if (pModel->subObjects.size() > 0)
		{
			TextureData& lastObject = pModel->subObjects[pModel->subObjects.size() - 1];
			lastObject.faceCount = pModel->faces.size() - lastObject.firstFace;
		}
		TextureData newObject;
		newObject.firstFace = pModel->faces.size();
		newObject.texturePath = temp + 7;
		pModel->subObjects.push_back(newObject);
	}
    if (strncmp(temp, "v ", 2) == 0)
    {
	  std::vector<string> components = split(temp + 2, ' ');
      vec3 vertex;
      vertex.x = float(atof(components[0].c_str()));
      vertex.y = float(atof(components[1].c_str()));
      vertex.z = float(atof(components[2].c_str()));	  
      pModel->vertices.push_back(vertex);
    }
    if (strncmp(temp, "vt ", 3) == 0)
    {
	  std::vector<string> components = split(temp + 3, ' ');
      vec2 uv;
      uv.x = float(atof(components[0].c_str()));
      uv.y = float(atof(components[1].c_str()));
	  
      pModel->uvs.push_back(uv);
    }
    if (strncmp(temp, "f ", 2) == 0)
    {
	  std::vector<string> components = split(temp + 2, ' ');
	  std::vector<string> indicies;
      triangle tri;
      for (uint32_t i = 0; i < components.size();i++)
      {
        indicies = split(components[i], '/');

		int temp = atoi(indicies[0].c_str());
		if (temp < 0)
		{
			temp = pModel->vertices.size() + temp + 1;
		}
        tri.vIndex[i] = temp;

		temp = atoi(indicies[1].c_str());
		if (temp < 0)
		{
			temp = pModel->uvs.size() + temp + 1;
		}
		tri.uvIndex[i] = temp;

		temp = atoi(indicies[2].c_str());
		if (temp < 0)
		{
			temp = pModel->normals.size() + temp + 1;
		}
		tri.normalIndex[i] = temp;
      }
      pModel->faces.push_back(tri);
    }
    if (strncmp(temp, "vn ", 3) == 0)
    {
	  std::vector<string> components = split(temp + 3, ' ');
      vec3 normal;
      normal.x = float(atof(components[0].c_str()));
      normal.y = float(atof(components[1].c_str()));
      normal.z = float(atof(components[2].c_str())); 
	  pModel->normals.push_back(normal);
    }
    if (strncmp(temp, "mtllib ", 7) == 0)
    {
      int i = strlen(temp) - 1;
      while (temp[i] != 'l')
      {
        temp[i] = NULL;
        i--;
      }
      string mtlPath = temp + 7;
	  materials = parseMtlFile(mtlPath);
      //pModel->texturePath = getTexturePathFromMtl(mtlPath);
    }
  }

  fclose(obj);

  TextureData& lastObject = pModel->subObjects[pModel->subObjects.size() - 1];
  lastObject.faceCount = pModel->faces.size() - lastObject.firstFace;

  for (uint32_t i = 0; i < pModel->subObjects.size(); i++)
  {
	  TextureData& object = pModel->subObjects[i];
	  for (int j = 0; materials.size(); j++)
	  {
		  if (object.texturePath == materials[j].Name)
		  {
			  object.texturePath = materials[j].TexturePath;

			  if (strncmp(object.texturePath.c_str(), "climb_", 6) == 0)
			  {
				  object.climbable = true;
			  }
			  else
			  {
				  object.climbable = false;
			  }

			  break;
		  }
	  }
  }
  return pModel;
}

std::vector<Material> parseMtlFile(string mtlfile)
{
	std::vector<Material> materials;

	FILE* mtl = NULL;
	fopen_s(&mtl, mtlfile.c_str(), "rb");

	if (mtl == NULL)
	{
		printf("Could not open file %s.", mtlfile.c_str());
		return materials;
	}
	string result = "";
	Material newmat;
	char temp[1024];

	while (fgets(temp, 1024, mtl))
	{
		if (strncmp(temp, "newmtl ", 7) == 0)
		{
			int i = strlen(temp) - 1;
			while (!isalpha(temp[i]))
			{
				temp[i] = NULL;
				i--;
			}
			result = temp + 7;
			newmat.Name = result;
		}
		if (strncmp(temp, "map_Kd ", 7) == 0)
		{
			int i = strlen(temp) - 1;
			while (!isalpha(temp[i]))
			{
				temp[i] = NULL;
				i--;
			}
			result = temp + 7;
			newmat.TexturePath = result;
			materials.push_back(newmat);
		}
	}
	fclose(mtl);
	return materials;
}
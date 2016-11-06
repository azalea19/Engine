#include "Model.h"
#include "MMath.h"

void Model::CenterModel()
{
  float minX = FLT_MAX;
  float minY = FLT_MAX;
  float minZ = FLT_MAX;
  float maxX = -FLT_MAX;
  float maxY = -FLT_MAX;
  float maxZ = -FLT_MAX;

  for (uint32_t i = 0; i < vertices.size(); i++)
  {
    minX = std::min(minX, vertices[i].x);
    minY = std::min(minY, vertices[i].y);
    minZ = std::min(minZ, vertices[i].z);
    maxX = std::max(maxX, vertices[i].x);
    maxY = std::max(maxY, vertices[i].y);
    maxZ = std::max(maxZ, vertices[i].z);
  }
  float xo = (minX + maxX) / 2;
  float yo = (minY + maxY) / 2;
  float zo = (minZ + maxZ) / 2;

  for (uint32_t i = 0; i < vertices.size(); i++)
  {
    vertices[i].x -= xo;
    vertices[i].y -= yo;
    vertices[i].z -= zo;
  }
}

void Model::Normalize()
{
	float minX = FLT_MAX;
	float minY = FLT_MAX;
	float minZ = FLT_MAX;
	float maxX = -FLT_MAX;
	float maxY = -FLT_MAX;
	float maxZ = -FLT_MAX;

	for (uint32_t i = 0; i < vertices.size(); i++)
	{
		minX = mMin(minX, vertices[i].x);
		minY = mMin(minY, vertices[i].y);
		minZ = mMin(minZ, vertices[i].z);
		maxX = mMax(maxX, vertices[i].x);
		maxY = mMax(maxY, vertices[i].y);
		maxZ = mMax(maxZ, vertices[i].z);
	}

	float scale = maxX - minX;
	scale = mMax(scale, maxY - minY);
	scale = mMax(scale, maxZ - minZ);
	scale = 1.0f / scale;

	for (uint32_t i = 0; i < vertices.size(); i++)
	{
		vertices[i].x = (vertices[i].x - minX) * scale - 0.5f;
		vertices[i].y = (vertices[i].y - minY) * scale - 0.5f;
		vertices[i].z = (vertices[i].z - minZ) * scale - 0.5f;
	}
}


vec3 Model::GetTriangleNormal(triangle const& tri)
{
	vec3 a = vertices[tri.vIndex[0] - 1];
	vec3 b = vertices[tri.vIndex[1] - 1];
	vec3 c = vertices[tri.vIndex[2] - 1];
	vec3 normal = glm::normalize(glm::cross(glm::normalize(c - a), glm::normalize(b - a)));
	return normal;
}

float Model::GetTriangleArea(triangle const& tri)
{
	vec3 corners[] = { vertices[tri.vIndex[0] - 1], vertices[tri.vIndex[1] - 1], vertices[tri.vIndex[2] - 1] };
	vec3 sides[] = { corners[1] - corners[0], corners[2] - corners[1], corners[0] - corners[2] };
	float length2s[] = { glm::dot(sides[0], sides[0]), glm::dot(sides[1], sides[1]), glm::dot(sides[2], sides[2]) };
	return (0.25f)*sqrtf(2 * (length2s[0] * length2s[1] + length2s[0] * length2s[2] + length2s[1] * length2s[2]) - (length2s[0] * length2s[0] + length2s[1] * length2s[1] + length2s[2] * length2s[2]));
}

void Model::GenerateSmoothNormals()
{
	normals.clear();
	for (uint32_t i = 0; i < vertices.size(); i++)
		normals.push_back(vec3(0, 0, 0));

	for (uint32_t i = 0; i < faces.size(); i++)
	{
		faces[i].normalIndex[0] = faces[i].vIndex[0];
		faces[i].normalIndex[1] = faces[i].vIndex[1];
		faces[i].normalIndex[2] = faces[i].vIndex[2];
	}

	for (uint32_t i = 0; i < faces.size(); i++)
	{
		triangle& tri = faces[i];

		vec3 weightedNormal = GetTriangleNormal(tri) * GetTriangleArea(tri);
		normals[tri.normalIndex[0] - 1] += weightedNormal;
		normals[tri.normalIndex[1] - 1] += weightedNormal;
		normals[tri.normalIndex[2] - 1] += weightedNormal;
	}

	for (uint32_t i = 0; i < normals.size(); i++)
	{
		normals[i] = glm::normalize(normals[i]);
	}
}

std::vector<float> Model::GetUVArray()
{
  std::vector<float> uv;
  for (size_t face = 0; face < faces.size(); ++face)
  {
    for (size_t corner = 0; corner < 3; ++corner)
    {
      uv.push_back(uvs[faces[face].uvIndex[corner] - 1].x);
      uv.push_back(uvs[faces[face].uvIndex[corner] - 1].y);
    }
  }
  return uv;
}

std::vector<float> Model::GetNormalArray()
{
  std::vector<float> norms;
  for (size_t face = 0; face < faces.size(); ++face)
  {
    for (size_t corner = 0; corner < 3; ++corner)
    {
      norms.push_back(normals[faces[face].normalIndex[corner] - 1].x);
      norms.push_back(normals[faces[face].normalIndex[corner] - 1].y);
      norms.push_back(normals[faces[face].normalIndex[corner] - 1].z);
    }
  }
  return norms;
}

std::vector<vec3> Model::GetVertexArray(int subIndex)
{
  TextureData &sub = subObjects[subIndex];
  std::vector<vec3> verts;
  for (size_t face = sub.firstFace; face < sub.firstFace + sub.faceCount; ++face)
  {
    for (size_t corner = 0; corner < 3; ++corner)
    {
      verts.push_back(vertices[faces[face].vIndex[corner] - 1]);
    }
  }
  return verts;
}

std::vector<float> Model::GetVertexArray()
{
  std::vector<float> verts;
  for (size_t face = 0; face < faces.size(); ++face)
  {
    for (size_t corner = 0; corner < 3; ++corner)
    {
      verts.push_back(vertices[faces[face].vIndex[corner] - 1].x);
      verts.push_back(vertices[faces[face].vIndex[corner] - 1].y);
      verts.push_back(vertices[faces[face].vIndex[corner] - 1].z);
    }
  }
  return verts;
}

bool Model::IsClimbable(int subIndex)
{
	return subObjects[subIndex].climbable;
}


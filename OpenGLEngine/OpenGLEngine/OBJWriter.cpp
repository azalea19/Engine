#include "OBJWriter.h"


void OBJWriter::SaveMeshToOBJ(IMesh const& model, string const& filepath)
{
  FILE* fp = fopen(filepath.c_str(), "wb");

  std::vector<vec3> positions = model.GetVertices();
  std::vector<vec3> normals = model.GetNormals();
  std::vector<vec2> texCoords = model.GetTexCoords();
  std::vector<int> indices = model.GetIndices();

  if (fp)
  {
	fprintf(fp, "mtllib test.mtl\n");
	fprintf(fp, "usemtl test\n");

    for (uint i = 0; i < model.GetVertexCount(); i++) // positions
    {
      vec3 pos = positions[i];
      fprintf(fp, "v %f %f %f\r\n", pos.x, pos.y, pos.z);
    }

    for (uint i = 0; i < model.GetNormalCount(); i++) // normals
    {
      vec3 norm = normals[i];
      fprintf(fp, "vn %f %f %f\r\n", norm.x, norm.y, norm.z);
    }

	for (uint i = 0; i < model.GetTexCoords().size() / 3; i++) // faces
	{
		vec2 tex = texCoords[i];
		fprintf(fp, "vt %f %f 0\r\n", tex.x, tex.y);
	}

    for (uint i = 0; i < model.GetIndexCount() / 3; i++) // faces
    {
      int v1 = indices[i * 3 + 0] + 1;
      int v2 = indices[i * 3 + 1] + 1;
      int v3 = indices[i * 3 + 2] + 1;
      fprintf(fp, "f %d %d %d\r\n", v1, v2, v3);
    }
    fclose(fp);
  }
}

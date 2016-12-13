#ifndef MeshLibrary_h__
#define MeshLibrary_h__

#include <unordered_map>
#include "Types.h"
#include "Singleton.h"
#include "Mesh.h"

class MeshLibrary : public Singleton<MeshLibrary>
{

public:

	MeshLibrary() {};

	void AddMesh(string name, MeshData const& mesh);

	Mesh GetMesh(string name);

private:

	std::unordered_map<string, Mesh> meshes;

};

#endif 
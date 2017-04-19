#ifndef ObjectLoader_h__
#define ObjectLoader_h__

#include <string>
#include <iostream>
#include <fstream>
#include "types.h"
#include <vector>
#include "ObjectInstance.h"
#include "LuaInstanceManager.h"

struct ObjectData
{
	vec3 pos;
	vec3 scale;
	std::string modelName;
	int yaw;
	int pitch;
	int activeAnimation;
};


class InstanceFileLoader
{
	std::vector<ObjectData> m_objectFileData;
	string m_currentFileName;


public:

	void LoadFile(string path);

	int GetNumObjects();


private:

  void ReadObjectDataFromFile(std::string fileName);

};
#endif

#ifndef ObjectLoader_h__
#define ObjectLoader_h__

#include <string>
#include <iostream>
#include <fstream>
#include "types.h"
#include <vector>
#include "ObjectInstance.h"
#include "LuaInstanceManager.h"

struct ObjectData{
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

	std::vector<ObjectInstance*> m_instances;

private:

public:
	 //m_objectFileData;
	void ReadObjectDataFromFile( std::string fileName);
	int ReadInstancesFromFile(std::string fileName);
	void LoadFile(string path);
	InstanceHandle ReadFromLoadedFile(int i);  
};
#endif

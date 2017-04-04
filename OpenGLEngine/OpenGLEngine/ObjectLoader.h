#ifndef ObjectLoader_h__
#define ObjectLoader_h__

#include <string>
#include <iostream>
#include <fstream>
#include "types.h"
#include <vector>

struct ObjectData{
	vec3 pos;
	vec3 scale;
	std::string modelName;
	int yaw;
	int pitch;
	int activeAnimation;
};


class ObjectLoader
{

private:

public:
	std::vector<ObjectData> m_objectFileData;
	void ReadFile(std::string fileName);
	void SaveFile(std::string fileName, std::string modelName, vec3 position, vec3 scale, int yaw, int pitch, int activeAnimation);
};
#endif

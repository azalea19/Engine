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

  //This should not be here, the file loader only needs to know about the object instance data
  //when we want to create the actual object instances we will use the 
	std::vector<ObjectInstance*> m_instances;

private:


public:

  //This should be private
  void ReadObjectDataFromFile(std::string fileName);

	int ReadInstancesFromFile(std::string fileName);
	void LoadFile(string path);

  //Not sure how you actually use this or what is is meant to do
	InstanceHandle ReadFromLoadedFile(int i);  

	int GetLength();

};
#endif

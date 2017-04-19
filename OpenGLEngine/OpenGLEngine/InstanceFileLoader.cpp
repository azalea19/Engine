#include "InstanceFileLoader.h"

void InstanceFileLoader::ReadObjectDataFromFile(std::string fileName)
{

	m_objectFileData.clear();

	std::ifstream m_dataFile;
	std::string temp;
	m_dataFile.open("Assets/Data/" + fileName + ".csv");
	int vectorIndex = 0;
	ObjectData oData;

	if (!m_dataFile) {
		//error text here
	}

	std:getline(m_dataFile, temp);	//removes the headers of the csv

	while (!m_dataFile.eof())	//reads in data till the file is empty
	{
		std::cout << m_objectFileData.size() << "    ";

		m_objectFileData.push_back(oData);


		std::getline(m_dataFile, temp, ',');	//Get modelName
		m_objectFileData.at(vectorIndex).modelName = temp;

		std::getline(m_dataFile, temp, ',');										//Get Position
		m_objectFileData.at(vectorIndex).pos.x = atof(temp.c_str());
		std::getline(m_dataFile, temp, ',');
		m_objectFileData.at(vectorIndex).pos.y = atof(temp.c_str());
		std::getline(m_dataFile, temp, ',');
		m_objectFileData.at(vectorIndex).pos.z = atof(temp.c_str());

		std::getline(m_dataFile, temp, ',');										//Get Scale
		m_objectFileData.at(vectorIndex).scale.x = atof(temp.c_str());
		std::getline(m_dataFile, temp, ',');
		m_objectFileData.at(vectorIndex).scale.y = atof(temp.c_str());
		std::getline(m_dataFile, temp, ',');
		m_objectFileData.at(vectorIndex).scale.z = atof(temp.c_str());

		std::getline(m_dataFile, temp, ',');
		m_objectFileData.at(vectorIndex).yaw = atof(temp.c_str());

		std::getline(m_dataFile, temp, ',');
		m_objectFileData.at(vectorIndex).pitch = atof(temp.c_str());

		std::getline(m_dataFile, temp);
		m_objectFileData.at(vectorIndex).activeAnimation = atoi(temp.c_str());

		vectorIndex += 1;
	}

	m_dataFile.close();

}

void InstanceFileLoader::LoadFile(string fileName)
{
	m_currentFileName = fileName;
	ReadObjectDataFromFile(fileName);
}

//Creates an object from some object data that got loaded in the object data vector
//And gives back its handle
InstanceHandle InstanceFileLoader::ReadFromLoadedFile(int i)
{
	InstanceHandle h = LuaInstanceManager::AddNewInstance(m_objectFileData.at(i).modelName);
	ObjectInstance * object = LuaInstanceManager::GetInstance(h);
	object->SetTranslation(m_objectFileData.at(i).pos),
	object->SetScale(m_objectFileData.at(i).scale);
	object->SetActiveAnimation(m_objectFileData.at(i).activeAnimation);

	return h;
}


int InstanceFileLoader::GetNumObjects()
{
  //Return the number of object instances
	return m_objectFileData.size();
}
#include "ObjectLoader.h"

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

InstanceHandle InstanceFileLoader::ReadFromLoadedFile(int i)
{
	InstanceHandle h = LuaInstanceManager::AddNewInstance(m_objectFileData.at(i).modelName);
	ObjectInstance * object = LuaInstanceManager::GetInstance(h);
	object->SetTranslation(m_objectFileData.at(i).pos),
	object->SetScale(m_objectFileData.at(i).scale);
	object->SetActiveAnimation(m_objectFileData.at(i).activeAnimation);

	return h;
}

int InstanceFileLoader::ReadInstancesFromFile(std::string fileName)
{
	std::vector<ObjectInstance*> objects;

	int newInstanceCount = 0;

	ReadObjectDataFromFile("test");

	for (int i = 0; i < m_objectFileData.size(); i++) 
	{
		newInstanceCount += 1;
		std::cout << m_objectFileData.size() << " AND " << i << " ";
		std::cout << m_objectFileData.at(i).modelName << " ";
		objects.push_back(ModelLibrary::GetInstance().GetObjectInstance(m_objectFileData.at(i).modelName));

		std::cout << m_objectFileData.at(i).pos.x << " " << m_objectFileData.at(i).pos.y << " " << m_objectFileData.at(i).pos.z << " ";
		objects.at(i)->SetTranslation(m_objectFileData.at(i).pos.x,
			m_objectFileData.at(i).pos.y,
			m_objectFileData.at(i).pos.z);

		std::cout << m_objectFileData.at(i).scale.x << " " << m_objectFileData.at(i).scale.y << " " << m_objectFileData.at(i).scale.z << " ";
		objects.at(i)->SetScale(m_objectFileData.at(i).scale);

		std::cout << m_objectFileData.at(i).pitch << " ";
		std::cout << m_objectFileData.at(i).yaw << " ";

		std::cout << m_objectFileData.at(i).activeAnimation << std::endl;
		objects.at(i)->SetActiveAnimation(m_objectFileData.at(i).activeAnimation);

		return newInstanceCount;

	}
}
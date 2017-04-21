#include "ObjectLoader.h"
#include <string>
#include <iostream>
#include <fstream>

void ObjectLoader::ReadFile(std::string fileName) {
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

void ObjectLoader::SaveFile(std::string fileName, std::string modelName, vec3 position, vec3 scale, int yaw, int pitch, int activeAnimation) {
	{
		ofstream myfile;
		myfile.open("example.csv");
		myfile << "This is the first cell in the first column.\n";
		myfile << "a,b,c,\n";
		myfile << "c,s,v,\n";
		myfile << "1,2,3.456\n";
		myfile << "semi;colon";
		myfile.close();
		return 0;
	}
}
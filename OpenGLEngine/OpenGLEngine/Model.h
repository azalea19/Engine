#ifndef Model_h__
#define Model_h__

#include <algorithm>
#include "Types.h"

/**
* @file   Model.h
* @Author Maddisen Topaz
* @date   S2, 2016
* @brief  The model struct.
*
* The model struct contains all the data relating to a model.
*/


struct triangle
{
	uint32_t vIndex[3];			
	uint32_t uvIndex[3];			
	uint32_t normalIndex[3];		
};


struct TextureData
{
	bool climbable;				
	uint32_t firstFace;			
	uint32_t faceCount;			
	string texturePath;			
};

struct Model
{
	std::vector<TextureData> subObjects;		
	std::vector<vec3> vertices;					
	std::vector<vec3> normals;					
	std::vector<vec2> uvs;						
	std::vector<triangle> faces;				

												
	std::vector<float> GetVertexArray();

	
	std::vector<vec3> GetVertexArray(int subIndex);

	
	std::vector<float> GetNormalArray();


	std::vector<float> GetUVArray();


	bool IsClimbable(int subIndex);


	vec3 GetTriangleNormal(triangle const& tri);

	
	float GetTriangleArea(triangle const& tri);


	
	void GenerateSmoothNormals();

	
	void CenterModel();

	
	void Normalize();

};

#endif // Model_h__

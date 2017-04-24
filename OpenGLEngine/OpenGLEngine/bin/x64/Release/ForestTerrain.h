#ifndef ForestTerrain_h__
#define ForestTerrain_h__

#include "Terrain.h"
#include "ObjectInstance.h"
#include "Random.h"
#include "ModelLibrary.h"
#include "OBJWriter.h"



/**
* @file   ForestTerrain.h
* @Author Maddisen Topaz
* @date   S1, 2017
* @brief  Generates forest terrain
*
*/
class ForestTerrain : public IRenderable, public IMesh
{
public:



	/// <summary>
	/// Initializes a new instance of the ForestTerrain class.
	/// </summary>
	/// <param name="terrainWidth">Width of the terrain.</param>
	/// <param name="terrainHeight">Height of the terrain.</param>
	/// <param name="heightScale">The height scale.</param>
	/// <param name="textureTileCount">The texture tile count.</param>
	/// <param name="filepath">The filepath.</param>
	/// <param name="density">The density.</param>
	ForestTerrain(uint terrainWidth, uint terrainHeight, float heightScale, float textureTileCount, string const& filepath, int density);


	/// <summary>
	/// Generates the forest.
	/// </summary>
	void GenerateForest();


	/// <summary>
	/// Saves the terrain to object.
	/// </summary>
	/// <param name="filepath">The filepath.</param>
	void SaveTerrainToOBJ(const string& filepath) const;


	/// <summary>
	/// Renders the specified world matrix.
	/// </summary>
	/// <param name="worldMatrix">The world matrix.</param>
	/// <param name="viewMatrix">The view matrix.</param>
	/// <param name="projectionMatrix">The projection matrix.</param>
	/// <param name="time">The time.</param>
	virtual void Render(mat4 const& worldMatrix, mat4 const& viewMatrix, mat4 const& projectionMatrix, float time) override;


	/// <summary>
	/// Gets the vertices.
	/// </summary>
	/// <returns></returns>
	virtual std::vector<vec3> const& GetVertices() const override;


	/// <summary>
	/// Gets the normals.
	/// </summary>
	/// <returns></returns>
	virtual std::vector<vec3> const& GetNormals() const override;


	/// <summary>
	/// Gets the indices.
	/// </summary>
	/// <returns></returns>
	virtual std::vector<int> const& GetIndices() const override;
  
  //virtual std::vector<vec2> const& GetTexCoords(int index) const override;

private:

	/// <summary>
	/// The m trees
	/// </summary>
	std::vector<ObjectInstance*> m_trees;

	/// <summary>
	/// The m p land
	/// </summary>
	Terrain* m_pLand;

};


#endif // ForestTerrain_h__

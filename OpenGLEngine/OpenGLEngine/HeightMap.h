#ifndef HeightMap_h__
#define HeightMap_h__

#include "Types.h"
#include "Interface2D.h"

class HeightMap
{
public:

	/// <summary>
	/// Initializes a new instance of the <see cref="HeightMap"/> class.
	/// </summary>
	/// <param name="filePath">The file path.</param>
	HeightMap(string const& filePath);

	/// <summary>
	/// Loads the height map.
	/// </summary>
	void LoadHeightMap();

/// <summary>
/// Gets the height value at pixel.  Assuming 4 bytes per pixel 32 bit image depth.
/// </summary>
/// <param name="pixelPos">The pixel position.</param>
/// <returns></returns>
	float GetHeightValueAtPixel(vec2i const& pixelPos);

	/// <summary>
	/// Gets the width.
	/// </summary>
	/// <returns></returns>
	int GetWidth() const;

	/// <summary>
	/// Gets the height.
	/// </summary>
	/// <returns></returns>
	int GetHeight() const;

private:

	/// <summary>
	/// The height map
	/// </summary>
	uint* m_pHeightMap;
	/// <summary>
	/// The height map dimensions
	/// </summary>
	vec2 m_heightMapDimensions;
	/// <summary>
	/// The height map file
	/// </summary>
	string m_heightMapFile;

};


#endif // HeightMap_h__

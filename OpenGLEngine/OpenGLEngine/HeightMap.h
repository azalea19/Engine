#ifndef HeightMap_h__
#define HeightMap_h__

#include "Types.h"
#include "Interface2D.h"

class HeightMap
{
public:

  HeightMap(string const& filePath);

  void LoadHeightMap();

  //Assuming 4 bytes per pixel 32 bit image.
  float GetHeightValue(vec2i const& pixelPos);

  int GetWidth() const;

  int GetHeight() const;

private:

  uint* m_pHeightMap;
  vec2 m_heightMapDimensions;
  string m_heightMapFile;

};


#endif // HeightMap_h__

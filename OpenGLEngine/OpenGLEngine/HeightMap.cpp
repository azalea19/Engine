#include "HeightMap.h"
#include "Interface2D.h"
#include "SDL_image.h"

HeightMap::HeightMap(string const& filePath) 
  : m_heightMapFile(filePath)
{
  LoadHeightMap();
}

void HeightMap::LoadHeightMap()
{
  SDL_Surface* pHeightMapSurface = GetSurfaceFromImg(m_heightMapFile);
  m_heightMapDimensions = GetImageDimensions(pHeightMapSurface);
  m_pHeightMap = (uint*)malloc(sizeof(uint) * m_heightMapDimensions.x * m_heightMapDimensions.y);
  m_pHeightMap = GetPixelData(pHeightMapSurface);
}

float HeightMap::GetHeightValue(vec2i const& pixelPos)
{
  uint pos = (m_heightMapDimensions.x * pixelPos.y) + pixelPos.x;

  //Color = 0xRRGGBBAA
  //Color packed in to a four-byte integer with RGBA component
  //We need mask and shift to get back the color channels.

  ubyte redChannel = ubyte((m_pHeightMap[pos] & 0x00FF0000) >> 16);
  ubyte blueChannel = ubyte((m_pHeightMap[pos] & 0x0000FF00) >> 8);
  ubyte greenChannel = ubyte((m_pHeightMap[pos] & 0x000000FF) >> 0);

  float ave = (redChannel + blueChannel + greenChannel) / 3.f;

  return ave / 255;
}

int HeightMap::GetWidth() const
{
  return m_heightMapDimensions.x;
}

int HeightMap::GetHeight() const
{
  return m_heightMapDimensions.y;
}

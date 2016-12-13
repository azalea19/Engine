#include <cstdint>

typedef float (*HeightMapSampleFunc)(int64_t x, int64_t y, void *args);

float* CreateHeightMap(int64_t width, int64_t height, HeightMapSampleFunc sampleFunc, void *args);



struct WaveSampleArgs
{
	float minHeight;
	float maxHeight;
	float waveLength;
};

float XWaveSample(int64_t x, int64_t y, void* args);
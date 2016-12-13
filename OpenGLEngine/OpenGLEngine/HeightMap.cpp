#include "HeightMap.h"
#include <cstdlib>
#include <math.h>
#include "MMath.h"

float * CreateHeightMap(int64_t width, int64_t height, HeightMapSampleFunc sampleFunc, void * args)
{
	float *heightMap = (float*)malloc(width * height * sizeof(float));

	for (int64_t y = 0; y < height; y++)
		for (int64_t x = 0; x < width; x++)
			heightMap[y * width + x] = sampleFunc(x, y, args);

	return heightMap;
}

float XWaveSample(int64_t x, int64_t y, void * _args)
{
	WaveSampleArgs *args = (WaveSampleArgs*)_args;

	float val = sin(x * 2 * PI / args->waveLength);
	val = (val + 1) * 0.5f;
	return mLerp(args->minHeight, args->maxHeight, val);
}

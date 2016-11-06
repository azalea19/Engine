#include "Texture.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include "SDL.h"
#include "SDL_image.h"
#include "Types.h"

struct FloatColor
{
	float r;
	float g;
	float b;
	float a;
};

float GammaCorrectedAverage(float a, float b, float c, float d, float wa, float wb, float wc, float wd)
{
	return sqrt((a * a * wa + b * b * wb + c * c * wc + d * d * wd) / (wa + wb + wc + wd));
}

GLuint loadBMP(const char * imagepath) 
{

	//printf("Reading image %s\n", imagepath);

	// Data read from the header of the BMP file
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	unsigned int width, height;
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE *file;
	fopen_s(&file, imagepath, "rb");
	if (!file) { printf("%s could not be opened.\n", imagepath); getchar(); return 0; }

	// Read the header, i.e. the 54 first bytes

	// If less than 54 bytes are read, problem
	if (fread(header, 1, 54, file) != 54) {
		printf("Not a correct BMP file\n");
		return 0;
	}
	// A BMP files always begins with "BM"
	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		return 0;
	}
	// Make sure this is a 24bpp file
	if (*(int*)&(header[0x1E]) != 0) { printf("Not a correct BMP file\n");    return 0; }
	if (*(int*)&(header[0x1C]) != 24) { printf("Not a correct BMP file\n");    return 0; }

	// Read the information about the image
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize == 0)    imageSize = width*height * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      dataPos = 54; // The BMP header is done that way

										 // Create a buffer
	data = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);

	// Everything is in memory now, the file wan be closed
	fclose(file);

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	// OpenGL has now copied the data. Free our own version
	delete[] data;

	// Poor filtering, or ...
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// ... nice trilinear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Return the ID of the texture we just created
	return textureID;
}

SDL_Surface* ConvertToRGBA(SDL_Surface* source)
{
	SDL_PixelFormat pf;
	memset(&pf, 0, sizeof(SDL_PixelFormat));
	pf.BitsPerPixel = 32;
	pf.BytesPerPixel = 4;
	pf.Rmask = 0x000000ff;
	pf.Gshift = 8;
	pf.Gmask = 0x0000ff00;
	pf.Bshift = 16;
	pf.Bmask = 0x00ff0000;
	pf.Ashift = 24;
	pf.Amask = 0xff000000;

	return SDL_ConvertSurface(source, &pf, NULL);
}

SDL_Surface* FlipSurface(SDL_Surface* source)
{
	SDL_Surface* dst = SDL_CreateRGBSurface(NULL, source->w, source->h, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
	uint32_t* dstPixels = (uint32_t*)(dst->pixels);
	uint32_t* srcPixels = (uint32_t*)(source->pixels);
	for (int y = 0; y < source->h; y++)
	{
		uint32_t* dstRow = dstPixels + y * (dst->pitch / 4);
		uint32_t* srcRow = srcPixels + (source->h - y - 1) * (source->pitch / 4);
		for (int x = 0; x < source->w; x++)
		{
			dstRow[x] = srcRow[x];
		}
	}
	return dst;
}

uint32_t* GetPixelData(SDL_Surface* source)
{
	uint32_t* data = (uint32_t*)malloc(sizeof(uint32_t) * source->w * source->h);

	uint32_t* dst = data;
	uint8_t* pixels = (uint8_t*)(source->pixels);

	for (int y = 0; y < source->h; y++)
	{
		memcpy(dst, pixels, sizeof(uint32_t) * source->w);
		dst += source->w;
		pixels += source->pitch;
	}

	return data;
}

FloatColor* ConvertToFloatColors(uint32_t* data, int count)
{
	FloatColor* dst = (FloatColor*)malloc(count * sizeof(FloatColor));
	for (int i = 0; i < count; i++)
	{
		dst[i].a = ((data[i] >> 24) & 255) / 255.f;
		dst[i].r = ((data[i] >> 16) & 255) / 255.f;
		dst[i].g = ((data[i] >> 8) & 255) / 255.f;
		dst[i].b = ((data[i] >> 0) & 255) / 255.f;
	}
	return dst;
}

uint32_t* ConvertToIntColors(FloatColor* data, int count)
{
	uint32_t* dst = (uint32_t*)malloc(count * sizeof(uint32_t));
	for (int i = 0; i < count; i++)
	{
		dst[i] = (((uint32_t)(data[i].a * 255.0)) & 255) << 24;
		dst[i] |= (((uint32_t)(data[i].r * 255.0)) & 255) << 16;
		dst[i] |= (((uint32_t)(data[i].g * 255.0)) & 255) << 8;
		dst[i] |= (((uint32_t)(data[i].b * 255.0)) & 255) << 0;
	}
	return dst;
}

void ThresholdAlpha(FloatColor* data, int count, float threshold = 1)
{
	for (int i = 0; i < count; i++)
		if (data[i].a < threshold)
			data[i].a = 0;
}

FloatColor* GenerateMip(FloatColor* source, int width, int height, int* mipWidth, int* mipHeight)
{
	int newWidth = width >> 1;
	int newHeight = height >> 1;

	if (newWidth * newHeight == 0)
	{
		*mipWidth = 0;
		*mipHeight = 0;
		return nullptr;
	}

	FloatColor* mip = (FloatColor*)malloc(sizeof(FloatColor) * newWidth * newHeight);

	for (int y = 0; y < newHeight; y++)
	{
		for (int x = 0; x < newWidth; x++)
		{
			FloatColor& dst = mip[y * newWidth + x];
			FloatColor& s1 = source[y * 2 * width + x * 2];
			FloatColor& s2 = source[y * 2 * width + x * 2 + 1];
			FloatColor& s3 = source[(y * 2 + 1) * width + x * 2];
			FloatColor& s4 = source[(y * 2 + 1) * width + x * 2 + 1];
			
			dst.a = (s1.a + s2.a + s3.a + s4.a) / 4;
			dst.r = GammaCorrectedAverage(s1.r, s2.r, s3.r, s4.r, s1.a, s2.a, s3.a, s4.a);
			dst.g = GammaCorrectedAverage(s1.g, s2.g, s3.g, s4.g, s1.a, s2.a, s3.a, s4.a);
			dst.b = GammaCorrectedAverage(s1.b, s2.b, s3.b, s4.b, s1.a, s2.a, s3.a, s4.a);
		}
	}

	*mipWidth = newWidth;
	*mipHeight = newHeight;
	return mip;
}

GLuint UploadTextureMipped(SDL_Surface* source)
{
	int width = source->w;
	int height = source->h;
	int newWidth = 0;
	int newHeight = 0;

	uint32_t* intPixels = GetPixelData(source);
	FloatColor* floatPixels = ConvertToFloatColors(intPixels, width * height);
	ThresholdAlpha(floatPixels, width * height, 0.8f);
	free(intPixels);
	intPixels = ConvertToIntColors(floatPixels, width * height);

	GLuint textureID = 0;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, intPixels);
	free(intPixels);

	FloatColor* mip = GenerateMip(floatPixels, width, height, &newWidth, &newHeight);
	free(floatPixels);

	int mipLevel = 1;
	while (mip)
	{
		intPixels = ConvertToIntColors(mip, newWidth * newHeight);
		glTexImage2D(GL_TEXTURE_2D, mipLevel, GL_RGBA, newWidth, newHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, intPixels);
		free(intPixels);
		FloatColor* newMips = GenerateMip(mip, newWidth, newHeight, &newWidth, &newHeight);
		free(mip);
		mip = newMips;
		mipLevel++;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, mipLevel - 1);

	return textureID;
}

GLuint loadImage(const char * imagepath)
{
	GLuint TextureID = 0;

	SDL_Surface* rawSurface = IMG_Load(imagepath);
	SDL_Surface* convertedSurface = ConvertToRGBA(rawSurface);
	SDL_Surface* flippedSurface = FlipSurface(convertedSurface);

	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);

	int Mode = GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, Mode, flippedSurface->w, flippedSurface->h, 0, Mode, GL_UNSIGNED_BYTE, flippedSurface->pixels);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	SDL_FreeSurface(rawSurface);
	SDL_FreeSurface(convertedSurface);
	SDL_FreeSurface(flippedSurface);

	return TextureID;
}
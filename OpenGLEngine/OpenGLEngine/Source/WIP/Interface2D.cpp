#include "Interface2D.h"
#include "SDL.h"
#include "Screen.h"
#include <stdio.h>
#include <GL/glew.h>
#include "ShaderLibrary.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Shader.h"

static uint32_t* GetPixelData(SDL_Surface* source)
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

SDL_Surface* GetSurfaceFromImg(const string& filePath)
{
  SDL_Surface* surface;
  surface = IMG_Load(filePath.c_str());

  if (surface == nullptr)
  {
    printf("Image %s error could not render to surface.", filePath.c_str());
    getchar();
    return 0;
  }
  return surface;
}

uint32_t* GetImgData(const string& filePath)
{
  SDL_Surface* surface = GetSurfaceFromImg(filePath);

  //Create a surface to the correct size in RGB format, and copy the old image
  SDL_Surface * s = SDL_CreateRGBSurface(0, surface->w, surface->h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
  SDL_BlitSurface(surface, NULL, s, NULL);

  uint32_t* pixData = GetPixelData(s);

  return pixData;
}

vec2 GetImageDimensions(SDL_Surface* surface)
{
  vec2 dim = vec2(0);
  dim.x = surface->w;
  dim.y = surface->h;
  return dim;
}

void DrawText(int size, string const& filePath, string const& text, vec2 pos, vec3 const& color, int center, int screenWidth,int screenHeight)
{
  //Load the font
  TTF_Font *font = TTF_OpenFont(filePath.c_str(), size);

  if (font == nullptr)
  {
    printf("TTF_OpenFont error, could not open font %s ", filePath.c_str());
    getchar();
    return;
  }

  SDL_Color colorFg = { uint8_t(color.b * 255), uint8_t(color.g * 255) , uint8_t(color.r * 255) };
  SDL_Surface *surface;

  //Render font to a SDL_Surface
  if ((surface = TTF_RenderText_Blended(font, text.c_str(), colorFg)) == nullptr)
  {
    TTF_CloseFont(font);
    printf("TTF_OpenFont error could not render to surface.");
    return;
  }

  GLuint texId;

  //Generate OpenGL texture
  glGenTextures(1, &texId);
  glBindTexture(GL_TEXTURE_2D, texId);

  //Avoid mipmap filtering
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  //Create a surface to the correct size in RGB format, and copy the old image
  SDL_Surface * s = SDL_CreateRGBSurface(0, surface->w, surface->h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
  SDL_BlitSurface(surface, NULL, s, NULL);

  uint32_t* pixData = GetPixelData(s);

  //Copy the created image into OpenGL format
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixData);

  string previousShader = ShaderLibrary::GetInstance().GetCurrentShaderName();

  ShaderLibrary::GetInstance().BindShader("orthoShader");

  std::unique_ptr<IShader> const& shader = ShaderLibrary::GetInstance().CurrentShader();

  GLuint gVBO;
  GLuint gUVBO;


  if (center)
  {
    int halfscreen = screenWidth / 2;
    int halfheight = screenHeight / 2;
    pos.x = halfscreen - (surface->w / 2);
    pos.y = halfheight - (surface->h / 2);
  }

    const GLfloat g_vertex_buffer_data[] =
    {
      (float)(pos.x),				(float)(pos.y + surface->h),				0,
      (float)(pos.x + surface->w),	(float)(pos.y + surface->h),				0,
      (float)(pos.x),				(float)(pos.y),							0,
      (float)(pos.x + surface->w),	(float)(pos.y + surface->h),				0,
      (float)(pos.x + surface->w),	(float)(pos.y),							0,
      (float)(pos.x),				(float)(pos.y),							0
    };

  const GLfloat g_uv_buffer_data[] =
  {
    0,1,
    1,1,
    0,0,
    1,1,
    1,0,
    0,0
  };


  glGenBuffers(1, &gVBO);
  glBindBuffer(GL_ARRAY_BUFFER, gVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  //Handle the uv buffer
  glGenBuffers(1, &gUVBO);
  glBindBuffer(GL_ARRAY_BUFFER, gUVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);


  glDisable(GL_DEPTH_TEST);

  glEnable(GL_TEXTURE_2D);

  // Enable blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);




  glEnableVertexAttribArray(shader->Attribute("position"));
  glBindBuffer(GL_ARRAY_BUFFER, gVBO);
  glVertexAttribPointer(shader->Attribute("position"), 3, GL_FLOAT, GL_FALSE, 0, NULL);


  glEnableVertexAttribArray(shader->Attribute("uvIn"));
  glBindBuffer(GL_ARRAY_BUFFER, gUVBO);
  glVertexAttribPointer(shader->Attribute("uvIn"), 2, GL_FLOAT, GL_FALSE, 0, NULL);


  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texId);

  shader->TransmitUniform("diffuse", 0);

  glDrawArrays(GL_TRIANGLES, 0, 6);

  glFlush();

  glDisable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);

  ShaderLibrary::GetInstance().BindShader(previousShader);

  //Cleanup
  TTF_CloseFont(font);
  SDL_FreeSurface(s);
  free(pixData);
  SDL_FreeSurface(surface);
  glDeleteTextures(1, &texId);
  glDeleteBuffers(1, &gVBO);
  glDeleteBuffers(1, &gUVBO);

  glDisable(GL_BLEND);
}

void DrawImage(string const& filePath)
{
  SDL_Surface* surface;

  surface = IMG_Load(filePath.c_str());

  //Render font to a SDL_Surface
  if (surface == nullptr)
  {
    printf("Texture %s error could not render to surface.", filePath);
    getchar();
    return;
  }

  GLuint texId;

  //Generate OpenGL texture
  glGenTextures(1, &texId);
  glBindTexture(GL_TEXTURE_2D, texId);

  //Avoid mipmap filtering
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


  //Create a surface to the correct size in RGB format, and copy the old image
  SDL_Surface * s = SDL_CreateRGBSurface(0, surface->w, surface->h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
  SDL_BlitSurface(surface, NULL, s, NULL);

  uint32_t* pixData = GetPixelData(s);

  //Copy the created image into OpenGL format
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, s->w, s->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixData);

  string previousShader = ShaderLibrary::GetInstance().GetCurrentShaderName();

  ShaderLibrary::GetInstance().BindShader("orthoShader");

  std::unique_ptr<IShader> const& shader = ShaderLibrary::GetInstance().CurrentShader();

  GLuint gVBO;
  GLuint gUVBO;

  //Y flipped in shader
  //Top left corner at 0,0
  const GLfloat g_vertex_buffer_data[] =
  {
    (float)(0),(float)(s->h), 0,
    (float)(s->w),(float)(s->h), 0,
    (float)(0), (float)(0), 0,

    (float)(s->w), (float)(s->h),	0,
    (float)(s->w), (float)(0), 0,
    (float)(0), (float)(0), 0
  };

  const GLfloat g_uv_buffer_data[] =
  {
    0,1,
    1,1,
    0,0,
    1,1,
    1,0,
    0,0
  };

  glGenBuffers(1, &gVBO);
  glBindBuffer(GL_ARRAY_BUFFER, gVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  //Handle the uv buffer
  glGenBuffers(1, &gUVBO);
  glBindBuffer(GL_ARRAY_BUFFER, gUVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);


  glDisable(GL_DEPTH_TEST);

  glEnable(GL_TEXTURE_2D);

  shader->TransmitUniform("width", GetScreenDimensions().x);
  shader->TransmitUniform("height", GetScreenDimensions().y);

  glEnableVertexAttribArray(shader->Attribute("position"));
  glBindBuffer(GL_ARRAY_BUFFER, gVBO);
  glVertexAttribPointer(shader->Attribute("position"), 3, GL_FLOAT, GL_FALSE, 0, NULL);


  glEnableVertexAttribArray(shader->Attribute("uvIn"));
  glBindBuffer(GL_ARRAY_BUFFER, gUVBO);
  glVertexAttribPointer(shader->Attribute("uvIn"), 2, GL_FLOAT, GL_FALSE, 0, NULL);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texId);

  shader->TransmitUniform("diffuse", 0);

  glDrawArrays(GL_TRIANGLES, 0, 6);

  glFlush();

  glDisable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);

  ShaderLibrary::GetInstance().BindShader(previousShader);

  //Cleanup
  free(pixData);
  SDL_FreeSurface(s);
  SDL_FreeSurface(surface);
  glDeleteTextures(1, &texId);
  glDeleteBuffers(1, &gVBO);
  glDeleteBuffers(1, &gUVBO);

}

static void BreakOnGLError()
{
	int error = glGetError();
	if (error != 0)
	{
		printf("Open GL error code: %d", error);
		getchar();
	}
}
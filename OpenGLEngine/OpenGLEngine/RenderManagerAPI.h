

#pragma once
#include "LuaContext.h"
#include "LuaManager.h"
#include "SDL.h"
#include "time.h"
#include "ModelLibrary.h"
#include "Utility.h"
#include "ShaderLibrary.h"
#include "InputManager.h"
#include "Interface2D.h"
#include "SDL_ttf.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include "SoundManager.h"
#include "Screen.h"
#include "MCamera.h"
#include <GL/glew.h>
#include "assimp/Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postProcess.h"
#include <chrono>
#include "RenderableObject.h"
#include "TextureLibrary.h"
#include "FrameBuffer.h"
#include "SceneDecomposeEffect.h"
#include "Texture.h"
#include <iostream>
#include "FXAAEffect.h"
#include "ObjectInstance.h"
#include "MMath.h"
#include "Terrain.h"
#include "MVCView.h"
#include "RenderManager.h"

class RenderManagerAPI
{
public:
	static void Expose(LuaContextHandle contextHandle, string luaAPIName);
	static void Render(mat4 const& worldMatrix, mat4 const& viewMatrix, mat4 const& projectionMatrix, float time);
	static void TestRender();
	static void UpdatePlayer();

};
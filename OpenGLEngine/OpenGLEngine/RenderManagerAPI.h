#pragma once
#include "LuaContext.h"
#include "LuaManager.h"
#include "RenderManager.h"
#include "MathAPI.h"
#include "TextureLibrary.h"
#include "ShaderLibrary.h"
#include "FrameBuffer.h"

#include "Types.h"
#include "SDL.h"
#include "ModelLibrary.h"
#include "Utility.h"
#include "ShaderLibrary.h"
#include "InputManager.h"
#include "Interface2D.h"
#include "SDL_ttf.h"
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
#include "LuaManager.h"
#include <iostream>
#include "DepthThresholdEffect.h"
#include "GodRaysEffect.h"
#include "BloomEffect.h"
#include "FXAAEffect.h"
#include "ObjectInstance.h"
#include "MMath.h"
#include "ForestTerrain.h"
#include "MultiplicativeBlendEffect.h"
#include "DirectionalLightingEffect.h"
#include "RenderManager.h"
#include "Terrain.h"
#include "MPlayer.h"



#include "MCamera.h"
#include "LuaInstanceManager.h"
#include "LuaObjectInstanceManager.h"


/**
* @file LuaVectorUtility.h
* @Author Elizabeth Haynes
* @date   S1, 2017
* @brief API for rendering with the engine through a Lua interface
*/
class RenderManagerAPI
{
public:


	static void RenderManagerAPI::Initialise();
	static void RenderManagerAPI::Render(LuaRef worldMatrix, LuaRef viewMatrix, LuaRef projectionMatrix, float time);
  static void RenderManagerAPI::RenderObject(int camID, float time, int instanceHandle);
	static void RenderManagerAPI::RenderFromCamera(int camID, float time);
	static void RenderManagerAPI::AddObject(int object);

  static void RenderManagerAPI::BeginRender();
  static void RenderManagerAPI::EndRender();

  static void SetShader(string const& shader);
  static void Present();

	static void Expose(LuaContextHandle contextHandle, string luaAPIName);

};
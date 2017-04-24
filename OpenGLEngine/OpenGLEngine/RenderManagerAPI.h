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


	/// <summary>
	/// Initialises this instance.
	/// </summary>
	static void RenderManagerAPI::Initialise();

	/// <summary>
	/// Renders the specified world matrix.
	/// </summary>
	/// <param name="worldMatrix">The world matrix.</param>
	/// <param name="viewMatrix">The view matrix.</param>
	/// <param name="projectionMatrix">The projection matrix.</param>
	/// <param name="time">The time.</param>
	/// todo fix broken
	static void RenderManagerAPI::Render(LuaRef worldMatrix, LuaRef viewMatrix, LuaRef projectionMatrix, float time);
	/// <summary>
	/// Renders the object.
	/// </summary>
	/// <param name="camID">The cam identifier.</param>
	/// <param name="time">The time.</param>
	/// <param name="instanceHandle">The instance handle.</param>
	/// <param name="lightingApplied">The lighting applied.</param>
	static void RenderManagerAPI::RenderObject(int camID, float time, int instanceHandle, int lightingApplied);
	/// <summary>
	/// Renders from camera.
	/// </summary>
	/// <param name="camID">The cam identifier.</param>
	/// <param name="time">The time.</param>
	static void RenderManagerAPI::RenderFromCamera(int camID, float time);
	/// <summary>
	/// Adds the object.
	/// </summary>
	/// <param name="object">The object.</param>
	static void RenderManagerAPI::AddObject(int object);
	/// <summary>
	/// Removes the object.
	/// </summary>
	/// <param name="object">The object.</param>
	static void RenderManagerAPI::RemoveObject(int object);

	/// <summary>
	/// Begins the render.
	/// </summary>
	static void RenderManagerAPI::BeginRender();
	/// <summary>
	/// Ends the render.
	/// </summary>
	static void RenderManagerAPI::EndRender();
	/// <summary>
	/// Sets the fill mode (wireframe = 0, fill = 1).
	/// </summary>
	/// <param name="fillMode">The fill mode.</param>
	static void RenderManagerAPI::SetFillMode(int fillMode);

	/// <summary>
	/// Applies post processing and displays resulting texture on screen
	/// </summary>
  static void Present(int camID);

	/// <summary>
	/// Exposes the lua API
	/// </summary>
	/// <param name="contextHandle">The context handle.</param>
	/// <param name="luaAPIName">Name of the lua API.</param>
	static void Expose(LuaContextHandle contextHandle, string luaAPIName);

};
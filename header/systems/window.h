#pragma once
#include <SDL.h>
#include <core/subsystem.h>
#include <systems/renderSystem.h>
#include <systems/inputHandler.h>
#include <systems/assetManager.h>

// todo: Ways to change parameters after creation
// todo: Fullscreen and other modes

class Window : public SubSystem
{
public:
  Window(const char* title = "GDL-Collab-Game", int width = 640, int height = 480);
private:
  friend class RenderSystem;
  friend class AssetManager;
  SDL_Window* window;
};
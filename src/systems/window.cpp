#include <SDL.h>
#include <systems/window.h>

Window::Window(const char* title, int width, int height)
{
  window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
  if (!window)
  {
    throw "Cannot initialize window";
  }
}

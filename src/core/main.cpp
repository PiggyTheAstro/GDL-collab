#ifdef __GNUC__
	#define SDL_MAIN_AVAILABLE
#endif
#include <SDL.h>
#include <core/game.h>
#include <components/rectRenderer.h>
#include <systems/assetManager.h>
#include <components/spriteRenderer.h>
#include <components/rectCollider.h>

using namespace Vectors;

int main(int argc, char** argv)
{
	Game game = Game();
	EntitySystem* entitySystem = ServiceHandler::instance->GetModule<EntitySystem>();
	SDL_DisplayMode display;
	SDL_GetCurrentDisplayMode(0, &display);
	while (ServiceHandler::instance->isRunning)
	{
		game.Update();
	}
	game.Cleanup();
	SDL_Quit();
	return 0;
}
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <core/game.h>

extern void GameMain(Game&);

int main(int argc, char** argv)
{
	SDL_SetMainReady();
	Game game = Game();
	GameMain(game);
	game.Cleanup();
	SDL_Quit();
	return 0;
}
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <core/game.h>

extern void gameMain(Game&);

int main(int argc, char** argv)
{
	SDL_SetMainReady();
	Game game = Game();
	gameMain(game);
	game.Cleanup();
	SDL_Quit();
	return 0;
}
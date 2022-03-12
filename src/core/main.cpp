#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <core/serviceHandler.h>

extern void GameMain();

int main(int argc, char** argv)
{
	SDL_SetMainReady();
	ServiceHandler::Instance().Init();
	// todo: Call Start() for every added SubSystem
	GameMain();
	ServiceHandler::Instance().Cleanup();
	SDL_Quit();
	return 0;
}
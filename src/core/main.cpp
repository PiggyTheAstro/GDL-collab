#include <exception>
#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <core/serviceHandler.h>

extern void GameMain();

int main(int argc, char** argv)
{
	SDL_SetMainReady();
	SDL_Init(SDL_INIT_VIDEO);
	ServiceHandler::Instance().Init();
	// todo: Call Start() for every added SubSystem
	try
	{
		GameMain();
	}
	catch (const std::exception& err)
	{
		std::cout << "Error occured:\n" << std::endl;
		std::cout << err.what();
	}
	ServiceHandler::Instance().Cleanup();
	SDL_Quit();
	return 0;
}
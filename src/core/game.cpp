#include <core/game.h>
#include <core/serviceHandler.h>
#include <components/rectRenderer.h>

Game::Game()
{
	window = SDL_CreateWindow("Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 550, 750, SDL_WINDOW_MAXIMIZED);
	ServiceHandler::instance().AddModule<Clock>();
	ServiceHandler::instance().AddModule<InputHandler>();
	ServiceHandler::instance().AddModule<CollisionSystem>();
	ServiceHandler::instance().AddModule<EntitySystem>();
	ServiceHandler::instance().AddModule<Camera>();
	ServiceHandler::instance().AddModule<RenderSystem>();
	ServiceHandler::instance().AddModule<AssetManager>();
}

void Game::Update()
{
	for (SubSystem* sys : ServiceHandler::instance().systems)
	{
		sys->Update();
	}
}

void Game::Cleanup()
{
	for (SubSystem* sys : ServiceHandler::instance().systems)
	{
		delete sys;
	}
}
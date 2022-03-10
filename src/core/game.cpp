#include <core/game.h>
#include <components/rectRenderer.h>

Game::Game()
{
	window = SDL_CreateWindow("Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 550, 750, SDL_WINDOW_MAXIMIZED);
	serviceManager = new ServiceHandler();
	systems.push_back(serviceManager->AddModule<Clock>());
	systems.push_back(serviceManager->AddModule<InputHandler>());
	systems.push_back(serviceManager->AddModule<CollisionSystem>());
	systems.push_back(serviceManager->AddModule<EntitySystem>());
	systems.push_back(serviceManager->AddModule<Camera>());
	systems.push_back(serviceManager->AddModule<RenderSystem>());
	systems.push_back(serviceManager->AddModule<AssetManager>());
}

void Game::Update()
{
	for (SubSystem* sys : systems)
	{
		sys->Update();
	}
}

void Game::Cleanup()
{
	for (SubSystem* sys : systems)
	{
		delete sys;
	}
}
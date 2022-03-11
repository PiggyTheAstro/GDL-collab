#include <core/game.h>
#include <core/serviceHandler.h>
#include <components/rectRenderer.h>

Game::Game()
{
	ServiceHandler::instance().AddModule<Window>("test");
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
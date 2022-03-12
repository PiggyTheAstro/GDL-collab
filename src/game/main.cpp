#include <core/serviceHandler.h>
#include <systems/window.h>
#include <systems/clock.h>
#include <systems/inputHandler.h>
#include <systems/collisionSystem.h>
#include <systems/camera.h>
#include <systems/renderSystem.h>
#include <systems/assetManager.h>
#include <systems/entitySystem.h>
#include <components/spriteRenderer.h>
#include <components/rectCollider.h>

void ServiceHandler::Init()
{
  ServiceHandler::Instance().AddModule<Window>("test");
  ServiceHandler::Instance().AddModule<Clock>();
  ServiceHandler::Instance().AddModule<InputHandler>();
  ServiceHandler::Instance().AddModule<CollisionSystem>();
  ServiceHandler::Instance().AddModule<Camera>();
  ServiceHandler::Instance().AddModule<RenderSystem>();
  ServiceHandler::Instance().AddModule<AssetManager>();
  ServiceHandler::Instance().AddModule<EntitySystem>();
}

void GameMain()
{
  EntitySystem& entitySystem = ServiceHandler::Instance().GetModule<EntitySystem>();

  Entity& player = entitySystem.CreateEntity();
  player.transform.position = Vectors::Vector2(100.0f, 100.0f);
  player.transform.scale = Vectors::Vector2(100.0f, 100.0f);
  player.AddComponent<SpriteRenderer>().SetSprite("test.bmp");

  while (ServiceHandler::Instance().isRunning)
  {
    ServiceHandler::Instance().Update();
  }
}
#include <core/game.h>
#include <components/rectRenderer.h>
#include <systems/assetManager.h>
#include <components/spriteRenderer.h>
#include <components/rectCollider.h>

using namespace Vectors;

void GameMain(Game& game)
{
  EntitySystem* entitySystem = ServiceHandler::instance().GetModule<EntitySystem>();
  Entity& player = entitySystem->CreateEntity();
  player.transform.position = Vector2(100.0f, 100.0f);
  player.transform.scale = Vector2(100.0f, 100.0f);
  player.AddComponent<RectRenderer>();
  while (ServiceHandler::instance().isRunning)
  {
    game.Update();
  }
}
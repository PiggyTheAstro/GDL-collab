#include <iostream>
#include <cassert>
#include <components/spriteRenderer.h>
#include <core/serviceHandler.h>
#include <systems/assetManager.h>

void SpriteRenderer::Start(Transform* parent)
{
	transform = parent;
	renderModule = &ServiceHandler::Instance().GetModule<RenderSystem>();
	assetModule = &ServiceHandler::Instance().GetModule<AssetManager>();
	sprite = new Sprite(); // todo: Does it have to be dynamically allocated?
	sprite->rect = SDL_FRect();
	sprite->rotation = transform->rotation;
	renderModule->AddRenderable(sprite);
}

void SpriteRenderer::SetSprite(std::string path)
{
	assert(sprite);

	auto defer_dereference = sprite->texture;

	sprite->texture = assetModule->LoadTexture(path);

	if (defer_dereference)
		assetModule->Dereference(defer_dereference);
}

void SpriteRenderer::Update()
{
	sprite->rotation = transform->rotation;
	sprite->rect.x = transform->position.x;
	sprite->rect.y = transform->position.y;
	sprite->rect.w = transform->scale.x;
	sprite->rect.h = transform->scale.y;
}

SpriteRenderer::~SpriteRenderer()
{
	assetModule->Dereference(sprite->texture);
	renderModule->RemoveRenderable(sprite);
	delete sprite;
}
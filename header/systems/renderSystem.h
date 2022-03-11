#pragma once
#include <SDL.h>
#include <core/subsystem.h>
#include <core/sprite.h>
#include <systems/camera.h>

class RenderSystem : public SubSystem // TODO: Add sprite rendering support
{
public:
	RenderSystem();
	void Render();
	void Update() override;
	void AddRenderable(SDL_FRect* rect);
	void AddRenderable(Sprite* sprite);
	void RemoveRenderable(Sprite* sprite);
private:
	void RenderRects();
	void RenderSprites();
	Camera* cam;
	SDL_Renderer* renderer;
	std::vector<SDL_FRect*> rects;
	std::vector<Sprite*> sprites;
};
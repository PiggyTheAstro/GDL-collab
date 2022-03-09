#pragma once
#include <SDL.h>

class Sprite
{
public:
	SDL_FRect rect;
	SDL_Texture* texture;
	float rotation;
};
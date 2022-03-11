#pragma once
#include <SDL.h>
#include <core/subsystem.h>
#include <Math/vectors.h>

class Camera : public SubSystem
{
public:
	Camera();
	Vectors::Vector2 offset;
	void MoveTo(Vectors::Vector2 pos);
	
private:
	SDL_DisplayMode screenRes;
};
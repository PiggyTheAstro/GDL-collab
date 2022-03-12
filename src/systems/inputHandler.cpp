#include <SDL.h>
#include <cassert>
#include <algorithm>
#include <core/serviceHandler.h>
#include <systems/inputHandler.h>
#include <systems/window.h>

void InputHandler::CheckEvent()
{
	assert(ServiceHandler::Instance().HasModule<Window>());

	SDL_Event eventData = SDL_Event();
	while (SDL_PollEvent(&eventData))
	{
		switch (eventData.type)
		{
		case SDL_QUIT:
			ServiceHandler::Instance().isRunning = false;
			break;

		case SDL_KEYDOWN:
			PushEvent(eventData.key.keysym.sym);
			break;

		case SDL_KEYUP:
			PopEvent(eventData.key.keysym.sym);
			break;
		}
	}
}

void InputHandler::Update()
{
	CheckEvent();
}

void InputHandler::PushEvent(int eventValue)
{
	keys.insert(eventValue);
}

void InputHandler::PopEvent(int eventValue)
{
	keys.erase(eventValue);
}

bool InputHandler::GetKey(int key)
{
	return std::find(keys.cbegin(), keys.cend(), key) != keys.cend();
}
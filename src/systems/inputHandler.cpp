#include <systems/inputHandler.h>
#include <SDL.h>
#include <core/serviceHandler.h>

void InputHandler::CheckEvent()
{
	SDL_Event eventData = SDL_Event();
	while (SDL_PollEvent(&eventData))
	{
		switch (eventData.type)
		{
		case SDL_QUIT:
			ServiceHandler::instance->isRunning = false;
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

void InputHandler::PushEvent(int eventValue)
{
	for (int i = 0; i < keys.size(); i++)
	{
		if (keys[i] == eventValue)
		{
			return;
		}
	}
	keys.push_back(eventValue);
}

void InputHandler::PopEvent(int eventValue)
{
	for (int i = 0; i < keys.size(); i++)
	{
		if (keys[i] == eventValue)
		{
			keys.erase(keys.begin() + i);
			return;
		}
	}
}

bool InputHandler::GetKey(int key)
{
	for (int i = 0; i < keys.size(); i++)
	{
		if (keys[i] == key)
		{
			return true;
		}
	}
	return false;
}
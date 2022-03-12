#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <string>
#include <core/serviceHandler.h>
#include <systems/assetManager.h>
#include <systems/window.h>

// todo: It only covers BPM textures, better reflect it in the naming
// 			 Also transparency color mask is (0, 0, 0) without ability to set, maybe better give optional color mask argument
SDL_Texture* AssetManager::LoadTexture(std::string path)
{
	// todo: Might be preferable to resolve window once on Start()
	SDL_Window* window = ServiceHandler::Instance().GetModule<Window>().window;

	auto renderable = std::find_if(tempTextures.cbegin(), tempTextures.cend(),
		[path] (Renderable* r) {
			return r->path == path;
		}
	);

	if (renderable != tempTextures.cend())
	{
		(*renderable)->refCount += 1;
		return (*renderable)->texture;
	}

	SDL_Surface* img;
	if (!(img = SDL_LoadBMP(path.c_str())))
		throw std::runtime_error(SDL_GetError());

	int colorKey = SDL_MapRGB(img->format, 0, 0, 0);
	if (SDL_SetColorKey(img, SDL_TRUE, colorKey))
		throw std::runtime_error(SDL_GetError());

	SDL_Renderer* renderer;
	if (!(renderer = SDL_GetRenderer(window)))
		throw std::runtime_error(SDL_GetError());

	SDL_Texture* tex;
	if (!(tex = SDL_CreateTextureFromSurface(renderer, img)))
		throw std::runtime_error(SDL_GetError());

	SDL_FreeSurface(img);
	tempTextures.push_back(new Renderable(tex, path));
	return tex;
}

void AssetManager::Dereference(SDL_Texture* texture)
{
	assert(texture);

	auto result = std::find_if(tempTextures.cbegin(), tempTextures.cend(),
		[texture] (Renderable* r) {
			return r->texture == texture;
		}
	);

	if (result != tempTextures.cend())
	{
		(*result)->refCount -= 1;
		assert((*result)->refCount >= 0);
		if ((*result)->refCount == 0)
		{
			SDL_DestroyTexture((*result)->texture);
			delete *result;
			tempTextures.erase(result);
		}
	}
	else
	{
		throw std::runtime_error("Invalid texture to dereference");
	}
}
#include <core/serviceHandler.h>
#include <systems/assetManager.h>
#include <systems/window.h>

SDL_Texture* AssetManager::LoadTexture(std::string path)
{
	// todo: Might be preferable to resolve window once on Start()
	SDL_Window* window = ServiceHandler::Instance().GetModule<Window>()->window;

	for (Renderable* renderable : tempTextures)
	{
		if (renderable->path == path)
		{
			renderable->refCount += 1;
			return renderable->texture;
		}
	}
	SDL_Surface* img = SDL_LoadBMP(path.c_str());
	int colorKey = SDL_MapRGB(img->format, 0, 0, 0);
	SDL_SetColorKey(img, SDL_TRUE, colorKey);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(SDL_GetRenderer(window), img);
	SDL_FreeSurface(img);
	tempTextures.push_back(new Renderable(tex, path));
	return tex;
}

void AssetManager::Dereference(SDL_Texture* texture)
{
	for (int i = 0; i < tempTextures.size(); i++)
	{
		if (texture == tempTextures[i]->texture)
		{
			tempTextures[i]->refCount -= 1;
			if (tempTextures[i]->refCount <= 0)
			{
				SDL_DestroyTexture(tempTextures[i]->texture);
				delete tempTextures[i];
				tempTextures.erase(tempTextures.begin() + i);
			}
		}
	}
}

#include "ResourceManager.h"

ResourceManager::ResourceManager(Game* game)
{
	this->game = game;
}

void ResourceManager::loadTexture(std::string filename)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(game->getRenderer(), filename.c_str());

	if(texture == NULL)
		throw std::runtime_error("Error while loading texture: " + filename);

	/*Imagine std::pair is a single row in the table i mentioned
	earlier.*/
	textures.insert(std::pair<std::string, SDL_Texture*>(filename, texture));
}

SDL_Texture* ResourceManager::getTexture(std::string filename)
{
	SDL_Texture* texture = NULL;
	std::map<std::string, SDL_Texture*>::iterator i;

	/* attempts to search the hash map for the key specified.
	If it fails, returns an iterator to std::map::end.*/
	i = textures.find(filename);

	/* this assigns the value of pair to texture */
	texture = i->second;

	return texture;
}

ResourceManager::~ResourceManager()
{
	std::map<std::string, SDL_Texture*>::iterator i;
	for(i = textures.begin(); i != textures.end(); i++)
	{
		SDL_DestroyTexture(i->second);
	}
	textures.clear();
}

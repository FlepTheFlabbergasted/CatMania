
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <map>
#include <iterator>
#include <string>

#include "Game.h" // TODO: I ADDED THIS DUNNO MAN

//class Game;	// TODO: AT THE SAME TIME I TOOK AWAY THIS

/* Every state should have a ResourceManager,
and every state should take care of it's own
data. That includes freeing the data when it's
no longer needed.*/
class ResourceManager
{
private:
	std::map<std::string, SDL_Texture*> textures;
	Game* game;
public:
	/*We won't be supplying the class with default constructor because
	we want to force the programmer to pass the pointer to instance of Game
	to the ResourceManager.*/
	ResourceManager(Game* game);

	//Deleting the instance will wipe all the textures allocated by that instance from memory
	~ResourceManager();

	void loadTexture(std::string filename);

	//Returns NULL if can't find the texture with the designated filename
	SDL_Texture* getTexture(std::string filename);
};

#endif

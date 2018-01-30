
#ifndef LEVEL_BACKGROUND_H_
#define LEVEL_BACKGROUND_H_

#include "../GameEngine/Game.h"
#include "../GameEngine/ResourceManager.h"

class Background
{
private:
	SDL_Texture* textures[8];
	SDL_Rect r;

	Game* game;
	ResourceManager* rm;
public:
	void Init(Game* game, ResourceManager* rm);
	void Render();
};

#endif /* LEVEL_BACKGROUND_H_ */

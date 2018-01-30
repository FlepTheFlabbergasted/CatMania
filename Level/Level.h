
#ifndef LEVEL_H_
#define LEVEL_H_

#include <stdlib.h>
#include <cstring>

#include "../GameEngine/Game.h"
#include "../GameEngine/ResourceManager.h"

class Level
{
private:
	SDL_Texture* tile_sprite;
	SDL_Rect tile_source_rect;
	SDL_Rect tile_dest_rect;

	int* grid;

	int tile_width;
	int tile_height;

	int gridRows, gridColumns;

	Game* game;
	ResourceManager* rm;
public:
	Level(Game* game, ResourceManager* rm);
	void Init();
	bool CollideWithTerrain(float player_x, float player_y, int player_w, int player_h);
	void Render();
};

#endif /* LEVEL_H_ */

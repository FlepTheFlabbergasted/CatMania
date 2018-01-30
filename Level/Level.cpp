
#include "Level.h"

Level::Level(Game* game, ResourceManager* rm)
{
	this->game = game;
	this->rm = rm;

	tile_width = 70;
	tile_height = 35;
	tile_sprite = rm->getTexture("graphics\\tile0.png");

	gridRows = (SCREEN_HEIGHT/tile_height);
	gridColumns = (SCREEN_WIDTH/tile_width) + 1;

	grid = (int*)calloc(gridRows * gridColumns, sizeof(int));

	std::cout << "gridRows: " << gridRows << " gridColumns: " << gridColumns << std::endl;
}

void Level::Init()
{
	tile_source_rect.x = 0;
	tile_source_rect.y = 0;
	tile_source_rect.w = tile_width;
	tile_source_rect.h = tile_height;

	tile_dest_rect.x = 0;
	tile_dest_rect.y = 0;
	tile_dest_rect.w = tile_width;
	tile_dest_rect.h = tile_height;

	for(int x = 0; x < gridColumns; x++)
	{
		grid[(gridRows-1)*(gridColumns)+x] = 1;
	}

	for(int x = 0; x < 4; x++)
	{
		grid[(gridRows-4)*(gridColumns)+x] = 1;
		grid[(gridRows-3)*(gridColumns)-(x+1)] = 1;
		grid[(gridRows-9)*(gridColumns)+x] = 1;
		grid[(gridRows-8)*(gridColumns)-(x+1)] = 1;
	}

	for(int x = 0; x < 5; x++)
	{
		grid[(gridRows-6)*(gridColumns)+(x-2+gridColumns/2)] = 1;
	}

	grid[(gridRows-10)*(gridColumns)+(gridColumns/2)] = 1;


}

bool Level::CollideWithTerrain(float player_x, float player_y, int player_w, int player_h)
{
	// Find out what row player is on
	int row = player_y / tile_height;
	int row2 = (player_y + player_h) / tile_height;

	// Find out what column player is on
	int column = player_x / tile_width;
	int column2 = (player_x + player_w) / tile_width;

	// Check if that/those grids have terrain in them
	if(grid[row*(gridColumns)+column] == 1)
		return true;
	if(grid[row2*(gridColumns)+column2] == 1)
		return true;

	return false;
}

void Level::Render()
{
	for(int y = 0; y < gridRows; y++)
		for(int x = 0; x <gridColumns; x++)
		{
			tile_dest_rect.x = x*tile_width;
			tile_dest_rect.y = y*tile_height;
			if(grid[(y*(gridColumns))+x] != 0)
				SDL_RenderCopy(game->getRenderer(), tile_sprite, &tile_source_rect, &tile_dest_rect);
		}
}



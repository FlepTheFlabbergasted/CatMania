#include "Background.h"

void Background::Init(Game* game, ResourceManager* rm)
{
	this->game = game;
	this->rm = rm;

	r.x = 0;
	r.y = 0;
	r.w = SCREEN_WIDTH;
	r.h = SCREEN_HEIGHT;

	textures[0] = rm->getTexture("graphics\\background0.png");
	textures[1] = rm->getTexture("graphics\\background1.png");
	textures[2] = rm->getTexture("graphics\\background2.png");
}


void Background::Render()
{
	SDL_RenderCopy(game->getRenderer(), textures[0], NULL, &r);
}

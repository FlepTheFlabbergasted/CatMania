
#include "Font.h"

Font::Font(Game* game, SDL_Texture* sheet, int num_charsX, int num_charsY, int char_width, int char_height)
{
	this->game = game;
	this->sheet = sheet;
	this->num_charsX = num_charsX;
	this->num_charsY = num_charsY;
	this->char_width = char_width;
	this->char_height = char_height;
}

void Font::RenderChar(float x, float y, int size, unsigned char data)
{
	SDL_Rect src_rect, dst_rect;

	src_rect.x = (data % num_charsX) * char_width;
	src_rect.y = (data / num_charsX) * char_height;
	src_rect.w = char_width;
	src_rect.h = char_height;

	dst_rect.x = x;
	dst_rect.y = y;
	dst_rect.w = char_width * size;
	dst_rect.h = char_height * size;

	SDL_RenderCopy(game->getRenderer(), sheet, &src_rect, &dst_rect);
}

void Font::RenderString(float x, float y, int size, std::string data)
{
	for(int i=0; i<(int)data.length(); i++)	// TODO: ADDED '(INT)'
	{
		RenderChar(x + i*char_width*size, y, size, data.at(i));
	}
}

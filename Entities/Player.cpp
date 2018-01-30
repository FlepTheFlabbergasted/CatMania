
#include "Player.h"

void Player::Init(Game* game, ResourceManager* rm, int playerNr)
{
	this->game = game;
	this->rm = rm;

	/* Sprite size */
	sizeX = 46;
	sizeY = 35;

	/* Initial positions */
	x = (280*playerNr) + sizeX;
	y = 350 - sizeY;

	/* Stand still from the start */
	velocityY = 0.0f;
	velocityX = 0.0f;
	dirX = 0.0f;
	dirY = 0.0f;

	/* We want Player to move x pixels per second. */
	move_speed = 48.0f;

	sheet_row = 1.0f;
	sheet_column = 0.0f;
	sheet_animSpeed = 12.0f;

	/* Physics for movement */
	gravity = 0.6f;
	friction = 0.9f;

	/* Start in air */
	onGround = false;

	try
	{
		if(playerNr == 0)
			sprite = rm->getTexture("graphics\\cat_sprite0.png");
		else if(playerNr == 1)
			sprite = rm->getTexture("graphics\\cat_sprite1.png");
		else if(playerNr == 2)
			sprite = rm->getTexture("graphics\\cat_sprite2.png");
		else if(playerNr == 3)
			sprite = rm->getTexture("graphics\\cat_sprite3.png");
	}
	catch(std::runtime_error &e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void Player::Update(float deltaTime)
{
	/* If Player's not standing still, we increment the walk cycle. */
	if(velocityX != 0)
	{
		sheet_column += sheet_animSpeed*deltaTime;
		if((int)sheet_column >= 3)
			sheet_column = 0.0f;
	}
	else
		sheet_column = 0.0f;

	/* This is where we determine the sheet row,
	based on the direction player is facing. Note that
	up and down are preferred to left and right. */
	if(dirX > 0)	// Right
		sheet_row = 1;
	if(dirX < 0)	// Left
		sheet_row = 0;

	/* Update the players horizontal velocity */
	velocityX *= friction;
	/* If the velocity is too small, set it to zero */
	if(velocityX < 0.2 && velocityX > -0.2)
		velocityX = 0;
	/* Update x position */
	x += velocityX * move_speed * deltaTime;

	/* If player is not on the ground, update vertical velocity and y position */
	if(!onGround)
	{
		velocityY += gravity;
		y += velocityY * move_speed * deltaTime;
	}

	/* Keep player within screen borders */
	if(x > SCREEN_WIDTH - sizeX)
		x = SCREEN_WIDTH - sizeX;
	if(x < 0)
		x = 0;

	/* Src rectangle on the sprite sheet */
	source_rect.x = sizeX * (int)sheet_column;
	source_rect.y = sizeY * (int)sheet_row;
	source_rect.w = sizeX;
	source_rect.h = sizeY;

	/* Where to render the player */
	dest_rect.x = x;
	dest_rect.y = y;
	dest_rect.w = sizeX;
	dest_rect.h = sizeY;

	/* Reset moving direction after every frame */
	dirX = 0;
}

void Player::StartJump()
{
	/* If the player is standing on the ground, allow jumping */
	if(onGround)
	{
		onGround = false;
		velocityY = -12.0f;
	}
}

void Player::EndJump()
{
	/* Set the vertical velocity to half the initial value for a controlled jump */
	if(velocityY < -6.0)
		velocityY = -6.0;
}

void Player::StopFall()
{
	onGround = true;
	velocityY = 0.0f;
}

void Player::StartFall()
{
	onGround = false;
}

bool Player::OnGround()
{
	return onGround;
}

void Player::Render()
{
	SDL_RenderCopy(game->getRenderer(), sprite, &source_rect, &dest_rect);
}

void Player::Move(float dx)
{
	/* Increase the horizontal velocity and update direction */
	velocityX += dx;
	dirX = dx;
}

bool Player::collidesWith(Player* other)
{
	/*Instead of checking if two objects intersect,
	a mathematical approach is easier - to check if they
	DON'T intersect :D */

	if(other->x + other->sizeX < x)	return false;
	if(other->x > x+sizeX)	return false;

	if(other->y + other->sizeY < y)	return false;
	if(other->y > y + sizeY)	return false;

	return true;
}

float Player::GetX(){return x;}

float Player::GetY(){return y;}

float Player::GetWidth(){return sizeX;}

float Player::GetHeight(){return sizeY;}

float Player::GetNextYPos(float deltaTime)
{
	return (velocityY+gravity) * move_speed * deltaTime;
}

float Player::GetNextXPos(float deltaTime)
{
	return (velocityX*friction) * move_speed * deltaTime;
}

void Player::SetNextY(int nextY){
	y += nextY;
}

void Player::SetNextX(int nextX){
	x += nextX;
}

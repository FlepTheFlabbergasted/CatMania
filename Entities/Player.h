
#ifndef ENTITIES_PLAYER_H_
#define ENTITIES_PLAYER_H_

#include "../GameEngine/ResourceManager.h"
#include "../Utilities/Random.h"

class Player
{
private:
	Game* game;
	ResourceManager* rm;

	/* For sprite sheet */
	SDL_Rect source_rect;
	SDL_Rect dest_rect;

	/* A pointer to our sheet texture, which we will be
	getting from resource manager. */
	SDL_Texture* sprite;

	/* The variables I was talking about earlier. */
	float sheet_row;
	float sheet_column;
	/* This is just a value that increments sheet_row
	each frame of the walk cycle. */
	float sheet_animSpeed;

	/* Position in the world */
	float x, y;
	/* Size in pixels */
	float sizeX, sizeY;
	/* Move speed in pixels */
	float move_speed;

	/* We want our character to move in 8 directions, so we need
	these to keep track of which direction that character is facing. */
	float dirX, dirY;

	/* The players horizontal and vertical velocity */
	float velocityX, velocityY;
	/* Constants for moving and jumping */
	float gravity, friction;
	/* Tells if the player is on the ground or not */
	bool onGround;

public:
	void Init(Game* game, ResourceManager* rm, int playerNr);
	void Update(float deltaTime);
	void Render();

	bool collidesWith(Player* other);
	float GetX(), GetY(), GetWidth(), GetHeight();

	float GetNextYPos(float deltaTime);
	float GetNextXPos(float deltaTime);
	void SetNextY(int nextY);
	void SetNextX(int nextX);

	void Move(float dx);

	void StartJump();
	void EndJump();
	bool OnFloor();
	void StartFall();
	void StopFall();
	bool OnGround();
};

#endif

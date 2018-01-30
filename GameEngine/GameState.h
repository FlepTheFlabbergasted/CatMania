
#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <SDL2/SDL.h>

#include "Game.h"

class GameState
{
protected:
	Game* game;
public:
	virtual bool Init(Game* game) = 0;
	virtual void HandleEvents(SDL_Event* event) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Quit() = 0;
};

#endif /* GAMESTATE_H_ */

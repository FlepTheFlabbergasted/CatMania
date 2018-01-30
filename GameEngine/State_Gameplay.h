
#ifndef STATE_GAMEPLAY_H_
#define STATE_GAMEPLAY_H_

#include <string>
#include <stdio.h>

#include "../Entities/Player.h"
#include "GameState.h"
#include "ResourceManager.h"

#include "../Level/Level.h"
#include "../Miscellaneous/Font.h"
#include "../Miscellaneous/audio.h" // https://github.com/jakebesworth/Simple-SDL2-Audio - AWESOME
#include "../Level/Background.h"
#include "../Utilities/Timer.h"
#include "../Utilities/Random.h"

class State_Gameplay : public GameState
{
private:
	ResourceManager* rm;

	Player player[4];
	Timer playerTimer[4];
	Timer gameTimer;
	int gameTime;
	Timer timeout;
	int chaser;
	Random randomNr;
	Level* level;
	Background background;
	Font* font;
	char randomMeow[50];
	int nrPlayers;
public:
	State_Gameplay(int players);
	bool Init(Game* game);
	void HandleEvents(SDL_Event* event);
	void Update(float deltaTime);
	void Render();
	void Quit();

	void KeyboardInput();
	void PlayerCollision();
	void EndGame();
};

#endif


#ifndef STATE_MENU_H_
#define STATE_MENU_H_

#include "State_Gameplay.h"
#include "GameState.h"
#include "ResourceManager.h"
#include "../Miscellaneous/Font.h"

class State_Menu : public GameState
{
private:
	ResourceManager* rm;

	Font* font;

	/*This will be used to determine whether
	the blinking text is visible or not at
	certain moment */
	float blinking;

	int nrPlayers;
	int mouseX, mouseY;
	SDL_Texture* menu[4];
public:
	bool Init(Game* game);
	void HandleEvents(SDL_Event* event);
	void Update(float deltaTime);
	void Render();
	void Quit();
};

#endif /* STATE_MENU_H_ */

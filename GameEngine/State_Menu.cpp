
#include "State_Menu.h"

bool State_Menu::Init(Game* game)
{
	this->game = game;

	rm = new ResourceManager(game);

	try
	{
		rm->loadTexture("graphics\\font_texture.png");
		rm->loadTexture("graphics\\catmania_menu.png");
		rm->loadTexture("graphics\\catmania_menu_2p.png");
		rm->loadTexture("graphics\\catmania_menu_3p.png");
		rm->loadTexture("graphics\\catmania_menu_4p.png");
	}
	catch(std::runtime_error &e)
	{
		std::cerr << e.what() << std::endl;
		return false;
	}

	font = new Font(game, rm->getTexture("graphics\\font_texture.png"), 16, 16, 8, 16);
	menu[0] = rm->getTexture("graphics\\catmania_menu.png");
	menu[1] = rm->getTexture("graphics\\catmania_menu_2p.png");
	menu[2] = rm->getTexture("graphics\\catmania_menu_3p.png");
	menu[3] = rm->getTexture("graphics\\catmania_menu_4p.png");

	blinking = 0.0f;
	nrPlayers = 2;

	return true;
}

void State_Menu::HandleEvents(SDL_Event* event)
{
	if(event->type == SDL_QUIT)
		game->PopState();
}

void State_Menu::Update(float deltaTime)
{
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);

	if(keyboard[SDL_SCANCODE_SPACE] && nrPlayers > 0)
	{
		game->PushState(new State_Gameplay(nrPlayers));
	}

	if(SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		if(mouseY > SCREEN_HEIGHT-(SCREEN_HEIGHT/4)){
			if(mouseX >= 0 && mouseX <= 333)
				nrPlayers = 2;
			else if(mouseX >= 334 && mouseX <= 666)
				nrPlayers = 3;
			else if(mouseX >= 667 && mouseX <= 1000)
				nrPlayers = 4;
		}
	}

	blinking += 2 * deltaTime;
	if(blinking >= 2.0f)
		blinking = 0.0f;
}

void State_Menu::Render()
{
	SDL_RenderCopy(game->getRenderer(), menu[nrPlayers-1], NULL, NULL);

	std::string text = "PRESS SPACEBAR TO START";
	float x = text.length() * 8 / 2;

	if((int)blinking > 0)
		font->RenderString(SCREEN_WIDTH/2 - x, 400, 1, text);

	/*text = "C A T  M A N I A";
	x = text.length() * 8 / 2;

	font->RenderString(SCREEN_WIDTH/2 - x, 250, 2, text);*/
}

void State_Menu::Quit()
{
	delete font;
	delete rm;
}

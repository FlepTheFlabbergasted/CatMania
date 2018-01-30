
#include "State_Gameplay.h"

State_Gameplay::State_Gameplay(int players){
	nrPlayers = players;
	chaser = randomNr.Int(0, nrPlayers - 1);
	gameTime = 90;
}

bool State_Gameplay::Init(Game* game)
{
	this->game = game;
	rm = new ResourceManager(game);

	try
	{
		rm->loadTexture("graphics\\cat_sprite0.png");		// Player1
		rm->loadTexture("graphics\\cat_sprite1.png");		// Player2
		rm->loadTexture("graphics\\cat_sprite2.png");		// Player3
		rm->loadTexture("graphics\\cat_sprite3.png");		// Player4
		rm->loadTexture("graphics\\background0.png");		// Background
		rm->loadTexture("graphics\\tile0.png");				// Tile0
		rm->loadTexture("graphics\\font_texture.png");		// Font
	}
	catch(std::runtime_error &e)
	{
		std::cerr << e.what() << std::endl;
		return false;
	}

	/* Initiate everything */
	initAudio();

	background.Init(game, rm);

	level = new Level(game, rm);
	level->Init();

	font = new Font(game, rm->getTexture("graphics\\font_texture.png"), 16, 16, 8, 16);

	for(int i = 0; i < nrPlayers; i++)
	{
		player[i].Init(game, rm, i);
		playerTimer[i].Start();
	}
	playerTimer[chaser].Pause();
	gameTimer.Start();
	timeout.Start();

	playMusic("music//BakerCat.wav", SDL_MIX_MAXVOLUME/2);

	return true;
}

void State_Gameplay::HandleEvents(SDL_Event* event)
{
	/* If the X in the program window is pressed exit the game */
	if(event->type == SDL_QUIT)
		game->PopState();
}

void State_Gameplay::Update(float deltaTime)
{
	/* Check for collision between all players and terrain */
	for(int i = 0; i < nrPlayers; i++)
	{
		if(level->CollideWithTerrain(player[i].GetX(), player[i].GetY(), player[i].GetWidth(), player[i].GetHeight()) && !player[i].OnGround())
			player[i].StopFall();
		else if(!level->CollideWithTerrain(player[i].GetX(), player[i].GetY(), player[i].GetWidth(), player[i].GetHeight()))
			player[i].StartFall();
	}

	/* Handle player collision */
	PlayerCollision();

	/* Handle all the keyboard inputs from players */
	KeyboardInput();

	/* Update all the players positions and states */
	for(int i = 0; i < nrPlayers; i++)
	{
		player[i].Update(deltaTime);
	}
}

void State_Gameplay::KeyboardInput()
{
	/* Get key */
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);

	/* Player 1 */
	if(keyboard[SDL_SCANCODE_D])
		player[0].Move(0.8f);
	if(keyboard[SDL_SCANCODE_A])
		player[0].Move(-0.8f);
	if(keyboard[SDL_SCANCODE_W])
		player[0].StartJump();
	else
		player[0].EndJump();

	/* Player 2 */
	if(keyboard[SDL_SCANCODE_L])
		player[1].Move(0.8f);
	if(keyboard[SDL_SCANCODE_J])
		player[1].Move(-0.8f);
	if(keyboard[SDL_SCANCODE_I])
		player[1].StartJump();
	else
		player[1].EndJump();

	/* Player 3 */
	if(keyboard[SDL_SCANCODE_RIGHT])
		player[2].Move(0.8f);
	if(keyboard[SDL_SCANCODE_LEFT])
		player[2].Move(-0.8f);
	if(keyboard[SDL_SCANCODE_UP])
		player[2].StartJump();
	else
		player[2].EndJump();

	/* Player 4 */
	if(keyboard[SDL_SCANCODE_KP_6])
		player[3].Move(0.8f);
	if(keyboard[SDL_SCANCODE_KP_4])
		player[3].Move(-0.8f);
	if(keyboard[SDL_SCANCODE_KP_8])
		player[3].StartJump();
	else
		player[3].EndJump();
}

void State_Gameplay::PlayerCollision()
{
	int tagged = -1;
	if(timeout.GetTicks() >= 500)
		switch(chaser)
		{
		case 0:
			if(player[0].collidesWith(&player[1]))
			{
				std::cout << "Collision 0 -> 1" << std::endl;
				tagged = 1;
			}
			else if(player[0].collidesWith(&player[2]))
			{
				std::cout << "Collision 0 -> 2" << std::endl;
				tagged = 2;
			}
			else if(player[0].collidesWith(&player[3]))
			{
				std::cout << "Collision 0 -> 3" << std::endl;
				tagged = 3;
			}
			break;
		case 1:
			if(player[1].collidesWith(&player[0]))
			{
				std::cout << "Collision 1 -> 0" << std::endl;
				tagged = 0;
			}
			else if(player[1].collidesWith(&player[2]))
			{
				std::cout << "Collision 1 -> 2" << std::endl;
				tagged = 2;
			}
			else if(player[1].collidesWith(&player[3]))
			{
				std::cout << "Collision 1 -> 3" << std::endl;
				tagged = 3;
			}
			break;
		case 2:
			if(player[2].collidesWith(&player[0]))
			{
				std::cout << "Collision 2 -> 0" << std::endl;
				tagged = 0;
			}
			else if(player[2].collidesWith(&player[1]))
			{
				std::cout << "Collision 2 -> 1" << std::endl;
				tagged = 1;
			}
			else if(player[2].collidesWith(&player[3]))
			{
				std::cout << "Collision 2 -> 3" << std::endl;
				tagged = 3;
			}
			break;
		case 3:
			if(player[3].collidesWith(&player[0]))
			{
				std::cout << "Collision 3 -> 0" << std::endl;
				tagged = 0;
			}
			else if(player[3].collidesWith(&player[1]))
			{
				std::cout << "Collision 3 -> 1" << std::endl;
				tagged = 1;
			}
			else if(player[3].collidesWith(&player[2]))
			{
				std::cout << "Collision 3 -> 2" << std::endl;
				tagged = 2;
			}
			break;
		default:
			break;
		}

	if(tagged != -1)
	{
		playerTimer[chaser].Unpause();
		playerTimer[tagged].Pause();
		chaser = tagged;
		timeout.Start();
		tagged = -1;
		sprintf(randomMeow, "sounds//meow%d.wav", randomNr.Int(0, 10));
		playSound(randomMeow, SDL_MIX_MAXVOLUME / 2);
	}

	//playMusic("music/highlands.wav", SDL_MIX_MAXVOLUME);
	//playSound("sounds//PEWPEW.wav", SDL_MIX_MAXVOLUME / 2);

	/*if(player[chaser].collidesWith(&player[1]) || player[chaser].collidesWith(&player[1]))
		{
			std::cout << "Collision" << std::endl;
			if(!playerTimer[0].IsStarted())
				playerTimer[0].Start();
		}*/
}

void State_Gameplay::EndGame()
{
	gameTimer.Pause();
	uint32_t max = 0;
	uint32_t winnerTime[nrPlayers];
	int winner = -3;

	for(int i = 0; i < nrPlayers; i++)
	{
		winnerTime[i] = playerTimer[i].GetTicks();
		playerTimer[i].Pause();

		if(winnerTime[i] >= max)
		{
			max = winnerTime[i];
			winner = i;
		}
	}

	char buffer[64];
	font->RenderString((SCREEN_WIDTH/2) - 6*8, (SCREEN_HEIGHT/2) + 50, 2, "PLAYER " + std::string(itoa(winner+1, buffer, 10)) + " WINS");
}

void State_Gameplay::Render()
{
	background.Render();

	level->Render();

	for(int i = 0; i < nrPlayers; i++)
	{
		if(chaser == i)
			font->RenderString(player[i].GetX() + 16, player[i].GetY() - 16, 1, "IT");
		player[i].Render();
	}

	char buffer[64];
	font->RenderString(SCREEN_WIDTH/2 - 8, 25, 2, std::string(itoa((gameTime-(gameTimer.GetTicks()/1000)), buffer, 10)));

	for(int i = 0; i < nrPlayers; i++)
	{
		font->RenderString((i*300)+20, 0, 1, "P" + std::string(itoa(i+1, buffer, 10)) + " " + std::string(itoa((playerTimer[i].GetTicks()/10), buffer, 10)));
	}

	if(gameTimer.GetTicks() >= 90000)
		EndGame();
}

void State_Gameplay::Quit()
{
	delete level;
	delete font;
	delete rm;
	endAudio();
}

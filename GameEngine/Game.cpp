
#include <iostream>
#include <cstdlib>
#include <time.h>

#include "Game.h"
#include "GameState.h"

Game::Game(){
	window = NULL;
	renderer = NULL;

	old_time = 0;
	new_time = 0;

	quit = false;
}

bool Game::Init(GameState* state)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cerr << SDL_GetError() << std::endl;
		return false;
	}

	window = SDL_CreateWindow("Cat Mania", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(window == NULL)
	{
		std::cerr << SDL_GetError() << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL)
	{
		std::cerr << SDL_GetError() << std::endl;
		return false;
	}

	srand(time(NULL)); //seed for random number generation, not really important

	PushState(state);

	return true;
}

void Game::Thread()
{
	while(quit == false)
	{
		fpsTimer.Start();
		Update();
		Render();
		fpsTimer.DelayFrames();
	}
	Quit();
}

void Game::Update()
{
	/*We need to cycle through the event queue and process events that will then be handled by
	a particular state.*/
	while(SDL_PollEvent(&event))
	{
		if(states.size() > 0)
			states.back()->HandleEvents(&event);
	}

	/*We need to check if the stack is not empty again, because there's a
	chance stack is emptied after handling events	*/
	if(states.size() > 0)
	{
		old_time = new_time;
		new_time = SDL_GetTicks();

		if(new_time > old_time)
		{
			float deltaTime = (float)(new_time - old_time) / 1000.0f;

			states.back()->Update(deltaTime);
		}
	}
}

void Game::Render()
{
	//clear the back buffer
	SDL_RenderClear(renderer);

	//render stuff onto the back buffer
	if(states.size() > 0)
		states.back()->Render();

	//switch front and the back buffer
	SDL_RenderPresent(renderer);
}

void Game::Quit()
{
	/*Remember, Quit might be called when there are still
	some states on the stack, so we need to get rid of them*/
	while(states.size() > 0)
	{
		states.back()->Quit();

		//we need to delete the dynamically allocated space
		delete states.back();

		states.pop_back();
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::setQuit()
{
	quit = true;
}

SDL_Renderer* Game::getRenderer()
{
	return renderer;
}

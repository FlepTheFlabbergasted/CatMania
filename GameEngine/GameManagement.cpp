
#include "Game.h"
#include "GameState.h"

void Game::PushState(GameState* state)
{
	/*This is actually really simple. We push the new state to the top of the stack,
	and if something goes wrong, we set the quit flag to true, which will prevent
	the rest of the state code from executing.*/
	states.push_back(state);
	if(state->Init(this) == false)
	{
		quit = true;
	}
}

void Game::PopState()
{
	states.back()->Quit();
	delete states.back();
	states.pop_back();

	/*If we popped the last state, the size will be 0.
	This means we can comfortably quit the program. This is
	NOT error handling! This is exactly how the program is
	supposed to work.*/
	if(states.size() == 0)
	{
		quit = true;
	}
}

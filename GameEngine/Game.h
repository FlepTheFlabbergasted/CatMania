
#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>

#include "../Utilities/Dlist.h"
#include "../Utilities/FpsTimer.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 420

/*Why this, and not just include GameState.h? Because we're going to be
including Game.h in GameState.h, and we can't have it both ways (we would
get infinite recursion). We don't need functionality here, just declaration.
So we're going to include GameState.h in Game.cpp, and not in Game.h*/
class GameState;

class Game
{
private:
	/*I'm not going to cover those. This tutorial is about game code, not SDL. There is an
	awesome tutorial done by Twinklebear at
	http://twinklebeardev.blogspot.com/p/sdl-20-tutorial-index.html
	Check it out, because most of the code will be based on SDL framework.*/
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;

	/* Just a simple variable to determine if we want to terminate the application or not.
	If this is set to true, main loop will break and the program will proceed to quit*/
	bool quit;

	/*This is the stack structure I've been talking about earlier.*/
	std::vector<GameState*> states;

	/*deltaTime related variables - ignore these for now, they are used to calculate time to
	achieve framerate independent movement*/
	Uint32 new_time;
	Uint32 old_time;

	FpsTimer fpsTimer;
public:
	Game(); //we'll just be setting some default values in the constructor

	/*This function will initialize SDL and will put the argument state on the state stack.
	That's the initial game state. Why bool, and not void? We want it to return false
	if something goes wrong, so then we can terminate the program. More about this later.*/
	bool Init(GameState* state);

	//this function will begin the main thread and will loop until quit is set to true
	void Thread();
private:
	//internal loop functions
	void Update();
	void Render();

	void Quit(); //will free SDL resources and perform cleanup of states
public:
	//state management functions (three stack operations I've been talking about earlier)
	void PushState(GameState* state);
	void PopState();

	//this will just force the game to quit regardless of how many states there are on stack
	void setQuit();

	//we'll be using the renderer on multiple occasions, so we need a 'get' function
	SDL_Renderer* getRenderer();
};

#endif

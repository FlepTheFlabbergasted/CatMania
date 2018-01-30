
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#include "GameEngine/Game.h"
#include "GameEngine/State_Gameplay.h"
#include "GameEngine/State_Menu.h"

using namespace std;

#if defined(_WIN32) || defined(_WIN64)
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
#elif linux
int main(int argc, char *argv[]) {
#else
#error "OS not supported"
#endif

	Game g;

	/*We create an instance of State_Gameplay and send it to Init function.
	If everything goes okay, we start executing the thread. If not, we just
	elegantly bounce out and terminate the program.*/
	if(g.Init(new State_Menu()))
		g.Thread();

	return 0;
}

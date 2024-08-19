#include "gamestate.h"

void SetGameState(void * handle) // Used as callback function
{
	GameStateHandle * gsh = (GameStateHandle *) handle;

	(*gsh->gs) = gsh->value; 
}
#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED

typedef enum
{
	GameMain = 0,
	GamePlay = 1,
	GameInfo = 2,
	GameExit = 3,
	GameFinished = 4

} GameState;

typedef struct
{
	GameState * gs;
	GameState value;

} GameStateHandle;

void SetGameState(void *);

#endif
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "hanoi_util.h"
#include "hanoi_menu.h"
#include "gamestate.h"

int main()
{
	// Creating Window
	InitWindow(800, 450, "Hanoi");
	SetTargetFPS(30);

	GameState game_state = GameMain;
	while(!WindowShouldClose() && game_state != GameFinished)
	{
		switch(game_state)
		{
			case GamePlay:
				PlayHanoi(&game_state);
			break;
			case GameInfo:
				HanoiInfo(&game_state);
			break;
			case GameExit:
				ConfirmQuit(&game_state);
			break;
			case GameMain:
				HanoiMainMenu(&game_state);
			break; 
		}
	}

	CloseWindow();

	return EXIT_SUCCESS;
}

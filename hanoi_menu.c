#include "hanoi_menu.h"

#include "sama_gui.h"

void HanoiMainMenu(GameState * game_state)
{

	// Creating widgets

	Title main_title = {
		"Hanoi Towers",
		(Layout)
		{
			(Vector2) {0, 0},
			(Vector2) {200, 50}
		},
		WHITE
	};

	const size_t button_count = 3llu;
	Button buttons[] = {
		(Button)
		{
			"Play",
			(Layout)
			{
				(Vector2) {0, 100},
				(Vector2) {100, 50}
			},
			NULL,
			NULL,
			Rest,
			(Color) {50, 50, 50, 255},
			(Color) {100, 100, 100, 255},
			(Color) {150, 150, 150, 255}
		},
		(Button)
		{
			"Info",
			(Layout)
			{
				(Vector2) {0, 175},
				(Vector2) {100, 50}
			},
			NULL,
			NULL,
			Rest,
			(Color) {50, 50, 50, 255},
			(Color) {100, 100, 100, 255},
			(Color) {150, 150, 150, 255}
		},
		(Button)
		{
			"Quit",
			(Layout)
			{
				(Vector2) {0, 250},
				(Vector2) {100, 50}
			},
			NULL,
			NULL,
			Rest,
			(Color) {50, 50, 50, 255},
			(Color) {100, 100, 100, 255},
			(Color) {150, 150, 150, 255}
		}
	};

	GameStateHandle handles[4] = {0};
	for(int i = 0; i < 4; i++)
	{
		handles[i].gs = game_state;
		handles[i].value = (GameState) i;
		
		if(i > 0)
		{
			buttons[i - 1].callback_arg = handles + i;
			buttons[i - 1].callback = SetGameState;
		}
	}

	// Menu loop
	while(!WindowShouldClose() && *game_state == GameMain)
	{
		BeginDrawing();
			ClearBackground(BLACK);
			
			DrawTitle(main_title);

			for(size_t i = 0; i < button_count; i++)
			{
				ButtonListenEvent(buttons + i);
				DrawButton(buttons[i]);
			}

		EndDrawing();
	}
}

void HanoiInfo(GameState * game_state)
{
	// Creating main menu button

	GameStateHandle main_handle = {
		game_state,
		GameMain
	};

	Button main_menu = {
		"Back to menu",
		(Layout)
		{
			(Vector2) {0, 400},
			(Vector2) {100, 50}
		},
		&main_handle,
		&SetGameState,
		Rest,
		(Color) {100, 0, 0, 255},
		(Color) {255, 255, 255, 255},
		(Color) {255, 0, 0, 255}
	};

	char info[] = "Welcome to the Towers of Hanoi !\n\n\
Move the tower on the left to the very\n\n\
right, remember you can't move multiple\n\n\
disks at a time or stack a disk on a\n\n\
smaller disk.\n\n\n\n\
Programmed by Sama Rive.\n\n\
V.0.1 (19/08/2024 3:14)";

	// Info loop
	while(!WindowShouldClose() && *game_state == GameInfo)
	{
		ButtonListenEvent(&main_menu);

		BeginDrawing();
			ClearBackground(BLACK);

			DrawText(info, 100, 100, 30, WHITE);

			DrawButton(main_menu);
		EndDrawing();
	}

}

void ConfirmQuit(GameState * game_state)
{
	// Creating main menu button

	GameStateHandle main_handle = {
		game_state,
		GameMain
	};
	GameStateHandle finish_handle = {
		game_state,
		GameFinished
	};

	const size_t button_count = 2llu;
	Button buttons[] = {
		(Button)
		{
			"Back to menu",
			(Layout)
			{
				(Vector2) {100, 200},
				(Vector2) {200, 50}
			},
			&main_handle,
			&SetGameState,
			Rest,
			(Color) {0, 100, 0, 255},
			(Color) {255, 255, 255, 255},
			(Color) {0, 255, 0, 255}
		},
		(Button)
		{
			"Close window",
			(Layout)
			{
				(Vector2) {500, 200},
				(Vector2) {200, 50}
			},
			&finish_handle,
			&SetGameState,
			Rest,
			(Color) {100, 0, 0, 255},
			(Color) {255, 255, 255, 255},
			(Color) {255, 0, 0, 255}
		}
	};

	// Confirm loop
	while(!WindowShouldClose() && *game_state == GameExit)
	{

		BeginDrawing();
			ClearBackground(BLACK);

			DrawText("Quit ?", 0, 0, 30, WHITE);

			for(size_t i = 0llu; i < button_count; i++)
			{
				ButtonListenEvent(buttons + i);
				DrawButton(buttons[i]);
			}
		
		EndDrawing();
	}

}

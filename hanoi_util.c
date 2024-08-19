#include "hanoi_util.h"

#include "gamestate.h"
#include "sama_gui.h"

#include <time.h>
#include <string.h>

void PlayHanoi(GameState * game_state)
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

	// Creating base game
	int stacks[NBR_STICK][MAX_STACK] = {0};
	Vector2 tiles[MAX_STACK] = {0};

	for(int i = 0; i < MAX_STACK; i++)
	{
		stacks[0][i] = MAX_STACK - i + 1;
	}

	Game game = {
		(Vector2) {100, 100}, // Position
		(Vector2) {600, 250}, // Size
		-1
	};

	int flash = -1;
	int won = 0;

	time_t start_time = time(NULL);
	time_t end_time = 0;

	while(!WindowShouldClose() && *game_state == GamePlay)
	{

		// Input
		ButtonListenEvent(&main_menu);

		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			if(game.selected == -1)
			{
				game.selected = GetClosestStick(GetMousePosition(), game);
			}
			else // (if player attempts to move a piece)
			{
				int target = GetClosestStick(GetMousePosition(), game);
				
				if(!HanoiMove(game.selected, target, &stacks[0][0])) // HanoiMove() has side-effect
				{
					flash = FLASH_DURATION; // Begin flash
				}

				game.selected = -1; // Unselect piece

				if(end_time == 0 && stacks[NBR_STICK - 1][MAX_STACK - 1] != 0)
				{
					end_time = time(NULL);
				}

			}
		}

		// Drawing
		BeginDrawing();
			Color bg = BLACK;

			// Flash effect
			if(flash > 0)
			{
				float x = 1.5708f * (FLASH_DURATION - flash)/FLASH_DURATION;
				bg.r = 255.f * cos(x);
				flash --;
			}

			ClearBackground(bg);

			// Some lines for clarity
			DrawLine(game.position.x + game.size.x/NBR_STICK, game.position.y, game.position.x + game.size.x/NBR_STICK, game.position.y + game.size.y, WHITE);
			DrawLine(game.position.x + 2.f * game.size.x/NBR_STICK, game.position.y, game.position.x + 2.f * game.size.x/NBR_STICK, game.position.y + game.size.y, WHITE);

			DrawGame(game, &stacks[0][0], tiles);

			// Win screen
			if(end_time != 0)
			{
				char t[64] = {0};
				sprintf(t, "You won in %d seconds !", end_time - start_time);
				DrawText(t, 0, 0, 30, GREEN);
			}

			DrawButton(main_menu);

		EndDrawing();
	}
}

void DrawGame(Game g, int * stacks, Vector2 * tiles)
{
	for(int i = 0; i < NBR_STICK; i++)
	{
		// Drawing the stick
		DrawRectangle(
			GetStickX(g, i),
			g.position.y,
			STICK_WIDTH,
			g.size.y,
			DARKGRAY
		);
	
		// Drawing game pieces
		for(int j = 0; j < MAX_STACK; j++)
		{
			if(stacks[i * MAX_STACK + j] == 0) continue;

			// Draw red outline on selected piece
			if(g.selected == i && (j == MAX_STACK - 1 || stacks[i * MAX_STACK + j + 1] == 0))
			{
				DrawRectangle(
					GetStickX(g, i) +  (STICK_WIDTH - GetPaletteSize(stacks[i * MAX_STACK + j])) / 2.f - 5,
					g.position.y + g.size.y - (j + 1) * GetPaletteHeight(g) - 5,
					GetPaletteSize(stacks[i * MAX_STACK + j]) + 10,
					GetPaletteHeight(g) + 10,
					RED
				);
			}

			// Position the tile should end up at after animation
			Vector2 target_pos = {
				GetStickX(g, i) +  (STICK_WIDTH - GetPaletteSize(stacks[i * MAX_STACK + j])) / 2.f,
				g.position.y + g.size.y - (j + 1) * GetPaletteHeight(g)
			};

			// Moving the tiles with linear interpolation
			tiles[stacks[i * MAX_STACK + j] - 1] = Vector2Add(
				tiles[stacks[i * MAX_STACK + j] - 1],
				Vector2Scale(
					Vector2Subtract(
						target_pos,
						tiles[stacks[i * MAX_STACK + j] - 1]
					),
					0.5f
				)
			);

			// Drawing the piece itself
			DrawRectangle(
				tiles[stacks[i * MAX_STACK + j] - 1].x,
				tiles[stacks[i * MAX_STACK + j] - 1].y,
				GetPaletteSize(stacks[i * MAX_STACK + j]),
				GetPaletteHeight(g),
				WHITE
			);
		}
	}
}

float GetStickX(Game g, unsigned int index)
{
	// Returns the x-coordinates of the index'th stick

	return g.position.x + ((float) (index) + 0.5f) * g.size.x / NBR_STICK;
}

float GetPaletteSize(int id)
{
	// (Should have been named GetPaletteWidth)
	return MIN_PALETTE_SIZE + id * PALETTE_SIZE_INCREMENT;
}

float GetPaletteHeight(Game g)
{
	return g.size.y / MAX_STACK;
}

int GetClosestStick(Vector2 v, Game g)
{
	int result = NBR_STICK * (v.x - g.position.x) / g.size.x;

	if(result < 0) result = 0;
	if(result >= NBR_STICK) result = NBR_STICK - 1;

	return result;
}

int HanoiMove(int from, int to, int * stacks)
{
	// Check if the move is possible, applies it if it is.

	int indices[] = {GetTopOfStackIndex(stacks + from * MAX_STACK), GetTopOfStackIndex(stacks + to * MAX_STACK)}; 
	int moving = stacks[from * MAX_STACK + indices[0]];
	int target = stacks[to * MAX_STACK + indices[1]];

	if((target == 0 || moving <= target) && indices[1] != MAX_STACK - 1 && from != to)
	{

		stacks[to * MAX_STACK + indices[1] + 1] = moving;
		stacks[from * MAX_STACK + indices[0]] = 0;

		return 1;
	}
	return 0;
}

int GetTopOfStackIndex(int * stack)
{
	for(int i = MAX_STACK - 1; i > -1; i--)
	{
		if(stack[i] != 0)
			return i;
	}

	return -1;
}
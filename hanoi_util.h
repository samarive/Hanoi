#ifndef HANOI_UTIL_H_INCLUDED
#define HANOI_UTIL_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include <raymath.h>

#include "gamestate.h"

#define MAX_STACK 5
#define NBR_STICK 3
#define STICK_WIDTH 10.f
#define MIN_PALETTE_SIZE 50.f
#define PALETTE_SIZE_INCREMENT 20.f
#define FLASH_DURATION 15

typedef struct
{
	Vector2 position;
	Vector2 size;
	int selected;

} Game;

void PlayHanoi(GameState*);

void DrawGame(Game g, int * stacks, Vector2 * tiles_pos);
float GetStickX(Game g, unsigned int index);
float GetPaletteSize(int id);
float GetPaletteHeight(Game g);
int GetClosestStick(Vector2, Game);
int HanoiMove(int from, int to, int * stacks);
int GetTopOfStackIndex(int * stack);

#endif
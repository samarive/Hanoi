#ifndef SAMAGUI_H_INCLUDED
#define SAMAGUI_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>


typedef enum
{
	Rest,
	Hover,
	Press

} ButtonState;

typedef struct
{
	Vector2 position;
	Vector2 size;

} Layout;

typedef struct
{
	char * text;
	Layout layout;
	Color color;

} Title;

typedef struct
{
	char * text;
	Layout layout;

	void * callback_arg;
	void (*callback) (void*);

	ButtonState state;

	Color action_color;
	Color rest_color;
	Color hover_color;

} Button;

void DrawTitle(Title);
void DrawButton(Button);

void ButtonListenEvent(Button*);


#endif
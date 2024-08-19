#include "sama_gui.h"

#include <raylib.h>

void DrawTitle(Title t)
{
	unsigned int font_size = 0;
	// I know...
	while(MeasureText(t.text, font_size) < t.layout.size.x)
	{
		font_size ++;
	}

	DrawText(t.text, t.layout.position.x, t.layout.position.y, font_size, t.color);
}


void DrawButton(Button b)
{
	Color color = {0};
	switch(b.state)
	{
		case Rest:
			color = b.rest_color;
		break;
		case Hover:
			color = b.hover_color;
		break;
		case Press:
			color = b.action_color;
		break; 
	}

	DrawRectangleV(b.layout.position, b.layout.size, color);

	unsigned int font_size = 0;
	// I still know... Could have been a function but
	// I hate it so much I want it to be clear that it needs
	// to be changed in a future version
	// (if there is one)
	while(MeasureText(b.text, font_size) < b.layout.size.x - 20)
	{
		font_size ++;
	}

	DrawText(b.text, b.layout.position.x + 10, b.layout.position.y, font_size, BLACK);
}

void ButtonListenEvent(Button * b)
{
	Vector2 mouse = GetMousePosition();

	if(mouse.x > b->layout.position.x
	&& mouse.x < b->layout.position.x + b->layout.size.x
	&& mouse.y > b->layout.position.y
	&& mouse.y < b->layout.position.y + b->layout.size.y)
	{
		b->state = Hover;

		if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			b->state = Press;
		if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			if(b->callback != NULL) b->callback(b->callback_arg);
		}
	}
	else
	{
		b->state = Rest;
	}
}

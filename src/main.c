#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "memory.h"
#include "cvec.h"
#include "uuid.h"
#include "state_machine.h"

#include "ttcard.h"
#include "board.h"
#include "st_startmenu.h"


#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

CVecVoid TTCard_allTTCards = { 0 };
int cards_read = 0;

extern int add(int a, int b);

void initialize();
void ready();
void update(double delta);
void physics_update(double delta);
void draw(double delta);

int main()
{
	initialize();

	int result = add(1, 2);
	
	printf("Result: %d \n", result);

	const int screenWidth = 1280;
	const int screenHeight = 720;
	

	InitWindow(screenWidth, screenHeight, "Triple Triad");
	SetTargetFPS(60);             

	ready();

	while (!WindowShouldClose())    
	{
		
		double frame_time = GetFrameTime();
		update(frame_time);
		physics_update(frame_time);
		
		BeginDrawing();
		ClearBackground(RAYWHITE);
		draw(frame_time);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}

void initialize()
{
	st_startmenu_initialize_state();
}

void ready()
{
	ttcard_read_data_json(&TTCard_allTTCards, "./data/cards.json");
	printf("Cards read from JSON...\n");
	cards_read = 1;

	printf("Capacity: %d\n", TTCard_allTTCards.capacity);
	printf("Count: %d\n", TTCard_allTTCards.count);

	sm_switch_state(&st_startmenu_state);
}

void update(double delta)
{
	sm_execute_state_update(delta);
}

void physics_update(double delta)
{
	sm_execute_state_physics_update(delta);
}

void draw(double delta)
{
	sm_execute_state_draw(delta);
}

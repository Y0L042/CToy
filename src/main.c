#include "raylib.h"

#include "memory.h"
#include "cvec.h"
#include "uuid.h"
#include "ttcard.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

CVecVoid TTCard_allTTCards = { 0 };

extern int add(int a, int b);

void ready();
void update(double delta);
void physics_update(double delta);
void draw(double delta);

int cards_read = 0;

int main()
{
	

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

void ready()
{
	ttcard_read_data_json(&TTCard_allTTCards, "./data/cards.json");
	printf("Cards read from JSON...\n");
	cards_read = 1;

	printf("Capacity: %d\n", TTCard_allTTCards.capacity);
	printf("Count: %d\n", TTCard_allTTCards.count);
}

void update(double delta)
{
}

void physics_update(double delta)
{
}

void draw(double delta)
{
	if (cards_read == 1)
	{
		ttcard_draw((TTCard*)TTCard_allTTCards.data[0], 25, 25);
	}
}


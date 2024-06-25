#include "raylib.h"

#include "memory.h"
#include "cvec.h"
#include "uuid.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>


typedef struct {
	UUID uuid;
	int nums[4]; // TBLR
	char* name;
	char* imgPath;
	Texture* texture;
} TTCard;	

TTCard* card;

extern int add(int a, int b);

void Ready();
void Update(double delta);
void PhysicsUpdate(double delta);
void Draw(double delta);
void Exit();

TTCard CreateTTCardBlank();
TTCard CreateTTCardFilled(int nums[], char* name, char* imgPath);

int main()
{
	

	int result = add(1, 2);
	
	printf("Result: %d \n", result);

	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
	SetTargetFPS(60);             

	Ready();

	while (!WindowShouldClose())    
	{
		
		double frame_time = GetFrameTime();
		Update(frame_time);
		PhysicsUpdate(frame_time);
		
		BeginDrawing();
		ClearBackground(RAYWHITE);
		Draw(frame_time);
		EndDrawing();
	}
	Exit();

	CloseWindow();
	return 0;
}

void Ready()
{
	card = malloc(sizeof(TTCard));
	*card = CreateTTCardBlank();
	card->uuid = uuid_generate();

	printf("card uuid: %"PRIu64"\n", card->uuid);

	CVecInt test;
	cvec_int_init(&test);
	for (int i = 0; i < 100; i++)
	{
		cvec_int_add_item(&test, i);
		printf("CVecInt data[%d], cap: %d , %d\n", i, test.data[i], test.capacity);
	}
	printf("CVecInt count: %d \n", test.count);
	printf("CVecInt capacity: %d \n", test.capacity);

	printf("\n ------------------- \n");

	for (int i = 77; i > 0; i--)
	{
		cvec_int_remove_idx(&test, i);
		printf("CVecInt data[%d], cap: %d , %d\n", i-1, test.data[i-1], test.capacity);
	}
	printf("CVecInt count: %d \n", test.count);
	printf("CVecInt capacity: %d \n", test.capacity);
}

void Update(double delta)
{
}

void PhysicsUpdate(double delta)
{
}

void Draw(double delta)
{
	
}

void Exit()
{
	free(card);
}

TTCard CreateTTCardBlank()
{
	TTCard card;
	return card;
}

TTCard CreateTTCardFilled(int nums[], char* name, char* imgPath)
{
	TTCard card;
	memcpy(card.nums, nums, 4);
	card.name = name;
	card.imgPath = imgPath;
	// card.texture = &LoadTexture(imgPath);
	return card;
}


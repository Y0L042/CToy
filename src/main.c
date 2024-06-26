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

CVecVoid TTCard_allTTCards;

extern int add(int a, int b);

void Ready();
void Update(double delta);
void PhysicsUpdate(double delta);
void Draw(double delta);
void Exit();

TTCard* CreateTTCardBlank();
TTCard* CreateTTCardFilled(int T, int B, int L, int R, const char* name, const char* imgPath);
void  ReadTTCardCSVData (const char* source, int cols);

int main()
{
	

	int result = add(1, 2);
	
	printf("Result: %d \n", result);

	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "Triple Triad");
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

	ReadTTCardCSVData("./assets/skyrim_triple_triad_cards.csv", 5);
	printf("Cards read from csv...\n");

	for (int i = 0; i < TTCard_allTTCards.count; i++)
	{
		TTCard* card =  (TTCard*)(TTCard_allTTCards.data[i]);
		printf("Card: %s \n", card->name);
	}
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
}

TTCard* CreateTTCardBlank()
{
	TTCard* card = (TTCard*)malloc(sizeof(TTCard));
	return card;
}

TTCard* CreateTTCardFilled(int T, int B, int L, int R, const char* name, const char* imgPath)
{
	int MAX_NAME_LEN = 50;
	int MAX_PATH_LEN = 150;
	TTCard* card = (TTCard*)malloc(sizeof(TTCard));
	card->nums[0] = T;
	card->nums[1] = B;
	card->nums[2] = L;
	card->nums[3] = R;
	card->name = (char*)malloc(MAX_NAME_LEN);
	strncpy(card->name, name, MAX_NAME_LEN - 1);
	card->name[MAX_NAME_LEN - 1] = '\0';
	card->imgPath = (char*)malloc(MAX_PATH_LEN);
	strncpy(card->imgPath, imgPath, MAX_PATH_LEN - 1);
	card->imgPath[MAX_PATH_LEN - 1] = '\0';
	// card.texture = &LoadTexture(imgPath);
	return card;
}

void ReadTTCardCSVData(const char* source, int cols)
{
	const int MAXCHAR = 1000;
	char row[MAXCHAR];

	FILE* file = fopen(source, "r");
	if (file == NULL)
	{
		perror(source);
		return;
	}
	
	int idx = 0;
	while (fgets(row, sizeof(row), file) != NULL)
	{
		if (idx++ == 0) { continue; }
		row[strcspn(row, "\n")] = '\0';
		char* tokens[cols];
		int i = 0;
		char* token = strtok(row, ",");
		while(token != NULL && i < cols)
		{
			tokens[i++] = token;
			token = strtok(NULL, ",");
		}

		cvec_void_add_item(
				&TTCard_allTTCards, 
				(void*)CreateTTCardFilled(
					atoi(tokens[0]), // T
					atoi(tokens[1]), // B
					atoi(tokens[2]), // L
					atoi(tokens[3]), // R
					(char*)tokens[4], // Name
					"" // Path
				)
		);
		idx++;
	}
	fclose(file);
}

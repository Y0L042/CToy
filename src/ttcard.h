#ifndef TTCARD_H
#define TTCARD_H

#include "uuid.h"
#include "raylib.h"
#include "cvec.h"

#include <cJSON.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct {
	UUID uuid;
	int nums[4]; // TBLR
	char* name;
	char* img_path;
	Texture* texture;

	Color default_bgcolor;
	float def_whratio;
	int def_width;
	int def_height;

	int num_size;
	int num_y_spacing;
	int num_x_spacing;
	Vector2 num_pos;
	Color num_color;

	int name_size;
	Vector2 name_pos;
	Color name_color;

} TTCard;





TTCard* ttcard_create_blank();
TTCard* ttcard_create_filled(int T, int B, int L, int R, const char* name, const char* imgPath);
void  ttcard_read_data_csv(CVecVoid* ttcardList, const char* source, int cols);
void ttcard_read_data_json(CVecVoid* ttcardList, const char* source);
void ttcard_draw(TTCard* card, int x, int y);
void ttcard_read_data_json(CVecVoid* ttcardList, const char* source);

char* _read_file(const char* path);
void _parse_card_default(cJSON* default_card, TTCard* card);
void _parse_card_filled(cJSON* filled_cards_json, TTCard* default_card, TTCard* card);
Color _parse_color(cJSON* color);
Vector2 _parse_vector2(cJSON* vector2_json);

#endif // !TTCARD_H

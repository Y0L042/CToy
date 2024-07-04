#include "ttcard.h"

#include <cJSON.h>

TTCard* ttcard_create_blank()
{
	TTCard* card = (TTCard*)malloc(sizeof(TTCard));
	return card;
}

TTCard* ttcard_create_filled(int T, int B, int L, int R, const char* name, const char* img_path)
{
	TTCard* card = (TTCard*)malloc(sizeof(TTCard));
	
	card->nums[0] = T;
	card->nums[1] = B;
	card->nums[2] = L;
	card->nums[3] = R;

	int MAX_NAME_LEN = 50;
	card->name = (char*)malloc(MAX_NAME_LEN);
	strncpy(card->name, name, MAX_NAME_LEN - 1);
	card->name[MAX_NAME_LEN - 1] = '\0';

	int MAX_PATH_LEN = 150;
	card->img_path = (char*)malloc(MAX_PATH_LEN);
	strncpy(card->img_path, img_path, MAX_PATH_LEN - 1);
	card->img_path[MAX_PATH_LEN - 1] = '\0';

	card->default_bgcolor = BLUE;
	card->def_whratio = 0.66f;
	card->def_height = 200;
	if (card->def_whratio < 0.95f || card->def_whratio > 1.05f)
	{
		card->def_width = card->def_height * card->def_whratio;
	}
	else { card->def_width = 100; }

	

	return card;
}

void ttcard_read_data_csv(CVecVoid* ttcardList, const char* source, int cols)
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
		while (token != NULL && i < cols)
		{
			tokens[i++] = token;
			token = strtok(NULL, ",");
		}

		cvec_void_add_item(
			ttcardList,
			(void*)ttcard_create_filled(
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

void ttcard_read_data_json(CVecVoid* ttcardList, const char* source) 
{
	char* json_content = _read_file(source);
	if (json_content == NULL) 
	{
		return;
	}

	cJSON* root = cJSON_Parse(json_content);
	if (root == NULL) 
	{
		fprintf(stderr, "Error before: [%s]\n", cJSON_GetErrorPtr());
		free(json_content);
		return;
	}

	cJSON* default_card_json = cJSON_GetObjectItem(root, "default_card");
	cJSON* cards_json = cJSON_GetObjectItem(root, "cards");


	// Create cards

	TTCard default_card;
	_parse_card_default(default_card_json, &default_card);

	int num_cards = cJSON_GetArraySize(cards_json);
	for (int i = 0; i < num_cards; ++i) 
	{
		cJSON* card_json = cJSON_GetArrayItem(cards_json, i);
		TTCard* card = (TTCard*)malloc(sizeof(TTCard));
		_parse_card_filled(card_json, &default_card, card);
		cvec_void_add_item(ttcardList, (void*)card);
	}

	cJSON_Delete(root);
	free(json_content);
}



void ttcard_draw(TTCard* card, int x, int y)
{
	int num_size = 15;
	int num_y_spacing = 30;
	int num_x_spacing = 20;
	Vector2 num_pos = card->num_pos;
	//Vector2 num_pos = { 25, 25 };
	Color num_color = GREEN;

	int name_size = 15;
	Vector2 name_pos = { 10, 30 };
	Color name_color = GREEN;

	DrawRectangle(x, y, card->def_width, card->def_height, card->default_bgcolor);

	char numStr[2] = { 0 };
	for (int i = 0; i < 4; ++i)
	{
		snprintf(numStr, sizeof(numStr), "%d", card->nums[i]);
		switch (i)
		{
		case 0: DrawText(numStr, x + num_pos.x, y + num_pos.y - num_y_spacing / 2, num_size, num_color); break; // Top
		case 1: DrawText(numStr, x + num_pos.x, y + num_pos.y + num_y_spacing / 2, num_size, num_color); break; // Bottom
		case 2: DrawText(numStr, x + num_pos.x - num_x_spacing / 2, y + num_pos.y, num_size, num_color); break; // Left
		case 3: DrawText(numStr, x + num_pos.x + num_x_spacing / 2, y + num_pos.y, num_size, num_color); break; // Right
		}
	}
	DrawText(card->name, x + 50, y + 75, name_size, name_color);
}










char* _read_file(const char* path)
{
	FILE* file = fopen(path, "r");
	if (file == NULL)
	{
		printf("file {%s} could not be read.\n", path);
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	long length = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* buffer = (char*)malloc(length + 1);
	if (buffer == NULL)
	{
		printf("Buffer memory allocation failed.\n");
		fclose(file);
		return NULL;
	}

	fread(buffer, 1, length, file);
	buffer[length] = '\0';

	fclose(file);
	return buffer;
}

void _parse_card_default(cJSON* default_card_json, TTCard* default_card)
{
	default_card->default_bgcolor = _parse_color(cJSON_GetObjectItem(default_card_json, "default_bgcolor"));
	default_card->def_whratio = (float)cJSON_GetObjectItem(default_card_json, "def_whratio")->valuedouble;
	default_card->def_height = cJSON_GetObjectItem(default_card_json, "def_height")->valueint;
	default_card->def_width = (int)(default_card->def_whratio * default_card->def_height);
	default_card->num_pos = _parse_vector2(cJSON_GetObjectItem(default_card_json, "num_pos"));
}

void _parse_card_filled(cJSON* filled_cards_json, TTCard* default_card, TTCard* card)
{
	// Copy default card properties to the new card
	card->default_bgcolor = default_card->default_bgcolor;
	card->def_whratio = default_card->def_whratio;
	card->def_height = default_card->def_height;
	card->def_width = default_card->def_width;
	card->num_pos = default_card->num_pos;

	for (int i = 0; i < 4; ++i)
	{
		card->nums[i] = default_card->nums[i];
	}

	// Allocate and copy name and img_path from default_card to card
	card->name = strdup(default_card->name);
	card->img_path = strdup(default_card->img_path);

	// Override properties with values from filled_cards_json if they exist
	cJSON* item = NULL;

	item = cJSON_GetObjectItem(filled_cards_json, "default_bgcolor");
	if (item)
	{
		card->default_bgcolor = _parse_color(item);
	}

	item = cJSON_GetObjectItem(filled_cards_json, "def_whratio");
	if (item)
	{
		card->def_whratio = (float)item->valuedouble;
		card->def_width = (int)(card->def_whratio * card->def_height);
	}

	item = cJSON_GetObjectItem(filled_cards_json, "def_height");
	if (item)
	{
		card->def_height = item->valueint;
		card->def_width = (int)(card->def_whratio * card->def_height);
	}

	item = cJSON_GetObjectItem(filled_cards_json, "nums");
	if (item)
	{
		for (int i = 0; i < 4; ++i)
		{
			card->nums[i] = cJSON_GetArrayItem(item, i)->valueint;
		}
	}

	item = cJSON_GetObjectItem(filled_cards_json, "name");
	if (item)
	{
		free(card->name);
		card->name = strdup(item->valuestring);
	}

	item = cJSON_GetObjectItem(filled_cards_json, "img_path");
	if (item)
	{
		free(card->img_path);
		card->img_path = strdup(item->valuestring);
	}

	item = cJSON_GetObjectItem(filled_cards_json, "num_pos");
	if (item)
	{
		card->num_pos = _parse_vector2(item);
	}
}


Color _parse_color(cJSON* color_json)
{
	Color color;
	color.r = cJSON_GetObjectItem(color_json, "r")->valueint;
	color.g = cJSON_GetObjectItem(color_json, "g")->valueint;
	color.b = cJSON_GetObjectItem(color_json, "b")->valueint;
	color.a = cJSON_GetObjectItem(color_json, "a")->valueint;

	return color;
}

Vector2 _parse_vector2(cJSON* vector2_json)
{
	Vector2 vector2;
	vector2.x = cJSON_GetObjectItem(vector2_json, "x")->valueint;
	vector2.y = cJSON_GetObjectItem(vector2_json, "y")->valueint;

	return vector2;
}
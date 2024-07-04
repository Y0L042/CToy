#ifndef BOARD_H
#define BOARD_H

#include "uuid.h"
#include "ttcard.h"

typedef struct {
	UUID uuid;
	TTCard* ttCard;
	UUID owner;
	UUID currentPlr;
} ActiveTTCard;

typedef struct {
	UUID uuid;
	ActiveTTCard* board[3][3];
	int open_spaces;
	
	int plr1_score;
	ActiveTTCard* plr1_cards[5];

	int plr2_score;
	ActiveTTCard* plr2_cards[5];

} TTBoard;

ActiveTTCard* activettcard_create();
               

#endif

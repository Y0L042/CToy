#ifndef BOARD_H
#define BOARD_H

#include "uuid.h"

typedef struct {
	UUID uuid;
	// store 9 cards
	// store info about each position (1/2 point positions...)
	// track scores?
	// track turns?
} TTBoard;

#endif

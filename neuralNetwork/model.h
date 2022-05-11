#ifndef MODEL_H
#define MODEL_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef enum
{
	ZERO_WAY = 0,
	LEFT,
	UP,
	RIGHT,
	DOWN,
	LEFT_UP,
	UP_RIGHT,
	RIGHT_DOWN,
	LEFT_DOWN,
	UP_DOWN,
	LEFT_RIGHT,
	LEFT_UP_RIGHT,
	UP_RIGHT_DOWN,
	LEFT_RIGHT_DOWN,
	LEFT_UP_DOWN,
	FOUR_WAY,
} blocks;

double recognition(double input[]);

#endif
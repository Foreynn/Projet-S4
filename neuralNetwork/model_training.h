#ifndef MODEL_TRAINING_H
#define MODEL_TRAINING_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>

typedef enum
{
	ZERO_WAY_1 = 0,
	ZERO_WAY_2,
	ZERO_WAY_3,
	LEFT_1,
	LEFT_2,
	LEFT_3,
	UP_1,
	UP_2,
	UP_3,
	RIGHT_1,
	RIGHT_2,
	RIGHT_3,
	DOWN_1,
	DOWN_2,
	DOWN_3,
	LEFT_UP_1,
	LEFT_UP_2,
	LEFT_UP_3,
	UP_RIGHT_1,
	UP_RIGHT_2,
	UP_RIGHT_3,
	RIGHT_DOWN_1,
	RIGHT_DOWN_2,
	RIGHT_DOWN_3,
	LEFT_DOWN_1,
	LEFT_DOWN_2,
	LEFT_DOWN_3,
	LEFT_UP_RIGHT_1,
	LEFT_UP_RIGHT_2,
	LEFT_UP_RIGHT_3,
	UP_RIGHT_DOWN_1,
	UP_RIGHT_DOWN_2,
	UP_RIGHT_DOWN_3,
	LEFT_RIGHT_DOWN_1,
	LEFT_RIGHT_DOWN_2,
	LEFT_RIGHT_DOWN_3,
	LEFT_UP_DOWN_1,
	LEFT_UP_DOWN_2,
	LEFT_UP_DOWN_3,
	FOUR_WAY_1,
	FOUR_WAY_2,
	FOUR_WAY_3,
} blocks;

double sigmoid(double x);
double relu(double x);
double dSigmoid(double x);
double dRelu(double x);
double init_weight();
void shuffle(int *array, size_t n);
void training();

#endif
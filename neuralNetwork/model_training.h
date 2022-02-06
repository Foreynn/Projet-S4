#ifndef MODEL_TRAINING_H
#define MODEL_TRAINING_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>

double sigmoid(double x);
double relu(double x);
double dSigmoid(double x);
double dRelu(double x);
double init_weight();
void shuffle(int *array, size_t n);
void training();

#endif
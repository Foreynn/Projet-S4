#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include "model_training.h"
#include "model.h"
#include "imgToArray.h"

int main(int argc, char** argv)
{
	// Checking arguments
    if (argc > 2)
    {
        printf("Too many arguments");
        return 1;
    }

	// Creating inputs and outputs
    double *inputs;
	size_t size = atoi(argv[1]) * atoi(argv[1]);
    double outputs[size];
    
    for (size_t i = 0; i < size; i++)
    {
        inputs = ImageToList(i);
        outputs[i] = recognition(inputs);
    }
    
    for (size_t i = 0; i < size; i++)
    {
        if (outputs[i] == 0)
        {
            printf(". | ");
            continue;
        }
        printf("%.0f | ", round(outputs[i]));
    }
    printf("\n");
    return 0;
}
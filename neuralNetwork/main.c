#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include "model_training.h"
#include "model.h"
#include "imgToBoard.h"

int main(char argc, char** argv)
{
    if (argc > 2)
        printf("Too many arguments");
        return 1;
    
    double *inputs;
    double outputs[argv[1]];

    for (size_t i = 0; i < argv[1]; i++)
    {
        inputs = ImageToList(i+1);
        outputs[i] = recognition(inputs);
    }

    for (size_t i = 0; i < argv[1]; i++)
    {
        if (outputs[i] == 0)
        {
            printf(". / ");
            continue;
        }
        printf("%.0f / ", round(outputs[i]));
    }
    printf("\n");
    return 0;
}
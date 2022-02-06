#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include "model_training.h"
#include "model.h"


double recognition(double input[])
{
    // Layers
    double hiddenLayer[9*9];
    double outputLayer[1];
    
    double hiddenLayerBias[9*9];
    double outputLayerBias[1];

    double hiddenWeights[9*9][9*9];
    double outputWeights[9*9][1];

    FILE *g = fopen("weights/outputLayerBias.data", "r +");
    fread(outputLayerBias, sizeof(double), sizeof(outputLayerBias)/sizeof(double), g);
    fclose(g);
    
    FILE *f = fopen("weights/hiddenLayerBias.data", "r +");
    fread(hiddenLayerBias, sizeof(double), sizeof(hiddenLayerBias)/sizeof(double), f);
    fclose(f);

    FILE *h = fopen("weights/hiddenWeights.data", "r +");
    fread(hiddenWeights, sizeof(double), sizeof(hiddenWeights)/sizeof(double), h);
    fclose(h);

    FILE *i = fopen("weights/outputWeights.data", "r +");
    fread(outputWeights, sizeof(double), sizeof(outputWeights)/sizeof(double), i);
    fclose(i);

    for (int j=0; j<9*9; j++)
    {
        double activation=hiddenLayerBias[j];
        for (int k=0; k<9*9; k++)
        {
            activation+=input[k]*hiddenWeights[k][j];
        }
        hiddenLayer[j] = sigmoid(activation);
    }
    
    for (int j=0; j<1; j++)
    {
        double activation=outputLayerBias[j];
        for (int k=0; k<9*9; k++)
        {
            activation+=hiddenLayer[k]*outputWeights[k][j];
        }
        outputLayer[j] = relu(activation);
    }
    return outputLayer[0];
}
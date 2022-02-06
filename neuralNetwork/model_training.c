#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include "model_training.h"
#include "imgToBoard.h"


double sigmoid(double x)
{
	return 1 / (1 + exp(-x));
}

double relu(double x)
{
    return x < 0 ? 0 : x;
}

double dSigmoid(double x)
{
	return x * (1 - x);
}

double dRelu(double x)
{
    return x < 0 ? 0 : 1;
}

double init_weight()
{
	return ((double)rand())/((double)RAND_MAX);
}


void shuffle(int *array, size_t n)
{
    if (n > 1)
    {
        size_t i;
        for (i = 0; i < n - 1; i++)
        {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}



void training()
{
    // 9*9 => size of the image
    // 42 => siwe of the training set

    const double lr = 0.1;
    
    // Layers
    double hiddenLayer[9*9];
    double outputLayer[1];
    
    double hiddenLayerBias[9*9];
    double outputLayerBias[1];

    double hiddenWeights[9*9][9*9];
    double outputWeights[9*9][1];
    
    // Training set

    double training_inputs[42][9*9] =
    {
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }, /* */
        { }  /* */
    };
    
    double training_outputs[42][1] = {};
    
    // Initialising the weights of each layer
    for (int i=0; i<9*9; i++)
	{
        for (int j=0; j<9*9; j++)
		{
            hiddenWeights[i][j] = init_weight();
        }
    }   
    
	for (int i=0; i<9*9; i++)
	{
        hiddenLayerBias[i] = init_weight();
        for (int j=0; j<1; j++)
		{
            outputWeights[i][j] = init_weight();
        }
    }
    
	for (int i=0; i<1; i++)
	{
        outputLayerBias[i] = init_weight();
    }
    

    // Training process
    int trainingSetOrder[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,
                              24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41};
    double error = 1;
    int n = 0;
    
    while (/*error > 0.001 &&*/ n < 1000)//for (int n=0; n < 500; n++)
	{
        shuffle(trainingSetOrder,42);
        for (int x=0; x<42; x++)
		{            
            error = 0;
            
            int i = trainingSetOrder[x];
            
            // Forward pass
            
            for (int j=0; j<9*9; j++)
			{
                double activation=hiddenLayerBias[j];
                for (int k=0; k<9*9; k++)
				{
                    activation+=training_inputs[i][k]*hiddenWeights[k][j];
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
            
            error += fabs(outputLayer[0] - training_outputs[i][0]);
            //printf("Input: %d \nOutput: %f \nExpected Output: %f\n", i, outputLayer[0], training_outputs[i][0]);
            
           // Backprop
            
            double deltaOutput[1];
            for (int j=0; j<1; j++)
			{
                double errorOutput = (training_outputs[i][j]-outputLayer[j]);
                deltaOutput[j] = errorOutput*dRelu(outputLayer[j]);
            }
            
            double deltaHidden[9*9];
            for (int j=0; j<9*9; j++)
			{
                double errorHidden = 0.0f;
                for(int k=0; k<1; k++)
				{
                    errorHidden+=deltaOutput[k]*outputWeights[j][k];
                }
                deltaHidden[j] = errorHidden*dRelu(hiddenLayer[j]);
            }
            
            for (int j=0; j<1; j++)
			{
                outputLayerBias[j] += deltaOutput[j]*lr;
                for (int k=0; k<9*9; k++)
				{
                    outputWeights[k][j]+=hiddenLayer[k]*deltaOutput[j]*lr;
                }
            }
            
            for (int j=0; j<9*9; j++)
			{
                hiddenLayerBias[j] += deltaHidden[j]*lr;
                for(int k=0; k<9*9; k++)
				{
                    hiddenWeights[k][j]+=training_inputs[i][k]*deltaHidden[j]*lr;
                }
            }
        }
        printf("Iteration %3d: error = %f\n", n, error/42);
        n++;
    }

    FILE *f = fopen("weights/hiddenLayerBias.data", "w");
    fwrite(hiddenLayerBias, sizeof(double), sizeof(hiddenLayerBias)/sizeof(double), f);
    fclose(f);

    FILE *g = fopen("weights/outputLayerBias.data", "w");
    fwrite(outputLayerBias, sizeof(double), sizeof(outputLayerBias)/sizeof(double), g);
    fclose(g);

    FILE *h = fopen("weights/hiddenWeights.data", "w");
    fwrite(hiddenWeights, sizeof(double), sizeof(hiddenWeights)/sizeof(double), h);
    fclose(h);

    FILE *i = fopen("weights/outputWeights.data", "w");
    fwrite(outputWeights, sizeof(double), sizeof(outputWeights)/sizeof(double), i);
    fclose(i);
}
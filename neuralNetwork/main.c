#include <math.h>
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
    
    FILE *f = fopen("output.csv", "w+");
    for (size_t i = 0; i < size; i++)
    {
        printf("%.0f | ", round(outputs[i]));
        fprintf(f, "%.0f\n", round(outputs[i]));
    }
    fclose(f);

    printf("\n");
    return 0;
}

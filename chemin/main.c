#include "tile.h"
#include "path_finder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// N'a ete pour l'instant concu que pour les labyrinthes de format carre.

int main() {

    char *filename = "../neuralNetwork/output.csv";
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
        return 1;
    }

    // TODO : avoir automatiquement les dimensions (utiliser le nombre de ligne du fichier output.csv ?)

    int r = 5;  // r : total number of line.

    // Having a square, we state c = r.
    int c = r;  // c : total number of column.

    /* SRFC is an abreviation for SURFACE.
     * (We've merely kept the consonants.) */
    SRFC = r * c;

    tiles = malloc(sizeof(struct tile *) * c);
    for (int i = 0; i < c; i++)
        tiles[i] = malloc(sizeof(struct tile) * r);

    // Reading line by line, max 256 bytes.
    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];

    for (int i = 0; fgets(buffer, MAX_LENGTH, fp); i++) {
        int number = atoi(buffer);
        int degree;
        int arr[4];
        switch (number) {
            case 0:
                degree = 0;
                break;
            case 1:
                degree = 1;
                arr[0] = LEFT;
                break;
            case 2:
                degree = 1;
                arr[0] = UP;
                break;
            case 3:
                degree = 1;
                arr[0] = RIGHT;
                break;
            case 4:
                degree = 1;
                arr[0] = DOWN;
                break;
            case 5:
                degree = 2;
                arr[0] = LEFT;
                arr[1] = UP;
                break;
            case 6:
                degree = 2;
                arr[0] = UP;
                arr[1] = RIGHT;
                break;
            case 7:
                degree = 2;
                arr[0] = RIGHT;
                arr[1] = DOWN;
                break;
            case 8:
                degree = 2;
                arr[0] = DOWN;
                arr[1] = LEFT;
                break;
            case 9:
                degree = 2;
                arr[0] = UP;
                arr[1] = DOWN;
                break;
            case 10:
                degree = 2;
                arr[0] = LEFT;
                arr[1] = RIGHT;
                break;
            case 11:
                degree = 3;
                arr[0] = LEFT;
                arr[1] = UP;
                arr[2] = RIGHT;
                break;
            case 12:
                degree = 3;
                arr[0] = UP;
                arr[1] = RIGHT;
                arr[2] = DOWN;
                break;
            case 13:
                degree = 3;
                arr[0] = RIGHT;
                arr[1] = LEFT;
                arr[2] = DOWN;
                break;
            case 14:
                degree = 3;
                arr[0] = DOWN;
                arr[1] = LEFT;
                arr[2] = UP;
                break;
            case 15:
                degree = 4;
                arr[0] = LEFT;
                arr[1] = UP;
                arr[2] = RIGHT;
                arr[3] = DOWN;
                break;
        }

        // We fill tiles column by column.
        tiles[i/r][i%c].dgr = degree;
        tiles[i/r][i%c].traveled = 0;

        tiles[i/r][i%c].accs = malloc(sizeof(enum direction) * degree);
        for(int j = 0; j < degree; j++)
            tiles[i/r][i%c].accs[j] = arr[j];
    }

    // We choose an entry point.
    struct point entry = {.x = 2, .y = 0}; 

    // We create the exit of our maze test.
    xt.x = 2;
    xt.y = 4;

    // Where to stock the solution of the maze.
    path_found = malloc(sizeof(struct tile *) * SRFC);
    memset(path_found, 0, sizeof(struct tile *));

    // We run our path finder.
    get_path(entry);

    printf("\nSolution: \n");
    // printf("%i", found_size);
    for(int s = 0; s < SRFC; s++)
        for(int i = 0; i < c; i++)
            for(int j = 0; j < r; j++)
                if (path_found[s] == &tiles[i][j]) {
                    printf("\t · case[%i][%i]", i, j);
                    if (i == entry.x && j == entry.y)
                        printf(" (départ)");
                    else if (i == xt.x && j == xt.y)
                        printf(" (arrivé)");
                    printf("\n");
                    break;
                }
    printf("\n");
}

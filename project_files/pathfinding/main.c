#include "tile.h"
#include "path_finder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <err.h>

// Only for "square" mazes.

int main() {

    char *filename = "../neuralNetwork/output.csv";

    FILE *fp;

    int count_lines = 0;

    char chr;

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
        return 1;
    }

    // Extract character from file and store in chr.

    chr = getc(fp);

    while (chr != EOF)

    {
        // Count whenever new line is encountered.

        if (chr == '\n') count_lines++;

        // Get next character from file.

        chr = getc(fp);
    }

    fclose(fp); // Close the file.

    fp = fopen(filename, "r");

    int r = (int) sqrt(count_lines);  // r : total number of line.

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

    struct point entry = {.x = 0, .y = 0};

    // Found number of potential entrance or exit.
    int nmbrIO = 0;

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

        /* 
         * Try to auto-detect entry and exit points ("IO tile") of the maze.
         * If a tile is on a side of the maze and has an outward
         * opening then this tile is considered as an "IO tile".
        */

        // If we have an IO on the left side of the maze.
        if (i/r == 0) {
            switch(number) {
                case 5: case 8: case 10: case 11:
                case 13: case 14: case 15:
                    if (nmbrIO == 0) {
                        entry.x = 0;
                        entry.y = i%r;
                    }
                    else if (nmbrIO == 1) {
                        xt.x = 0;
                        xt.y = i%r;
                    }
                    nmbrIO++;
                    // printf("[0][%i] (number: %i)\n", i%r, number);
                    break;
                default: break;
            }
        }

        // If we have an IO on the right side of the maze.
        else if (i/r == c - 1) {
            switch(number) {
                case 6: case 7: case 10: case 11:
                case 12: case 13: case 15:
                    if (nmbrIO == 0) {
                        entry.x = c - 1;
                        entry.y = i%r;
                    }
                    else if (nmbrIO == 1) {
                        xt.x = c - 1;
                        xt.y = i%r;
                    }
                    nmbrIO++;
                    // printf("[%i][%i] (number: %i)\n", c - 1, i%r, number);
                    break;
                default: break;
            }
        }
       
        // If we have an IO on the top side of the maze.
        if (i%r == 0) {
            switch(number) {
                case 5: case 6: case 9: case 11:
                case 12: case 14: case 15:
                    if (nmbrIO == 0) {
                        entry.x = i/r;
                        entry.y = 0;
                    }
                    else if (nmbrIO == 1) {
                        xt.x = i/r;
                        xt.y = 0;
                    }
                    nmbrIO++;
                    // printf("[%i][0] (number: %i)\n", i/r, number);
                    break;
                default: break;
            }
        }

        // If we have an IO on the bottom side of the maze.
        else if (i%r == r - 1) {
            switch(number) {
                case 7: case 8: case 9: case 12:
                case 13: case 14: case 15:
                    if (nmbrIO == 0) {
                        entry.x = i/r;
                        entry.y = r - 1;
                    }
                    else if (nmbrIO == 1) {
                        xt.x = i/r;
                        xt.y = r - 1;
                    }
                    nmbrIO++;
                    // printf("[%i][%i] (number: %i)\n", i/r, r - 1, number);
                    break;
                default: break;
            }
        }

        // We fill tiles column by column.
        tiles[i/r][i%r].dgr = degree;
        tiles[i/r][i%r].traveled = 0;

        tiles[i/r][i%r].accs = malloc(sizeof(enum direction) * degree);
        for(int j = 0; j < degree; j++)
            tiles[i/r][i%r].accs[j] = arr[j];
    }

    if (nmbrIO != 2) {
        
        if (nmbrIO > 2)
            printf("Erreur. nmbrIO > 2.\n");
        else
            printf("Erreur. nmbrIO < 2.\n");
        
        errx(EXIT_FAILURE, "Indiquer manuellement au programme\
                ou sont les points d'entree et de sortie\
                permettrait au programme de continuer.");
        
        // We could do a scanf to manually get entry and exit points.
    }

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
                    /*
                    if (i == entry.x && j == entry.y)
                        printf(" (point A)");
                    else if (i == xt.x && j == xt.y)
                        printf(" (point B)");
                    */
                    printf("\n");
                    break;
                }
    printf("\n");
}

#include "trncn.h"
#include "chemin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    char *filename = "neuralNetwork/output.csv";
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: could not open file %s", filename);
        return 1;
    }

    int n; // total number of case.
    int r; // total number of line.
    int c; // total number of column.

    SIZE = n; // We copie n in SIZE.

    trncns = malloc(sizeof(struct trncn *) * c);
    for (int i = 0; i < c; i++) {
        trncns[i] = malloc(sizeof(struct trncn) * r);
    }
    
    // reading line by line, max 256 bytes
    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];

    for (int i = 0; fgets(buffer, MAX_LENGTH, fp); i++) {
        int number = atoi(buffer);
        int degre;
        int arr[4];
        switch (number) {
            case 0:
                degre = 0;
                break;
            case 1:
                degre = 1;
                arr[0] = LEFT;
                break;
            case 2:
                degre = 1;
                arr[0] = UP;
                break;
            case 3:
                degre = 1;
                arr[0] = RIGHT;
                break;
            case 4:
                degre = 1;
                arr[0] = DOWN;
                break;
            case 5:
                degre = 2;
                arr[0] = LEFT;
                arr[1] = UP;
                break;
            case 6:
                degre = 2;
                arr[0] = UP;
                arr[1] = RIGHT;
                break;
            case 7:
                degre = 2;
                arr[0] = RIGHT;
                arr[1] = DOWN;
                break;
            case 8:
                degre = 2;
                arr[0] = DOWN;
                arr[1] = LEFT;
                break;
            case 9:
                degre = 3;
                arr[0] = LEFT;
                arr[1] = UP;
                arr[2] = RIGHT;
                break;
            case 10:
                degre = 3;
                arr[0] = UP;
                arr[1] = RIGHT;
                arr[2] = DOWN;
                break;
            case 11:
                degre = 3;
                arr[0] = RIGHT;
                arr[1] = LEFT;
                arr[2] = DOWN;
                break;
            case 12:
                degre = 3;
                arr[0] = DOWN;
                arr[1] = LEFT;
                arr[2] = UP;
                break;
            case 13:
                degre = 4;
                arr[0] = LEFT;
                arr[1] = UP;
                arr[2] = RIGHT;
                arr[3] = DOWN;
                break;
        }

        trncns[i/n][i%n].dgr = degre;
        trncns[i/n][i%n].accs = malloc(sizeof(int) * degre);
        trncns[i/n][i%n].parcourue = 0;
        for(int i = 0; i < degre; i++)
            trncns[i/n][i%n].accs[i] = arr[i];
    }

    // We create the exit of our maze test.
    srt.x = 0;
    srt.y = 4;

    // Where to stock the solution of the maze.
    chemin_trouve = malloc(sizeof(struct trncn *) * 15);
    memset(chemin_trouve, 0, sizeof(struct trncn *));

    // We choose an entry point.
    struct point entry = {.x = 0, .y = 0}; 

    // We run our solver.
    get_chemin(entry);

    printf("\nSolution: \n");
    // printf("%i", found_size);
    for(int s = 0; s < SIZE; s++) {
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 5; j++) {
                if (chemin_trouve[s] == &trncns[i][j]) {
                    printf("\t · case[%i][%i]", i, j);
                    if (i == entry.x && j == entry.y)
                        printf(" (départ)");
                    else if (i == srt.x && j == srt.y)
                        printf(" (arrivé)");
                    printf("\n");
                    break;
                }
            }
        }
    }
    printf("\n");
}

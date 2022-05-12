#include "trncn.h"
#include "chemin.h"
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

    int r = 5; // total number of line.

    // On a un carre donc c = r.
    int c = r; // total number of column.
    int n = r * c; // total number of case.

    SIZE = n; // We copie n in SIZE.

    trncns = malloc(sizeof(struct trncn *) * c);
    for (int i = 0; i < c; i++) {
        trncns[i] = malloc(sizeof(struct trncn) * r);
    }
    
    // reading line by line, max 256 bytes
    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];

    // #### D'ici a 
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
                degre = 2;
                arr[0] = UP;
                arr[1] = DOWN;
                break;
            case 10:
                degre = 2;
                arr[0] = LEFT;
                arr[1] = RIGHT;
                break;
            case 11:
                degre = 3;
                arr[0] = LEFT;
                arr[1] = UP;
                arr[2] = RIGHT;
                break;
            case 12:
                degre = 3;
                arr[0] = UP;
                arr[1] = RIGHT;
                arr[2] = DOWN;
                break;
            case 13:
                degre = 3;
                arr[0] = RIGHT;
                arr[1] = LEFT;
                arr[2] = DOWN;
                break;
            case 14:
                degre = 3;
                arr[0] = DOWN;
                arr[1] = LEFT;
                arr[2] = UP;
                break;
            case 15:
                degre = 4;
                arr[0] = LEFT;
                arr[1] = UP;
                arr[2] = RIGHT;
                arr[3] = DOWN;
                break;
        }

        // printf("x : %i\ny: %i\n(%i)\n", i/r, i%c, number);
        
        // On remplit trncns colonne par colonne.
        trncns[i/r][i%c].dgr = degre;
        trncns[i/r][i%c].parcourue = 0;
       
        trncns[i/r][i%c].accs = malloc(sizeof(enum direction) * degre);
        // printf("Case [x: %i][y: %i] :\n", i/r, i%c);
        for(int j = 0; j < degre; j++) {
            trncns[i/r][i%c].accs[j] = arr[j];
            // printf("Possibilite %i: %i\n", j, trncns[i/r][i%c].accs[j]);
        }
        // a la, c'est ok.
    }

    // We create the exit of our maze test.
    srt.x = 2;
    srt.y = 4;

    // Where to stock the solution of the maze.
    chemin_trouve = malloc(sizeof(struct trncn *) * n);
    memset(chemin_trouve, 0, sizeof(struct trncn *));

    // We choose an entry point.
    struct point entry = {.x = 2, .y = 0}; 

    // We run our solver.
    get_chemin(entry);

    printf("\nSolution: \n");
    // printf("%i", found_size);
    for(int s = 0; s < n; s++) {
        for(int i = 0; i < c; i++) {
            for(int j = 0; j < r; j++) {
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

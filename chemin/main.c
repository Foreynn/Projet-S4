#include "trncn.h"
#include "chemin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

    // Creation of cases for our test.
   
    SIZE = 15;

    trncns = malloc(sizeof(struct trncn *) * 3);
    for(int i = 0; i < 3; i++) {
        trncns[i] = malloc(sizeof(struct trncn) * 5);
    }
    
    struct trncn c0 = {
        .dgr = 1,
        .accs = malloc(sizeof(int)),
        .parcourue = 0
    };
    c0.accs[0] = RIGHT;
    trncns[0][0] = c0;
    
    struct trncn c3 = {
        .dgr = 1,
        .accs = malloc(sizeof(int)),
        .parcourue = 0
    };
    c3.accs[0] = DOWN;
    trncns[0][1] = c3;
    
    struct trncn c6 = {
        .dgr = 2,
        .accs = malloc(sizeof(int) * 3),
        .parcourue = 0
    };
    c6.accs[0] = UP;
    c6.accs[1] = RIGHT;
    c6.accs[2] = DOWN;
    trncns[0][2] = c6;
    
    struct trncn c9 = {
        .dgr = 3,
        .accs = malloc(sizeof(int) * 3),
        .parcourue = 0
    };
    c9.accs[0] = UP;
    c9.accs[1] = RIGHT;
    c9.accs[2] = DOWN;
    trncns[0][3] = c9;
    
    struct trncn c12 = {
        .dgr = 1,
        .accs = malloc(sizeof(int)),
        .parcourue = 0
    };
    c12.accs[0] = UP;
    trncns[0][4] = c12;
    
    struct trncn c1 = {
        .dgr = 2,
        .accs = malloc(sizeof(int) * 2),
        .parcourue = 0
    };
    c1.accs[0] = LEFT;
    c1.accs[1] = DOWN;
    trncns[1][0] = c1;
    
    struct trncn c4 = {
        .dgr = 2,
        .accs = malloc(sizeof(int) * 2),
        .parcourue = 0
    };
    c4.accs[0] = UP;
    c4.accs[1] = RIGHT;
    trncns[1][1] = c4;
    
    struct trncn c7 = {
        .dgr = 1,
        .accs = malloc(sizeof(int)),
        .parcourue = 0
    };
    c7.accs[0] = LEFT;
    trncns[1][2] = c7;
    
    struct trncn c10 = {
        .dgr = 2,
        .accs = malloc(sizeof(int) * 2),
        .parcourue = 0
    };
    c10.accs[0] = LEFT;
    c10.accs[1] = RIGHT;
    trncns[1][3] = c10;
    
    struct trncn c13 = {
        .dgr = 1,
        .accs = malloc(sizeof(int)),
        .parcourue = 0
    };
    c13.accs[0] = RIGHT;
    trncns[1][4] = c13;
    
    struct trncn c2 = {
        .dgr = 1,
        .accs = malloc(sizeof(int)),
        .parcourue = 0
    };
    c2.accs[0] = DOWN;
    trncns[2][0] = c2;
    
    struct trncn c5 = {
        .dgr = 3,
        .accs = malloc(sizeof(int) * 3),

        .parcourue = 0
    };
    c5.accs[0] = UP;
    c5.accs[1] = LEFT;
    c5.accs[2] = DOWN;
    trncns[2][1] = c5;
    
    struct trncn c8 = {
        .dgr = 2,
        .accs = malloc(sizeof(int) * 2),
        .parcourue = 0
    };
    c8.accs[0] = UP;
    c8.accs[1] = DOWN;
    trncns[2][2] = c8;
    
    struct trncn c11 = {
        .dgr = 3,
        .accs = malloc(sizeof(int) * 3),
        .parcourue = 0
    };
    c11.accs[0] = LEFT;
    c11.accs[1] = UP;
    c11.accs[2] = DOWN;
    trncns[2][3] = c11;
    
    struct trncn c14 = {
        .dgr = 2,
        .accs = malloc(sizeof(int) * 2),
        .parcourue = 0
    };
    c14.accs[0] = UP;
    c14.accs[1] = LEFT;
    trncns[2][4] = c14;

    // We create the exit of our maze test.
    srt.x = 0;
    srt.y = 4;

    // Maze generated!

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

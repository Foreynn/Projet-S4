#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <math.h>
#include <string.h>
#include "pixel_operations.h"
#include "tile.h"
#include "pf_aux.h"
/*
struct tile **tiles;
struct tile **path_found;
int found_size;
struct point {int x; int y;};
struct point xt;    // xt : exit.
int main();
struct point[] solution;
*/

SDL_Surface* pathfinding(SDL_Surface* img);

#endif

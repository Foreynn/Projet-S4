#ifndef SIZE_REDUCTION_H
#define SIZE_REDUCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <math.h>
#include "pixel_operations.h"

SDL_Surface* size_reduction(SDL_Surface * image, int w, int h);

#endif
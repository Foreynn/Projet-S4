#ifndef IMGTOARRAY_H_
#define IMGTOARRAY_H_
#define _GNU_SOURCE
#include <stdio.h>
#include <SDL/SDL_image.h>
#include <err.h>
#include <string.h>

#include "pixel_operations.h"

double* ImageToList(int imageNumber);

#endif

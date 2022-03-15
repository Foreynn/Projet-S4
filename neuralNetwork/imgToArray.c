#include <err.h>
#include <string.h>
#include "imgToArray.h"

void init_sdl()
{
    // Init only the video part.
    // If it fails, die with an error message.
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
}

SDL_Surface* load_image(char *path)
{
    SDL_Surface *img;

    // Load an image using SDL_image with format detection.
    // If it fails, die with an error message.
    img = IMG_Load(path);
    if (!img)
        errx(3, "can't load %s: %s", path, IMG_GetError());

    return img;
}

void SDL_FreeSurface(SDL_Surface *surface);

// la fonction qui transforme l'image en list de 0 et 1
double* ImageToList(double imageNumber)
{
    char path[23] = {'.','.','/','c','u','t','_','i','m','a','g','e','s','/','0','0','0','0','.','b','m','p',0};
    //char* path = "../cut_images/0000.png";

    init_sdl();
    SDL_Surface *img;
    double* list = calloc(9*9, sizeof(double));

    path[14] = 48 + (int)imageNumber / 1000;        // chiffre des milliers de l'image 
    path[15] = 48 + (int)imageNumber / 100 % 10;    // chiffre des centaines de l'image
    path[16] = 48 + (int)imageNumber / 10 % 10;     // chiffre des dizaines de l'image
    path[17] = 48 + (int)imageNumber % 10;          // chiffre des unités de l'image

    img = load_image(path);
    Uint32 pixel = 0;
    Uint8 r = 0, g = 0, b = 0;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            pixel = get_pixel(img, j, i);
            SDL_GetRGB(pixel, img->format, &r, &g, &b);
            list[j+(i*9)] = (r < 50 && g < 50 && b < 50) ? 0.5 : -0.5;
        }
    }


    SDL_FreeSurface(img);
    return list;
}
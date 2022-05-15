#include "imgToArray.h"

void SDL_FreeSurface(SDL_Surface *surface);

// la fonction qui transforme l'image en list de 0 et 1
double* ImageToList(double imageNumber)
{
    char path[23] = {'c','u','t','_','i','m','a','g','e','s','/','0','0','0','0','.','b','m','p',0};
    //char* path = "../cut_images/0000.png";

    init_sdl();
    SDL_Surface *img;
    double* list = calloc(9*9, sizeof(double));

    path[11] = 48 + (int)imageNumber / 1000;        // chiffre des milliers de l'image 
    path[12] = 48 + (int)imageNumber / 100 % 10;    // chiffre des centaines de l'image
    path[13] = 48 + (int)imageNumber / 10 % 10;     // chiffre des dizaines de l'image
    path[14] = 48 + (int)imageNumber % 10;          // chiffre des unités de l'image

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

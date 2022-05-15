#include "imgToArray.h"

void SDL_FreeSurface(SDL_Surface *surface);

// la fonction qui transforme l'image en list de 0 et 1
double* ImageToList(int imageNumber)
{
    char* path;
//    char* path = "project_files/cut_images/0000.png";

    asprintf(&path, "project_files/cut_images/%04d.bmp", imageNumber);

    init_sdl();
    SDL_Surface *img;
    double* list = calloc(9*9, sizeof(double));

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

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <string.h>
#include "pixel_operations.h"

void init_sdl()
{
    // Init only the video part.
    // If it fails, die with an error message.
    if(SDL_Init(SDL_INIT_VIDEO) == -1)
        errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());    
}

SDL_Surface* load_image(char *path)
{
    //An image is represented by a surface
    SDL_Surface *img;

    //We transform the image to SDL_Surface 
    // If it fails, die with an error message.
    img = IMG_Load(path);
    if (!img)
        errx(3, "can't load %s: %s", path, IMG_GetError());

    return img;
}

// This function returns the size of a case (the width or height since it's
// a square) and the size of the border int the borderSize argument.
unsigned int getDimension(SDL_Surface *img, int *borderSize)
{
    unsigned int size = 0;
    unsigned int white = 0;

    while (white < 2)
    {
        Uint32 pixel = get_pixel(img, size, size);

        Uint8 r, g, b;
        SDL_GetRGB(pixel, img->format, &r, &g, &b);

        if (white == 0)
        {
            if (r == 255 && g == 255 && b == 255)
                white++;

            (*borderSize)++;
        }

        if (white == 1 && r == 0 && g == 0 && b == 0)
            white++;

        size++;
    }

    return size;
}

// This function saves an image (the case corresponding to the given
// coordinates) to a file named cut_images_XXXX.bmp.
void saveImg(SDL_Surface *img, int x, int y, int size, char* name)
{
    SDL_Rect srcrect = { x, y, size, size };
    SDL_Surface *cut_image = SDL_CreateRGBSurface(0, size, size, 32, 0, 0, 0, 0);

    SDL_BlitSurface(img, &srcrect, cut_image, NULL);

    //TODO RESIZE IMAGE TO 9x9.

    SDL_SaveBMP(cut_image, name);
}

SDL_Surface *display_image(SDL_Surface *img)
{
    SDL_Surface *screen;
    //it's through the window that we can display the image/surface
    //Set the window to the same size as the image/surface
    screen = SDL_SetVideoMode(1920,1080, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
    if (screen == NULL)
    {
        //handle error
        errx(1,"Couldn' set %dx%d video mode : %s\n",img->w, img->h,SDL_GetError());
    }
    //We color the screen in blue-green
    if ( SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 17, 206, 112)) != 0)
        errx(1,"Could not color the screen : %s\n", SDL_GetError());

    //We paste the SDL_Surface representing img on SDL_Surface representing the screen 
    if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

    //We update the screen
    SDL_Flip(screen);
    return screen;

}

void wait_for_keypressed()
{
    SDL_Event event;

    // Wait for a key to be down.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYDOWN);

    // Wait for a key to be up.
    do
    {
        SDL_PollEvent(&event);
    } while(event.type != SDL_KEYUP);
}

int main()
{
    SDL_Surface *screen;
    SDL_Surface *image_surface;

    init_sdl();

    image_surface = load_image("image/maze5x5.png");
    screen = display_image(image_surface);

    int borderSize = 0;
    unsigned int size = getDimension(image_surface, &borderSize);

    saveImg(image_surface, 1, 1, size, "cut_images_0001.bmp");

    printf("The dimension of a case is: %ux%u pixels.\nThe border is %i pixels wide\n", size, size, borderSize);

    wait_for_keypressed();
    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen);
    SDL_Quit();
}

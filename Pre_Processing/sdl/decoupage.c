#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <stdlib.h>
#include <stdio.h>
#include <err.h>
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

//This functions allow me to get the dimension (width*height) of one case of the maze
/*We travel the first line of the image (maze) and we must to detect the entrance
  so when the pixel is white, considering this we get the dimension of one case 
  by detect the first pixel white and the last pixel white before the next pixel black
 */
unsigned int getDimension(SDL_Surface *img)
{

    unsigned int res = 0;
    unsigned int width = img->w;
    unsigned int i = 0;
    unsigned int firstWhite = 0;
    // unsigned lastWhite;
    int found = 0;
    //unsigned firstpos;
    Uint8 total =0;
    //Travel only the first line of maze because the entrance is in first line
    while ((i < width) && (found == 0)) 
    {   
        Uint32 pixel = get_pixel(img,i,0);
        Uint8 r,g,b;
        SDL_GetRGB(pixel, img->format, &r, &g, &b);
        total = r;
        total = g;
        total = b;
        //pixel = SDL_MapRGB(img->format, r, g, b); 
        //     printf("p[%u][0] = " "%" PRIu8 "\n", i, total);

        if (total == 255) //pixel white means, r=g=b = 255
        { 
            firstWhite = i;
            while (total != 0)
            {
                pixel = get_pixel(img, firstWhite, 0);
                SDL_GetRGB(pixel, img->format, &r, &g, &b);
                total = r;
                firstWhite++;
            }
            res = (firstWhite - 1) - i;       
            found = 1;
            //printf("the first pixel white is in (%u,0)\n", firstWhite); 
        }

        i++;
    }

    return res;
}



SDL_Surface *extraction_from_image(SDL_Surface *img)
{
    SDL_Rect srcrect;
    SDL_Surface *case1;
    case1 = SDL_CreateRGBSurface(0, 14,14, 32,0,0,0,0);

    srcrect.x = 0;
    srcrect.y = 0;
    srcrect.w = 14;
    srcrect.h = 14;

    if (SDL_BlitSurface(img, &srcrect, case1, NULL) != 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());
    //SDL_UpdateRect(case1, 0,0, 14,14);
    SDL_SaveBMP(case1, "case1.bmp");
    return case1;
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
    unsigned int a = getDimension(image_surface);
    printf("the dimension of one case is : %ux%u\n", a,a);

    wait_for_keypressed();
    SDL_FreeSurface(image_surface);
    SDL_FreeSurface(screen);
    SDL_Quit();
}


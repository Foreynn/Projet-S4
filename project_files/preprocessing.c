#include "preprocessing.h"
#include "pixel_operations.h"

//! Resize functions (compress, size_reduciton)
Uint32 compress(SDL_Surface *image, int w, int h, double ratio_w, double ratio_h)
{
    int nb_black = 0;

    for (int x = ratio_w * w; x < ratio_w * (w+1); x++)
    {
        for (int y = ratio_h * h; y < ratio_h * (h+1); y++)
        {
            Uint32 pixel = get_pixel(image, x, y);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image->format, &r, &g, &b);
            if (r != 255 || g != 255 || b != 255)
                nb_black++;
        }
    }

    if (nb_black > 0)
        return SDL_MapRGBA(image->format, 0, 0, 0, 0);
    return SDL_MapRGBA(image->format, 255, 255, 255, 0);
}

SDL_Surface* size_reduction(SDL_Surface * image, double W, double H)
{
    double og_width = image->w;
    double og_height = image->h;

    double ratio_w = og_width / W;
    double ratio_h = og_height / H;

    SDL_Surface *new_image = SDL_CreateRGBSurface(0, W, H, 32, 255, 255, 255, 0);
    for (int x = 0; x < W; x++)
    {
        for (int y = 0; y < H; y++)
        {
            Uint32 pixel = compress(image, x, y, ratio_w, ratio_h);
            put_pixel(new_image, x, y, pixel);
        }
    }
    
    return new_image;
}


//! Segmentation functions (getDimension)
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
            else
                (*borderSize)++;
        }

        if (white == 1 && r == 0 && g == 0 && b == 0)
            break;

        size++;
    }

    return size;
}


//! Preprocessing functions (blackAndWhite, saveImg)
void blackAndWhite(SDL_Surface* image_surface)
{
    int width = image_surface->w;
    int height = image_surface->h;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            Uint32 pixel = get_pixel(image_surface, i, j);
            Uint8 r, g, b;
            SDL_GetRGB(pixel, image_surface->format, &r, &g, &b);
            if (r != 255 && g != 255 && b != 255)
                r = g = b = 0;
            pixel = SDL_MapRGB(image_surface->format, r, g, b);
            put_pixel(image_surface, i, j, pixel);
        }
    }
}

void saveImg(SDL_Surface *img, int x, int y, int size, char* name)
{
    SDL_Rect srcrect = { x, y, size, size };
    SDL_Surface *cut_image = SDL_CreateRGBSurface(0, size, size, 32, 0, 0, 0, 0);

    SDL_BlitSurface(img, &srcrect, cut_image, NULL);

    cut_image = size_reduction(cut_image, 9, 9);

    blackAndWhite(cut_image);

    SDL_SaveBMP(cut_image, name);
    free(cut_image);
}


//! Main function: gets an inmage of a maze and cuts it into small 9x9 black and white images.
unsigned int pre_processing(SDL_Surface *image_surface)
{
    int borderSize = 0;
    unsigned int size = getDimension(image_surface, &borderSize);

    int n = 0;
    for (int i = borderSize/2; i < image_surface->h-1; i += size)
    {
        for (int j = borderSize/2; j < image_surface->w-1; j += size)
        {
            char* name;
            asprintf(&name, "cut_images/%04d.bmp", n);

            saveImg(image_surface, i, j, size, name);
            n++;
        }
    }

    return image_surface->w/size;
}

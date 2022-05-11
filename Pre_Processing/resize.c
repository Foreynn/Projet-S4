#include "resize.h"

// Load image
SDL_Surface* load_image(char *path){
    SDL_Surface *image;
    image = IMG_Load(path);

    if (!image){
        errx(1,"Error: cannot load %s due to %s.\n", path, IMG_GetError());
    }

    return image;
}

// clamp function
int clamp(int value, int lower_bound, int upper_bound){
    if (value < lower_bound){
        return lower_bound;
    }
    if (value>upper_bound)
    {
        return upper_bound;
    }
    return value;

}

Uint32 compress(SDL_Surface * image, int w, int h, int ratio_w, int ratio_h){

    int nb_black = 0;
    int nb_white = 0;

    for (int x = ratio_w*w; x<ratio_w*(w+1); x++){
        for (int y = ratio_h*h; y<ratio_h*(h+1); y++){
            Uint32 pixel = get_pixel(image,x,y);
            Uint8 r, g, b;
            SDL_GetRGB(pixel,image->format,&r,&g,&b);
            if (r==0){
                nb_black++;
                continue;
            }
            nb_white++;
        }
    }
    if (nb_white < 0.78*nb_black){
        return SDL_MapRGBA(image->format,0,0,0,0);
    }
    return SDL_MapRGBA(image->format,255,255,255,0);
}

// Size reduce function
SDL_Surface* size_reduction(SDL_Surface * image, int W, int H){
    int og_width = image->w;
    int og_height = image->h;

    int ratio_w = og_width / W;
    int ratio_h = og_height / H;

    SDL_Surface * new_image = SDL_CreateRGBSurface(0, W, H, 32, 255, 255, 255, 0);
    for (int x = 0; x<W; x++){
        for (int y = 0; y<H; y++){
            Uint32 pixel = compress(image, x, y, ratio_w, ratio_h);
            put_pixel(new_image,x,y,pixel);
        }
    }
    
    return new_image;
}
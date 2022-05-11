#include <stdlib.h>
#include <string.h>
#include <err.h>
#include "tile.h"
#include <stdio.h>

/* Coordinate reference.
   x0 x1 x2 →
   y0 
   y1 
   y2 
   ↓ 
   */


/* SRFC is an abreviation for SURFACE.
 * (We've merely kept the consonants.) */
int SRFC;

struct tile **tiles;
struct tile **path_found;
int found_size;

struct point {int x; int y;};
struct point xt;

int __get_path(struct point entry, int beginning) {

    struct tile *t = &(tiles[entry.x][entry.y]);
    t->traveled = 1;

    if (xt.x == entry.x && xt.y == entry.y)
        return 1;   // If we've arrived at the xt.

    int dgr = t->dgr;
    if (dgr == 1 && !beginning) 
        return 0;   // If we are in a dead end.

    enum direction *access = t->accs;

    for(int i = 0; i < dgr; i++) {
        
        struct point new_entry = {
            .x = entry.x,
            .y = entry.y,
        };
        
        switch(access[i]) {
            case 0: new_entry.y--;
                    break;
            case 1: new_entry.y++;
                    break;
            case 2: new_entry.x--;
                    break;
            case 3: new_entry.x++;
                    break;
        }
        
        if (new_entry.x < 0 || new_entry.y < 0)
            errx(0, "Erreur : direction de tronçon d'entrée.");

        if (tiles[new_entry.x][new_entry.y].traveled == 0) {
            
            // If the adjacent tile has never been visited.
            
            beginning = 0;

            if (__get_path(new_entry, beginning) == 1) {
                
                /* If we are on the way to the xt,
                 * we add the tile to path_found.*/
                
                path_found[SRFC-1 - found_size] = &(tiles[new_entry.x][new_entry.y]);
                found_size++;
                
                return 1;
            }
        }
    }

    /* If we have not returned 1,
     * then we return 0. */

    beginning = 0;
    return 0;
}


/* Before calling get_path, path_found 
 * should have enough reserved memory. */

void get_path(struct point entry) {

    found_size = 0;
    int beginning = 1;

    __get_path(entry, beginning);

    if (found_size > 0) {

        // We add the starting tile.

        path_found[SRFC - 1 - found_size] = &(tiles[entry.x][entry.y]);
        found_size++;
    }

}

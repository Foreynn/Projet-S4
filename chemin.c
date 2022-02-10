#include <stdlib.h>
#include <string.h>
#include "trncn.h"

/* Coordinate reference.
   : x0 x1 x2 →
y0 :
y1 :
y2
 ↓ :
*/

int SIZE = 1000; // The number of section.
struct trncn **trncns;
struct trncn **chemin_trouve;
int found_size;

struct point {int x; int y;};
struct point srt; // sortie

int __get_chemin(struct point entry) {
    
    struct trncn *t = &(trncns[entry.x][entry.y]);
    t->parcourue = 1;
    
    if (srt.x == entry.x && srt.y == entry.y) {
    // if we've arrived at the exit
        return 1;
    }

    int dgr = t->dgr;
    if (dgr == 1) {
    // if dead end
        return 0;
    }
    enum direction *accs = t->accs;
    
    for(int i = 0; i < dgr; i++) {
        struct point new_entry = {
            .x = entry.x,
            .y = entry.y,
        };
        switch(accs[i]) {
            case 0: new_entry.y--;
                break;
            case 1: new_entry.y++;
                break;
            case 2: new_entry.x--;
                break;
            case 3: new_entry.x++;
                break;
        }
        if (trncns[new_entry.x][new_entry.y].parcourue == 0)
            // if the adjacent section has never been visited
            if (__get_chemin(new_entry) == 1) {
            // if we are on the way to the exit
            // we add the section to chemin_trouve
                chemin_trouve[SIZE-1 - found_size] = &(trncns[new_entry.x][new_entry.y]);
                found_size++;
                return 1;
            }
    }

    // if we have not returned 1
    // then we return 0
    return 0;
}

// Before calling get_chemin, chemin_trouve
// should have enough reserved memory.

void get_chemin(struct point entry) {
    found_size = 0;
    __get_chemin(entry);
    struct trncn **tmp = malloc(found_size * sizeof(struct trncn *));
    memcpy(tmp, chemin_trouve + SIZE-1-found_size, found_size);
    free(chemin_trouve);
    chemin_trouve = tmp;
}

int main() {
    chemin_trouve = malloc(SIZE * sizeof(struct trncn *));
    // get_chemin();
    return 1;
}

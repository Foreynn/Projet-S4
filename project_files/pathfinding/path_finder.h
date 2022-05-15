#ifndef PATH_FINDER_H
#define PATH_FINDER_H

/* SRFC is an abreviation for SURFACE.
 * (We've merely kept the consonants.) */
unsigned long long SRFC;

struct tile **tiles;
struct tile **path_found;
unsigned long long found_size;
struct point {int x; int y;};
struct point xt;    // xt : exit.
void get_path(struct point entry);

#endif

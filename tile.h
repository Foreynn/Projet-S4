#ifndef TILE_H
#define TILE_H

enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct tile {
    enum direction *accs;   // accs : access.
    int dgr;                // degree of freedom : total number of access.
    int traveled;          // boolean.
};

#endif

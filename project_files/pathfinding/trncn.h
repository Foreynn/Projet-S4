#ifndef TRNCN_H
#define TRNCN_H

enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// trncn : tronçon
struct trncn {
    // accs : accès
    enum direction *accs;
    int dgr; // degré de liberté : nombre d'accès
    int parcourue; // booléen
};

#endif

enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// trncn : tronçon
struct trncn {
    // accs : accès
    enum direction accs;
    int parcourue; // booléen
};

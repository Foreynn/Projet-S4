#include "project_files/gui/gui.h"
#include "project_files/neuralnetwork/model.h"
#include "project_files/pathfinding/pathfinding.h"
#include "project_files/preprocessing/preprocessing.h"

void main(void)
{
    //! Exemples, pas le vrai code.
    gui(); //* Fait tourner le code en dessous grâce aux boutons

    //? Variables utiles
    SDL_Surface* image;
    unsigned int entrance_coords[2];
    unsigned int exit_coords[2];
    unsigned int *solution;

    size_t size = pre_processing(image); //* Crée les images decoupées dans cut_images et retourne la taille du labyrinthe.
    neuralNetwork(size); //* Enregistre les valeurs des cases dans output.csv
    solution = pathfinding(size, entrance_coords, exit_coords); //* Eregistre le chemin dans la liste solution
    tracePath(solution); //* Trace le chemin sur le labyrinthe
}

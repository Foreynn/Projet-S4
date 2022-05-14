#include <gtk/gtk.h>
#include "../neuralnetwork/model.h"
#include "../pathfinding/pathfinding.h"
#include "../preprocessing/preprocessing.h"

void solve(SDL_Surface* image)
{
    size_t size = pre_processing(image); //* Crée les images decoupées dans cut_images et retourne la taille du labyrinthe.
    neuralNetwork(size); //* Enregistre les valeurs des cases dans output.csv
    pathfinding(size, entrance_coords, exit_coords); //* Eregistre le chemin dans un fichier solution
    // tracePath(solution); //* Trace le chemin sur le labyrinthe
}

// Main function.
int main (int argc, char *argv[])
{
    // Initializes GTK.
    gtk_init(NULL, NULL);

    // Loads the UI description and builds the UI.
    // (Exits if an error occurs.)
    GtkBuilder* builder = gtk_builder_new();
    GError* error = NULL;
    if (gtk_builder_add_from_file(builder, "main.glade", &error) == 0)
    {
        g_printerr("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }

    // Runs the main loop.
    gtk_main();

    // Exits.
    return 0;
}

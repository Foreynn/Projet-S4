#include <gtk/gtk.h>
#include "model.h"
#include "pathfinding/pathfinding.h"
#include "preprocessing.h"
#include "pixel_operations.h"

SDL_Surface* image;
char* file_name;

char save = 0;

void on_SolveButton_clicked(GtkButton* SolveButton)
{
    image = load_image(file_name);

    size_t size = pre_processing(image); //* Crée les images decoupées dans cut_images et retourne la taille du labyrinthe.
    neuralNetwork(size); //* Enregistre les valeurs des cases dans output.csv
    pathfinding(size); //* Eregistre le chemin dans un fichier solution
}

void on_SaveButton_clicked(GtkButton* SaveButton)
{
    save = 1;
}

void on_FileChooser_file_set(GtkFileChooserButton* FileChooserButton, GtkWidget* ImageSurface)
{
    file_name = (char *)gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(FileChooserButton));

    gtk_image_set_from_file(GTK_IMAGE(ImageSurface), file_name);
}

void on_ExitButton_clicked()
{
    gtk_main_quit();
}

// Main function.
int main (int argc, char** argv)
{
    gtk_init(&argc, &argv);

    GtkBuilder* builder = gtk_builder_new_from_file("main.glade");
    GtkWidget* AppWindow = GTK_WIDGET(gtk_builder_get_object(builder, "AppWindow"));

    g_signal_connect(AppWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(builder, NULL);

    GtkWidget* FileChooser = GTK_WIDGET(gtk_builder_get_object(builder, "FileChooser"));
    GtkWidget* SolveButton = GTK_WIDGET(gtk_builder_get_object(builder, "SolveButton"));
    GtkWidget* SaveButton = GTK_WIDGET(gtk_builder_get_object(builder, "SaveButton"));
    GtkWidget* ExitButton = GTK_WIDGET(gtk_builder_get_object(builder, "ExitButton"));
    GtkWidget* ImageSurface = GTK_WIDGET(gtk_builder_get_object(builder, "ImageSurface"));

    gtk_widget_show(AppWindow);

    g_signal_connect(SolveButton, "clicked", G_CALLBACK(on_SolveButton_clicked), NULL);
    g_signal_connect(SaveButton, "clicked", G_CALLBACK(on_SaveButton_clicked), NULL);
    g_signal_connect(FileChooser, "file-set", G_CALLBACK(on_FileChooser_file_set), ImageSurface);
    g_signal_connect(ExitButton, "clicked", G_CALLBACK(on_ExitButton_clicked), NULL);


    gtk_main();

    if (save == 0)
    {
        remove("solution.txt");
    }

    return 0;
}

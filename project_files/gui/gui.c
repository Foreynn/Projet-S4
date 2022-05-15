#include <gtk/gtk.h>
#include "../neuralnetwork/model.h"
#include "../pathfinding/pathfinding.h"
#include "../preprocessing/preprocessing.h"

SDL_Surface* image;
gchar* file_name;

void on_SolveButton_clicked(GtkButton* SolveButton)
{
    image = IMG_Load(file_name);

    size_t size = pre_processing(image); //* Crée les images decoupées dans cut_images et retourne la taille du labyrinthe.
    neuralNetwork(size); //* Enregistre les valeurs des cases dans output.csv
    pathfinding(size, entrance_coords, exit_coords); //* Eregistre le chemin dans un fichier solution
    // tracePath(solution); //* Trace le chemin sur le labyrinthe
}

void on_SaveButton_clicked(GtkButton* SaveButton, gpointer solution)
{
    save_solution(solution);
}

void on_FileChooser_file_set(GtkFileChooserButton* FileChooserButton, gpointer ImageSurface)
{
    file_name = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(FileChooserButton));

	gtk_image_set_from_file(ImageSurface, file_name);
}

void on_ExitButton_clicked()
{
    gtk_main_quit();
}
// Main function.
int main (void)
{
    gpointer file_name;

    gtk_init();

	GtkBuilder* builder = gtk_builder_new_from_file("main.glade");
 	GtkWidget* AppWindow = GTK_WIDGET(gtk_builder_get_object(builder, "AppWindow"));

	g_signal_connect(AppWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(builder, NULL);

	GtkWidget* MainGrid = GTK_WIDGET(gtk_builder_get_object(builder, "MainGrid"));
	GtkWidget* FileChooser = GTK_WIDGET(gtk_builder_get_object(builder, "FileChooser"));
	GtkWidget* SolveButton = GTK_WIDGET(gtk_builder_get_object(builder, "SolveButton"));
	GtkWidget* SaveButton = GTK_WIDGET(gtk_builder_get_object(builder, "SaveButton"));
	GtkWidget* ExitButton = GTK_WIDGET(gtk_builder_get_object(builder, "ExitButton"));
	GtkWidget* ImageSurface = GTK_WIDGET(gtk_builder_get_object(builder, "ImageSurface"));

	gtk_widget_show(AppWindow);

	gtk_main();

	return 0;
}
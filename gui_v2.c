// gcc $( pkg-config --cflags gtk+-3.0 ) -o gui_v2 gui_v2.c $( pkg-config --libs gtk+-3.0 )

#include <stdlib.h>
#include <gtk/gtk.h>
#include <glib/gstdio.h>

// Make these Widgets Global

GtkWidget       *window;
GtkWidget       *fixed1;
GtkWidget       *button1;
GtkWidget       *player1;
GtkBuilder      *builder;

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv); //init Gtk

    builder = gtk_builder_new_from_file("Tic_Tac_Toe_GUI.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
    button1 = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
    player1 = GTK_WIDGET(gtk_builder_get_object(builder, "player1"));

    gtk_widget_show(window);

    gtk_main();

    return EXIT_SUCCESS;
}

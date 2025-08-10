#include <gtk-4.0/gtk/gtk.h>
#include <libadwaita-1/adwaita.h>
#include <iostream>

static GtkWidget *window = nullptr;

static void activate(GtkApplication *app, gpointer user_data)
{
    if (window != NULL)
    {
        gtk_window_present(GTK_WINDOW(window));
        return;
    }
    window = adw_application_window_new(app);

    GtkWidget *toolbar_view = adw_toolbar_view_new();
    GtkWidget *header = adw_header_bar_new();

    adw_header_bar_set_title_widget(ADW_HEADER_BAR(header), gtk_label_new("Convert SVG to PNG"));
    // button for header
    GtkWidget *w_open = gtk_button_new_from_icon_name("folder-symbolic");
    adw_header_bar_pack_start(ADW_HEADER_BAR(header), w_open);
    // end button for header
    
    adw_toolbar_view_add_top_bar(ADW_TOOLBAR_VIEW(toolbar_view), header);
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);
    adw_application_window_set_content(ADW_APPLICATION_WINDOW(window), GTK_WIDGET(toolbar_view));

    adw_toolbar_view_set_content(ADW_TOOLBAR_VIEW(toolbar_view), gtk_label_new("this is example :)")); // Content intro

    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[])
{
    AdwApplication *app;
    int status;
    app = adw_application_new("io.github.rsvzz.svgtopng", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
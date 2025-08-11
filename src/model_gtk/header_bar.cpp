#include "../../inc/gtk4/header_bar.hpp"
#include <glib-2.0/glib.h>

static void on_folder_selected(GtkFileDialog *dialog, GAsyncResult *res, gpointer user_data) {
    GError *error = nullptr;
    GFile *folder = gtk_file_dialog_select_folder_finish(dialog, res, &error);

    if (folder) {
        HeaderBar *my_obj = static_cast<HeaderBar*>(user_data);
        gchar *path = g_file_get_path(folder);
        g_print("Carpeta seleccionada: %s\n", path);
        g_free(path);
        g_object_unref(folder);
    } else {
        g_warning("Error al seleccionar carpeta: %s", error->message);
        g_error_free(error);
    }
}

HeaderBar::HeaderBar(GtkWidget *_parent, GtkWidget *_header) : parent(_parent), header(_header)
{
    adw_header_bar_set_title_widget(ADW_HEADER_BAR(header), gtk_label_new("Convert SVG to PNG"));
    // button for header
    hb_open = gtk_button_new_from_icon_name("folder-symbolic");

    g_signal_connect(hb_open, "clicked", G_CALLBACK(&HeaderBar::on_clicked_open_header_bar), static_cast<gpointer>(this)); //send gpointer
    adw_header_bar_pack_start(ADW_HEADER_BAR(header), hb_open);
}

HeaderBar::~HeaderBar() {}

void HeaderBar::on_clicked_open_header_bar(GtkWidget *button, gpointer data)
{
    auto my_obj = static_cast<HeaderBar*>(data); //catch gpointer
    if(GTK_IS_WINDOW(my_obj->get_parent())){
         GtkFileDialog *dialog = gtk_file_dialog_new();
         gtk_file_dialog_select_folder(GTK_FILE_DIALOG(dialog), my_obj->get_parent(), nullptr, GAsyncReadyCallback(on_folder_selected), static_cast<gpointer>(my_obj));
        
    }
    
}

GtkWindow *HeaderBar::get_parent(){ return GTK_WINDOW(parent);}
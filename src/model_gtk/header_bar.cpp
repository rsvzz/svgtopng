#include "../../inc/gtk4/header_bar.hpp"
#include "../../inc/read_file_st.hpp"
#include "../../inc/gtk4/content_box.hpp"

#include <memory>

#include <glib-2.0/glib.h>

static void on_folder_selected(GtkFileDialog *dialog, GAsyncResult *res, gpointer user_data)
{
    GError *error = nullptr;
    GFile *folder = gtk_file_dialog_select_folder_finish(dialog, res, &error);

    if (folder)
    {
        HeaderBar *my_obj = static_cast<HeaderBar *>(user_data);
        gchar *path = g_file_get_path(folder);
        auto st_file = ReadFileSt::get_files_path(string(path));
        if(st_file != nullptr)
            if (!st_file->empty())
            {
                my_obj->set_box_clean_child(); // clear box
                auto box = my_obj->get_box_content();
                auto content = std::make_shared<ContentBox>(st_file);
                gtk_box_append(box, content->get_content_items());
            
            }
        //g_print("Carpeta seleccionada: %s\n", path);
        g_free(path);
        g_object_unref(folder);
    }
    else
    {
        g_warning("Error al seleccionar carpeta: %s", error->message);
        g_error_free(error);
    }
}

HeaderBar::HeaderBar(GtkWidget *_parent, GtkWidget *_header) : parent(_parent), header(_header)
{
    adw_header_bar_set_title_widget(ADW_HEADER_BAR(header), gtk_label_new("Convert SVG to PNG"));
    // button for header
    hb_open = gtk_button_new_from_icon_name("folder-symbolic");
    bx_content = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    g_signal_connect(hb_open, "clicked", G_CALLBACK(&HeaderBar::on_clicked_open_header_bar), static_cast<gpointer>(this)); // send gpointer
    adw_header_bar_pack_start(ADW_HEADER_BAR(header), hb_open);
}

HeaderBar::~HeaderBar() {}

void HeaderBar::on_clicked_open_header_bar(GtkWidget *button, gpointer data)
{
    auto my_obj = static_cast<HeaderBar *>(data); // catch gpointer
    if (GTK_IS_WINDOW(my_obj->get_parent()))
    {
        GtkFileDialog *dialog = gtk_file_dialog_new();
        gtk_file_dialog_select_folder(GTK_FILE_DIALOG(dialog), my_obj->get_parent(), nullptr, GAsyncReadyCallback(on_folder_selected), static_cast<gpointer>(my_obj));
    }
}

GtkWindow *HeaderBar::get_parent() { return GTK_WINDOW(parent); }
GtkBox *HeaderBar::get_box_content() { return GTK_BOX(bx_content); }

void HeaderBar::set_box_clean_child()
{
    auto child = gtk_widget_get_first_child(bx_content);
    while (child != NULL)
    {
        GtkWidget *aux = gtk_widget_get_next_sibling(child);
        gtk_widget_unparent(child);
        child = aux;
    }
}

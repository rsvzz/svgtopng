#pragma once

#include <gtk-4.0/gtk/gtk.h>
#include <libadwaita-1/adwaita.h>
#include <glib-2.0/glib.h>
extern "C" {
    #include "c_model/item_file.h"
}

/// @brief Class used for ADW_HEADER_BAR customer
class HeaderBar
{
private:
    /* data */
    GtkWidget *header, *parent, *hb_open, *bx_content;
    /// @brief signal open button of header_bar
    /// @param
    /// @param
    static void on_clicked_open_header_bar(GtkWidget *, gpointer); // needed it static
public:
    /// @brief ctor
    /// @param  GtkWidget* wg_window main
    /// @param  GtkWidget* wg_header
    HeaderBar(GtkWidget *, GtkWidget *);
    ~HeaderBar();

    GtkWindow *get_parent();
    GtkBox *get_box_content();
    /// @brief clear child box
    void set_box_clean_child();
};

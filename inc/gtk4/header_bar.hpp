#pragma once

#include <gtk-4.0/gtk/gtk.h>
#include <libadwaita-1/adwaita.h>
#include <glib-2.0/glib.h>
#include "gtk4/content_box.hpp"
extern "C" {
    #include "c_model/item_file.h"
}
#include <iostream>
#include <memory>
#include <stack>

/// @brief Class used for ADW_HEADER_BAR customer
class HeaderBar
{
private:
    /* data */
    GtkWidget *header, *parent, *hb_open, *hb_select_all, *bx_content;
    gulong id_select_hb;
    
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
    std::shared_ptr<ContentBox> cbox;
    GtkWindow *get_parent();
    GtkBox *get_box_content();
    /// @brief clear child box
    void set_box_clean_child();
    GtkWidget *get_btn_select_all();
    /// @brief signal for find select items
    /// @param  
    /// @param  
    static void on_clicked_select_header_bar(GtkWidget *, gpointer);
    gulong get_select_hb_id_signal();
    void set_select_hb_id_signal(gulong);
    std::shared_ptr<ContentBox> get_content_item_grid();
    void set_content_item_grid(std::stack<ItemFile*> *);
};

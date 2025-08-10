#include "../../inc/gtk4/header_bar.hpp"
#include <glib-2.0/glib.h>

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
        
        g_print("clicked open %s \n", GTK_WIDGET(my_obj->get_parent()));
    }
    
}

GtkWindow *HeaderBar::get_parent(){ return GTK_WINDOW(parent);}
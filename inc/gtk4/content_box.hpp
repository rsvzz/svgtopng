#pragma once
#include <gtk-4.0/gtk/gtk.h>
#include <glib-2.0/glib.h>
#include <iostream>
#include <stack>

extern "C"
{
#include "c_model/item_file.h"
}

class ContentBox
{
private:
    /* data */
    GtkWidget *content;

public:
    ContentBox(std::stack<ItemFile *> *);
    ~ContentBox();
    static void on_checkbutton_toggled(GtkCheckButton *, gpointer);
    GtkWidget *get_content_items();
};

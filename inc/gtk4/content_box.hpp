#pragma once
#include "c_model/item_file.h"
#include <gtk-4.0/gtk/gtk.h>

#include <iostream>
#include <stack>

class ContentBox
{
private:
    /* data */
    std::stack<ItemFile> *items;
    GtkWidget *content;
public:
    ContentBox(std::stack<ItemFile*>*);
    ~ContentBox();

    GtkWidget *get_content_items();
};

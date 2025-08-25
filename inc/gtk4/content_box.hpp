#pragma once
#include <glib-2.0/glib.h>
#include <gtk-4.0/gtk/gtk.h>
#include <iostream>
#include <stack>

extern "C" {
    #include "c_model/item_file.h"
}

class ContentBox {
private:
  /* data */
  GtkWidget *content, *hb_select, *parent;
  bool status;
  gulong id_start_hb;

public:
/// @brief ctor
/// @param stack<ItemFiles*>* items
/// @param GtkWidget* button
/// @param GtkWidget* parent
  ContentBox(std::stack<ItemFile *>*, GtkWidget*, GtkWidget*);
  ~ContentBox();
  static void on_checkbutton_toggled(GtkCheckButton *, gpointer);
  static void on_clicked_start_header_bar(GtkWidget *, gpointer);
  GtkWidget *get_content_items();
  GtkWidget *get_select_button();
  /// @brief GtkWidget* start button
  /// @param
  void set_id_start_hb(GtkWidget *, gulong);
  gulong get_id_start_hb();
  void set_status(bool);
  bool get_status();
  GtkWidget* get_parent();
};

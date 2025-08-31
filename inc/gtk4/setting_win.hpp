#pragma once
#include <gtk-4.0/gtk/gtk.h>
#include <libadwaita-1/adwaita.h>
#include <iostream>

class SettingWin{
private:
        GtkWindow *parent;
        GListStore *list;
        int width, height;
        GtkWidget *entry_w, *entry_h, *setting, *hb_save, *toolbar_view, *pg_status, *lbl_path;
        static void on_clicked_button_find(GtkWidget *button, gpointer data); 
        static void on_clicked_button_save(GtkWidget *button, gpointer data); 
public:
    SettingWin(GtkWindow*, GListStore*);
    ~SettingWin();
    void show();

    GtkWidget *get_entry_wigth();
    GtkWidget *get_entry_height();
    void set_width(int);
    int get_width();
    void set_height(int);
    int get_height();

    GtkWindow* get_window();
    GListStore *get_list_items();

    GtkWindow *get_parent();

    void set_pg_status(gboolean);
    GtkWidget *get_pg_status();
    GtkWidget *get_lbl_path();
};

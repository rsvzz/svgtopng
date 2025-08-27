#pragma once
#include <gtk-4.0/gtk/gtk.h>
#include <libadwaita-1/adwaita.h>
#include <iostream>

class SettingWin{
private:
        GtkWindow *parent;
        GListStore *list;
        int width, height;
        GtkWidget *entry_w, *entry_h, *setting, *hb_save, *toolbar_view, *pg_status;
public:
    SettingWin(GtkWindow*, GListStore*);
    ~SettingWin();
    void show();
    static void on_clicked_button_save(GtkWidget *button, gpointer data); 
    GtkWidget *get_entry_wigth();
    GtkWidget *get_entry_height();
    void set_width(int);
    int get_width();
    void set_height(int);
    int get_height();

    GtkWindow* get_window();
};

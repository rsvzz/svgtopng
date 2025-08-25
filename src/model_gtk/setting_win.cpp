#include "../../inc/gtk4/setting_win.hpp"
#include "adwaita.h"
#include "glibconfig.h"
#include "gtk/gtk.h"
#include "gtk/gtkshortcut.h"

SettingWin::SettingWin(GtkWindow *_parent, GListStore *_list) {
  GtkWidget *setting = adw_window_new();
  gtk_window_set_default_size(GTK_WINDOW(setting), 200, 200);
  gtk_window_set_modal(GTK_WINDOW(setting), true);

  GtkWidget *toolbar_view = adw_toolbar_view_new();

  GtkWidget *header = adw_header_bar_new();
  GtkWidget *hb_save = gtk_button_new_from_icon_name("selection-mode-symbolic");
  adw_header_bar_pack_start(ADW_HEADER_BAR(header), hb_save);
  adw_toolbar_view_add_top_bar(ADW_TOOLBAR_VIEW(toolbar_view), header);

  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  //gtk_widget_set_vexpand_set(box, FALSE);
  //gtk_widget_set_hexpand_set(box, FALSE);

  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);

  GtkWidget *entry_width = gtk_entry_new();
  GtkWidget *entry_heigth = gtk_entry_new();
  GtkWidget *label_x = gtk_label_new(" X ");

  gtk_entry_set_placeholder_text(GTK_ENTRY(entry_width), "Width :");
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry_heigth), "Height :");

  gtk_box_append(GTK_BOX(box), entry_width);
  gtk_box_append(GTK_BOX(box), label_x);
  gtk_box_append(GTK_BOX(box), entry_heigth);

  adw_toolbar_view_set_content(ADW_TOOLBAR_VIEW(toolbar_view), box);

  adw_window_set_content(ADW_WINDOW(setting), toolbar_view);
  gtk_window_present(GTK_WINDOW(setting));
}

SettingWin::~SettingWin() {}

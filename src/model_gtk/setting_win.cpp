#include "../../inc/gtk4/setting_win.hpp"
extern "C"
{
#include "../../inc/gtk4/c_model/item_file.h"
}
#include <iostream>
#include <string>
#include <memory>

using namespace std;

void SettingWin::on_clicked_button_save(GtkWidget *button, gpointer data)
{
  auto setting = static_cast<SettingWin *>(data);
  GtkWidget *width_entry = setting->get_entry_wigth();
  GtkWidget *height_entry = setting->get_entry_height();

  if (width_entry != nullptr && height_entry != nullptr)
  {

    GtkEntryBuffer *buffer_w = gtk_entry_get_buffer(GTK_ENTRY(width_entry));
    GtkEntryBuffer *buffer_h = gtk_entry_get_buffer(GTK_ENTRY(height_entry));

    int width = std::atoi(gtk_entry_buffer_get_text(buffer_w));
    int heigth = std::atoi(gtk_entry_buffer_get_text(buffer_h));

    setting->set_width(width);
    setting->set_height(heigth);

    if (width > 0 && heigth > 0)
    {
      GListModel *model = G_LIST_MODEL(setting->get_list_items());
      guint n_items = g_list_model_get_n_items(model);

      if (n_items > 0)
      {
        auto pg_status = setting->get_pg_status();
        gtk_widget_set_visible(pg_status, TRUE);
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pg_status), 0.5);
        gtk_progress_bar_set_text(GTK_PROGRESS_BAR(pg_status), "Londing Convert Files .SVG to .PNG");
        gtk_progress_bar_set_show_text(GTK_PROGRESS_BAR(pg_status), TRUE);

        gtk_widget_queue_draw(setting->get_pg_status());
        for (guint i = 0; i < n_items; ++i)
        {
          gpointer item = g_list_model_get_item(model, i);
          ItemFile *my_item = (ItemFile *)(item); // o cast GObject from C
          GtkCheckButton *checkbutton = item_file_get_check_button(my_item);
          if (item_file_get_check(my_item) == ACTIVE)
          {

            gtk_check_button_set_active(checkbutton, FALSE);
          }
        }
      }
      // gtk_window_close(setting->get_window());
    }
  }

  // GtkEntryBuffer *buffer_h = gtk_entry_get_buffer(setting->get_entry_height());
  /*int width =
      std::atoi(std::string(gtk_entry_buffer_get_text(buffer_w)).c_str());
  int heigth = std::atoi(gtk_entry_buffer_get_text(buffer_h));
  setting->set_width(width);
  setting->set_height(heigth);
  g_print("width : %d, height : %d \n", setting->get_width(),
          setting->get_height());
          */
}

SettingWin::SettingWin(GtkWindow *_parent, GListStore *_list) : width(0), height(0), parent(_parent), list(_list)
{
  setting = adw_window_new();
  gtk_window_set_default_size(GTK_WINDOW(setting), 250, 250);
  gtk_window_set_transient_for(GTK_WINDOW(setting), parent);
  gtk_window_set_modal(GTK_WINDOW(setting), true);

  GtkWidget *path = gtk_label_new(NULL);
  GtkWidget *button_find = gtk_button_new_from_icon_name("document-open-symbolic");
  GtkWidget *button_exe = gtk_button_new_from_icon_name("selection-mode-symbolic");

  g_signal_connect(button_exe, "clicked", G_CALLBACK(&SettingWin::on_clicked_button_save), static_cast<gpointer>(this));

  entry_w = gtk_entry_new();
  entry_h = gtk_entry_new();
  pg_status = gtk_progress_bar_new();

  GtkWidget *label_x = gtk_label_new(" X ");

  gtk_entry_set_placeholder_text(GTK_ENTRY(entry_w), "Width :");
  gtk_entry_set_placeholder_text(GTK_ENTRY(entry_h), "Height :");
  toolbar_view = adw_toolbar_view_new();

  GtkWidget *header = adw_header_bar_new();
  // hb_save = gtk_button_new_from_icon_name("selection-mode-symbolic");
  // adw_header_bar_pack_start(ADW_HEADER_BAR(header), hb_save);

  adw_toolbar_view_add_top_bar(ADW_TOOLBAR_VIEW(toolbar_view), header);

  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  // GtkWidget *box_w_h = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

  GtkWidget *grid = gtk_grid_new();
  gtk_grid_attach(GTK_GRID(grid), entry_w, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), label_x, 1, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), entry_h, 2, 0, 1, 1);

  gtk_grid_attach(GTK_GRID(grid), path, 0, 1, 2, 1);
  /// | -  - | 2 |
  gtk_grid_attach(GTK_GRID(grid), button_find, 2, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), button_exe, 2, 2, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), pg_status, 0, 3, 3, 1);
  gtk_widget_set_visible(pg_status, FALSE);

  gtk_widget_set_halign(button_find, GTK_ALIGN_END);
  gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
  // gtk_box_append(GTK_BOX(box_w_h), entry_w);
  // gtk_box_append(GTK_BOX(box_w_h), label_x);
  // gtk_box_append(GTK_BOX(box_w_h), entry_h);
  //  gtk_widget_set_vexpand_set(box, FALSE);
  //  gtk_widget_set_hexpand_set(box, FALSE);

  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  // gtk_widget_set_valign(box, GTK_ALIGN_CENTER);
  gtk_box_append(GTK_BOX(box), grid);
  // gtk_box_append(GTK_BOX(box), pg_status);
  gtk_widget_set_margin_top(pg_status, 50);
  gtk_widget_set_margin_start(box, 10);
  gtk_widget_set_margin_end(box, 10);
  adw_toolbar_view_set_content(ADW_TOOLBAR_VIEW(toolbar_view), box);

  adw_window_set_content(ADW_WINDOW(setting), toolbar_view);
}

SettingWin::~SettingWin() {}

void SettingWin::show()
{
  gtk_window_present(GTK_WINDOW(setting));
}

GtkWidget *SettingWin::get_entry_wigth() { return entry_w; }

GtkWidget *SettingWin::get_entry_height() { return entry_h; }

void SettingWin::set_width(int w) { width = w; }
int SettingWin::get_width() { return width; }

void SettingWin::set_height(int h) { height = h; }

int SettingWin::get_height() { return height; }

GtkWindow *SettingWin::get_window() { return GTK_WINDOW(setting); }

GListStore *SettingWin::get_list_items() { return list; }

void SettingWin::set_pg_status(gboolean status)
{
  gtk_widget_set_visible(pg_status, status);
}

GtkWidget *SettingWin::get_pg_status() { return pg_status; }

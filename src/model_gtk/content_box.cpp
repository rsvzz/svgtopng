#include "../../inc/gtk4/content_box.hpp"
#include <gtk-4.0/gdk/gdk.h>

static void setup_item(GtkListItemFactory *factory, GtkListItem *item, gpointer user_data)
{
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *picture = gtk_picture_new();
    gtk_widget_set_size_request(picture, 40, 40);
    gtk_widget_set_margin_top(picture, 5);
    gtk_picture_set_keep_aspect_ratio(GTK_PICTURE(picture), true);

    GtkWidget *check = gtk_check_button_new();
    gtk_box_append(GTK_BOX(box), picture);
    gtk_box_append(GTK_BOX(box), check);
    gtk_list_item_set_child(item, box);
}

static void bind_item(GtkListItemFactory *factory, GtkListItem *item, gpointer user_data)
{
    ItemFile *item_f = (ItemFile *)gtk_list_item_get_item(item);
    GtkWidget *box = gtk_list_item_get_child(item);
    GtkWidget *picture = gtk_widget_get_first_child(box);
    GtkWidget *check = gtk_widget_get_next_sibling(picture);
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(item_file_get_path(item_f), NULL);
    GdkPixbuf *scaled = gdk_pixbuf_scale_simple(pixbuf, 40, 40, GDK_INTERP_BILINEAR);
    gtk_picture_set_pixbuf(GTK_PICTURE(picture), scaled);
    g_signal_connect(check, "toggled", G_CALLBACK(&ContentBox::on_checkbutton_toggled), item_f);
    item_file_set_check_button(item_f, GTK_CHECK_BUTTON(check));
    //item_file_set_check(item_f, INACTIVE);
    //GFile *file = g_file_new_for_path(item_file_get_path(item_f));
    //gtk_picture_set_file(GTK_PICTURE(picture), file);
}

ContentBox::ContentBox(std::stack<ItemFile *> *st_items)
{
    GListStore *store = g_list_store_new(ITEM_FILE_TYPE);
    status = true;
    GtkListItemFactory *factory = gtk_signal_list_item_factory_new();
    g_signal_connect(factory, "setup", G_CALLBACK(setup_item), NULL);
    g_signal_connect(factory, "bind", G_CALLBACK(bind_item), NULL);

    while (!st_items->empty())
    {
        /* code */
        ItemFile *item = st_items->top();
        if (item != nullptr)
        {
            g_list_store_append(store, item);
        }
        st_items->pop();
    }

    content = gtk_grid_view_new(GTK_SELECTION_MODEL(gtk_no_selection_new(G_LIST_MODEL(store))), factory);
    gtk_widget_set_vexpand(content, TRUE);
    gtk_widget_set_hexpand(content, TRUE);
    gtk_grid_view_set_min_columns(GTK_GRID_VIEW(content), 4);
    gtk_grid_view_set_max_columns(GTK_GRID_VIEW(content), 6);
}

ContentBox::~ContentBox()
{
}

GtkWidget *ContentBox::get_content_items()
{
    return content;
}

void ContentBox::on_checkbutton_toggled(GtkCheckButton *check_button, gpointer user_data) {
    gboolean active = gtk_check_button_get_active(check_button);
    ItemFile *item = (ItemFile*)user_data;
    if(active)
        item_file_set_check(item, ACTIVE);
    else
        item_file_set_check(item, INACTIVE);
}

bool ContentBox::get_status(){ return status;}
void ContentBox::set_status(bool _status) { status = _status;}
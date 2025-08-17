#include "../../inc/gtk4/header_bar.hpp"
#include "../../inc/read_file_st.hpp"
#include <glib-2.0/glib.h>

std::shared_ptr<ContentBox> HeaderBar::get_content_item_grid(){
    return cbox;
}

void HeaderBar::set_content_item_grid(std::stack<ItemFile*> *items){
    cbox.reset();
    cbox = std::make_shared<ContentBox>(items);
}


static void on_folder_selected(GtkFileDialog *dialog, GAsyncResult *res, gpointer user_data)
{
    GError *error = nullptr;
    GFile *folder = gtk_file_dialog_select_folder_finish(dialog, res, &error);

    if (folder != nullptr)
    {
        HeaderBar *my_obj = static_cast<HeaderBar *>(user_data);
        gchar *path = g_file_get_path(folder);
        auto st_file = ReadFileSt::get_files_path(string(path));
        if (st_file != nullptr)
            if (!st_file->empty())
            {
                my_obj->set_box_clean_child(); // clear box
                auto box = my_obj->get_box_content();
                my_obj->set_content_item_grid(st_file); // std::make_shared<ContentBox>(st_file); // send gpointer with new
                std::shared_ptr<ContentBox> content = my_obj->get_content_item_grid();
                gtk_box_append(box, content->get_content_items());
                // select all items gridview
                GtkWidget *btn_select = my_obj->get_btn_select_all();
                gtk_widget_set_visible(btn_select, TRUE);
                if (my_obj->get_select_hb_id_signal() != 0)
                {
                    g_signal_handler_disconnect(btn_select, my_obj->get_select_hb_id_signal());
                }
                gulong id_select = g_signal_connect(btn_select, "clicked", G_CALLBACK(&HeaderBar::on_clicked_select_header_bar), static_cast<gpointer>(content.get())); // send gpointer new
                my_obj->set_select_hb_id_signal(id_select);
            }
        // g_print("Carpeta seleccionada: %s\n", path);
        g_free(path);
        g_object_unref(folder);
    }
    else
    {
        g_warning("Error al seleccionar carpeta: %s", error->message);
        g_error_free(error);
    }
}

HeaderBar::HeaderBar(GtkWidget *_parent, GtkWidget *_header) : parent(_parent), header(_header)
{
    adw_header_bar_set_title_widget(ADW_HEADER_BAR(header), gtk_label_new("Convert SVG to PNG"));
    // button for header
    hb_open = gtk_button_new_from_icon_name("folder-symbolic");
    hb_select_all = gtk_button_new_from_icon_name("view-grid-symbolic");
    gtk_widget_set_visible(hb_select_all, FALSE);
    id_select_hb = 0; // init
    //
    bx_content = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    g_signal_connect(hb_open, "clicked", G_CALLBACK(&HeaderBar::on_clicked_open_header_bar), static_cast<gpointer>(this)); // send gpointer
    adw_header_bar_pack_start(ADW_HEADER_BAR(header), hb_open);
    adw_header_bar_pack_start(ADW_HEADER_BAR(header), hb_select_all);
}

HeaderBar::~HeaderBar() {}

void HeaderBar::on_clicked_open_header_bar(GtkWidget *button, gpointer data)
{
    auto my_obj = static_cast<HeaderBar *>(data); // catch gpointer
    if (GTK_IS_WINDOW(my_obj->get_parent()))
    {
        GtkFileDialog *dialog = gtk_file_dialog_new();
        gtk_file_dialog_select_folder(GTK_FILE_DIALOG(dialog), my_obj->get_parent(), nullptr, GAsyncReadyCallback(on_folder_selected), static_cast<gpointer>(my_obj));
    }
}

void HeaderBar::on_clicked_select_header_bar(GtkWidget *button, gpointer data)
{

    auto bx_grid = static_cast<ContentBox *>(data); // catch gpointer from C++

    GtkWidget *grid = bx_grid->get_content_items();

    if (grid == nullptr)
    {
        return;
    }

    if (!GTK_IS_GRID_VIEW(grid))
        return;

    GtkSelectionModel *selection_model = gtk_grid_view_get_model(GTK_GRID_VIEW(grid));
    GListModel *model = gtk_no_selection_get_model(GTK_NO_SELECTION(selection_model));
    // GListStore *list_store = G_LIST_STORE(model);
    guint n_items = g_list_model_get_n_items(model);
    for (guint i = 0; i < n_items; ++i)
    {
        gpointer item = g_list_model_get_item(model, i);
        ItemFile *my_item = (ItemFile *)(item); // o cast GObject from C
        //item_file_set_check(my_item, ACTIVE);
        const gchar *name = item_file_get_name(my_item);
        STATUS status = item_file_get_check(my_item);
        g_print("item select : %s status : %d \n", name, status);

    }
}

GtkWindow *HeaderBar::get_parent() { return GTK_WINDOW(parent); }
GtkBox *HeaderBar::get_box_content() { return GTK_BOX(bx_content); }

void HeaderBar::set_box_clean_child()
{
    auto child = gtk_widget_get_first_child(bx_content);
    if (!GTK_IS_GRID_VIEW(child))
        return;

    GtkSelectionModel *selection_model = gtk_grid_view_get_model(GTK_GRID_VIEW(child));

    if (GTK_IS_NO_SELECTION(selection_model))
    {
        GListModel *model = gtk_no_selection_get_model(GTK_NO_SELECTION(selection_model));

        if (G_IS_LIST_STORE(model))
        {
            GListStore *list_store = G_LIST_STORE(model);
            guint n_items = g_list_model_get_n_items(model);

            for (guint i = n_items; i > 0; i--)
            {
                g_list_store_remove(list_store, i - 1);
            }

            gtk_widget_unparent(child); // child remove from box
            child = nullptr;
        }
    }
}

GtkWidget *HeaderBar::get_btn_select_all()
{
    return hb_select_all;
}

gulong HeaderBar::get_select_hb_id_signal() { return id_select_hb; }
void HeaderBar::set_select_hb_id_signal(gulong id)
{
    id_select_hb = id;
}

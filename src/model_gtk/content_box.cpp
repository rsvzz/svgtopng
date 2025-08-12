#include "../../inc/gtk4/content_box.hpp"

ContentBox::ContentBox(std::stack<ItemFile*> *st_items){
    content = gtk_label_new("the items show here :-)");
}

ContentBox::~ContentBox(){

}

GtkWidget *ContentBox::get_content_items(){
    return content;
}
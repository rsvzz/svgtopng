#pragma once

#include <glib-2.0/glib-object.h>

#define ITEM_FILE_TYPE item_file_get_type()

typedef enum ItemStatusFile{
    ACTIVE = 0,
    INACTIVE = 1
} STATUS;

G_DECLARE_FINAL_TYPE(ItemFile, item_file, ITEM, FILE, GObject);

ItemFile *item_file_new(void);
/// @brief set data for ItemFile
/// @param  self
/// @param  Path
/// @param  Name
/// @param  Extention
void item_file_set_data(ItemFile*, const char*, const char*, const char*);

char* item_file_get_path(ItemFile*);
char* item_file_get_name(ItemFile*);
char* item_file_get_extention(ItemFile*);

STATUS item_file_get_check(ItemFile*);
void item_file_set_check(ItemFile*, STATUS);
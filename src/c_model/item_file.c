#include "../../inc/gtk4/c_model/item_file.h"

struct _ItemFile
{
    GObject parent_instance;
    char *path, *name, *extention;
    STATUS status;
};

G_DEFINE_TYPE(ItemFile, item_file, G_TYPE_OBJECT);

static void item_file_dispose(GObject *object)
{
    // g_print("llega dispose \n");
    ItemFile *self = ITEM_FILE(object);

    if (self->path != NULL)
    {
        free(self->path);
        self->path = NULL;
    }

    if (self->name != NULL)
    {
        free(self->name);
        self->name = NULL;
    }

    if (self->extention != NULL)
    {
        free(self->extention);
        self->extention = NULL;
    }

    G_OBJECT_CLASS(item_file_parent_class)->dispose(object);
}

static void item_file_finalize(GObject *object)
{
    G_OBJECT_CLASS(item_file_parent_class)->finalize(object);
}

static void item_file_class_init(ItemFileClass *Klass)
{
    // add signal and property
    GObjectClass *object_class = G_OBJECT_CLASS(Klass);

    // Asignar la función de destrucción
    object_class->dispose = item_file_dispose;

    // Asignar la función de finalización
    object_class->finalize = item_file_finalize;
};

static void item_file_init(ItemFile *self) {
    // obj gtk no here

};

ItemFile *item_file_new(void)
{
    return g_object_new(ITEM_FILE_TYPE, NULL);
}

void item_file_set_data(ItemFile *self, const char *path, const char *name, const char *extention)
{
    self->path = malloc(strlen(path) + 1);
    strcpy(self->path, path);

    self->name = malloc(strlen(name) + 1);
    strcpy(self->name, name);

    self->extention = malloc(strlen(extention) + 1);
    strcpy(self->extention, extention);
    
    self->status = ACTIVE;
}

char *item_file_get_path(ItemFile *self) { return self->path; }
char *item_file_get_name(ItemFile *self) { return self->name; }
char *item_file_get_extention(ItemFile *self) { return self->extention; }

STATUS item_file_get_check(ItemFile* self){
    return self->status;
}
void item_file_set_check(ItemFile* self, STATUS _status){
    self->status = _status;
}
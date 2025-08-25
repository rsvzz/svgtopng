#include <gtk-4.0/gtk/gtk.h>
#include <libadwaita-1/adwaita.h>

class SettingWin{
    private:
        GtkWindow *parent;
        GListStore *list;
    public:
    SettingWin(GtkWindow*, GListStore*);
    ~SettingWin();
};

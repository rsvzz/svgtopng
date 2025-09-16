#include "../../inc/model/changed_pg.hpp"

ChangedPG::ChangedPG(int _items) : items(_items)
{
    if (items >= 20)
        refresh = 0.05; // 5%
    else
        refresh = 0.5; // 50%

    next = items * refresh;
}

ChangedPG::~ChangedPG() {}

void ChangedPG::set_calc_update(int count)
{
    if (count >= next)
    {
        status = true;
        next++;

        if (update > 0)
            update += refresh;
        else
            update = refresh;
    }
    else
    {
        status = false;
    }
}
double ChangedPG::get_next() { return next; }
double ChangedPG::get_update() { 
    status = false; //changed status
    return update; 
}
bool ChangedPG::get_status() { return status; }
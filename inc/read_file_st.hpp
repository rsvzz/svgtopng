#pragma once
#include <iostream>
#include <stack>
#include <string>

extern "C"{
    #include "gtk4/c_model/item_file.h"
}


using namespace std;

class ReadFileSt
{
private:
    /* data */
public:
    ReadFileSt();
    ~ReadFileSt();

    static stack<ItemFile*> *get_files_path(string path);
};
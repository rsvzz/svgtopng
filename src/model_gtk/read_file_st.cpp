#include "../../inc/read_file_st.hpp"
#include <filesystem>

ReadFileSt::ReadFileSt(/* args */)
{
}

ReadFileSt::~ReadFileSt()
{
}

stack<ItemFile *> *ReadFileSt::get_files_path(string path)
{

    std::stack<ItemFile *> *file_list = new std::stack<ItemFile *>;
    for (const auto &file : std::filesystem::recursive_directory_iterator(path))
    {
        if (!file.is_directory() && file.path().extension().string() == ".svg")
        {
            auto item = item_file_new();
            item_file_set_data(item, file.path().c_str(), file.path().filename().c_str(), file.path().extension().c_str());
            file_list->push(item);
        }
    }

    return file_list;
}

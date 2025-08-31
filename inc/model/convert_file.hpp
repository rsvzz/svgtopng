#pragma once
#include <iostream>
extern "C"{
    #include "../../inc/gtk4/c_model/svg_draw.h"
}
    
class ConvertFile
{
private:
    /* data */
    std::string path, path_date;
    int w, h;
    SvgDraw *svg;
public:
    ConvertFile(std::string, int, int);
    ~ConvertFile();
    /// @brief convert file .svg to png
    /// @param  string path file .svg
    void convert_files_to(std::string);
};

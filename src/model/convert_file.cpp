#include "../../inc/model/convert_file.hpp"
#include <filesystem>
using namespace std;
ConvertFile::ConvertFile(string _path, int width, int height) : path(_path), w(width), h(height) {
    path_date = path + "/svgtopng";
    //std::cout<< path_date<< " "<< w<<" x "<< h<< std::endl;
    svg = svg_draw_new();
    svg_draw_set_draw_width_and_height(svg, w, h);
    if(!filesystem::create_directory(path_date))
        std::cout<< "Exist directory"<< std::endl;
    
}

ConvertFile::~ConvertFile(){
    g_object_unref(svg);
    svg = NULL;
}

void ConvertFile::convert_files_to(string p_file){
    svg_draw_file_svg_to_png(svg, p_file.c_str(), path_date.c_str());
}
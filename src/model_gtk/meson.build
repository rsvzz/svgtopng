inc_src = include_directories('../../src', '../../inc')
src_files = files([
    'header_bar.cpp',
    'read_file_st.cpp',
    'content_box.cpp'
])

gtk_dep = dependency('gtk4')
adw_dep = dependency('libadwaita-1')

mgtk_dep = static_library(
    'mgtk', 
    sources: src_files,
    include_directories: inc_src,
    dependencies: [gtk_dep, adw_dep]
)
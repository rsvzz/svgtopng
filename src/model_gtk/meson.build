inc_src = include_directories('../../src', '../../inc')
src_files = files([
    'header_bar.cpp'
])

gtk_dep = dependency('gtk4')
adw_dep = dependency('libadwaita-1')
glib_dep = dependency('glib-2.0')

mgtk_dep = static_library(
    'mgtk', 
    sources: src_files,
    include_directories: inc_src,
    dependencies: [gtk_dep, adw_dep, glib_dep]
)
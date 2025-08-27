inc_src = include_directories('../../src', '../../inc')
src_files = files('content_box.cpp', 'header_bar.cpp', 'read_file_st.cpp', 'setting_win.cpp')

gtk_dep = dependency('gtk4')
adw_dep = dependency('libadwaita-1')
gobj_dep = dependency('gobject-2.0')
mgtk_dep = static_library(
  'mgtk',
  sources: src_files,
  include_directories: inc_src,
  dependencies: [gtk_dep, adw_dep, gobj_dep],
)

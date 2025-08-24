inc_src = include_directories('../../src', '../../inc')
src_files = files('item_file.c', 'svgdraw.c')

glib_dep = dependency('glib-2.0')
gobj_dep = dependency('gobject-2.0')
gtk_dep = dependency('gtk4')
librsvg_dep = dependency('librsvg-2.0')
cmodel_dep = static_library(
  'libcmodel',
  sources: src_files,
  include_directories: inc_src,
  dependencies: [gtk_dep, glib_dep, gobj_dep, librsvg_dep],
)

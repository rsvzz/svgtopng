inc_src = include_directories('../../src', '../../inc')
src_files = files('convert_file.cpp')

gobj_dep = dependency('gobject-2.0')
librsvg_dep = dependency('librsvg-2.0')
gtk_dep = dependency('gtk4')

model_dep = static_library(
  'modelcpp',
  sources: src_files,
  dependencies : [gtk_dep, gobj_dep, librsvg_dep],
  include_directories: inc_src
)

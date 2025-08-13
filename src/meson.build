inc_src = include_directories('../src', '../inc')
subdir('c_model')
subdir('model_gtk')


executable('svgtopng',
  sources: ['app.cpp'],
  include_directories: [inc_src],
  dependencies : [gtk_dep, adw_dep, glib_dep, gobj_dep],
  link_with: [mgtk_dep, cmodel_dep],
  install: true
)
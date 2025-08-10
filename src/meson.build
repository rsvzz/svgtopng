inc_src = include_directories('../src', '../inc')
subdir('model_gtk')
#subdir('model')
#subdir('model_c')


executable('svgtopng',
  sources: ['app.cpp'],
  include_directories: [inc_src],
  dependencies : [gtk_dep, adw_dep, glib_dep],
  link_with: [mgtk_dep],
  install: true
)
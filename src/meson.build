inc_src = include_directories('../src', '../inc')
#subdir('model_gtk')
#subdir('model')
#subdir('model_c')

gtk_dep = dependency('gtk4')
adw_dep = dependency('libadwaita-1')
glib_dep = dependency('glib-2.0')

executable('svgtopng',
  sources: ['app.cpp'],
  include_directories: [inc_src],
  dependencies: [gtk_dep, adw_dep, glib_dep],
  install: true
)
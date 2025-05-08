project('yestty', 'c',
        version: '0.1.0',
        license: 'MIT',
        default_options: ['warning_level=3'])

yestty_lib = shared_library('libyestty', 'src/libyestty.c', name_prefix: '', install: true)

yestty_exe = executable('yestty', 'src/yestty.c', install: true)
notty_exe = executable('notty', 'src/notty.c', install: true)


# yestty
Tricks apps into thinking that they are reading from / writing to a TTY.
Achieves so by preloading libyestty.so, which replaces isatty() function
from libc, so it obviously won't work with static binaries, raw syscalls,
binaries that don't use libc, etc.

## Building
```sh
git clone 'https://github.com/heather7283/yestty.git'
cd yestty
meson setup build
meson compile -C build
sudo meson install -C build
sudo ldconfig
```

## Usage
```sh
yestty dmesg | less
# enjoy colors
notty dmesg
# enjoy no colors
```


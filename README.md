## Colors

For make:
```gcc -lstdc++ src/color-utils.cpp -o color-utils```

For run:
```./color-utils```

Help:
+ l - list color table
+ gx <path> - generate xresources file
+ gr <path> - generate xresources rofi file
+ gt <path> - generate termite config file
+ mx <path> - merge colors with xresources file
+ mr <path> - merge rofi colors with xresources file
+ mt <path> - merge colors with termite config file
+ -p <path> - path to default xresources file
+ -r <7 int> - rofi configuration; 7 ids of xresources colors for:
```
rofi.color-normal: id0, id1, id2, id3, id4
rofi.color-window: id5, id6
```
+ -c <19 colors> - colors configuration(without xresources file); order: color[0-15] background foreground cursorColor

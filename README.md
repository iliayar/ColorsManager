## Colors

For make:
```gcc -lstdc++ src/color-utils.cpp -o color-utils```

For run:
```./color-utils```

Help:
* l - list color table
* gx <path> - generate xresources file
* gr <path> - generate xresources rofi file
* gt <path> - generate termite config file
* mx <path> - merge colors with xresources file
* mr <path> - merge rofi colors with xresources file
* mt <path> - merge colors with termite config file
* -p <path> - path to default xresources file
* -r <7 int> - rofi configuration
* -c <19 colors> - colors configuration(without xresources file)


Rofi configuration:
Pass 7 ids(id0,id1,..):
```
rofi.color-normal: id0, id1, id2, id3, id4
rofi.color-window: id5, id6
```

Colors configuration:
Pass 19 colors as #ffffff, the order of colors:
color[0-15] background foreground cursorColor

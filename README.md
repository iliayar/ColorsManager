## Colors

![color table](https://raw.githubusercontent.com/iliayar/ColorsManager/master/color_table.png)

Build:
`make`

Install:
`make install`

Help:
* l - list color table
* gx \<path> - generate xresources file
* gr \<path> - generate xresources rofi file
* gt \<path> - generate termite config file
* mx \<path> - merge colors with xresources file
* mr \<path> - merge rofi colors with xresources file
* mt \<path> - merge colors with termite config file
* -p \<path> - path to default xresources file
* -r \<7 int> - rofi configuration
* -c \<19 colors> - colors configuration(without xresources file)
* -cr \<id(int)> \<color\> - set color with id to color

Rofi configuration:
Pass 7 ids(id0,id1,..):
```
!                  'bg', 'fg', 'bgalt','hlbg','hlfg'
rofi.color-normal:  id0,  id1,  id2,     id3,   id4
!                  'background', 'border'
rofi.color-window:     id5,        id6
```

Colors configuration:
Pass 19 colors as #ffffff, the order of colors:
color[0-15] background foreground cursorColor

Example:
* Set color2 to value #123456:
  ```./color-utils -p ~/.resoures/.Xresources -cr 2 \#123456 mx ~/.resources/.Xresources```
* Print current color table(Watch image):
  ```./color-utils l```

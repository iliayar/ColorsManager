all: build

build:
	g++ src/color-utils.cpp -o color-utils
install:
	cp color-utils ~/bin/

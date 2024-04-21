prog:main.o background.o
	gcc main.o background.o -o prog -lSDL -g -lSDL_image -lSDL_mixer -lSDL_ttf
main.o:main.c
	gcc -c main.c -g
background.o:background.c
	gcc -c background.c -g

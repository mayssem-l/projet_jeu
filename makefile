programme:enigme.o main.o
	gcc enigme.o main.o -o programme -lSDL -g -lSDL_image -lSDL_mixer -lSDL_ttf 
main.o:main.c
	gcc -c main.c -g
enigme.o:enigme.c
	gcc -c enigme.c -g

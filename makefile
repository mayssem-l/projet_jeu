prog:fonction.o main.o 
	gcc fonction.o main.o -o prog -lSDL -g -lSDL_image -lSDL_mixer -lSDL_ttf
main.o:main.c
	gcc -c main.c -g
fonction.o:fonction.c
	gcc -c fonction.c -g


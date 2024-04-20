prog:enigme.o ennemie.o entity.o fonction.o main.o 
	gcc enigme.o ennemie.o entity.o fonction.o main.o -o prog -lSDL -g -lSDL_image -lSDL_mixer -lSDL_ttf 
main.o:main.c
	gcc -c main.c -g
fonction.o:fonction.c
	gcc -c fonction.c -g
entity.o:entity.c
	gcc -c entity.c -g
ennemie.o:ennemie.c
	gcc -c ennemie.c -g
enigme.o:enigme.c
	gcc -c enigme.c -g


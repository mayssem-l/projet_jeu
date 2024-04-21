#include "background.h"
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>

int main(){
Mix_Music *musique;
int quitter=1, play=0;
SDL_Surface *ecran;
SDL_Event event;
background bg;


TTF_Init();
SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) ;
Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,1024);

if(SDL_Init(SDL_INIT_VIDEO) < 0){
printf("ECHEC D'INITIALISATION DE SDL!! : %s\n",SDL_GetError());}
else{
printf("SDL est initialisé avec succès.\n");}

ecran=SDL_SetVideoMode(700, 500,  32,SDL_HWSURFACE | SDL_DOUBLEBUF);

if ( ecran == NULL )
	{
		fprintf(stderr, "Echec de creation de la fenetre de 560*360: %s.\n", SDL_GetError());
	}
else {printf("fenetre cree avec success. \n");}

SDL_BlitSurface(bg.bg,&bg.posanim,ecran,&bg.poscam1);

initBack(&bg,ecran,musique);
initAnim(&bg,ecran);

while(quitter){
	
	afficherBack(bg,ecran);
	//nimerBack(&bg,ecran);
	SDL_PollEvent(&event);

switch(event.type){
	case SDL_QUIT:
		quitter=0;
	break;
	case SDL_KEYDOWN:
		if(event.key.keysym.sym == SDLK_ESCAPE){quitter = 0;}
		if(event.key.keysym.sym == SDLK_RIGHT){bg.direction=0; bg.num=1; }
		if(event.key.keysym.sym == SDLK_LEFT){bg.direction=1; bg.num=1;}
		if(event.key.keysym.sym == SDLK_UP){bg.direction=2; bg.num=1;}
		if(event.key.keysym.sym == SDLK_DOWN){bg.direction=3; bg.num=1;}
		if(event.key.keysym.sym == SDLK_r){bg.direction=0; bg.num=2; }
		if(event.key.keysym.sym == SDLK_u){bg.direction=1; bg.num=2; }
		if(event.key.keysym.sym == SDLK_d){bg.direction=2; bg.num=2; }
		if(event.key.keysym.sym == SDLK_s){bg.direction=3; bg.num=2; }
	break;
	
}

scrolling(&bg,1,ecran);

SDL_Flip(ecran);
}

SDL_FreeSurface(bg.bg);
Mix_FreeMusic(musique);
Mix_CloseAudio();
SDL_Quit();
return 0;
}
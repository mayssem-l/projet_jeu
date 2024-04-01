#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "enigme.h"
int main(int argc, char** argv)
{
  SDL_Surface *screen;
  Enigme e;
  int quitter=1;
  SDL_Event event;
  char reponse[TAILLE_MAX]="";
//**************Initialisation
//initialisation des sous systemes de SDL
  SDL_Init(SDL_INIT_EVERYTHING);
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,2,1024);
  TTF_Init();

/* initialisation de SDL_Video */
   if ((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER)!=0) || (TTF_Init()!=0) || Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT,2,1024)!=0)
      {
         printf("Echec d'initialisation de SDL : %s\n", SDL_GetError());
	 return 1;
	
      }
	
   else
         printf("Bonjour le monde, SDL est initialisé avec succès.\n");
//création fenetre
  screen = SDL_SetVideoMode(1200, 800, 32,SDL_HWSURFACE | SDL_DOUBLEBUF);
	if ( screen == NULL )
	{
		fprintf(stderr, "Echec de creation de la fenetre de 300*300: %s.\n", SDL_GetError());
		return 1;
	}
//initialison enigme
init_enigme(&e);
while(quitter)
{
  if(e.etat==1)
    { 
       printf("mabrouk!!!!!!");
       //quitter=0;
       //blit
       //delay
       break;
    }
  if(e.etat==-1)
    {
       printf("Game over");
       //quitter=0;
       break;
    }
  if(e.etat==0)
    {
       if(e.num_tent==3)
         {
 		printf(" mizelk a syed 1");
         }
       if(e.num_tent==2)
         {
		printf(" mizelk a syed 2");
         }
       if(e.num_tent==1)
         {
		printf(" mizelk a syed 3");
         }
    }
  generer_enigme(&e,"les_enigmes.txt");
  afficherEnigme(&e,screen);
  printf("reponse: %s\n",reponse);

  
  SDL_Flip(screen);
  //SDL_PollEvent(&event);
  while(SDL_PollEvent(&event))
  {
  switch (event.type)
         { 
        // exit if the window is closed
		case SDL_QUIT:
                  {quitter = 0;
                   //SDL_Quit();
        	break;}
                case SDL_KEYDOWN:
                     {
                       
                       if(event.key.keysym.sym==SDLK_a)
                             {
                                strcpy(reponse,e.rep1.ch);
                                //resol_enigme(&e,reponse);
                              }
                       if(event.key.keysym.sym==SDLK_b)
                              {
                                  strcpy(reponse,e.rep2.ch);
                              }
                       if(event.key.keysym.sym==SDLK_c)
                              {
                                 strcpy(reponse,e.rep3.ch);
                              }
                       resol_enigme(&e,reponse);  
                      }
                     
         }
   
   SDL_Flip(screen);
  }

}
//liberation
libererenigme(&e);
Mix_CloseAudio();
TTF_Quit();
SDL_Quit();
printf("Iam out"); 
return 0;
}

#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

typedef struct
{
Mix_Music *son;
SDL_Surface *bg;
SDL_Rect posecran1;
SDL_Rect poscam1;

SDL_Rect posecran2;	
SDL_Rect poscam2;

int direction;
SDL_Surface *anim;
SDL_Rect posanim;

int num; //numero de la background 1|2

//animation:

int i,j;

SDL_Rect tab[3][4];//tableau pour stocker les images d'animation

}background;


typedef struct
{
int score;
int temps;
char nomJ[20];
SDL_Surface *s1,*s2,*s3;
SDL_Rect pos1,pos2,pos3; 
}infoscore;


void initBack(background *b,SDL_Surface *ecran,Mix_Music *musique);
void initAnim(background *b,SDL_Surface *ecran);
void afficherBack(background b, SDL_Surface *ecran);
void scrolling(background *b, int pas, SDL_Surface *ecran);
void animerBack(background *b,SDL_Surface *ecran);
void savescore(infoscore s, char *nomfichier); //sauvegarder s dans un fichier texte /// elle doit etre appelee a chaque fin de partie
void bestscore(char *nomfichier, infoscore trois[]);
void afficherbest(SDL_Surface *ecran, infoscore t[]);




#endif
#ifndef ENIGME_H_INCLUDED
#define ENIGME_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#define TAILLE_MAX 1000 // Tableau de taille 1000
typedef struct
{
  char ch[TAILLE_MAX];
  SDL_Surface *texte;
  SDL_Rect pos;
  SDL_Color color;
  TTF_Font *police;
  
}Rep;
typedef struct
{
  char ch[TAILLE_MAX];
  SDL_Surface *texte1;
  SDL_Surface *texte2;
  SDL_Rect pos1;
  SDL_Rect pos2;
  SDL_Color color;
  TTF_Font *police;
  
}Quest;

typedef struct
{
  SDL_Surface *sprite;
  //int direction;
  SDL_Rect posscreen;
  SDL_Rect possprite;

}Sprite;

typedef struct
{
  SDL_Surface *back_enigme;
  SDL_Rect pos_back;
  Sprite anim;
  Quest question;
  Rep rep1;
  Rep rep2;
  Rep rep3;
  char rep_corr[TAILLE_MAX];
  int etat;
  SDL_Surface *msg_res[2];
  int nb_tent;
  int num_tent;

}Enigme;
void init_question(Quest *q,int x,int y);
void init_reponse(Rep *r,int x,int y);
void init_enigme(Enigme *e);
void generer_enigme(Enigme *e, char *enigmes);
void afficherEnigme(Enigme *e, SDL_Surface *screen);
void animerEnigme(Enigme *e, SDL_Surface *screen);
void resol_enigme(Enigme *e, char *reponse);
void libererenigme(Enigme *e);
#endif


#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

typedef struct
{ 
  SDL_Surface *backgroundImg[205];
  SDL_Rect pos_back_ecran;
  SDL_Rect pos_back_affiche;
  Mix_Music *music_back;
  int etat_back;
  int nbr;
}background;

typedef struct
{
  SDL_Surface *buttImg[2];
  SDL_Rect pos_but_ecran;
  SDL_Rect pos_but_affiche;
  Mix_Chunk *son_but;
  int etat_but;
}button;

typedef struct
{
	SDL_Color color;
	SDL_Rect pos;
	TTF_Font *police;
	char ch[50];
        SDL_Surface *texteSurf;
	

}text;


typedef struct {
    int x, y;          // Position of the slider
    int width, height; // Dimensions of the slider
    int value;         // Current value of the slider (volume)
    SDL_Rect bar;      // Rectangle representing the slider bar
} Slider;

typedef struct {
    SDL_Surface *ImgSurf;       // Current value of the slider (volume)
    SDL_Rect pos;      // Rectangle representing the slider bar
} Image;


void initialiser_button(button *but, int num,int X,int Y);
void initialiser_background(background *back,int nbr,int nb,int X,int Y);
void afficher_button(SDL_Surface *ecran, button but);
void afficher_background(SDL_Surface *ecran, background back,int nbrImage);
void libererbut(button *but);
void libererback(background *back);
void initialiser_text(text *txt,int colorR,int colorG,int colorB,int posX,int posY,char textToShow[50],int fontSize);
void animation_background(SDL_Surface *ecran, background back,int imageNbr);
void initialiser_slider(Slider *volumeSlider);
void render(Slider *slider, SDL_Surface *ecran);
void initialiser_image(Image *img,int x,int y,char ch[]);
#endif


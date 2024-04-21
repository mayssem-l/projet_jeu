#include "background.h"
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>

void initBack(background *b,SDL_Surface *ecran,Mix_Music *musique)
{
	
b->bg=IMG_Load("yTxlv88-.jpeg");

if (b == NULL) {printf( "echec d'installer l'image!! \n" );}	



b->direction=-1 ;


//background 1 :

b->posecran1.x= 0;
b->posecran1.y= 0;
b->posecran1.w= ecran->w/2;
b->posecran1.h= ecran->h;

b->poscam1.x= 0;
b->poscam1.y= (b->bg->h - ecran->h)/2 ;
b->poscam1.w= ecran->w / 2 ;
b->poscam1.h= ecran->h ; 

//background 2 :

b->posecran2.x= ecran->w/2;
b->posecran2.y= 0;
b->posecran2.w= ecran->w/2;
b->posecran2.h= ecran->h;

b->poscam2.x= 0;
b->poscam2.y= (b->bg->h - ecran->h)/2 ;
b->poscam2.w= ecran->w / 2 ;
b->poscam2.h= ecran->h ; 

//musique:
musique = Mix_LoadMUS("Y2meta.app - Cyberpunk 2077 OST - Main Theme (128 kbps).mp3");
Mix_PlayMusic(musique,-1);

}

void initAnim(background *b,SDL_Surface *ecran)
{
b->i=0;
	b->j=0;
	b->anim=IMG_Load("clockf.png");
for (int i = 0; i < 4; i++)
{
	b->tab[0][i].x=i*58;
	b->tab[0][i].y=0;
	b->tab[0][i].h=58;
	b->tab[0][i].w=58;
}

for (int i = 0; i < 4; i++)
{
	b->tab[1][i].x=i*58;
	b->tab[1][i].y=0;
	b->tab[1][i].h=58;
	b->tab[1][i].w=58;
}

for (int i = 0; i < 4; i++)
{
	b->tab[2][i].x=i*58;
	b->tab[2][i].y=0;
	b->tab[2][i].h=58;
	b->tab[2][i].w=58;
}

b->posanim.x=270;
b->posanim.y=05;
b->posanim.w=b->anim->w/4;
b->posanim.h=b->anim->h/3;
}

void afficherBack(background b, SDL_Surface *ecran)
{
/*SDL_Surface *img=SDL_CreateRGBSurface(SDL_SWSURFACE,560,360,32,0,0,0,0);
if(img==NULL){
	fprintf(stderr,"erreur lors de la creation de la surface redimensionnee : %s \n",SDL_GetError());
	return;
}
SDL_SoftStretch(b.bg,NULL,img,NULL);*/

SDL_BlitSurface(b.bg,&b.poscam1,ecran,&(b.posecran1));

SDL_BlitSurface(b.bg,&b.poscam2,ecran,&(b.posecran2));

SDL_BlitSurface(b.anim,&b.tab[b.i][b.j],ecran,&b.posanim);
}

void scrolling(background *b, int pas, SDL_Surface *ecran)
{

switch(b->direction){
	case 0:
		if(b->num==1){b->poscam1.x += pas;}
		else{b->poscam2.x += pas;}
        b->direction=-1;
	break;
	case 1:
		if(b->num==1){b->poscam1.x -= pas;}
		else{b->poscam2.x -= pas;}
		b->direction=-1;
	break;
	case 2:
		if(b->num==1){b->poscam1.y -= pas;}
		else{b->poscam2.y -= pas;}
		b->direction=-1;
	break;
	case 3:
		if(b->num==1){b->poscam1.y += pas;}
		else{b->poscam2.y += pas;}
		b->direction=-1;
	break;
		  }

if (b->poscam1.x >= b->bg->w/2){ b->poscam1.x=0; b->posecran1.x= 0; SDL_BlitSurface(b->bg,&b->poscam1,ecran,&(b->posecran1));}
if (b->poscam2.x >= b->bg->w/2){ b->poscam2.x=0; b->posecran2.x= ecran->w/2; SDL_BlitSurface(b->bg,&b->poscam2,ecran,&(b->posecran2));}

if (b->poscam1.x < 0){ b->poscam1.x=ecran->w; b->posecran1.x= 0; SDL_BlitSurface(b->bg,&b->poscam1,ecran,&(b->posecran1));}
if (b->poscam2.x < 0){ b->poscam2.x=ecran->w; b->posecran2.x= ecran->w/2; SDL_BlitSurface(b->bg,&b->poscam2,ecran,&(b->posecran2));}

if (b->poscam1.y >= b->bg->h){ b->poscam1.y=(b->bg->h - ecran->h)/2; b->posecran1.y= 0; SDL_BlitSurface(b->bg,&b->poscam1,ecran,&(b->posecran1));}
}

void animerBack(background *b,SDL_Surface *ecran)
{
	//b->posanim.x+=1;

	if(b->j<4){
		b->j++;
		SDL_Delay(1000);
	}
	else {
		
		b->i++;
		b->j=0;//ana
		SDL_Delay(1000);
	}
	if((b->i==2) /*|| (b->j==3)*/){ //b->i=0;
		if(b->j<4){ 
		b->j++;
		SDL_Delay(1000);
		}
		else{
		b->i=0;
		b->j=0;
		SDL_Delay(1000);
		}
	}	
	//else b->j++; SDL_Delay(1000);
	

	/*else{
		
		b->j++;
		SDL_BlitSurface(b->anim,&b->tab[b->i][b->j],ecran,&b->posanim);
		SDL_Delay(150);
	}*/
	//SDL_BlitSurface(b->anim,&b->tab[b->i][b->j],ecran,&b->posanim);

}


void savescore(infoscore s, char *nomfichier)
{
	FILE *file = fopen(nomfichier, "a"); 
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    fprintf(file, "%d %d %s\n", s.score, s.temps, s.nomJ);
    fclose(file);
}
void bestscore(char *nomfichier, infoscore trois[])
{
	 FILE *file = fopen(nomfichier, "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    int i = 0;
    while (fscanf(file, "%d %d %s", &trois[i].score, &trois[i].temps, trois[i].nomJ) != EOF && i < 3) {
        i++;
    }
    fclose(file);

    int j;
    infoscore temp;
    for (i = 0; i < 3 - 1; i++) {
        for (j = 0; j < 3 - i - 1; j++) {
            if (trois[j].score < trois[j + 1].score || (trois[j].score == trois[j + 1].score && trois[j].temps > trois[j + 1].temps)) {
                temp = trois[j];
                trois[j] = trois[j + 1];
                trois[j + 1] = temp;
            }
        }
    }
}
void afficherbest(SDL_Surface *ecran, infoscore t[])

{
	//SDL_Surface *texte = NULL;
    SDL_Color couleur = {255, 255, 255}; // Couleur du texte : blanc
    TTF_Font *police = TTF_OpenFont("arial.ttf",30);
	if(police==NULL){
		fprintf(stderr, "Echec de creation de la police: %s.\n", SDL_GetError());
	}

    /*SDL_Rect position;
    position.x = 100;
    position.y = 100;*/
	t[0].pos1.x=100;
	t[0].pos1.y=100;
	t[1].pos2.x=100;
	t[1].pos2.x=180;
	t[2].pos3.x=100;
	t[2].pos3.y=260;

    char chaine[50];

    for (int i = 0; i < 3; i++) {
        sprintf(chaine, "%s %d %d", t[i].nomJ, t[i].score, t[i].temps);
        t[0].s1 = TTF_RenderText_Blended(police, chaine, couleur);
        t[1].s2 = TTF_RenderText_Blended(police, chaine, couleur);
		t[2].s3 = TTF_RenderText_Blended(police, chaine, couleur);
		SDL_BlitSurface(t[0].s1, NULL,ecran, &t[0].pos1);
		SDL_BlitSurface(t[1].s2, NULL,ecran, &t[1].pos2);
		SDL_BlitSurface(t[2].s3, NULL,ecran, &t[2].pos3);
        
    }
}

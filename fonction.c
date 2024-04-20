#include "fonction.h"

void initialiser_button(button *but, int num,int X,int Y)
{ 
  char ch[9];
  char chaine[3];
  strcpy(ch,"but");
  for(int i=0;i<2;i++)
  {
    sprintf(chaine,"%d",num);
    num++;
    strcat(ch,chaine);
    strcat(ch,".png");
    but->buttImg[i]=IMG_Load(ch);
    if(but->buttImg[i]==NULL)
      {printf("unable to load image button %s \n",SDL_GetError());
       return;
      }
    
    strcpy(ch,"but");
  }
  but->pos_but_ecran.x=X;
  but->pos_but_ecran.y=Y;
  but->pos_but_affiche.x=0;
  but->pos_but_affiche.y=0;
  but->pos_but_affiche.h=but->buttImg[0]->h;
  but->pos_but_affiche.w=but->buttImg[0]->w;
  but->etat_but=0;
  but->son_but=Mix_LoadWAV("button1.wav");
  if( but->son_but == NULL )
    {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
       
    }
}

void initialiser_background(background *back,int nbr,int nb,int X,int Y)
{ 
  char ch[50],num[50];
  back->nbr=nbr;
  back->etat_back=0;
  for(int i=0;i< back->nbr ; i++)
	{
           strcpy(ch,"BG Animated/back");
	   sprintf(num,"%d",nb+1);
           nb++;
	   strcat(ch,num);
	   strcat(ch,".png");
	   back->backgroundImg[i]=IMG_Load(ch);
	   if(back->backgroundImg[i]==NULL)
	     {
		printf("unable to load image background %s \n",SDL_GetError());
                return;
	     }
	}
	back->pos_back_ecran.x=X;
        back->pos_back_ecran.y=Y;
        back->pos_back_affiche.x=0;
	back->pos_back_affiche.y=0;
	back->pos_back_affiche.h=back->backgroundImg[0]->h;
	back->pos_back_affiche.w=back->backgroundImg[0]->w;
	back->music_back=Mix_LoadMUS("Menusound.mp3");
        if( back->music_back == NULL )
    	{
        	printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
       
    	}
}
void afficher_button(SDL_Surface *ecran, button but)
{

  SDL_BlitSurface(but.buttImg[but.etat_but],&but.pos_but_affiche,ecran,&but.pos_but_ecran);
}
void afficher_background(SDL_Surface *ecran, background back,int nbrImage)
{
  
  SDL_BlitSurface(back.backgroundImg[nbrImage],&back.pos_back_affiche,ecran,&back.pos_back_ecran);

}

void animation_background(SDL_Surface *ecran, background back,int imageNbr)
{
 //for(int i=0;i<200;i++)
  { 
    afficher_background(ecran,back,imageNbr);
    
    
    //SDL_Delay(0.1);
  }	
}
void libererbut(button *but)
{
	SDL_FreeSurface(but->buttImg[0]);
	SDL_FreeSurface(but->buttImg[1]);
        Mix_FreeChunk(but->son_but);
}
void libererback(background *back)
{
   for(int i=0 ; i< back->nbr ; i++)
	{
		SDL_FreeSurface(back->backgroundImg[i]);
	}
   Mix_FreeMusic(back->music_back);
}

 

void initialiser_text(text *txt,int colorR,int colorG,int colorB,int posX,int posY,char textToShow[50],int fontSize)
{
 
  txt->police=TTF_OpenFont("CyborgPunk.ttf",fontSize);
  txt->color.r=colorR;
  txt->color.g=colorG;
  txt->color.b=colorB;
  txt->pos.x=posX;
  txt->pos.y=posY;
  strcpy(txt->ch,textToShow);
  txt->texteSurf=TTF_RenderText_Solid(txt->police,txt->ch,txt->color);
 
 	
} 



void render(Slider *slider, SDL_Surface *ecran) {
    

    // Draw the slider bar on the screen
    SDL_FillRect(ecran, &slider->bar, SDL_MapRGB(ecran->format, 255, 255, 255));

    Mix_VolumeMusic(slider->value);

    // Update the screen
    
}

void initialiser_slider(Slider *volumeSlider)
{
    volumeSlider->x = 545;
    volumeSlider->y = 505;
    volumeSlider->width = 140;
    volumeSlider->height = 20;
    volumeSlider->value = 50; // Initial volume value
    volumeSlider->bar.x = volumeSlider->x;
    volumeSlider->bar.y = volumeSlider->y;
    volumeSlider->bar.w = volumeSlider->width-130;
    volumeSlider->bar.h = volumeSlider->height;
}


void initialiser_image(Image *img,int x,int y,char ch[])
{ 
  
  img->ImgSurf=IMG_Load(ch);
  img->pos.x=x;
  img->pos.y=y;
  
}



 

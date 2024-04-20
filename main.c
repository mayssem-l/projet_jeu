#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "fonction.h"


int main(int argc, char** argv)
{
  SDL_Surface *ecran;
  
  Image img_volup;

  Image img_voldown;

  Image img_vol;

  Image img_bar;
  
  	
  //les boutons du menu principal
  button but_play, but_options, but_quit, but_full,but_win;
  //les boutons du menu options
  button  but_screenmode, but_back;
  //les boutons du menu play
 // button but_returnmenu;
  //les backgrounds
  background back_menu,back_options,back_play;
  SDL_Event event;
  int quitter=1,niveau=0;
  text txt;
  text txt2;
  Slider volumeSlider;
//Initialisation
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
  ecran = SDL_SetVideoMode(1200, 800, 32,SDL_HWSURFACE | SDL_DOUBLEBUF);
	if ( ecran == NULL )
	{
		fprintf(stderr, "Echec de creation de la fenetre de 300*300: %s.\n", SDL_GetError());
		return 1;
	}
//initialiser les boutons et les backgrounds

initialiser_background(&back_menu,200,0,0,0);
initialiser_background(&back_play,1,200,0,0);
initialiser_background(&back_options,1,200,0,0);
initialiser_button(&but_play,0,480,250);
initialiser_button(&but_options,2,480,350);
initialiser_button(&but_quit,4,480,450);
initialiser_button(&but_back,6,25,25);

initialiser_button(&but_full,12,625,270);
initialiser_button(&but_win,14,330,270);

initialiser_slider(&volumeSlider);
initialiser_image(&img_bar,500,500,"but11.png");
initialiser_image(&img_volup,690,480,"but9.png");
initialiser_image(&img_voldown,480,480,"but8.png");
initialiser_image(&img_vol,480,400,"but10.png");
//initialisation du texte
/*initialiser_text(&txt,255,255,255,370,60,"BITSTORM :",60);
initialiser_text(&txt2,255,255,255,350,160,"REBELLION OF THE MACHINES",25);*/
initialiser_text(&txt,255,255,255,70,60,"BITSTORM :",60);
initialiser_text(&txt2,255,255,255,50,160,"REBELLION OF THE MACHINES",25);
//Play Background Music
Mix_PlayMusic(back_menu.music_back,-1);
//fin de l'initialisation
int nbrImage=0;
while(quitter)
{
  //affichage
  if(niveau==0){
   //afficher_background(ecran,back_menu,nbrImage);
   if(nbrImage==200)
 	nbrImage=0;
   animation_background(ecran,back_menu,nbrImage++);
   afficher_button(ecran,but_play);
   afficher_button(ecran,but_options);
   afficher_button(ecran,but_quit);
   SDL_BlitSurface(txt.texteSurf,NULL,ecran,&txt.pos);
   SDL_BlitSurface(txt2.texteSurf,NULL,ecran,&txt2.pos);
   }
  else if(niveau==1){
	afficher_background(ecran,back_play,0);
	afficher_button(ecran,but_back);
  
  }
  else if(niveau==2){
	afficher_background(ecran,back_options,0);
	afficher_button(ecran,but_back);
	SDL_BlitSurface(img_bar.ImgSurf,NULL,ecran,&img_bar.pos);
        SDL_BlitSurface(img_volup.ImgSurf,NULL,ecran,&img_volup.pos);
	SDL_BlitSurface(img_voldown.ImgSurf,NULL,ecran,&img_voldown.pos);
	SDL_BlitSurface(img_vol.ImgSurf,NULL,ecran,&img_vol.pos);
        render(&volumeSlider, ecran);
        afficher_button(ecran,but_full);
	afficher_button(ecran,but_win);
	
  }
  
  SDL_Flip(ecran);
  SDL_PollEvent(&event);
  switch(event.type)
  {  case SDL_QUIT:
     quitter=0;
     break;
     case SDL_MOUSEMOTION:
	switch(niveau)
  	{
	case 0:
	      if(event.motion.x>=480 && event.motion.x <= 480+272 && event.motion.y>=250 && event.motion.y<= 250+83)
		 {
		  but_play.etat_but=1;
		  Mix_PlayChannel(-1,but_play.son_but,0);
		 }
	       else{but_play.etat_but=0;}
	       if(event.motion.x>=480 && event.motion.x<=480+272 && event.motion.y >= 350 && event.motion.y <= 350+83)
		 {but_options.etat_but=1;
		  Mix_PlayChannel(-1,but_options.son_but,0);
		 }
	       else{but_options.etat_but=0;}
	       if(event.motion.x >= 480 && event.motion.x <= 480+272 && event.motion.y >= 450 && event.motion.y <= 450+83)
		 {but_quit.etat_but=1;
		  Mix_PlayChannel(-1,but_quit.son_but,0);
		 }
	       else{but_quit.etat_but=0;}   
	break;
	case 1:
	      if(event.motion.x>=25 && event.motion.x <= 25+272 && event.motion.y>=25 && event.motion.y<= 25+83)
		 {
		  but_back.etat_but=1;
		  Mix_PlayChannel(-1,but_back.son_but,0);
		 }
	       else{but_back.etat_but=0;}
	       
	break;
	case 2:
	      if(event.motion.x>=25 && event.motion.x <= 25+272 && event.motion.y>=25 && event.motion.y<= 25+83)
		 {
		  but_back.etat_but=1;
		  Mix_PlayChannel(-1,but_back.son_but,0);
		 }
	       else{but_back.etat_but=0;}
	     if(event.motion.x>=543 && event.motion.x<=670 && event.motion.y>=500 && event.motion.y<=525)
		{
		      	if (event.motion.x >= volumeSlider.x && event.motion.x <= volumeSlider.x + volumeSlider.width) {
		            volumeSlider.bar.x = event.motion.x;
		            volumeSlider.value = (event.motion.x - volumeSlider.x) * 100 / volumeSlider.width;
		        } 
		}
	       if(event.motion.x>=625 && event.motion.x <= 625+272 && event.motion.y>=270 && event.motion.y<= 270+83)
		 {
		  but_full.etat_but=1;
		  Mix_PlayChannel(-1,but_full.son_but,0);
		 }
	       else{but_full.etat_but=0;}
	       if(event.motion.x>=330 && event.motion.x<=330+272 && event.motion.y >= 270 && event.motion.y <= 270+83)
		 {but_win.etat_but=1;
		  Mix_PlayChannel(-1,but_win.son_but,0);
		 }
		else{but_win.etat_but=0;}
	break;
	}       
    break;
    case SDL_MOUSEBUTTONDOWN:
	if (event.button.button == SDL_BUTTON_LEFT)
	{
	 switch(niveau)
	  	{
		case 0:
		   if(event.motion.x>=480 && event.motion.x <= 480+272 && event.motion.y>=250 && event.motion.y<= 250+83)
			 {
			  niveau=1;
			 }
		    if(event.motion.x>=480 && event.motion.x<=480+272 && event.motion.y >= 350 && event.motion.y <= 350+83)
			 {
			  niveau=2;
			 }
		    if(event.motion.x >= 480 && event.motion.x <= 480+272 && event.motion.y >= 450 && event.motion.y <= 450+83)
			 {
			  quitter=0;
			 }	
		break;
	        case 1:
		   if(event.motion.x>=25 && event.motion.x <= 25+272 && event.motion.y>=25 && event.motion.y<= 25+83)
			 {
			  niveau=0;
			 }
		    	
		break;
		case 2:
		   if(event.motion.x>=25 && event.motion.x <= 25+272 && event.motion.y>=25 && event.motion.y<= 25+83)
			 {
			  niveau=0;
			 }
		     if (event.button.x >= volumeSlider.x && event.button.x <= volumeSlider.x + volumeSlider.width) {
                    volumeSlider.bar.x = event.button.x;
                    volumeSlider.value = (event.button.x - volumeSlider.x) * 100 / volumeSlider.width;
                     }
		    if(event.motion.x>=625 && event.motion.x <= 625+272 && event.motion.y>=270 && event.motion.y<= 270+83)
			 {
			   ecran = SDL_SetVideoMode(1920, 1080, 32, SDL_FULLSCREEN);
			 }	
		    if(event.motion.x>=330 && event.motion.x <= 330+272 && event.motion.y>=270 && event.motion.y<= 270+83)
			 {
			  ecran = SDL_SetVideoMode(1200, 800, 32,SDL_HWSURFACE | SDL_DOUBLEBUF);
			 }
		break;
	       }	 
	}
     break;
     case SDL_KEYDOWN:
          switch(niveau)
                {
                  case 0: 
                      if(event.key.keysym.sym==SDLK_ESCAPE || event.key.keysym.sym==SDLK_q)
                      {
		       Mix_PlayChannel(-1,but_quit.son_but,0);
		       quitter=0;
                       }
                      if(event.key.keysym.sym==SDLK_p)
                        {
		         Mix_PlayChannel(-1,but_play.son_but,0);
                         niveau=1;}
                      if(event.key.keysym.sym==SDLK_o)
                        {Mix_PlayChannel(-1,but_options.son_but,0);
                         niveau=2;}
                  break;
                  case 1: 
                      if(event.key.keysym.sym==SDLK_ESCAPE || event.key.keysym.sym==SDLK_b)
                        {Mix_PlayChannel(-1,but_back.son_but,0);
                         niveau=0;}
                  break;
                  case 2:
                       if(event.key.keysym.sym==SDLK_ESCAPE || event.key.keysym.sym==SDLK_b)
                        {Mix_PlayChannel(-1,but_back.son_but,0);
                         niveau=0;}
                       if(event.key.keysym.sym==SDLK_w)
                        {Mix_PlayChannel(-1,but_win.son_but,0); 
                         ecran = SDL_SetVideoMode(1200, 800, 32,SDL_HWSURFACE | SDL_DOUBLEBUF);}
                       if(event.key.keysym.sym==SDLK_f)
                        {Mix_PlayChannel(-1,but_full.son_but,0); 
                         ecran = SDL_SetVideoMode(1920, 1080, 32, SDL_FULLSCREEN);}
                 break;     
                }
     break;

  }
}
libererbut(&but_play);
libererbut(&but_back);
libererbut(&but_options);
libererbut(&but_quit);
libererbut(&but_full);
libererbut(&but_win);
libererback(&back_play);
libererback(&back_menu);
libererback(&back_options);
SDL_FreeSurface(img_volup.ImgSurf);
SDL_FreeSurface(img_voldown.ImgSurf);
SDL_FreeSurface(img_vol.ImgSurf);
SDL_FreeSurface(img_bar.ImgSurf);
Mix_CloseAudio();
TTF_CloseFont(txt.police);
TTF_CloseFont(txt2.police);
TTF_Quit();
SDL_Quit();
printf("Iam out");  
return 0;
}


 



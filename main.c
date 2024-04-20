#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "fonction.h"
#include "entity.h"
#include "ennemie.h"
#include "enigme.h"
int main(int argc, char** argv)
{
  SDL_Surface *ecran;
  
  Image img_volup;

  Image img_voldown;

  Image img_vol;

  Image img_bar;
  
/////////////menu_declaration//////////

 	
  //les boutons du menu principal
  button but_play, but_options, but_quit, but_full,but_win;
  //les boutons du menu options
  button  but_ecranmode, but_back;
  //les boutons du menu play
 // button but_returnmenu;
  //les backgrounds
  background back_menu,back_options,back_play;
  SDL_Event event;
  int quitter=1,niveau=0;
  text txt;
  text txt2;
  Slider volumeSlider;
///////////tache_entite_declaration/////////////

  //int hauteur_fenetre = 720,done=1,largeur_fenetre = 1280;
  
        int t,a=1,an=1;
	SDL_WM_SetCaption("CITY-OF-THE-FUTUR", NULL); 
 	SDL_Surface *background ;
	SDL_Surface *sorry ;
	SDL_Rect pos_sorry ; 
	SDL_Rect background_pos;
	background = IMG_Load("background.jpeg");
	background_pos.x = 0;
	background_pos.y = 0;
	sorry=IMG_Load("youlost.png");
	pos_sorry.x=300;
	pos_sorry.y=300;
/////////////enigme_declaration/////////////////////
  //SDL_Surface *screen;
  Enigme eg;
  char reponse[TAILLE_MAX]="";
  int compt=1;


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

//////menu_init///////////////////////////////////
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


/////////////////////////////////////////////tache_entite//////////////////////////////////////
//initialisation//

	personnage p;
	entity e;
	Ennemie en;
	 

	initialiser_perso (&p) ;
	initentity (&e) ;
	initEnnemi (&en) ;
        SDL_EnableKeyRepeat(200, 0);

///////////////////tache_enigme///////////////////////

init_enigme(&eg);

/////////////////////////////////////////////
while(quitter)
{
  printf("boucle jeu \n");
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
        printf("niveau 1\n");
	/*/afficher_background(ecran,back_play,0);
	afficher_button(ecran,but_back);*/
        SDL_BlitSurface(background,NULL,ecran,&background_pos);
	if(detect_collision(&p,&e)) a=gestion(&e);

	if (a){ 
              afficher_perso(p ,ecran);afficherentity(e ,ecran);
              //niveau=3;  
              //generer_enigme(&eg,"les_enigmes.txt");   
              }
        else {
               if(compt==1){compt++;niveau=3; }
             }
             
   	if (detect_collision_ennemie(&p,&en)) an=gerer(&en);
   	
   	if (an) {afficher_perso(p ,ecran);afficherEnnemi (en ,ecran);}
   	else{
    	 
   	SDL_BlitSurface(sorry,NULL,ecran,&pos_sorry); 
	}
	SDL_Delay(10);
        //SDL_Flip(ecran);
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
  else if(niveau==3)
  {
                       if(eg.etat==1)
                         { 
                           printf("mabrouk!!!!!!");
                           //quitter=0;
                           //blit
                           //delay
                           niveau=1;
                           //quitter=1;
                           //break;
                          }
                       if(eg.etat==-1)
                         {
                           printf("Game over");
                           //quitter=0;
                           //niveau=0;
                           //break;
                         }
                       if(eg.etat==0)
                         {
                          if(eg.num_tent==3)
                            {
 		             printf(" mizelk a syed 1");
                            }
                          if(eg.num_tent==2)
                            {
		             printf(" mizelk a syed 2");
                            }
                          if(eg.num_tent==1)
                            {
		             printf(" mizelk a syed 3");
                            }
                         }
  
                    generer_enigme(&eg,"les_enigmes.txt");
                    afficherEnigme(&eg,ecran);
                    printf("reponse: %s\n",reponse);
                    

  }
  SDL_Flip(ecran);
  
  while(SDL_PollEvent(&event))
  {
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
                      /*if(event.key.keysym.sym==SDLK_ESCAPE || event.key.keysym.sym==SDLK_b)
                        {Mix_PlayChannel(-1,but_back.son_but,0);
                         niveau=0;}*/
                      if(event.key.keysym.sym==SDLK_ESCAPE) niveau=0;
                      if(event.key.keysym.sym==SDLK_RIGHT)  p.perso_pos.x += 10;
                      if(event.key.keysym.sym==SDLK_LEFT)   p.perso_pos.x -= 10;
                      if(event.key.keysym.sym==SDLK_UP)     p.perso_pos.y -= 10;
                      if(event.key.keysym.sym==SDLK_DOWN)   p.perso_pos.y += 10;
                      
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
                 case 3:
                      if(event.key.keysym.sym==SDLK_a)
                             {
                                strcpy(reponse,eg.rep1.ch);
                                //resol_enigme(&e,reponse);
                              }
                       if(event.key.keysym.sym==SDLK_b)
                              {
                                  strcpy(reponse,eg.rep2.ch);
                              }
                       if(event.key.keysym.sym==SDLK_c)
                              {
                                 strcpy(reponse,eg.rep3.ch);
                              }
                       if(event.key.keysym.sym==SDLK_d)
                              {
                                 strcpy(reponse,eg.rep4.ch);
                              }
                       resol_enigme(&eg,reponse);
                 break;  
                         
                }
     break;

  }

}
  update_entity(&e);
  update_ennemie (&en,&p);
printf("quitter: %d\n",quitter);
}
////////////////////liberer_entite/////////////////
	SDL_FreeSurface(background);
	SDL_FreeSurface(sorry);
//////////////////liberer_enigme/////////////
libererenigme(&eg);
/////////////


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


 



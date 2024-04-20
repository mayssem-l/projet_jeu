
#include "ennemie.h"




int 
nb_frame1=12 ,
ennemie_h=100,
ennemie_w=100,
ennemie_y=100,
ennemie_x=100;


void init_tab_anim_ennemie(SDL_Rect *clip,Ennemie *e)
{	


for (int j=0;j<nb_frame1; j++)
	{
	clip[j].h=ennemie_h;
	clip[j].w=ennemie_w;
	clip[j].x = j*ennemie_w;
	clip[j].y = 0;
        }


}

void initEnnemi(Ennemie *e)
{

    e->ennemie = IMG_Load("ENNEMIE.png");

    e->pos_ennemie.x = 900;
    e->pos_ennemie.y = 400;
    init_tab_anim_ennemie(e->anim_ennemie,e);
    e->frame_ennemie=0;
    e->direction=0;  
    e->col=0;
    e->show=1;
    
    
}

void afficherEnnemi(Ennemie e, SDL_Surface *screen)
{
   
   SDL_BlitSurface(e.ennemie,&e.anim_ennemie[e.frame_ennemie], screen, &e.pos_ennemie);
  
  

}




void animerEnnemi(Ennemie *e)
{   if (e->frame_ennemie >=0 && e->frame_ennemie <(nb_frame1-1)) 
 e->frame_ennemie++;
    if ( e->frame_ennemie ==(nb_frame1-1)) 
       e->frame_ennemie=0;
}


void update_ennemie(Ennemie *e,personnage *p)
{ 	
	animerEnnemi(e);
	

}




int detect_collision_ennemie(personnage *p, Ennemie *e)
{
	

if ((p->perso_pos.x + p->perso_pos. w< e->pos_ennemie. x) || (p->perso_pos.x> e->pos_ennemie. x + e->pos_ennemie. w) ||
(p->perso_pos.y + p->perso_pos.h< e->pos_ennemie. y) || (p->perso_pos.y> e->pos_ennemie. y + e->pos_ennemie. h ))
return 0;
else 
return 1;
 
}

int gerer(Ennemie *e) {
	
	e->show=0;
	
	return 0; 
}









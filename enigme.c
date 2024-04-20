#include "enigme.h"
#define TAILLE_MAX 1000 // Tableau de taille 1000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void init_reponse(Rep *r,int x,int y)
{
  r->ch[0]='\0';
  //printf("iam here\n");
  r->color.r=0;
  r->color.g=0;
  r->color.b=0;
  r->police=TTF_OpenFont("reponses.ttf",20);//fontsize
  //qr->texte=TTF_RenderText_Solid(qr->police,qr->ch,qr->color);
  r->pos.x=x;//x;//x inserer la valeur apres
  r->pos.y=y;//y;//y inserer la valeur apres
  printf("function init rep\n");
}
void init_question(Quest *q,int x,int y)
{
  q->ch[0]='\0';
  //printf("iam here\n");
  q->color.r=0;
  q->color.g=0;
  q->color.b=0;
  q->police=TTF_OpenFont("conthrax.ttf",15);//fontsize
  //qr->texte=TTF_RenderText_Solid(qr->police,qr->ch,qr->color);
  q->pos1.x=x;//x;//x inserer la valeur apres
  q->pos1.y=y;//y;//y inserer la valeur apres
  q->pos2.x=x+30;//x;//x inserer la valeur apres
  q->pos2.y=y+30;//y;//y inserer la valeur apres
  
  printf("function init question\n");
}
void init_enigme(Enigme *e)
{ 
   e->back_enigme=IMG_Load("back_Enigme.png");
   if(e->back_enigme==NULL)
      {
          printf("unable to load background enigme %s \n",SDL_GetError());
          return;
      }
   e->pos_back.x=0;
   e->pos_back.y=0;
   e->pos_back.w=e->back_enigme->w;
   e->pos_back.h=e->back_enigme->h;
   e->anim.sprite=IMG_Load("hourglass_spritesheet.png");
   if(e->anim.sprite==NULL)
      {
          printf("unable to load spritesheet anim_engime %s \n",SDL_GetError());
          return;
      }
   
   //e->anim.direction=0;
   e->anim.posscreen.x=50;
   e->anim.posscreen.y=50;
   e->anim.possprite.x=0;
   e->anim.possprite.y=0;
   e->anim.possprite.h=96;
   e->anim.possprite.w=96;
   init_question(&(e->question),185,180);
   init_reponse(&(e->rep1),270,445);
   init_reponse(&(e->rep2),815,445);
   init_reponse(&(e->rep3),180,630);
   init_reponse(&(e->rep4),815,630);
   e->rep_corr[0]='\0';
   e->etat=0;//non encore resolu
   e->msg_res[0]=IMG_Load("resultat_correct.png");
   if(e->msg_res[0]==NULL)
             {printf("unable to load image resultat correct %s \n",SDL_GetError());
             return;
             }
   e->msg_res[1]=IMG_Load("resultat_incorrect.png");
   if(e->msg_res[1]==NULL)
             {printf("unable to load image resultat incorrect %s \n",SDL_GetError());
             return;
             }
   e->nb_tent=3;
   e->num_tent=1;
   printf("function init enigme\n");
   
}
void generer_enigme(Enigme *e, char *les_enigmes)
{
    
    printf("fonction generer_enigme\n");
    int num_ligne=1;
    FILE* fichier = NULL;
    char chaine[TAILLE_MAX] = ""; // Chaîne vide de taille TAILLE_MAX
    char *token;
    char question[TAILLE_MAX];
    char reponse1[TAILLE_MAX];
    char reponse2[TAILLE_MAX];
    char reponse3[TAILLE_MAX];
    char reponse_correcte[TAILLE_MAX];

    fichier = fopen("les_enigmes", "r");
 
    if (fichier != NULL)
    {
        fgets(chaine, TAILLE_MAX, fichier);
        while (num_ligne < e->num_tent && fgets(chaine, TAILLE_MAX, fichier) != NULL) 
        {
            num_ligne++; // Incrémentation du numéro de ligne
        }
        // Si nous avons atteint la ligne désirée
        if (num_ligne == e->num_tent)
        {
            printf("%s", chaine); // On affiche la chaîne
            token = strtok(chaine, "/");
            strcpy((e->question).ch,token);
            token = strtok(NULL, "/");
            strcpy((e->rep1).ch,token);
            token = strtok(NULL, "/");
            strcpy((e->rep2).ch,token);
            token = strtok(NULL, "/");
            strcpy((e->rep3).ch,token);
            token = strtok(NULL, "/");
            strcpy((e->rep4).ch,token);
            token = strtok(NULL, "/");
            strcpy(e->rep_corr,token);
            // Affichage des parties de la chaîne
            printf("Question : %s\n", (e->question).ch);
            printf("Réponse 1 : %s", (e->rep1).ch);
            printf("+");
            printf("Réponse 2 : %s\n", (e->rep2).ch);
            printf("Réponse 3 : %s\n", (e->rep3).ch);
            printf("Réponse 4 : %s\n", (e->rep4).ch);
            printf("Réponse correcte : %s", e->rep_corr);
            printf("+");
            printf("num_ligne:%d\n",num_ligne);
            printf("question:%s\n",e->question.ch);
            char part_ch1[TAILLE_MAX]="";
            char part_ch2[TAILLE_MAX]="";
            token=strtok(e->question.ch,"|");
            strcpy(part_ch1,token);
            token=strtok(NULL,"|");
            strcpy(part_ch2,token);
            e->question.texte1=TTF_RenderText_Solid(e->question.police,part_ch1,e->question.color);
            e->question.texte2=TTF_RenderText_Solid(e->question.police,part_ch2,e->question.color);
            e->rep1.texte=TTF_RenderText_Solid(e->rep1.police,(e->rep1).ch,e->rep1.color);
            e->rep2.texte=TTF_RenderText_Solid(e->rep2.police,(e->rep2).ch,e->rep2.color);
            e->rep3.texte=TTF_RenderText_Solid(e->rep3.police,(e->rep3).ch,e->rep3.color);
            e->rep4.texte=TTF_RenderText_Solid(e->rep4.police,(e->rep4).ch,e->rep4.color);
            //e->question.texte=TTF_RenderText_Solid(e->question.police,(e->question).ch,e->question.color);
 
        }
        else
        {
            printf("La ligne désirée n'existe pas dans le fichier.\n");
        }
        fclose(fichier);
    }
    else
    {
       printf("Impossible d'ouvrir le fichier.\n");
    }
    printf("fonction generer terminéé.\n");
   
}

void animerEnigme(Enigme *e, SDL_Surface *screen)
{ int j,i;
  for(i=0;i<1;i++)
    { 
       for(j=0;j<5;j++)
          {  
             SDL_BlitSurface(e->back_enigme,NULL,screen,&e->pos_back);
             SDL_BlitSurface(e->question.texte1,NULL,screen,&e->question.pos1);
             SDL_BlitSurface(e->question.texte2,NULL,screen,&e->question.pos2);
             SDL_BlitSurface(e->rep1.texte,NULL,screen,&e->rep1.pos);
             SDL_BlitSurface(e->rep2.texte,NULL,screen,&e->rep2.pos);
             SDL_BlitSurface(e->rep3.texte,NULL,screen,&e->rep3.pos);
             SDL_BlitSurface(e->rep4.texte,NULL,screen,&e->rep4.pos);
             SDL_Flip(screen);
             SDL_BlitSurface(e->anim.sprite,&e->anim.possprite,screen,&e->anim.posscreen);
             SDL_UpdateRect(screen, e->anim.posscreen.x, e->anim.posscreen.y,e->anim.possprite.w,e->anim.possprite.h);
             SDL_Delay(200);
             e->anim.possprite.x = e->anim.possprite.x + e->anim.possprite.w;
		
             
          }
       e->anim.possprite.x =0;	
       //e->anim.possprite.y  = e->anim.possprite.y + e->anim.possprite.h;
       
    }
   printf("function animer enigme\n");
}
void afficherEnigme(Enigme *e, SDL_Surface *screen)
{ 
   //int quitter=0;
   //SDL_Event Event;
   //SDL_BlitSurface(e->back_enigme,NULL,screen,&e->pos_back); 
   //while (!quitter)
      //{
        e->anim.possprite.x=0;
        e->anim.possprite.y=0;
        SDL_BlitSurface(e->back_enigme,NULL,screen,&e->pos_back);
        SDL_BlitSurface(e->question.texte1,NULL,screen,&e->question.pos1);
        SDL_BlitSurface(e->question.texte2,NULL,screen,&e->question.pos2);
        SDL_BlitSurface(e->rep1.texte,NULL,screen,&e->rep1.pos);
        SDL_BlitSurface(e->rep2.texte,NULL,screen,&e->rep2.pos);
        SDL_BlitSurface(e->rep3.texte,NULL,screen,&e->rep3.pos);
        SDL_BlitSurface(e->rep4.texte,NULL,screen,&e->rep4.pos);
        animerEnigme(e,screen);
        //SDL_BlitSurface(e->question.texte,NULL,screen,&e->question.pos);
        printf("iam here\n");
        
     /*while(SDL_PollEvent(&Event))
        {
           if(Event.type==SDL_QUIT)
             {
                quitter=1;
             }
        }*/
    //SDL_Delay(100);
      //}
   //SDL_Quit();
   printf("fonction afficher here\n");
}
void resol_enigme(Enigme *e, char *reponse)
{ 
   char caractere='\n';
   int comp;
   /*if(e->num_tent>4)
      {
        e->etat=-1;
        printf("non reussi\n");   
      }*/
   strncat(reponse,&caractere,1);
   printf("function resol here\n");
   printf("reponse ici:%s",reponse); 
   printf("reponse correcte:%s",e->rep_corr); 
   comp=strcmp(e->rep_corr,reponse);
   if(comp==0)
     {
        printf("reussite\n");
        e->etat=1;
     }
  /* else
     {*/
       

       else
         {
           if(e->num_tent==3)
             {
               e->etat=-1; 
             }
           else
           {
            e->etat=0;
            e->num_tent++;
            printf("non reussi\n");
           }
         }
     //}
}
void libererenigme(Enigme *e)
{ 
   SDL_FreeSurface(e->back_enigme);
   SDL_FreeSurface(e->anim.sprite);
   SDL_FreeSurface(e->question.texte1);
   SDL_FreeSurface(e->question.texte2);
   SDL_FreeSurface(e->rep1.texte);
   SDL_FreeSurface(e->rep2.texte);
   SDL_FreeSurface(e->rep3.texte);
   SDL_FreeSurface(e->rep4.texte);
   SDL_FreeSurface(e->msg_res[0]);
   SDL_FreeSurface(e->msg_res[1]);
   TTF_CloseFont(e->question.police);
   TTF_CloseFont(e->rep1.police);
   TTF_CloseFont(e->rep2.police);
   TTF_CloseFont(e->rep3.police);
   TTF_CloseFont(e->rep4.police);
   printf("fonction liberer here\n");
}
  



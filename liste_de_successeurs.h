//liste_de_successeurs.h
#ifndef __LISTE_DE_SUCCESSEURS_H__
#define __LISTE_DE_SUCCESSEURS_H__

#include "recup_infos_base2donnees.h"

typedef struct Element Element;
struct Element{
    int nombre;
    int ligne;
    int distance;
    Element *suivant;
};

typedef struct Liste Liste;
struct Liste{
    Element *premier;
};


Liste * ListeDeSuccesseurs[500];



Liste *initialisation(int);
void insertion_fin(Liste *, int, int, int);
void afficherListe(Liste *);
void creerListeDeSuccesseurs(void);


#endif

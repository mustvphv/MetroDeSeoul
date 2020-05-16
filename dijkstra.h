//dijkstra.h
#ifndef __DIJKSTRA_H__
#define __DIJKSTRA_H__

#include "recup_infos_base2donnees.h"
#include "matrice_compacte.h"
#include "liste_de_successeurs.h"
#include <stddef.h>


int Poids[500]; 
int A[500][2];
char * origine;
char * destination;


int PoidsL[500];
int AL[500][2];



int rechercheIndiceDebut(int);
void evaluationDijkstra(void);
void evaluationDijkstraListe(void);
void CorrectionChemin(int);
void meilleurChemin(void);
void CorrectionCheminListe(int);
void meilleurCheminListe(void);



#endif


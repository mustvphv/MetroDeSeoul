//seoul.c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"liste_de_successeurs.h"
#include"matrice_compacte.h"
#include"recup_infos_base2donnees.h"
#include"dijkstra.h"

extern int maxSommet;
extern int maxSommetL;
extern int maxListe;
extern int tout_sommet_etudie;
extern int origine_indice;
extern int destination_indice;

extern int tout_sommet_etudieL;


int origine_index = -1;
int destination_index = -1;


void quelTrajet(char * origine, char * destination){
    int i=0;
    for(i=0; i<500; ++i){
        if(strcmp(stations_finales[i].nom, origine) == 0){
            origine_index = i;
        }
    }
    for(i=0; i<500; ++i){
        if(strcmp(stations_finales[i].nom, destination) == 0){
            destination_index = i;
        }
    }

    if(origine_index == -1 || destination_index == -1){
        printf("Erreur,\norigine et/ou destination inconnue\n");
        exit(1);
    }
    if(strcmp(origine, destination) == 0 && origine_index != -1 && destination_index != -1){
        printf("erreur l'origine et la destination sont confondus\n");
        exit(1);
    }

}






int main(int argc, char * argv[]){
    clock_t debut, arret;
    double temps_ecoule;
    if(argc != 4){
        printf("Erreur,\nPour pouvoir exécuter le programme il faut écrire ./[nom de l'exécutable] [nom de la sation d'origine] [nom de la station de destination] [type de structure pour stocker les graphes qu'on veut utiliser(Mco ou Lis)]\n");
        exit(1);
    }

    else{
        if(strcmp(argv[3], "Mco") == 0){

            debut = clock();

            creerInformationsMetro();
            creerMatriceCompacte();
            quelTrajet(argv[1], argv[2]);
            
            origine=stations_finales[origine_index].nom;
            //printf("origine = %s\n", origine);

            destination=stations_finales[destination_index].nom;

            origine_indice = origine_index;
            destination_indice = destination_index;


            evaluationDijkstra();

            printf("\nmaxSommet=%d\n", maxSommet);
            //printf("\nmaxListe=%d\n", maxListe);

            printf("origine_indice = %d\n",origine_index);
            printf("destination_indice = %d\n",destination_index);


            if (tout_sommet_etudie == 0){
                printf("Pas de chemin\n");
                exit(1);
            }
            else {
                printf("Le chemin avec Matrice Compacte\n");
                meilleurChemin();
            }

            printf("\nmaxSommet=%d\n", maxSommet);

            arret = clock();
            temps_ecoule = ((double)arret - debut) / CLOCKS_PER_SEC;
            printf("Le temps écoulé est de : %f\n", temps_ecoule);
            
        }
        else if(strcmp(argv[3], "Lis") == 0){

            debut = clock();

            creerInformationsMetro();
            creerListeDeSuccesseurs();
            quelTrajet(argv[1], argv[2]);

            origine=stations_finales[origine_index].nom;
            destination=stations_finales[destination_index].nom;

            origine_indice = origine_index;
            destination_indice = destination_index;

            evaluationDijkstraListe();

            printf("\nmaxSommetL=%d\n", maxSommetL);
            printf("\nmaxListe=%d\n", maxListe);

            printf("origine_indice = %d\n",origine_indice);
            printf("destination_indice = %d\n",destination_indice);


            if (tout_sommet_etudieL == 0){
                printf("Pas de chemin\n");
                exit(1);
            }
            else {
                printf("Le chemin Liste\n");
                meilleurCheminListe();
            }

            printf("\nmaxSommetL=%d\n", maxSommetL);
            printf("\nmaxListe=%d\n", maxListe);
            
            arret = clock();
            temps_ecoule = ((double)arret - debut) / CLOCKS_PER_SEC;
            printf("Le temps écoulé est de : %f\n", temps_ecoule);
        }
        else{
            printf("erreur,\n argv[3] pdoit être égal à Mco ou Lis\n\n");
        }
    }


    return 0;
}

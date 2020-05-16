//liste_de_successeurs.c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "liste_de_successeurs.h"

int maxSommetL=0;
int maxListe =0;

Liste *initialisation(int premier_nombre){

    Liste *liste = malloc(sizeof(*liste));

    Element *element = malloc(sizeof(*element));


    if (liste == NULL || element == NULL){
        printf("erreur initialisation\n");
        exit(EXIT_FAILURE);
    }

    element->nombre = premier_nombre;
    element->ligne = 0;
    element->distance = 0;
    element->suivant = NULL;
    liste->premier = element;


    return liste;

}

void insertion_fin(Liste *liste, int nvNombre, int nvLigne, int nvDistance){
    Element *nouveau = malloc(sizeof(*nouveau));
    if (liste == NULL || nouveau == NULL){
        printf("erreur insertion_fin\n");
        exit(0);
    }
    nouveau->nombre = nvNombre;
    nouveau->ligne = nvLigne;
    nouveau->distance = nvDistance;

    nouveau->suivant = NULL;

    Element * temp = liste->premier;
    while(temp->suivant != NULL){
        temp = temp->suivant;
    }
    temp->suivant = nouveau;
}


void afficherListe(Liste *liste){
    if (liste == NULL){
        exit(0);
    }

    Element *utile = liste->premier;

    printf("<stations numero %d> <ligne %d> <distance %d> -> ", utile->nombre, utile->ligne, utile->distance);
    utile = utile->suivant;
    while (utile != NULL){
        printf("<succ %d> <ligne %d> <distance %d> -> ", utile->nombre, utile->ligne, utile->distance);
        utile = utile->suivant;
    }
    printf("NULL\n");
}


void creerListeDeSuccesseurs(){
    int vart = 0;
    int i = 0, j = 0;

    int var_limitation_nom_station = 0;
    int var_temoin_limitation_nom_station = 0;
    int avancement_sub = 0;
    int avancement_subLigne = 0;
    int indice_station_act = 0;
    int num_ligne_actuelle = 0;


    int num_poids;
    int var_recup_poids = 0;
    int avancement_poids = 0;

    for(i=0; i<500 ;i++){
        if (strlen(stations_finales[i].nom) != 0) {                
           maxSommetL++;
        }
        for(j=0, indice_station_act = 0; j<500 ;j++, indice_station_act++){
            if(indice_station_act == 0){

                ListeDeSuccesseurs[i] = initialisation(i);

                indice_station_act++;
            }

            char * sub = malloc(50 * sizeof(char*));
            char * subLigne = malloc(50 * sizeof(char*));
            char * poids = malloc(50 * sizeof(char*));
            var_temoin_limitation_nom_station = 0;
            avancement_sub = 0;
            avancement_subLigne = 0;
            strcpy(subLigne,"");
            bzero(sub,50);
            var_limitation_nom_station = 0;
            bzero(poids, 50);
            var_recup_poids = 0;
            avancement_poids = 0;

            for(var_limitation_nom_station=0; stations_finales[i].correspondances[vart][var_limitation_nom_station] != 0 ;++var_limitation_nom_station){
                if ((var_temoin_limitation_nom_station == 0) && (stations_finales[i].correspondances[vart][var_limitation_nom_station] != ':') && (var_recup_poids == 0)) {
                    subLigne[avancement_subLigne++] = stations_finales[i].correspondances[vart][var_limitation_nom_station];
                    }
                if(stations_finales[i].correspondances[vart][var_limitation_nom_station] == ':'){
                        var_recup_poids = 1;subLigne[avancement_subLigne]='\0';
                }
                if ((var_temoin_limitation_nom_station == 0) && (stations_finales[i].correspondances[vart][var_limitation_nom_station] != '|') && (stations_finales[i].correspondances[vart][var_limitation_nom_station] != ':') && (var_recup_poids == 1)) {
                    poids[avancement_poids++] = stations_finales[i].correspondances[vart][var_limitation_nom_station];
                }
                if(var_temoin_limitation_nom_station == 1){
                    sub[avancement_sub++] = stations_finales[i].correspondances[vart][var_limitation_nom_station];
                }
                if(stations_finales[i].correspondances[vart][var_limitation_nom_station] == '|'){
                    var_temoin_limitation_nom_station = 1;
                }
            }

            if(strcmp(stations_finales[j].nom, sub) == 0 && strlen(stations_finales[j].nom) != 0){

                
               num_ligne_actuelle = atoi(subLigne);
               if(strcmp(subLigne, "Jungang Line") == 0){
                    num_ligne_actuelle = 9;
               }
               if(strcmp(subLigne, "Bundang Line") == 0){
                    num_ligne_actuelle = 10;
               }
               if(strcmp(subLigne, "Incheon Subway Line 1") == 0){
                    num_ligne_actuelle = 11;
               }

               free(subLigne);
               num_poids = atoi(poids);
               insertion_fin(ListeDeSuccesseurs[i], j, num_ligne_actuelle, num_poids);
               j=0;
               maxListe++;
               vart++;
            }

            free(sub);
            free(poids);
            
            if(strlen(stations_finales[i].correspondances[vart]) == 0){

                vart=0;

                break;
            }
        }
    }
    for(int i=0; i<maxSommetL; ++i){
        afficherListe(ListeDeSuccesseurs[i]); 
    }
}

//matrice_compacte.c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "matrice_compacte.h"

int matrice_compacte[500*2][4];
int maxMCO = 0;
int maxSommet=0;

int redondances_correspondances_mco(int indice1, int indice2){
    int i;
    for(i=0; i<500*2; ++i){
        if(matrice_compacte[i][0] == indice1 && matrice_compacte[i][1] == indice2){
            return 1;
        }
    }
    return 0;
}

void creerMatriceCompacte(){
    int i,j;
    int var_matrice = 0;
    int vart = 0;
    int var_limitation_nom_station = 0;
    int var_temoin_limitation_nom_station = 0;
    int avancement_sub = 0;
    int avancement_subligne = 0;
    int num_ligne_actuelle = 0;

    int num_poids;
    int var_recup_poids = 0;
    int avancement_poids = 0;

    for(i=0; i<500 ; i++){
        if(strcmp(stations_finales[i].nom, "") != 0){

            maxSommet++;
       
            for(j=0; j<500 ; ++j){
                char * sub = malloc(50 * sizeof(char*));
                char * subligne = malloc(50 * sizeof(char*));
                char * poids = malloc(50 * sizeof(char*));
               

                var_temoin_limitation_nom_station = 0;
                avancement_sub = 0;
                avancement_subligne = 0;
                bzero(sub,50);
                strcpy(subligne,"");
                bzero(poids, 50);
                var_recup_poids = 0;
                avancement_poids = 0;
                for(var_limitation_nom_station=0; stations_finales[i].correspondances[vart][var_limitation_nom_station] != 0 ;++var_limitation_nom_station){
                    if ((var_temoin_limitation_nom_station == 0) && (stations_finales[i].correspondances[vart][var_limitation_nom_station] != ':') && (var_recup_poids == 0)) {
                        subligne[avancement_subligne++] = stations_finales[i].correspondances[vart][var_limitation_nom_station];
                    }
                    if(stations_finales[i].correspondances[vart][var_limitation_nom_station] == ':'){
                        var_recup_poids = 1;subligne[avancement_subligne]='\0';
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
               
                if(strcmp(stations_finales[j].nom, sub) == 0){

                    
                num_ligne_actuelle = atoi(subligne);
                if(strcmp(subligne, "Jungang Line") == 0){
                    num_ligne_actuelle = 9;
                }
                if(strcmp(subligne, "Bundang Line") == 0){
                    num_ligne_actuelle = 10;
                }
                if(strcmp(subligne, "Incheon Subway Line 1") == 0){
                    num_ligne_actuelle = 11;
                }

                num_poids = atoi(poids);


                free(subligne);
                free(poids);

                    matrice_compacte[var_matrice][0] = i;
                    matrice_compacte[var_matrice][1] = j;
                    if(matrice_compacte[var_matrice][2] == 0){
                        matrice_compacte[var_matrice][2] = num_ligne_actuelle;
                    }
                    matrice_compacte[var_matrice][3] = num_poids;

                    var_matrice++;
                   
                    j = 0;

                    vart++;
                   
               }

                free(sub);
 
                if(strcmp(stations_finales[i].correspondances[vart], "") == 0){
                    vart = 0;
                    break;
                }
            }
        }
    }

    printf("\n");
    printf("maxMCO = %d    maxSommet = %d", var_matrice, maxSommet);
    printf("\n");
    maxMCO=var_matrice;
    for(i=0; i<maxMCO ; ++i){
        printf("matrice_compactee[%d] = %d   %d    %d   %d\n", i, matrice_compacte[i][0], matrice_compacte[i][1], matrice_compacte[i][2], matrice_compacte[i][3]);
    }

}

//recup_infos_bases2donnees.c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "recup_infos_base2donnees.h"



void creerInformationsMetro(){
    FILE *fichier_a_lire;
    int i=0;
    int st_bzero = 0;
    station stations[500];


    fichier_a_lire = fopen("base2donnees_metro_seoul.txt", "r");

    st_bzero = 0;

    for(st_bzero = 0; st_bzero<500; st_bzero++){
        bzero(stations[st_bzero].nom, 500);
    }

    for(st_bzero = 0; st_bzero<500; st_bzero++){
        bzero(stations[st_bzero].lignes, 500);
    }

    for(st_bzero = 0; st_bzero<500; st_bzero++){
        bzero(stations[st_bzero].correspondances, 500);
    }

    st_bzero = 0;
    for(st_bzero = 0; st_bzero<500; st_bzero++){
        bzero(stations_finales[st_bzero].nom, 500);
    }

    for(st_bzero = 0; st_bzero<500; st_bzero++){
        bzero(stations_finales[st_bzero].lignes, 500);
    }

    for(st_bzero = 0; st_bzero<500; st_bzero++){
        bzero(stations_finales[st_bzero].correspondances, 500);
    }


    char * texte_a_lire = malloc(sizeof(char*)*1024);

    int n = 0;
    int n2 = 0;
    int n3 = 0;
    int numero_correspondance = 0;
    int numero_lignes = 0;
    int var_station = 0;

    int num_station = -1;

    while(!feof(fichier_a_lire)){
    bzero(texte_a_lire, 1024);
    n = 0;
    n2 = 0;
    n3 = 0;
    numero_correspondance = 0;
    num_station ++;
    texte_a_lire = fgets(texte_a_lire, 1024, fichier_a_lire);
    if(feof(fichier_a_lire)) break;
    for(i=0; texte_a_lire[i] != '\0' ;++i){
        if(texte_a_lire[i] == '|') break;
        
        stations[num_station].lignes[numero_lignes][n++] = texte_a_lire[i];
    }
    for(i+=1; texte_a_lire[i] != '\0' ;++i){
        if(texte_a_lire[i] == '<') break;
        
        stations[num_station].nom[n2++] = texte_a_lire[i];
    }

    for(i+=1; texte_a_lire[i] != '\0' ;++i){
        if(texte_a_lire[i] == ','){
            numero_correspondance ++;
            n3 = 0;
            i++;
        }
        if(texte_a_lire[i] == '>') break;
        
        stations[num_station].correspondances[numero_correspondance][n3++] = texte_a_lire[i];

    }

    for(int j=0; j<500 ;++j){
        if (strcmp(stations[j].nom, stations[num_station].nom) == 0 && strcmp(stations[j].lignes[numero_lignes], stations[num_station].lignes[numero_lignes]) != 0){
            
            for(int v = 0; v<20 ;v++){
                if(strcmp(stations[j].correspondances[v], "") == 0){
                    var_station = v;
                    break;
                }
            }
            int r = 0;
            while(strcmp(stations[num_station].correspondances[r],"") != 0){
                strcpy(stations[j].correspondances[var_station++], stations[num_station].correspondances[r++]);
            }

            while(strcmp(stations[j].lignes[numero_lignes], "") != 0){
                numero_lignes++;
            }
            
            strcpy(stations[j].lignes[numero_lignes], stations[num_station].lignes[0]);

            strcpy(stations[num_station].nom, "DEJA EXISTANT");
        }
        var_station = 0 ;
        numero_lignes = 0;
    }

    }


    int var_finales = 0;
    for(int v=0; v<500; v++){
        if(strcmp(stations[v].nom, "DEJA EXISTANT") != 0){
            strcpy(stations_finales[var_finales].nom, stations[v].nom);
            for(int v2 = 0; v2<8 ; ++v2){
                strcpy(stations_finales[var_finales].lignes[v2], stations[v].lignes[v2]);
            }
            for(int v3 = 0; v3<8 ; ++v3){
                strcpy(stations_finales[var_finales].correspondances[v3], stations[v].correspondances[v3]);
            }
            var_finales++;
        }
    }

     for(int v=0; v<500 ;++v){
        if(strlen(stations_finales[v].nom) != 0){
            printf("station %d : %s\n", v, stations_finales[v].nom);
        }
    }

    free(texte_a_lire);
}

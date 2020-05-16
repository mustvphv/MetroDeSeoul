//recup_infos_base2donnees.h
#ifndef __RECUP_INFOS_BASE2DONNEES_H__
#define __RECUP_INFOS_BASE2DONNEES_H__



struct station{
    char nom[50];
    char lignes[50][50];
    char correspondances[50][150];
};

typedef struct station station;

station stations_finales[500];


void creerInformationsMetro(void);


#endif

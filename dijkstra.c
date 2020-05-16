//dijkstra.c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "dijkstra.h"

extern int matrice_compacte[500*2][4];
extern int maxMCO;
extern int maxSommet;
extern int maxSommetL;
extern int maxListe;
int tout_sommet_etudie=0;
int origine_indice=0;
int destination_indice=0;
int tout_sommet_etudieL=0;
int remise = 0;

Element *utile = NULL;

int rechercheIndiceDebut(int sommet_pivot) {
    int i = -1;
    int trouve = 0;
    while ((i<=998) && (trouve==0)) {
        if (matrice_compacte[i+1][0]==sommet_pivot) {
           i++;
           trouve = 1;
        }
        i++;
    }
    return i-1;
}

int correspondanceTemps(int x_pivotMCO1, int x_pivot1) {
    if ((matrice_compacte[x_pivotMCO1][2]!=A[x_pivot1][1]) && (A[x_pivot1][1]!=-1)) {
       return 3;
    }
    else {
       return 0;
    }
}

int correspondanceTempsListe(int x_pivot1) {
    if ((utile->ligne!=AL[x_pivot1][1]) && (AL[x_pivot1][1]!=-1)) {
       return 3;
    }
    else {
       return 0;
    }
}


void evaluationDijkstra() {
     int plus_infini=0;
     int S[500];
     int s;
     int x_pivot;
     int x_pivotMCO;
     int maxS;
     int indice_existe;
     int minimum;

     plus_infini=3*maxMCO*4;

     plus_infini++;


     for (int i=0; i<maxSommet; i++) {
        S[i]=-2;
        Poids[i]=plus_infini;
     }

     s=origine_indice;

     S[s]=s;
     Poids[s]=0;
     x_pivot=s;
     x_pivotMCO=rechercheIndiceDebut(x_pivot);

     if (x_pivotMCO == -1) {
        printf("Pas de solution \n");
        exit(0); 
     }

     maxS=1;

     for (int i=0; i<maxSommet; i++) {
        for (int j=0; j<=1; j++) {
            A[i][j]=-1;
        }
     }
     tout_sommet_etudie=0;


     while (maxS!=maxSommet && Poids[x_pivot]<plus_infini) {
        indice_existe=1;
        while(indice_existe != 0) {
             if (S[matrice_compacte[x_pivotMCO][1]]==-2) {                
                if (Poids[matrice_compacte[x_pivotMCO][1]]>Poids[x_pivot]+matrice_compacte[x_pivotMCO][3]+correspondanceTemps(x_pivotMCO,x_pivot)) {
                    Poids[matrice_compacte[x_pivotMCO][1]]=Poids[x_pivot]+matrice_compacte[x_pivotMCO][3]+correspondanceTemps(x_pivotMCO,x_pivot); 
                    A[matrice_compacte[x_pivotMCO][1]][0]=x_pivot;

                    A[matrice_compacte[x_pivotMCO][1]][1]=matrice_compacte[x_pivotMCO][2];
                }
             }
             x_pivotMCO++;
             if (x_pivotMCO<maxMCO) {
                if (matrice_compacte[x_pivotMCO][0]!=x_pivot) {
                   indice_existe=0;
                }
             }
             if (x_pivotMCO>=maxMCO) {
                indice_existe=0;
             }
        }

        minimum=plus_infini;
        for (int i=0; i<maxSommet; i++) {
            if (S[i]==-2) {
                if (minimum>Poids[i]) {
                    minimum=Poids[i];
                    x_pivot=i;
                }
            }
        }

        S[x_pivot]=x_pivot;
        x_pivotMCO=rechercheIndiceDebut(x_pivot);
        maxS++;

     }
     if (maxS==maxSommet) {
         tout_sommet_etudie=1;
         /*for (int i=0; i<maxSommet; i++) {
             printf("S[%d] = %d et Poids[%d] = %d\n", i, S[i], i, Poids[i]);
         }*/
     }
     else {
         tout_sommet_etudie=0;
     }

}


void evaluationDijkstraListe() {
     int plus_infini=0;
     int S[500];
     int s;
     int x_pivot;
     int x_pivotLIS;
     int maxS;
     int indice_existe;
     int minimum;



     plus_infini=3*maxListe*4;

     plus_infini++;

     for (int i=0; i<maxSommetL; i++) {
        S[i]=-2;
        PoidsL[i]=plus_infini;
     }


     s=origine_indice;

     S[s]=s;
     PoidsL[s]=0;
     x_pivot=s;
     x_pivotLIS=0;
     maxS=1;

     for (int i=0; i<maxSommetL; i++) {
        for (int j=0; j<=1; j++) {
            AL[i][j]=-1;
        }
     }
     tout_sommet_etudieL=0;
     utile = ListeDeSuccesseurs[x_pivot]->premier;

     while (maxS!=maxSommetL && PoidsL[x_pivot]<plus_infini) {
        indice_existe=1;

        utile = utile->suivant;
        if (utile==NULL){
           exit(1);
        }
        

        while(indice_existe) {

             if (S[utile->nombre]==-2) {

                if (PoidsL[utile->nombre]>PoidsL[x_pivot]+utile->distance+correspondanceTempsListe(x_pivot)) {
                    PoidsL[utile->nombre]=PoidsL[x_pivot]+utile->distance+correspondanceTempsListe(x_pivot); 
                    AL[utile->nombre][0]=x_pivot;


                    AL[utile->nombre][1]=utile->ligne;
                }
             }
             x_pivotLIS++;
             utile = utile->suivant; 
             if (utile == NULL) {
                indice_existe=0;
             }
             if (x_pivotLIS>=maxListe) {
                indice_existe=0;
             }
        }
        minimum=plus_infini;


        for (int i=0; i<maxSommetL; i++) {
            if (S[i]==-2) {
                if (minimum>PoidsL[i]) {
                    minimum=PoidsL[i];
                    x_pivot=i;
                }
            }
        }

        S[x_pivot]=x_pivot;
        utile = ListeDeSuccesseurs[x_pivot]->premier;
        maxS++;
     }
     if (maxS==maxSommetL) {
         tout_sommet_etudieL=1;
     }
     else {
         tout_sommet_etudieL=0;
     }

}


void CorrectionChemin(int xIndice) {
    int corr = 0;
    int ajout = 0;
    int dist = 0;

    for (int i=0; i<maxMCO; i++) {
        if (matrice_compacte[i][1]==xIndice) {
            if ((A[matrice_compacte[i][0]][1]!=A[xIndice][1]) && (A[matrice_compacte[i][0]][1]!=-1) && (A[matrice_compacte[i][0]][0]!=xIndice)) {
                for (int j=0; j<maxMCO; j++) {
                    if ((matrice_compacte[j][1]==matrice_compacte[i][0]) && (matrice_compacte[j][0]!=xIndice) && (A[matrice_compacte[j][0]][0]!=matrice_compacte[j][1])) {
                       if (matrice_compacte[j][2]==A[xIndice][1]) {
                            corr = 0;
                            dist = 0;
                            ajout = 0;
                            remise = 0;
                            if ((A[A[matrice_compacte[i][0]][0]][1]!= A[matrice_compacte[i][0]][1]) && (A[A[matrice_compacte[i][0]][0]][1]!=-1)) {
                                corr=3;
                            }

                            if (matrice_compacte[j][2]!= A[matrice_compacte[j][0]][1]) {
                                ajout=3;
                            }

                            for (int k=0; k<maxMCO; k++) {
                                if ((matrice_compacte[k][0]==A[matrice_compacte[i][0]][0]) && (matrice_compacte[k][1]==matrice_compacte[i][0])) {
                                    dist=matrice_compacte[k][3];
                                    k=maxMCO;  
                                }
                            }


                                if (Poids[matrice_compacte[j][0]]+matrice_compacte[j][3]+ajout<Poids[A[matrice_compacte[i][0]][0]]+dist+3+corr) {
                                    remise =Poids[A[matrice_compacte[i][0]][0]]+dist+3+corr-(Poids[matrice_compacte[j][0]]+matrice_compacte[j][3]+ajout);
                                    A[matrice_compacte[j][1]][0]=matrice_compacte[j][0];
                                    A[matrice_compacte[j][1]][1]=matrice_compacte[j][2];
                                    Poids[matrice_compacte[j][1]]=Poids[matrice_compacte[j][0]]+ajout+matrice_compacte[j][3];
                                    Poids[xIndice]=Poids[matrice_compacte[j][1]]+matrice_compacte[i][3];

                                }
                        }
                     }
                }
            }
        }
    }
}




void meilleurChemin(){ //on retourne le meilleur chemin
    int xIndice=destination_indice;
    int plusCourtChemin[500*2][4];
    int longueur=0;


    plusCourtChemin[longueur][0]=xIndice;
 

       CorrectionChemin(xIndice);
       for (int i=0; i<=longueur; i++) {
           plusCourtChemin[i][2]=plusCourtChemin[i][2]-remise;
       }
       remise=0;

    plusCourtChemin[longueur][1]=A[xIndice][1];
    plusCourtChemin[longueur][2]=Poids[xIndice]; plusCourtChemin[longueur][3]=1;
    while (xIndice!=origine_indice) {
        xIndice=A[xIndice][0];
        longueur++;
 
        if ((A[xIndice][1]!=plusCourtChemin[longueur-1][1]) && (xIndice!=origine_indice)) {
           plusCourtChemin[longueur][0]=xIndice; 

           CorrectionChemin(xIndice);
           for (int i=0; i<=longueur; i++) {
               plusCourtChemin[i][2]=plusCourtChemin[i][2]-remise;
           }
           remise=0;

           plusCourtChemin[longueur][1]=plusCourtChemin[longueur-1][1]; 
           plusCourtChemin[longueur][2]=Poids[xIndice]+3; 
           plusCourtChemin[longueur][3]=0;        
           longueur++;
           plusCourtChemin[longueur][0]=xIndice; 
           plusCourtChemin[longueur][1]=A[xIndice][1]; 
           plusCourtChemin[longueur][2]=Poids[xIndice]; 
           plusCourtChemin[longueur][3]=1;
        }  
        else {
           if (xIndice!=origine_indice) {
              plusCourtChemin[longueur][0]=xIndice; 

           CorrectionChemin(xIndice);
           for (int i=0; i<=longueur; i++) {
               plusCourtChemin[i][2]=plusCourtChemin[i][2]-remise;
           }
           remise=0;

              plusCourtChemin[longueur][1]=A[xIndice][1]; 
              plusCourtChemin[longueur][2]=Poids[xIndice]; 
              plusCourtChemin[longueur][3]=1;
           }
           else {
              plusCourtChemin[longueur][0]=xIndice; 

              CorrectionChemin(xIndice);
              for (int i=0; i<=longueur; i++) {
                  plusCourtChemin[i][2]=plusCourtChemin[i][2]-remise;
              }
              remise=0;

              plusCourtChemin[longueur][1]=plusCourtChemin[longueur-1][1]; 
              plusCourtChemin[longueur][2]=Poids[xIndice]; plusCourtChemin[longueur][3]=1;
           }
        } 
    }
    for (int i=longueur; i>=0; i--) {
        if (plusCourtChemin[i][3]==1) {
           if (A[plusCourtChemin[i][0]][0]==-1) {
               printf("Poids= %d   stations.num= %d          station = %s   Ligne N° %d\n", plusCourtChemin[i][2], plusCourtChemin[i][0], stations_finales[plusCourtChemin[i][0]].nom, plusCourtChemin[i][1]);
           }
           else {
               printf("Poids= %d   stations.num= %d          station = %s   Ligne N° %d   venant de la station N° %s\n", plusCourtChemin[i][2], plusCourtChemin[i][0], stations_finales[plusCourtChemin[i][0]].nom, plusCourtChemin[i][1], 
stations_finales[A[plusCourtChemin[i][0]][0]].nom);
           }
        }
        else {
           printf("Poids= %d   stations.num= %d   correspondance = %s   Ligne N° %d   venant de la station N° %s\n", plusCourtChemin[i][2], plusCourtChemin[i][0], stations_finales[plusCourtChemin[i][0]].nom, plusCourtChemin[i][1], stations_finales[A[plusCourtChemin[i-1][0]][0]].nom );
        }
    }

}


void CorrectionCheminListe(int xIndice) {
    int corr = 0;
    int ajout = 0;
    int dist = 0;
    remise = 0;

    Element *actuel = NULL;
    Element *actuel1 = NULL;
    Element *actuelK = NULL;

    int trouveXindice=0;
    int trouveXindice1=0;
    int trouveXindiceK=0;
    int depart;
    int depart1;
    int departK;


    for (int i=0; i<maxSommetL; i++) {
        actuel = ListeDeSuccesseurs[i]->premier;
        depart=actuel->nombre;
        trouveXindice=0;
        
        while ((actuel != NULL) && (trouveXindice!=1)) { //Recherche de successeurs
            actuel = actuel->suivant;
            if (actuel != NULL) {
                 if (actuel->nombre==xIndice) {
                    trouveXindice=1; 
                 }
            }
        } 

        if (trouveXindice==1) {
            if ((AL[depart][1]!=AL[xIndice][1]) && (AL[depart][1]!=-1) && (AL[depart][0]!=xIndice)) {
                for (int j=0; j<maxSommetL; j++) {
                    actuel1 = ListeDeSuccesseurs[j]->premier;
                    depart1=actuel1->nombre;
                    trouveXindice1=0;
        
                    while ((actuel1 != NULL) && (trouveXindice1!=1)) {
                        actuel1 = actuel1->suivant;
                        if (actuel1 != NULL) {
                            if (actuel1->nombre==depart) {
                                trouveXindice1=1; 
                            }
                        }
                    } 

                    if ((trouveXindice1==1) && (depart1!=xIndice) && (AL[depart1][0]!=actuel1->nombre)) {
                        if (actuel1->ligne==AL[xIndice][1]) {
                            corr = 0;
                            dist = 0;
                            ajout = 0;
                            remise = 0;
                               
                            if ((AL[AL[depart][0]][1]!= AL[depart][1]) && (AL[AL[depart][0]][1]!=-1)) {
                                corr=3;
                            }

                            if (actuel1->ligne != AL[depart1][1]) {
                                ajout=3;
                            }

                            for (int k=0; k<maxSommetL; k++) {
                                actuelK = ListeDeSuccesseurs[k]->premier;
                                departK=actuelK->nombre;
                                trouveXindiceK=0;
                                if (departK==AL[depart][0]) { 
                                    while ((actuelK != NULL) && (trouveXindiceK!=1)) { //Recherche de successeurs
                                        actuelK = actuelK->suivant;
                                        if (actuelK != NULL) {
                                             if (actuelK->nombre==depart) {
                                                 trouveXindiceK=1;
                                                 dist=actuelK->distance;
                                                 k=maxSommetL;
                                             }
                                        }
                                    } 
                                 }
                            }

                            if (PoidsL[depart1]+actuel1->distance+ajout<PoidsL[AL[depart][0]]+dist+3+corr) {
                                    remise =PoidsL[AL[depart][0]]+dist+3+corr-(PoidsL[depart1]+actuel1->distance+ajout);
                                    AL[actuel1->nombre][0]=depart1;
                                    AL[actuel1->nombre][1]=actuel1->ligne;
                                    PoidsL[actuel1->nombre]=PoidsL[depart1]+ajout+actuel1->distance;
                                    PoidsL[xIndice]=PoidsL[actuel1->nombre]+actuel->distance;

                            }
                        }
                    }
                }
           }
       }
   }
}


void meilleurCheminListe(){ //on retourne le meilleur chemin
    int xIndice=destination_indice;
    int plusCourtChemin[500*2][4];
    int longueur=0;

    plusCourtChemin[longueur][0]=xIndice;

    CorrectionCheminListe(xIndice); 
    for (int i=0; i<=longueur; i++) {
        plusCourtChemin[i][2]=plusCourtChemin[i][2]-remise;
    }
    remise=0;

    plusCourtChemin[longueur][1]=AL[xIndice][1];
    plusCourtChemin[longueur][2]=PoidsL[xIndice]; plusCourtChemin[longueur][3]=1;
    while (xIndice!=origine_indice) {
        xIndice=AL[xIndice][0];
        longueur++;

        if ((AL[xIndice][1]!=plusCourtChemin[longueur-1][1]) && (xIndice!=origine_indice)) {
           plusCourtChemin[longueur][0]=xIndice; 

           CorrectionCheminListe(xIndice); 
           for (int i=0; i<=longueur; i++) {
               plusCourtChemin[i][2]=plusCourtChemin[i][2]-remise;
           }
           remise=0;

           plusCourtChemin[longueur][1]=plusCourtChemin[longueur-1][1]; 
           plusCourtChemin[longueur][2]=PoidsL[xIndice]+3; plusCourtChemin[longueur][3]=0;        
           longueur++;
           plusCourtChemin[longueur][0]=xIndice; plusCourtChemin[longueur][1]=AL[xIndice][1]; 
           plusCourtChemin[longueur][2]=PoidsL[xIndice]; plusCourtChemin[longueur][3]=1;
        }  
        else {
           if (xIndice!=origine_indice) {
              plusCourtChemin[longueur][0]=xIndice; 

              CorrectionCheminListe(xIndice); 
              for (int i=0; i<=longueur; i++) {
                  plusCourtChemin[i][2]=plusCourtChemin[i][2]-remise;
              }
              remise=0;

              plusCourtChemin[longueur][1]=AL[xIndice][1]; 
              plusCourtChemin[longueur][2]=PoidsL[xIndice]; plusCourtChemin[longueur][3]=1;
           }
           else {
              plusCourtChemin[longueur][0]=xIndice; 

              CorrectionCheminListe(xIndice); 
              for (int i=0; i<=longueur; i++) {
                  plusCourtChemin[i][2]=plusCourtChemin[i][2]-remise;
              }
              remise=0;

              plusCourtChemin[longueur][1]=plusCourtChemin[longueur-1][1]; 
              plusCourtChemin[longueur][2]=PoidsL[xIndice]; plusCourtChemin[longueur][3]=1;
           }
        } 
    }

    for (int i=longueur; i>=0; i--) {
        if (plusCourtChemin[i][3]==1) {
           if (AL[plusCourtChemin[i][0]][0]==-1) {
               printf("PoidsL= %d   stations.num= %d          station = %s   Ligne N° %d\n", plusCourtChemin[i][2], plusCourtChemin[i][0], stations_finales[plusCourtChemin[i][0]].nom, plusCourtChemin[i][1]);
           }
           else {
               printf("PoidsL= %d   stations.num= %d          station = %s   Ligne N° %d   venant de la station N° %s\n", plusCourtChemin[i][2], plusCourtChemin[i][0], stations_finales[plusCourtChemin[i][0]].nom, plusCourtChemin[i][1], 
stations_finales[AL[plusCourtChemin[i][0]][0]].nom);
           }
        }
        else {
           printf("PoidsL= %d   stations.num= %d   correspondance = %s   Ligne N° %d   venant de la station N° %s\n", plusCourtChemin[i][2], plusCourtChemin[i][0], stations_finales[plusCourtChemin[i][0]].nom, plusCourtChemin[i][1], stations_finales[AL[plusCourtChemin[i-1][0]][0]].nom );
        }

    }

}




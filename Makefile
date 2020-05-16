CC=gcc
CFLAGS=-W -Wall
AUTRE=recup_infos_base2donnees.c dijkstra.c matrice_compacte.c liste_de_successeurs.c
AUTRE_H=recup_infos_base2donnees.h dijkstra.h matrice_compacte.h liste_de_successeurs.h
seoul: seoul.o
	$(CC) $(CFLAGS) -o seoul seoul.c $(AUTRE) $(AUTRE_H)
seoul.o: seoul.c
	$(CC) $(CFLAGS) -c seoul.c $(AUTRE) $(AUTRE_H)
clean :
	rm seoul seoul.o recup_infos_base2donnees.o dijkstra.o matrice_compacte.o liste_de_successeurs.o recup_infos_base2donnees.h.gch dijkstra.h.gch matrice_compacte.h.gch liste_de_successeurs.h.gch

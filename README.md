# MetroDeSeoul
Projet d'Algorithmique Avancée


# Projet n°15 « Gérer un réseau de transports en commun, par exemple le métro de Séoul, via un graphe (Lis et Mco). Résoudre dans ce cas le problème du plus court chemin, algorithme de Dijkstra. »



### 1. Description du sujet :

Le sujet de mon projet est le sujet numéro 15 (Séoul), la consigne est «Gérer un réseau de
transports en commun, par exemple le métro de Séoul, via un graphe (Lis et Mco). Résoudre dans
ce cas le problème du plus court chemin, algorithme de Dijkstra.» (le terme «Mco» désigne
«matrice compacte» et le terme «Lis» désigne «liste de successeurs»).

Il y aura la nécessité de créer une matrice compacte et une liste de successeurs.
Pour ce faire, on devra d’abord récupérer les informations dans une base de données qu’on créera à
partir d’une carte montrant les stations du métro de Séoul, on y mettra les noms des stations, leurs
successeurs, ainsi que la distance en minute qui sépare les stations de leurs successeurs, on
renseignera aussi dans quelle(s) ligne(s) se trouveront les différentes stations et celles qui les
succèdent.

De plus, on devra créer une matrice de récupération où on stockera toutes les informations possibles
(noms des stations, lignes auxquelles elles appartiennent, poids/distance,
correspondances/successeurs).

À partir de cette matrice de récupération, on pourra créer une matrice compacte, puis une liste de
successeurs, et à partir desquelles, on pourra implémenter des fonctions qui traiteront ces structures
pour stocker les graphes avec l’algorithme de Dijkstra pour pouvoir retrouver le plus court chemin
entre une station d’origine et d’arrivé données au préalable.


### 2.Carte du métro et base de données :

La carte du métro que j’utilise est issue du site:
« https://unebretonneencoree.files.wordpress.com/2014/07/sc3a9oul-station.png ». (qu’on peut
retrouver dans l’archive, appelée : « mseong,png »).

Toutes les informations (écrites dans la base de donnée) qui concernent la durée d’un trajet d’une
station à une autre (station à successeur) est issue du site :
« [http://seoulmetro.co.kr/en/cyberStation.do?action=time#wayInfo](http://seoulmetro.co.kr/en/cyberStation.do?action=time#wayInfo) » où on peut taper le nom de la
station de départ (d’origine) dans la case « DPT, » et la station d’arrivée (de destination) dans la
case « ARV. ».

À partir de ces stations on a créé une base de données sur laquelle on s’appuiera pour construire ma
matrice de récupération des données puis pour faire ma matrice compacte et ma liste de successeurs.

Dans cette base de données, on a écrit tous les noms de stations avec leurs lignes, leurs successeurs
possibles :

Chaque ligne se présente de cette façon :
[ligne à laquelle appartient la station principale]|[nom de la station principale]<[ligne de
successeur1]:[temps du trajet station principale-successeur1]|[nom de successeur1],[ligne de
successeur2]:[temps du trajet station principale-successeur2]|[nom de successeur2]>

On peut prendre l’exemple suivant :

## 1|Gaebong<1:3|Oryu-dong,1:2|Guil>

On peut constater ici que la station « Gaebong », appartient à la ligne 1 et a pour successeurs les
stations « Oryu-dong » (qui appartient à la ligne 1 et le temps du trajet Gaebong à Oryu-dong est de
3 minutes) et « Gui l » (qui appartient à la ligne 1 et le temps du trajet Gaebong à Guil est de 2
minutes).

#### Attention : La ligne issue de la base de données « 1|Gaebong<1:3|Oryu-dong,1:2|Guil> » ne

#### veut pas forcément dire que la station Gaebong n’appartient qu’à la ligne 1 (pareil pour les

#### successeurs), dans le cas où elle appartiendrait à une autre ligne, on aurait une autre

déclaration de la même station mais avec une ligne différente, la fonction de récupération de
données se chargera elle, de « ranger » toutes les informations autour d’un même nom de station
(voir artie « 3. La récupération des informations issues de la base de données »).


#### Cas particuliers :

Dans un endroit de la carte, on peut remarquer une partie du métro qui fonctionne différemment des
autres. En effet, sur la ligne 6 du métro de Séoul, on observe qu’il y a ce qu’on appelle la «boucle
d’Eungam» («Eungam Loop») et qui fonctionne sur le modèle «one-way station», c’est-à-dire
qu’on peut aller de la station x vers la station y, mais qu’on ne peut pas aller de la station y vers la
station x.
Concrètement, si on est à la station « Eungam » et qu’on veut aller à la station «Gusan», qu’on
pourrait croire « proche » du fait que la station « Eungam » apparaît directement accessible à la
station « Gusan », on doit en fait, effectuer le trajet : « Eungam - Yeokchon - Bulgwang – Dokbawi

- Yeonnsinnae - Gusan » pour y arriver parce qu’on peut aller que dans un sens. Du coup, cette
partie du métro est orientée contrairement au reste du métro où on peut aller dans n’importe quel
sens.
Dans la base de donnée, les stations qui se trouvent au milieu de la boucle d’ « Eungam » , comme
la station « Dokbawi » par exemple sont déclarées comme des stations en bout de chemin qui n’ont
qu’un seul successeur possible ;
6|Dokbawi<6:3|Yeonsinnae>

On constate que la station Dokbawi ne peut aller qu’à la station Yeonsinnae et que le trajet «
Dokbawi – Yeonsinnae » durera 3 minutes.

Il y a aussi le cas de la station Magok sur la ligne 5 qui est notée sur la carte comme hors-service
« Magok(out of service) » mais que j’ai décidé de compter comme une station qui fonctionne
normalement.

#### Les correspondances et autres :

Certaines stations sont différentes des autres, en effet, elles sont sur plusieurs lignes en même temps
comme par exemple la station « Hapjeong » qui appartient à plusieurs lignes en même temps (la
ligne 2 et la ligne 6).
Dans la base de données cela se traduit par la présence deux fois de la station « Hapjeong » comme
station principale (différent d’une station écrite comme étant successive à une autre):
2|Hapjeong<2:2|Hongik University,2:3|Dangsan>
6|Hapjeong<6:2|Sangsu,6:2|Mangwon>

On constate ici, que la station « Hapjeong » fait bien partie de la ligne 2 (elle a comme successeurs
« Hongik University » et « Dangsan » qui eux aussi appartiennent à la ligne 2).
De même, « Hapjeong » fait aussi partie de la ligne 6 (elle a comme successeurs « Sangsu » et
« Dangsan qui eux aussi appartiennent à la ligne 6).

Il y arrive qu’une station ait plus de deux successeurs appartenant à la même ligne comme la station
« Sindorim » qui appartient à la ligne 1 et à la ligne 2.
Au niveau de la ligne 2, on constate que « Sindorim » a 3 successeurs appartenant eux aussi à la
ligne 2, dans la base de données, on la traduit comme suit :
2|Sindorim<2:2|Dorimcheon,2:3|Mullae,2:3|Daerim>


Il y arrive aussi qu’une station appartenant à plusieurs lignes ait des successeurs qui sont aussi sur
plusieurs lignes en même temps dont certaines en commun, on peut prendre comme exemple les
stations « Dongdaemun Station » et « Euljiro 4 (sa)-ga » qui ont en commun les lignes 2 et 5, dans
la base de données, on a :
2|Dongdaemun Stadium<2:2|Sindang,2:2|Euljiro 4(sa)-ga>
5|Dongdaemun Stadium<5:2|Euljiro 4(sa)-ga,5:2|Cheonggu>
On remarque en effet qu’il y a 2 fois l’occurence de la station « Euljiro 4(sa)-ga » en tant que
successeurs de « Dongdaemun Stadium » (« 2:2|Euljiro 4(sa)-ga » et « 5:2|Euljiro 4(sa)-ga »).

### 3. La récupération des informations issues de la base de données :

Au niveau du code, les programmes qui s’occupent de la récupération à partir de la base de données
sont « recup_infos_base2donnees.c» et « recup_ infos_base2donnees.h ».

Dans le programme « recup_infos_base2donnees.h», on a créé « stations_finales » de type station
qui est une structure de données, qui va stocker, pour chaque station déclarée dans la base de
données, un nom (« char nom[50] »), un tableau à deux dimensions (« char lignes[50][50] ») qui va
stoker là ou les lignes qui correspondent à un nom de station.

Enfin, la structure de données « station » est constituée d’un autre tableau à deux dimensions
(« char correspondances[50][150] ») qui va stocker les correspondances de la station en question.

Dans le programme « recup_infos_base2donnees.c », on a la fonction « creerInformationsMetro() »
qui va remplir au fur et à mesure « stations_finales » qui sera indispensable pour la suite de notre
programme. Cette fonction permet la jonction entre la base de données
« base2donnees_metro_seoul.txt» et la création de la matrice compacte et de la liste de successeur.

Dans la fonction « creerInformationsMetro() », on transfert caractère par caractère les données qui
nous intéressent dans les tableaux issus de la structure station, à l’aide des séparateurs définis dans
la base de données (« | », « , », « < », « > », « : ») pour faire la différence entre les données à mettre
dans le nom de la station, dans les correspondances ou dans les lignes.


### 4. La matrice compacte :

Au niveau du code, dans la matrice compacte, ce sont les programmes « matrice_compacte.c» et
« matrice_compacte.h », qui s’occupent de la création de la matrice compacte à partir des
informations stockées dans « stations_finales » précédemment.

Dans le programme « matrice_compacte.c», dans la procédure « creerMatriceCompacte() », on
utilise les indices de « stations_finales » comme des identifiants correspondant chacun à une station
différente (par exemple, la station qui a pour nom « Incheon » qui est la première a être déclarée
dans la base de données, aura pour indice 0 dans stations_finales à l’issue de la fonction
« creeInformationsMetro() » et 0 sera considéré comme l’identifiant de la station « Incheon » dans
la matrice compacte (comme station principale ou comme successeur direct d’une autre station).
Dans le même programme, on créé la matrice compacte « int matrice_compacte[500*2][4]; » qui
comporte 4 colonnes.

À l’issue de la fonction « creerMatriceCompacte() », on aura la première colonne qui représentera
l’identifiant (l’indice dans stations_finales) de la station principale, dans la deuxième colonne, on
aura la station qui la succède, dans la troisième colonne, on aura le numéro de la ligne qui sera en
commun entre la station principale et le successeur, puis à la quatrième colonne, on aura la distance
(le temps du trajet) entre ces deux stations.

### 5. La liste de successeurs:

Au niveau du code, dans la liste de successeurs, ce sont les programmes « liste_de_successeurs.c»
et « liste_de_successeurs.h », qui s’occupent de la création de la liste de successeurs à partir des
informations stockées dans « stations_finales » précédemment.

Dans le programme « liste_de_successeurs.c», dans la procédure « creerListeDeSuccesseurs()», on
initialise directement. 

Par exemple, pour l’indice 0, on crée une liste dans liste_de_successeur[0],
avec dans la liste, en premier, le numéro de la station départ comme suit : l’identifiant égal à
« element->nombre » qui est le numéro de l’indice [0] ou [i] i allant de 0 à nombre de stations, puis
pour la station départ qu’on place en tête de liste, element→ligne égal à zero ( element→ligne
prendra la valeur du numéro de ligne de métro au fur et à mesure qu’on ajoute des éléments dans la
liste correspondant à la ligne station départ – station successeur ), element→distance égal à zero
( element→distance prendra la valeur de la durée de déplacement au fur et à mesure qu’on ajoute
des éléments dans la liste correspondant à la ligne station départ – station successeur ), et au final
element→suivant valable à tous les éléments ajoutés. On aura donc le schéma suivant :
element(stations départ) → element(successeur1) → .................→ element(successeurN) →
NULL.


### 6. Algorithme de Dijkstra :

On démarre d’une station (sommet), on lui affecte un poids nul et le nom de Pivot. Le poids du reste
des stations est à plus infini. On crée un ensemble S des stations qui ont été désignées comme Pivot.
On initialise une matrice A qui enregistrera pour chaque station au fur et à mesure un prédécesseur
dans le plus court chemin provisoire ou définitif et le numéro de la ligne, ainsi qu’un vecteur Poids
pour Mco et PoidsL pour Lis, qui conservera les distances entre la station initiale(l’origine) et les
autres stations.

L’algorithme va ainsi parcourir tous les sommets en leur donnant le nom Pivot jusqu’à obtenir deux
possibilités.

- Soit l’algorithme a une solution : S compte toutes les stations (sommets).
- Soit l’algorithme n’a pas de solution : on a trouvé un Pivot dont le poids est infini (cas de
    non connexité). => qui n’est pas le cas dans ce projet, puisqu’on travaille sur un graphe
    connexe.

Le principe de l’algorithme est le suivant.
À partir du Pivot, on réévalue (parce qu’il y a la possibilité qu’un successeur ait déjà été
parcourue/évaluée à partie d’une station Pivot précédente) le poids de chaque successeur (station
suivante) en comparant son poids actuel avec la formule : Poids du Pivot + distance entre les 2
stations + le temps de la correspondance si elle existe.

Si le nouveau poids est inférieur alors on modifie le Poids de la station « successeur » et on lui
affecte comme prédécesseur le Pivot actuel et numéro de la ligne de métro du Pivot (voir matrice A
et Poids pour Mco ou AL et PoidsL pour Lis).

Puis une fois l’opération terminée, on ajoute la station Pivot dans S et on recommence l’opération
avec une autre station Pivot choisie parmi les stations n’appartenant pas à S et dont le poids est
minimum.

Une fois l’opération terminée, si S représente l’ensemble des stations du Métro de Séoul, alors il y a
une solution au départ de la première station Métro parcourue(station initiale) et la matrice A (ou
AL) permet de retrouver le chemin le plus court entre la station initiale et n’importe quelle autre
station avec le numéro de la ligne en remontant les stations prédécesseur.

Au niveau du code, c’est le programme « dijkstra.c » et le header « dijkstra.h » qui s’occupent de
l’algorithme de Dijkstra.


Explication des fonctions du programme :

int rechercheIndiceDebut(int sommet_pivot) : cette fonction permet de trouver l'indice de début des
lignes successeurs d'une station donnée dans la matrice compacte Mco.

int correspondanceTemps(int x_pivotMCO1, int x_pivot1) : détermine s'il y a une correspondance
entre la station Pivot et le successeur pour le calcul du poids. Elle donne 3 les deux stations sont
atteintes par des lignes de métro différentes, 0 sinon.

int correspondanceTempsListe(int x_pivot1) : idem que pour int correspondanceTemps(int
x_pivotMCO1, int x_pivot1).

void evaluationDijkstra() : exécute l'algorithme de Dijkstra dans la matrice Mco.

void evaluationDijkstraListe() : exécute l'algorithme de Dijkstra dans la matrice Lis.

void CorrectionChemin(int xIndice) : cette procédure permet de réévaluer le poids déterminé par
l'algorithme de Dijkstra en tenant compte des correspondances retenues. Elle servira à proposer un
plus court chemin différent en supprimant la correspondance.

void meilleurChemin() : elle retourne le meilleur chemin trouvé en s'aidant de la procédure
CorrectionChemin(int xIndice).

void CorrectionCheminListe(int xIndice) : idem que pour la procédure CorrectionChemin(int
xIndice).

void meilleurCheminListe() : idem que pour la procédure meilleurChemin().

### 7. Comparaison de la matrice compacte et de la liste de successeurs au niveau du

### temps de calcul et de la taille de la mémoire utilisé:

On peut constater avec par exemple, le trajet allant de la station « Incheon » à la station « Ori », en
utilisant d’abord la matrice compacte, un résultat du temps d’exécution du calcul de:
« Le temps écoulé est de : 0.080946 »(le temps est en seconde)

Et avec la liste de successeurs, j’obtiens le résultat suivant :

« Le temps écoulé est de : 0.065184 »(le temps est en seconde)

On constate que le temps d’exécution est plus long avec la matrice compacte qu’avec la liste de
successeurs, ceci peut s’expliquer par le fait que les listes de successeurs permettent une
concentration des informations en mémoire, ce qui diminue le temps d’accès à ces données
contrairement à la matrice compacte.


### 8. Difficultés rencontrées et améliorations possibles :

La principale difficulté rencontrée a été la comptabilisation de la durée des correspondances
(changements de ligne) dans le calcul du poids des stations.

J’ai fait le choix d’appliquer l’algorithme de Dijkstra en tenant compte des correspondances puis, au
moment de l’affichage du plus court chemin entre les deux stations choisies (station origine et
station destination), j’ai créé une fonction « CorrectionChemin(int xIndice) » pour Mco (et
« CorrectionCheminListe(int xIndice » pour Lis) qui permet de réévaluer le poids d’une station
trouvée en appliquant l’algorithme, en vérifiant si une correspondance qui précède la station en
question existe et, peut éventuellement être remplacée par une station dont la ligne correspond à
celle de la station étudiée.

Mais, après réflexion, on aurait pu procéder à cette amélioration en amont, en utilisant
« CorrectionChemin(int xIndice) » dans la procédure « evaluationDjikstra() » (pour Mco et
« evaluationDjikstraListe() » pour Lis) en l’utilisant pendant le déroulement de l’algorithme de
Dijkstra et non pas après.

On a pu constaté le problème en exécutant, le programme en aller-retour où on a trouvé un exemple
où le chemin aller n’était pas le même que le chemin inverse en terme de durée (exemple Incheon-
Maebong et Maebong-Incheon).

Par contre, ce problème n’aurait pas eu lieu si au préalable, on aurait considéré une station à
plusieurs lignes comme autant de stations à part entière à une seule ligne chacune en les joignant
par des arrêtes comme entre des stations différentes avec comme distance, la valeur 3 (3 minutes),
mais cette technique coûtera plus en place mémoire (puisque c’est comme si on avait augmenté le
nombre de stations).

</br>
</br>

![Optional Text](../master/images-readme/mseoul.png)

#include <stdio.h>
#include <stdlib.h>
#include "app/tache.h"

void test(void){
	Liste l;
	creerMaillonVide(&l);
	Tache tache1 = {"Plomberie", 30, 0, {NULL, NULL}, 0, false};
	Tache tache2 = {"Electricite", 30, 0, {NULL, NULL}, 0, false};
	Tache tache3 = {"Peinture", 30, 0, {NULL, NULL}, 0, false};

	printf("Ajout maillon : \n");
	ajouterMaillonFin(&l, &tache1);
	ajouterMaillonFin(&l, &tache2);
	ajouterMaillonFin(&l, &tache3);
	afficherListe(&l);

	printf("Suppression premier maillon : \n");
	supprimerPremierMaillon(&l);
	afficherListe(&l);

	printf("Suppression dernier maillon : \n");
	supprimerDernierMaillon(&l);
	afficherListe(&l);
	
}

int main(void){
	test();

	exit(EXIT_FAILURE);
}

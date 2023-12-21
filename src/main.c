#include <stdio.h>
#include <stdlib.h>
#include "app/tache.h"
#include "app/menu.h"

void test() {
    int nbDevis = 0, max = 0;
    Devis** tDevis = chargerFichierDevis("devis.txt", &nbDevis, &max);

    if (tDevis == NULL) {
        printf("Erreur lors du chargement du fichier.\n");
        return;
    }

    printf("Fichier chargé avec succès.\n");
    printf("Nombre de devis chargés : %d\n", nbDevis);

    afficherDevis(tDevis, nbDevis);

    // Libération de la mémoire si nécessaire (à compléter selon votre code)
    // ...

    // Remarque : Pensez à libérer la mémoire allouée pour tDevis à la fin
    // ...

    printf("Fin du test.\n");
}

int main(void){
	//global();


	test();

	exit(EXIT_FAILURE);
}

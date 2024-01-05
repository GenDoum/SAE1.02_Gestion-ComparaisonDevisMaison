#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "app/tache.h"
#include "app/menu.h"
#include "app/affichage.h"
#include "app/chargement.h"

//void afficherDevis(Devis devis) {
//    printf("Nom de la tâche : %s\n", devis.nomTache);
//    printf("Entreprise : %s\n", devis.entreprise);
//    printf("Adresse : %d %s, %d %s\n", devis.adresse.numero, devis.adresse.nomRue, devis.adresse.codePostal, devis.adresse.ville);
//    printf("Capital : %d\n", devis.capital);
//    printf("Durée : %d jours\n", devis.duree);
//    printf("Coût : %d €\n", devis.cout);
//    printf("-----------------------\n");
//}
//
//void afficherListeDeviss(ListeDevis liste) {
//    MaillonDevis *courant = liste;
//    while (courant != NULL) {
//        afficherDevis(courant->devis);
//        courant = courant->suivant;
//    }
//}

//void testFunctions(void){
//    Offre* tOffre[5];
//    for (int i = 0; i < 5; ++i) {
//        tOffre[i] = (Offre*) malloc(sizeof(Offre));
//        snprintf(tOffre[i]->travaux, sizeof(tOffre[i]->travaux), "Travail%d", i + 1);
//        tOffre[i]->ldevis = NULL; // Initialiser la liste de devis à NULL
//    }
//
//    // Trier le tableau d'offres
//    quickSort(tOffre, 5);
//
//    // Appel à la fonction nouveauDevis
//    Adresse adresse = {1, "Rue Test", "Ville Test", 12345};
//    nouveauDevis(tOffre, 5, "Travail3", "Entreprise Test", adresse, 10000, 10, 5000);
//
//    // Afficher les offres et leurs listes de devis
//    printf("Offres et leurs listes de devis après l'ajout :\n");
//    for (int i = 0; i < 5; ++i) {
//        printf("Travail%d : %s\n", i + 1, tOffre[i]->travaux);
//        ListeDevis currentDevis = tOffre[i]->ldevis;
//        while (currentDevis != NULL) {
//            printf("Liste de devis :\n");
//            printf("Nom de la tâche : %s\n", currentDevis->devis.nomTache);
//            printf("Entreprise : %s\n", currentDevis->devis.entreprise);
//            printf("Adresse : %d %s, %d %s\n",
//                   currentDevis->devis.adresse.numero,
//                   currentDevis->devis.adresse.nomRue,
//                   currentDevis->devis.adresse.codePostal,
//                   currentDevis->devis.adresse.ville);
//            printf("Capital : %d\n", currentDevis->devis.capital);
//            printf("Durée : %d jours\n", currentDevis->devis.duree);
//            printf("Coût : %d €\n", currentDevis->devis.cout);
//            printf("-----------------------\n");
//
//            currentDevis = currentDevis->suivant;
//        }
//    }
//
//    // Libérer la mémoire
//    for (int i = 0; i < 5; ++i) {
//        free(tOffre[i]);
//    }
//}

int main(void){
	//global();

    int nbOffre = 0, max;
    Offre** tOffre = chargement("donnee/devis.txt", &nbOffre, &max);
    printf("chargement ok\n");

    // Afficher les offres et leurs listes de devis
//    afficher(tOffre, nbOffre);
//    afficherDevisPourType(tOffre, nbOffre);
    afficherDevisEntreprisePourType(tOffre, nbOffre);

    // Libérer la mémoire
    for (int i = 0; i < nbOffre; ++i) {
        free(tOffre[i]);
    }
    free(tOffre);


    exit(EXIT_FAILURE);
}

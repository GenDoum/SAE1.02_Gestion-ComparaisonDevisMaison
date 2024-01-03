#include "chargement.h"

int chargerDevis(char* nomFichier, Offre** tOffre) {
    FILE *fe;
    char ligne[MAX_LIGNE];
    int nbDevis = 0;

    if ((fe = fopen(nomFichier, "r")) == NULL) {
        perror("fopen");
        exit(-1);
    }

    while (fgets(ligne, sizeof(ligne), fe) != NULL) {
        Offre *nouvelleOffre = (Offre *) malloc(sizeof(Offre));
        if (nouvelleOffre == NULL) {
            fprintf(stderr, "Erreur : Échec de l'allocation mémoire pour l'offre.\n");
            exit(-1);
        }

        nouvelleOffre->ldevis = (ListeDevis) malloc(sizeof(MaillonDevis));
        if (nouvelleOffre->ldevis == NULL) {
            fprintf(stderr, "Erreur : Échec de l'allocation mémoire pour la liste de devis.\n");
            exit(-1);
        }

        sscanf(ligne, "%s", nouvelleOffre->travaux);

        sscanf(ligne, "%[^\n]", nouvelleOffre->ldevis->devis.nomTache);
        fgets(ligne, sizeof(ligne), fe);
        sscanf(ligne, "%[^\n]", nouvelleOffre->ldevis->devis.entreprise);

        fgets(ligne, sizeof(ligne), fe);
        sscanf(ligne, "%d %[^0-9] %d %s",
               &(nouvelleOffre->ldevis->devis.adresse.numero),
               nouvelleOffre->ldevis->devis.adresse.nomRue,
               &(nouvelleOffre->ldevis->devis.adresse.codePostal),
               nouvelleOffre->ldevis->devis.adresse.ville);

        fscanf(fe, "%d", &(nouvelleOffre->ldevis->devis.capital));
        fscanf(fe, "%d", &(nouvelleOffre->ldevis->devis.duree));
        fscanf(fe, "%d", &(nouvelleOffre->ldevis->devis.cout));

        tOffre[nbDevis] = nouvelleOffre;
        nbDevis++;

        // enlève le caractère de nouvelle ligne restant (il y avait un décalage à chaque nouvelle tâche)
        fgetc(fe);

    }

    fclose(fe);
    return nbDevis;
}

void chargerPrecedences(char* nomFichier) {
    FILE* fe;

    if ( (fe = fopen(nomFichier, "r")) == NULL ) {
        perror("fopen");
        exit(-1);
    }

    fclose(fe);
}

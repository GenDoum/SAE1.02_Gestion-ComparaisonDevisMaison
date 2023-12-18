#ifndef TACHE_H
#define TACHE_H

#define MAX_TRAVAUX 30
#define MAX_LIGNE 200

// Structure pour un devis
typedef struct Devis {
    char entreprise[MAX_TRAVAUX];
    char adresse[MAX_TRAVAUX];
    int capital;
    int duree;
    int cout;
    struct Devis* suivant;
} Devis;

// Structure pour les maillons de la liste de devis
typedef struct MaillonDevis {
    Devis devis;
    struct MaillonDevis* suivant;
} MaillonDevis;

// Structure pour une offre de travaux
typedef struct Offre {
    char travaux[MAX_TRAVAUX];
    MaillonDevis* ldevis;
} Offre;

void chargerPrecedences(char* nomFichier);
void afficherPrecedences(char* nomFichier);
void creerPrecedences(char* nomFichier);
int chargerDevis(void);

// Maillon
void creerMaillonDevisVide( MaillonDevis *liste );
// void ajouterMaillonFin( Liste *liste, Tache *tache );
// void ajouterMaillonDebut( Liste *liste, Tache *tache );
// void supprimerDernierMaillon( Liste *liste );
// void supprimerPremierMaillon( Liste *liste );
// void afficherListe(Liste *liste);
// void verifInt(int *var);

// Liste

// Tache


#endif // TACHE_H

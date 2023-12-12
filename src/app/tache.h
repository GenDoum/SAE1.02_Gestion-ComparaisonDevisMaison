#ifndef TACHE_H
#define TACHE_H

#define MAX_TRAVAUX 30
#define MAX_LIGNE 200

// typedef struct maillon{
//     int val;
//     struct maillon *suivant;
// } Maillon;

// typedef struct{
//     Maillon *suivant;
//     Maillon *fin;
// } Liste;

// typedef struct{
//     char tache[21]; // nom de la tache ex : Plomberie
//     int duree; // duree de la tache
//     int nbPred; // nombre de predecesseurs de la tache
//     Liste succ; // liste des successeurs de la tache
//     int dateDebut;  // date de debut au plutot de la tache
//     bool traite ; // booleen : la tache est-elle traitee
// } Tache;

// Structure pour un devis
typedef struct Devis {
    char entreprise[MAX_TRAVAUX];
    char adresse[MAX_TRAVAUX];
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

// Maillon

// void creerMaillonVide( Liste *liste );
// void ajouterMaillonFin( Liste *liste, Tache *tache );
// void ajouterMaillonDebut( Liste *liste, Tache *tache );
// void supprimerDernierMaillon( Liste *liste );
// void supprimerPremierMaillon( Liste *liste );
// void afficherListe(Liste *liste);
// void verifInt(int *var);

// Liste

// Tache


#endif // TACHE_H

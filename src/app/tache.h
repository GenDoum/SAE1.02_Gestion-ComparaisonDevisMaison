#ifndef TACHE_H
#define TACHE_H

typedef enum { false, true } bool;

typedef struct maillon{
    int val;
    struct maillon *suivant;
} Maillon;

typedef struct{
    Maillon *suivant;
    Maillon *fin;
} Liste;

typedef struct{
    char tache[21]; // nom de la tache ex : Plomberie
    int duree; // duree de la tache
    int nbPred; // nombre de predecesseurs de la tache
    Liste succ; // liste des successeurs de la tache
    int dateDebut;  // date de debut au plutot de la tache
    bool traite ; // booleen : la tache est-elle traitee
} Tache;



// Maillon

void creerMaillonVide( Liste *liste );
void ajouterMaillonFin( Liste *liste, Tache *tache );
void ajouterMaillonDebut( Liste *liste, Tache *tache );
void supprimerDernierMaillon( Liste *liste );
void supprimerPremierMaillon( Liste *liste );
void afficherListe(Liste *liste);
void verifInt(int *var);

// Liste


// Tache

Tache creerTache(Liste *liste);


#endif // TACHE_H
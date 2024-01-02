#ifndef TACHE_H
#define TACHE_H

#define MAX_TRAVAUX 30
#define MAX_LIGNE 200
#define FILE_ERROR -1

typedef enum {false, true} bool;

typedef struct adresse{
    int numero;
    char nomRue[MAX_LIGNE];
    char ville[MAX_LIGNE];
    int codePostal;
} Adresse;

// Structure pour un devis
typedef struct Devis {
    char nomTache[MAX_TRAVAUX];
    char entreprise[MAX_TRAVAUX];
    Adresse adresse;
    int capital;
    int duree;
    int cout;
} Devis;

// Structure pour les maillons de la liste de devis
typedef struct MaillonDevis {
    Devis devis;
    struct MaillonDevis* suivant;
} MaillonDevis;

// Structure pour la liste de devis
typedef struct MaillonDevis* ListeDevis;

// Structure pour une offre de travaux
typedef struct Offre {
    char travaux[MAX_TRAVAUX];
    ListeDevis ldevis;
} Offre;


void chargerPrecedences(char* nomFichier);
void afficherPrecedences(char* nomFichier);
void creerPrecedences(char* nomFichier);
void chargerDevis(char* nomFichier, Offre* tabTravaux);
//int chargerDevis(char* nomFichier, MaillonDevis* liste);
ListeDevis creerListeDevisVide(void);
bool estVide(ListeDevis liste);
void afficherDevis(ListeDevis liste);

// Maillon
void creerMaillonDevisVide( MaillonDevis *liste );
void saisieMaillon( char *nomTache, char *entreprise, Adresse *adresse, int *capital, int *duree, int *cout);
void ajouterMaillonDevisDebut(ListeDevis *liste);
void ajouterMaillonDevisFin(ListeDevis *liste);
void ajouterMaillonDevisFinChargement(ListeDevis *liste, char *nomTache, char *entreprise, Adresse *adresse, int capital, int duree, int cout);
void supprimerMaillonFin( ListeDevis *liste );
// void supprimerMaillonDebut( Liste *liste );
// void afficherListe( MaillonDevis *liste);
// void verifInt(int *var);

// Liste

// Tache


#endif // TACHE_H

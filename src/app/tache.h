#ifndef TACHE_H
#define TACHE_H

#define MAX_TRAVAUX 500
#define MAX_LIGNE 200
#define MAX_OFFRE 100


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


/**
 * @brief creer une précédence.
 *
 * @param nomFichier le nom du fichier
 * @return void
 */
void creerPrecedences(char* nomFichier);

// Maillon
/**
 * @brief Les différentes saisies pour un devis
 *
 * @param nomTache le nom de la tache
 * @param entreprise le nom de l'entreprise
 * @param adresse les différents champs de l'adresse
 * @param capital le capital de l'entreprise en euro
 * @param duree la durée de la tache en jour
 * @param cout le cout de la tache en euro
 */
void saisieMaillon( char *nomTache, char *entreprise, Adresse *adresse, int *capital, int *duree, int *cout);

void ajouterMaillonDevisDebut(ListeDevis *liste);
void ajouterMaillonDevisFin(ListeDevis *liste);
void supprimerMaillonFin( ListeDevis *liste );



ListeDevis listeVide(void);
ListeDevis insererEnTete(ListeDevis l, char nomTache[], char entreprise[], Adresse adresse, int capital, int duree, int cout);
ListeDevis insertionCroissante(ListeDevis l, char nomTache[], char entreprise[], Adresse adresse, int capital, int duree, int cout);
void quickSort(Offre** tOffre, int tLogique);
void nouveauDevis(Offre** tOffre, int nbDevis, char* nomTache, char* entreprise, Adresse adresse, int capital, int duree, int cout);
int appartient(ListeDevis l, char* nomTache);
int rechercheDichotomique(Offre** tOffre, int tLogique, char* nomTache, int* trouve);
bool vide(ListeDevis l);
int len(ListeDevis l);
Offre** chargement(char* nomFichier, int* nbOffre, int* max);




ListeDevis supprimerEnTete(ListeDevis l);
ListeDevis supprimer(ListeDevis l, char* nomTache);
void supprimerDevis(Offre** tOffre, int nb);

#endif // TACHE_H

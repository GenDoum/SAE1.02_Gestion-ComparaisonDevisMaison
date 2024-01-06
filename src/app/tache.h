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
 * @brief Vérifie et récupère une valeur entière saisie par l'utilisateur.
 *
 * Cette fonction vérifie si l'entrée de l'utilisateur est un entier valide.
 * Si ce n'est pas le cas, elle affiche un message d'erreur et invite l'utilisateur à saisir à nouveau.
 *
 * @param var Un pointeur vers la variable où stocker la valeur entière saisie par l'utilisateur.
 */
void verifInt(int *var);

/**
 * @brief Crée une nouvelle précédence entre deux tâches et l'ajoute à un fichier.
 *
 * Cette fonction permet à l'utilisateur de créer une nouvelle précédence entre deux tâches
 * et de l'ajouter à un fichier spécifié.
 *
 * @param nomFichier Le chemin du fichier où ajouter la précédence.
 */
void creerPrecedences(char* nomFichier);

/**
 * @brief Saisie des informations d'un maillon (tâche, entreprise, adresse, etc.) par l'utilisateur.
 *
 * Cette fonction guide l'utilisateur à travers le processus de saisie des informations nécessaires
 * pour créer un nouveau maillon (tâche) avec ses détails associés (entreprise, adresse, capital, durée, coût).
 *
 * @param nomTache Un pointeur vers une chaîne où stocker le nom de la tâche.
 * @param entreprise Un pointeur vers une chaîne où stocker le nom de l'entreprise.
 * @param adresse Un pointeur vers une structure Adresse où stocker les détails de l'adresse.
 * @param capital Un pointeur vers une variable où stocker le capital de l'entreprise.
 * @param duree Un pointeur vers une variable où stocker la durée de la tâche.
 * @param cout Un pointeur vers une variable où stocker le coût de la tâche.
 */
void saisieMaillon( char *nomTache, char *entreprise, Adresse *adresse, int *capital, int *duree, int *cout);

void ajouterMaillonDevisDebut(ListeDevis *liste);
void ajouterMaillonDevisFin(ListeDevis *liste);
void supprimerMaillonFin( ListeDevis *liste );


#endif // TACHE_H

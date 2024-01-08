#ifndef TACHE_H
#define TACHE_H

#define MAX_TRAVAUX 500
#define MAX_LIGNE 200
#define MAX_OFFRE 100


typedef enum {false, true} bool;

/**
 * @struct Adresse
 * @brief Structure représentant une adresse.
 *
 * Cette structure contient les informations nécessaires pour représenter une adresse,
 * y compris le numéro de rue, le nom de la rue, la ville et le code postal.
 */
typedef struct adresse {
    int numero; /**< Le numéro de la rue. */
    char nomRue[MAX_LIGNE]; /**< Le nom de la rue. */
    char ville[MAX_LIGNE]; /**< Le nom de la ville. */
    int codePostal; /**< Le code postal de la ville. */
} Adresse;

/**
 * @struct Devis
 * @brief Structure représentant un devis.
 *
 * Cette structure contient les détails spécifiques d'un devis,
 * tels que le nom de la tâche, l'entreprise concernée, l'adresse, le capital, la durée et le coût.
 */
typedef struct Devis {
    char nomTache[MAX_TRAVAUX]; /**< Le nom de la tâche du devis. */
    char entreprise[MAX_TRAVAUX]; /**< Le nom de l'entreprise concernée par le devis. */
    Adresse adresse; /**< L'adresse de l'entreprise. */
    int capital; /**< Le capital nécessaire pour la tâche. */
    int duree; /**< La durée estimée de la tâche. */
    int cout; /**< Le coût estimé de la tâche. */
} Devis;

/**
 * @struct MaillonDevis
 * @brief Structure représentant un maillon d'une liste de devis.
 *
 * Cette structure contient un devis et un pointeur vers le maillon suivant dans la liste.
 */
typedef struct MaillonDevis {
    Devis devis; /**< Le devis contenu dans le maillon. */
    struct MaillonDevis* suivant; /**< Le pointeur vers le maillon suivant dans la liste. */
} MaillonDevis;

/**
 * @typedef ListeDevis
 * @brief Type de pointeur vers un MaillonDevis.
 *
 * Ce type représente une liste de devis, qui est essentiellement une liste chaînée de MaillonDevis.
 */
typedef struct MaillonDevis* ListeDevis;

/**
 * @struct Offre
 * @brief Structure représentant une offre de travaux.
 *
 * Cette structure contient les détails d'une offre de travaux, y compris le type de travaux
 * et une liste de devis associée.
 */
typedef struct Offre {
    char travaux[MAX_TRAVAUX]; /**< Le type de travaux offerts. */
    ListeDevis ldevis; /**< La liste de devis associée à l'offre. */
} Offre;

typedef struct
{
    char tache[20]; /**< Le nom de la tâche. */
    int duree; /**< La durée de la tâche. */
    int nbPred; /**< Le nombre de prédécesseurs de la tâche. */
    ListeDevis succ; /**< La liste des successeurs de la tâche. */
    int dateDebut;   /**< La date de début de la tâche. */
    bool traite; /**< Un booléen indiquant si la tâche a été traitée. */
} Tache;

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
void comparerDevis(Offre ** tOffre, int nbOffre);
void selectionnerEntreprises(Offre** tOffre, int nbOffre);


#endif // TACHE_H

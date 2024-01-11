#ifndef SAE1_02_STRUCT_H
#define SAE1_02_STRUCT_H

#define MAX_TRAVAUX 500
#define MAX_LIGNE 200
#define MAX_OFFRE 100
#define MAX_PREC 100

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

typedef struct ListeSuccesseur
{
    char nomTache[30];
    struct ListeSuccesseur* suivant;
} ListeSuccesseur;

typedef struct ListeSuccesseur* ListeSucc;

/**
 * @typedef ListeOffre
 * @brief Type de pointeur vers un MaillonOffre.
 *
 * Ce type représente une liste d'offres, qui est essentiellement une liste chaînée de MaillonOffre.
 */
typedef struct
{
    char tache[20]; /**< Le nom de la tâche. */
    int duree; /**< La durée de la tâche. */
    int nbPred; /**< Le nombre de prédécesseurs de la tâche. */
    ListeSucc succ; /**< La liste des successeurs de la tâche. */
    int dateDebut;   /**< La date de début de la tâche. */
    bool traite; /**< Un booléen indiquant si la tâche a été traitée. */
} Tache;

typedef struct MaillonFile
{
    Tache tacheCourrante;
    struct MaillonFile* suivant;
} File;

typedef File * ListeFile;

#endif //SAE1_02_STRUCT_H

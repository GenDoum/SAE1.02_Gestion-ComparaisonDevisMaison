#ifndef STRUCT_H
#define STRUCT_H

#define MAX_TRAVAUX 500
#define MAX_LIGNE 200

/**
 * @file struct.h
 * @brief Définition des structures utilisées dans le programme.
 *
 * Ce fichier contient les définitions des structures utilisées dans le programme, y compris
 * les structures représentant une adresse, un devis, une offre de travaux, une liste de successeurs,
 * une tâche, un maillon de file, et un maillon de liste de devis.
 *
 * @date 11/01/2024
 * @version 1.0
 * @authors Mathéo Hersan, Yannis Doumir-Fernandes
 */

/**
 * @enum bool
 * @brief Énumération pour représenter les valeurs de vérité.
 *
 * Cette énumération définit les valeurs de vérité, soit `false` soit `true`.
 */
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

/**
 * @struct ListeSuccesseur
 * @brief Structure représentant un maillon d'une liste de successeurs pour une tâche.
 *
 * Cette structure contient le nom d'une tâche successeur et un pointeur vers le maillon suivant dans la liste.
 */
typedef struct ListeSuccesseur {
    char nomTache[30]; /**< Le nom de la tâche successeur. */
    struct ListeSuccesseur* suivant; /**< Le pointeur vers le maillon suivant dans la liste. */
} ListeSuccesseur, *ListeSucc;

/**
 * @struct Tache
 * @brief Structure représentant une tâche.
 *
 * Cette structure contient les détails d'une tâche, tels que le nom, la durée, le nombre de prédécesseurs,
 * une liste de successeurs, la date de début, et un indicateur de traitement.
 */
typedef struct
{
    char tache[20]; /**< Le nom de la tâche. */
    int duree; /**< La durée estimée de la tâche. */
    int nbPred; /**< Le nombre de prédécesseurs de la tâche. */
    ListeSucc succ; /**< La liste des successeurs de la tâche. */
    int dateDebut; /**< La date de début planifiée de la tâche. */
    bool traite; /**< Un indicateur de traitement de la tâche. */
} Tache;

/**
 * @struct MaillonFile
 * @brief Structure représentant un maillon d'une file de tâches.
 *
 * Cette structure contient une tâche courante et un pointeur vers le maillon suivant dans la file.
 */
typedef struct MaillonFile
{
    Tache tacheCourante; /**< La tâche contenue dans le maillon. */
    struct MaillonFile* suivant; /**< Le pointeur vers le maillon suivant dans la file. */
} File;

/**
 * @typedef ListeFile
 * @brief Type de pointeur vers un MaillonFile.
 *
 * Ce type représente une liste de tâches, qui est essentiellement une liste chaînée de MaillonFile.
 */
typedef File * ListeFile;

#endif //STRUCT_H

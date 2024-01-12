#include <stdlib.h>
#include "app/menu.h"

/**
 * @file main.c
 * @brief Programme principal.
 *
 * Ce fichier contient la fonction principale `main`, qui sert de point d'entrée au programme.
 * Le programme initialise les variables nécessaires, charge les données, et gère l'interaction avec
 * l'utilisateur via un menu. Selon le choix de l'utilisateur, différentes fonctions sont appelées pour
 * afficher des précédences, créer des précédences, afficher des devis, créer des devis, etc.
 *
 * @date 10/12/2023
 * @version 1.0
 * @authors Mathéo Hersan
 */


/**
 * @brief Point d'entrée principal du programme.
 *
 * La fonction principale initialise les variables nécessaires, charge les données, et gère l'interaction avec
 * l'utilisateur via un menu. Selon le choix de l'utilisateur, différentes fonctions sont appelées pour
 * afficher des précédences, créer des précédences, afficher des devis, créer des devis, etc.
 *
 * @return EXIT_SUCCESS en cas de succès, EXIT_FAILURE en cas d'erreur.
 */
int main(void)
{
    global();

    exit(EXIT_SUCCESS);
}

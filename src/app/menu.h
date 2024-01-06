#ifndef MENU_H
#define MENU_H

/**
 * @brief Affiche le menu principal pour le client.
 *
 * Cette fonction affiche un menu interactif avec différentes options que le client peut choisir.
 * Les options comprennent l'affichage des précédences, l'ajout de précédences, l'affichage des devis, etc.
 */
void affiche_client(void);

/**
 * @brief Gère la sélection d'une option par le client.
 *
 * Cette fonction affiche le menu client et récupère le choix de l'utilisateur.
 * Elle vérifie également si le choix est valide et invite l'utilisateur à entrer un choix valide si nécessaire.
 *
 * @param choix Un pointeur vers une variable où stocker le choix de l'utilisateur.
 */
void menu_client(int *choix);

/**
 * @brief Fonction principale du projet
 *
 * Cette fonction représente le point d'entrée principal du programme.
 * Elle initialise les variables nécessaires, charge les données, et gère l'interaction avec l'utilisateur via un menu.
 * Selon le choix de l'utilisateur, elle appelle différentes fonctions pour afficher des précédences, créer des précédences,
 * afficher des devis, créer des devis, etc.
 */
void global(void);

#endif // MENU_H

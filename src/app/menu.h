#ifndef MENU_H
#define MENU_H

/**
 * @brief Affiche le menu principal
 *
 * @param void
 * @return void
 */
void affiche_client(void);

/**
 * @brief Affiche le menu principal et propose à l'utilisateur de choisir une option
 *
 * @param choix le choix de l'utilisateur
 * @return void
 */
void menu_client(int *choix);

/**
 * @brief Propose les différents choix à l'utilisateur
 *
 * @param void
 * @return void
 */
void global(void);

#endif // MENU_H

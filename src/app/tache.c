#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tache.h"



// void ajouterMaillonFin( Liste *liste, Tache *tache){
//     Maillon *nouveau;
    
//     if ( (nouveau = (Maillon *)malloc(sizeof(Maillon))) == NULL){
//         perror("Erreur d'allocation de memoire");
//         exit(EXIT_FAILURE);
//     }

//     nouveau->val = tache->duree;
//     nouveau->suivant = NULL;
    
//     if (liste->fin == NULL){
//         liste->suivant = nouveau;
//         liste->fin = nouveau;
//     } else {
//         liste->fin->suivant = nouveau;
//         liste->fin = nouveau;
//     }

// }
// void supprimerPremierMaillon( Liste *liste )
// {
//     Maillon *premier = liste->suivant;
//     liste->suivant = premier->suivant;

//     free(premier);
// }


// void supprimerDernierMaillon( Liste *liste )
// {
//     // Si liste vide
//     if ( liste == NULL || liste->suivant == NULL)
//     {
//         return;
//     }

//     Maillon *dernier = liste->fin;

//     // Si la liste à qu'un seul élément
//     if ( liste->suivant == liste->fin )
//     {
//         liste->suivant = NULL;
//         liste->fin = NULL;
//     }
//     else
//     {
//         Maillon * courant = liste->suivant;
//         while (courant->suivant != dernier)
//         {
//             courant = courant->suivant;
//         }

//         courant->suivant = NULL;
//         liste->fin =courant;
//     }

//     free(dernier);
// }

// void afficherListe(Liste *liste){
//     Maillon *courant = liste->suivant;
//     while(courant != NULL){
//         printf("%d\n", courant->val);
//         courant = courant->suivant;
//     }
//     puts("");
// }


// Tache creerTache(Liste *liste)
// {
//     Tache * newTache;
    
//     if ( (newTache = (Tache*)malloc(sizeof(Tache))) == NULL )
//     {
//         perror("malloc Tache");
//         exit(-1);
//     }

//     printf("Entre le nom de la tache : ");
//     while ( (scanf("%s", newTache->tache)) != 1 )
//     {
//         fprintf(stderr, "Entrez un nom de la tache valid ! Pas plus de 20 caractères.\n");
//         while (getchar() != '\n');
//     }

//     printf("Entre la durée :");
//     verifInt(&newTache->duree);
    

//     printf("Entre le nombre de prédecesseurs de la tache \n");
//     //fonction
    
// }

ListeDevis creerListeDevisVide(void) {
    return NULL;
}

bool estVide(ListeDevis liste) {
    return liste == NULL;
}

void verifInt(int *var){
    while (scanf("%d", var) != 1){
        fprintf(stderr, "\x1B[31mERREUR : Entrez un nombre valide : \x1B[0m");
        while (getchar() != '\n');
    }

    while (getchar() != '\n');
}

void chargerPrecedences(char* nomFichier) {
    FILE* fe;

    if ( (fe = fopen(nomFichier, "r")) == NULL ) {
        perror("fopen");
        exit(-1);
    }

    fclose(fe);
}

void afficherPrecedences(char* nomFichier) {
    FILE* fe;
    char tache1[21], tache2[21];

    if ( (fe = fopen(nomFichier, "r")) == NULL ) {
        perror("fopen");
        exit(-1);
    }

    while (fscanf(fe, "%s%s\n", tache1, tache2) == 2) {
        printf("%s -> %s\n", tache1, tache2);
    }

    fclose(fe);
}

void creerPrecedences(char* nomFichier) { // Je sais pas si c'est fait exprès masi pk pas faire en sorte que si la tache1 entré est la tache2 d'un autre alors 
// afficcher dans le fichier en mode : tache1 -> tache2 -> tache 3 ?
    FILE* fe;
    char tache1[21], tache2[21];

    if ( (fe = fopen(nomFichier, "a")) == NULL ) {
        perror("fopen");
        exit(-1);
    }

    printf("Entrez le nom de la tache 1 : ");
    while ( (scanf("%s", tache1)) != 1 ) {
        fprintf(stderr, "Entrez un nom de la tache valid ! Pas plus de 20 caractères.\n");
        while (getchar() != '\n');
    }

    printf("Entrez le nom de la tache 2 : ");
    while ( (scanf("%s", tache2)) != 1 ) {
        fprintf(stderr, "Entrez un nom de la tache valid ! Pas plus de 20 caractères.\n");
        while (getchar() != '\n');
    }

    fprintf(fe, "%s %s\n", tache1, tache2);

    fclose(fe);
}

void saisieMaillon( char *nomTache, char *entreprise, Adresse *adresse, int *capital, int *duree, int *cout)
{
    printf("Entrez le nom de la tâche : ");
    while( (scanf("%s", nomTache) != 1 ) )
    {
        printf("Entrez un nom correct, avec maximum 30 caractères.\n Entrez ici :");
        while (getchar() != '\n');
    }

    printf("Entrez le nom de l'entreprise : ");
    while( (scanf("%s", entreprise) != 1 ) )
    {
        printf("Entrez un nom correct, avec maximum 30 caractères.\n Entrez ici :");
        while (getchar() != '\n');
    }

    printf("Entrez la ville de l'entreprise : ");
    while( (scanf("%s", adresse->ville) != 1 ) )
    {
        printf("Entrez une adresse correct, avec maximum 100 caractères.\n Entrez ici :");
        while (getchar() != '\n');
    }

    printf("Entrez le numéro de rue de l'entreprise : ");
    while( (scanf("%d", &(adresse->numero)) != 1 ) && adresse->numero <= 0 )
    {
        printf("/!/Entrez un numéro de rue correct./!/\n Entrez ici :");
        while (getchar() != '\n');
    }

    printf("Entrez le nom de la rue de l'entreprise : ");
    while( (scanf("%s", adresse->nomRue) != 1 ) )
    {
        printf("/!/Entrez un nom de rue correct./!/\n Entrez ici :");
        while (getchar() != '\n');
    }
    
    printf("Entrez le code postale de l'entreprise : ");
    while( (scanf("%d", &(adresse->codePostal)) != 1 ) && adresse->codePostal <= 0 )
    {
        printf("/!/Entrez un code postale correct./!/\n Entrez ici :");
        while (getchar() != '\n');
    }

    printf("Entrez le capital de l'entreprise : ");
    while( (scanf("%d", capital) != 1 ) && *capital <= 0 )
    {
        printf("/!/Entrez un capital correct/!/\n Entrez ici :");
        while (getchar() != '\n');
    }

    printf("Entrez la durée en jours de la tâche : ");
    while( (scanf("%d", duree) != 1 ) )
    {
        printf("/!/Entrez une durée correct./!/\n Entrez ici :");
        while (getchar() != '\n');
    }

    printf("Entrez le cout de la tâche : ");
    while( (scanf("%d", cout) != 1 ) )
    {
        printf(" /!/ Entrez un cout correct. /!/\n Entrez ici :");
        while (getchar() != '\n');
    }

}

void ajouterMaillonDevisFinChargement(ListeDevis *liste, char *nomTache, char *entreprise, Adresse *adresse, int capital, int duree, int cout)
{
    printf("iciDevisChargementMaillonFin \n");

    MaillonDevis *nouveauMaillon = (MaillonDevis*)malloc(sizeof(MaillonDevis));
    printf("iciDevisChargementMaillonFin \n");
    

    if (nouveauMaillon == NULL) 
    {
        fprintf(stderr, "Erreur : Échec de l'allocation mémoire.\n");
        exit(-1);
    }
    printf("iciDevisChargementMaillonFin \n");


    // Copie des informations directement dans le maillon
    strcpy(nouveauMaillon->devis.nomTache, nomTache);
    printf("iciDevisChargementMaillonFin \n");

    strcpy(nouveauMaillon->devis.entreprise, entreprise);
    printf("iciDevisChargementMaillonFin \n");

    nouveauMaillon->devis.adresse = *adresse;  // Copie de la structure Adresse
    printf("iciDevisChargementMaillonFin \n");

    nouveauMaillon->devis.capital = capital;
    printf("iciDevisChargementMaillonFin \n");

    nouveauMaillon->devis.duree = duree;
    printf("iciDevisChargementMaillonFin \n");

    nouveauMaillon->devis.cout = cout;
    printf("iciDevisChargementMaillonFin \n");

    nouveauMaillon->suivant = NULL;
    printf("iciDevisChargementMaillonFin \n");

    if (*liste == NULL) {
        printf("iciIF\n");
        *liste = nouveauMaillon;
    } 
    else 
    {
        printf("iciIF\n");
        MaillonDevis *courant = *liste;
        printf("iciIF\n");
        // L'ERREUR VIENT DE CEUX BLOC 
        // résumé : en gros au premier tour de boucle de la fonction de cahrgement on arrive dans cette fonction et on arrive ici
        // tout ce passe bien puisque normalement pcq tt les printf s'affiche et du coup le if du dessus on ne rentre pas dedans ce qui est bizarre pcq au premier coup la liste est vide
        // breff après le if il ne va pas dans le while et on passe en dessous et c'est ça qui pose problème 
        // la ligne "courant->suivant = nouveauMaillon;" fait une erreur de seg alors j'ai foutu un if pour vérifier qeu le pointeur cournat est pas null
        // mais du coup il est pas null et fait qd même une erreur de seg
        // Donc la je suis en train de péter un plomb sa mère pcq ça marchait pas avant le nouvel an et que ça s'est pas réglé tout seul pendant que je faisais la fête
        while (courant->suivant != NULL) 
        {
            printf("iciIF\n");
            courant = courant->suivant;
            printf("iciIF\n");
        }
        printf("iciIF\n");
        if (courant != NULL) // Vérifie que le pointeur courant n'est pas NULL
        {
            courant->suivant = nouveauMaillon;
        }

        //courant->suivant = nouveauMaillon;
        printf("iciIF\n");

    }
    printf("iciDevisChargementMaillonFin \n");

}


void ajouterMaillonDevisFin(ListeDevis *liste) 
{
    MaillonDevis *nouveauMaillon = (MaillonDevis*)malloc(sizeof(MaillonDevis));
    
    if (nouveauMaillon == NULL)
    {
        fprintf(stderr, "Erreur : Échec de l'allocation mémoire.\n");
        exit(-1);
    }

    // Utiliser la fonction de saisie du dessus
    saisieMaillon(nouveauMaillon->devis.nomTache, nouveauMaillon->devis.entreprise, 
                   &(nouveauMaillon->devis.adresse), &(nouveauMaillon->devis.capital),
                   &(nouveauMaillon->devis.duree), &(nouveauMaillon->devis.cout));

    nouveauMaillon->suivant = NULL;

    if (*liste == NULL) 
    {
        *liste = nouveauMaillon;
    }
    else
    {
        MaillonDevis *courant = *liste;
        while (courant->suivant != NULL) {
            courant = courant->suivant;
        }
        courant->suivant = nouveauMaillon;
    }
}



void ajouterMaillonDevisDebut(ListeDevis *liste) 
{
    MaillonDevis *nouveauMaillon = (MaillonDevis*)malloc(sizeof(MaillonDevis));
    
    if (nouveauMaillon == NULL) {
        fprintf(stderr, "Erreur : Échec de l'allocation mémoire.\n");
        exit(EXIT_FAILURE);
    }

    // Utiliser la fonction de saisie du dessus
    saisieMaillon(nouveauMaillon->devis.nomTache, nouveauMaillon->devis.entreprise, 
                   &(nouveauMaillon->devis.adresse), &(nouveauMaillon->devis.capital),
                   &(nouveauMaillon->devis.duree), &(nouveauMaillon->devis.cout));

    nouveauMaillon->suivant = *liste;

    *liste = nouveauMaillon;
}

void afficherDevis(ListeDevis liste) {
    MaillonDevis *courant = liste;
    while (courant != NULL) {
        printf("Nom de la tache : %s\n", courant->devis.nomTache);
        printf("Nom de l'entreprise : %s\n", courant->devis.entreprise);
        printf("Adresse de l'entreprise : ");
        printf("%d, ", courant->devis.adresse.numero);
        printf("%s ", courant->devis.adresse.nomRue);
        printf(" - %d", courant->devis.adresse.codePostal);
        printf(" - %s \n", courant->devis.adresse.ville);
        printf("Capital de l'entreprise : %d\n", courant->devis.capital);
        printf("Duree de la tache : %d\n", courant->devis.duree);
        printf("Cout de la tache : %d\n", courant->devis.cout);
        courant = courant->suivant;
    }
}

int rechercheDichotomique(Offre* tOffre[], int nbOffre, char* nomTache, int* trouve){
    int debut = 0;
    int fin = nbOffre - 1, milieu;

    while (debut <= fin){
        milieu = (debut + fin) / 2;
        if (strcmp(tOffre[milieu]->travaux, nomTache) == 0){
            *trouve = 1;
            return milieu;
        } else if (strcmp(tOffre[milieu]->travaux, nomTache) < 0){
            debut = milieu + 1;
        } else {
            fin = milieu - 1;
        }
    }

    *trouve = 0;
    return debut;
}

void chargerDevis(char* nomFichier, Offre* tabTravaux) 
{
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier des devis");
        exit(FILE_ERROR);
    }
    printf("iciChargeDevis\n");

    char ligne[MAX_LIGNE];
    
    Offre* offreActuelle = tabTravaux;
    printf("iciChargeDevis\n");
    int i = 1;
    while (fgets(ligne, MAX_LIGNE, fichier) != NULL) {
        // Traitement de chaque ligne pour extraire les informations du devis
        printf("iciChargeDevis %d\n", i);
        Devis devis;
        sscanf(ligne, "%s\n%s\n%d %s %d %s\n%d\n%d\n%d[^\n]",
               devis.nomTache, devis.entreprise, &devis.adresse.numero, devis.adresse.nomRue,
               &devis.adresse.codePostal, devis.adresse.ville, &devis.capital, &devis.duree, &devis.cout);
        printf("iciChargeDevis %d\n", i);
        // Ajouter le devis à la liste de devis de l'offre actuelle
        ajouterMaillonDevisFinChargement(&(offreActuelle->ldevis), devis.nomTache, devis.entreprise,
                                &(devis.adresse), devis.capital, devis.duree, devis.cout);
        printf("iciChargeDevis %d\n", i);
        ++i;
    }

    fclose(fichier);
}

void supprimerDernierMaillon(ListeDevis *liste) {
    if (*liste == NULL) {
        fprintf(stderr, "Erreur : La liste est vide.\n");
        exit(-1);
    }

    MaillonDevis *courant = *liste;
    MaillonDevis *precedent = NULL;

    // va au bout de la chaine et supprime de dernier
    while (courant->suivant != NULL) {
        precedent = courant;
        courant = courant->suivant;
    }
    free(courant);

    // met NULL le dernier maillon
    if (precedent != NULL) {
        precedent->suivant = NULL;
    } 
    else // sinon y'a qu'un élément donc on le supr et la liste est vide
    { 

        *liste = NULL;
    }
}


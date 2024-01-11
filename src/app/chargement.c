#include "chargement.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


Offre** chargement(char* nomFichier, int* nbOffre, int* max){
    // faire gestion d'erreur
    int trouve, pos, i;
    int capital, duree, cout, codePostal, numero;
    char travaux[MAX_TRAVAUX], ligne[MAX_TRAVAUX], entreprise[MAX_TRAVAUX], nomRue[MAX_TRAVAUX], ville[MAX_TRAVAUX];
    Adresse adresse;
    FILE* fe;

    if ((fe = fopen(nomFichier, "r")) == NULL){
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    *nbOffre = 0;
    *max = 10;
    Offre** tOffre, **tmp;

    if ((tOffre = (Offre**)malloc(*max * sizeof(Offre*))) == NULL){
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    while (fgets(ligne, sizeof(ligne), fe) != NULL){
        sscanf(ligne, "%s", travaux);

        #ifdef DEBUG
        printf("Type de travaux lu : %s\n", travaux);  // Débogage
        #endif

        pos = rechercheDichotomique(tOffre, *nbOffre, travaux, &trouve);
        if (trouve == 0){

            #ifdef DEBUG
            printf("Offre insérée à la position %d:\n", pos);  // débogage
            printf("Type de travaux : %s\n", tOffre[pos]->travaux);  // débogage
            #endif

            #ifdef DEBUG
            // Pour vérifier les pointeurs
            printf("Adresse de l'offre à la position %d : %p\n", pos, (void *)tOffre[pos]);  // débogage
            #endif

            #ifdef DEBUG
            // Pour vérifier les offres précédentes
            for (int j = 0; j < pos; j++) {
                printf("Offre à la position %d:\n", j);  // débogage
                printf("Type de travaux : %s\n", tOffre[j]->travaux);  // débogage
            }
            #endif

            if (*nbOffre == *max){
                *max += 10;
                if ((tmp = (Offre**)realloc(tOffre, *max * sizeof(Offre*))) == NULL){
                    perror("realloc");
                    exit(EXIT_FAILURE);
                }
                tOffre = tmp;
            }
            for (i = *nbOffre; i > pos; --i){
                tOffre[i] = tOffre[i - 1];
            }
            if ((tOffre[pos] = (Offre*)malloc(sizeof(Offre))) == NULL){
                perror("malloc");
                exit(EXIT_FAILURE);
            }
            strcpy(tOffre[pos]->travaux, travaux);
            tOffre[pos]->ldevis = listeVide();
            ++(*nbOffre);
        }

        fgets(ligne, sizeof(ligne), fe);
        sscanf(ligne, "%[^\n]", entreprise);

        #ifdef DEBUG
        printf("Nom de l'entreprise lu : %s\n", entreprise);  // Débogage
        #endif

        fgets(ligne, sizeof(ligne), fe);
        sscanf(ligne, "%d %[^0-9] %d %s", &numero, nomRue, &codePostal, ville);

        #ifdef DEBUG
        printf("Adresse lu : %d %s, %d %s\n", numero, nomRue, codePostal, ville);  // Débogage
        #endif

        if (fscanf(fe, "%d", &capital) != 1) {
            printf("Erreur lors de la lecture du capital.\n");
            break;
        }

        #ifdef DEBUG
        printf("Capital lu : %d\n", capital);
        #endif

        if (fscanf(fe, "%d", &duree) != 1) {
            printf("Erreur lors de la lecture de la durée.\n");
            break;
        }

        #ifdef DEBUG
        printf("Durée lu : %d\n", duree);
        #endif

        if (fscanf(fe, "%d", &cout) != 1) {
            printf("Erreur lors de la lecture du coût.\n");
            break;
        }

        #ifdef DEBUG
        printf("Coût lu : %d\n", cout);
        #endif

        adresse.numero = numero;
        strcpy(adresse.nomRue, nomRue);
        strcpy(adresse.ville, ville);
        adresse.codePostal = codePostal;

        nouveauDevis(tOffre, *nbOffre, travaux, entreprise, adresse, capital, duree, cout);
        if (fscanf(fe, "%s", travaux) == EOF) {

            #ifdef DEBUG
            printf("Fin du fichier atteinte.\n");
            break;
            #endif
        }

    }

    fclose(fe);
    return tOffre;
}


//int chargerTache(Offre** tOffres, Tache** tabTaches, ListeFile* fileAttente, int nbrTache, char* nomFichier)
//{
//    FILE* fichier = fopen(nomFichier, "r");
//    if (fichier == NULL)
//    {
//        perror("Erreur d'ouverture du fichier 'précedences.txt'");
//        exit(EXIT_FAILURE);
//    }
//
//    char prec[MAX_TRAVAUX], succ[MAX_TRAVAUX];
//
//    int i;
//    for(i = 0; i < nbrTache; i++)
//    {
//        tabTaches[i] = (Tache*)malloc(sizeof(Tache));
//        if (tabTaches[i] == NULL)
//        {
//            perror("malloc");
//            for (int k = 0; k < i; ++k) free(tabTaches[k]);
//            free(tabTaches);
//            fclose(fichier);
//            return -1;
//        }
//
//        if(tOffres[i] == NULL || tOffres[i]->ldevis == NULL) continue;
//
//        strcpy(tabTaches[i]->tache, tOffres[i]->travaux);
//        tabTaches[i]->duree = tOffres[i]->ldevis->devis.duree;
//
//        tabTaches[i]->succ = NULL;
//        tabTaches[i]->nbPred = 0;
//        tabTaches[i]->traite = 0;
//        tabTaches[i]->dateDebut = 0;
//
//        // Ajout d'instructions de débogage
//        printf("Tâche ajoutée : %s, Durée : %d\n", tabTaches[i]->tache, tabTaches[i]->duree);
//    }
//
//    while (!feof(fichier))
//    {
//        if(fscanf(fichier, "%s %s", prec, succ) != 2)
//        {
//            fprintf(stderr, "Erreur lecture des successeurs\n");
//            printf("Valeurs lues : prec=%s, succ=%s\n", prec, succ);
//            printf("Longueur de prec : %lu, Longueur de succ : %lu\n", strlen(prec), strlen(succ));
//            return -1;
//        }
//
//        int idxPrec = trouverTache(tabTaches, nbrTache, prec, 0);
//        if (idxPrec != -1)
//        {
//            ajouterSuccesseur(tabTaches[idxPrec], succ);
//
//            int idxSucc = trouverTache(tabTaches, nbrTache, succ, 0);
//
//            if (idxSucc != -1)
//                tabTaches[idxSucc]->nbPred++;
//        }
//
//        // Ajout d'instructions de débogage
//        printf("Successeur ajouté pour la tâche %s : %s\n", prec, succ);
//    }
//
//    fclose(fichier);
//
//    for(i = 0; i < nbrTache; i++)
//    {
//        if(!tabTaches[i]) continue;
//
//        if(!tabTaches[i]->nbPred)
//        {
//            enfilerDebut(fileAttente, tabTaches[i]);
//
//            // Ajout d'instructions de débogage
//            printf("Tâche enfilée : %s\n", tabTaches[i]->tache);
//        }
//    }
//
//    if(fileAttente == NULL || *fileAttente == NULL) return -2;
//
//    traitementFile(fileAttente, tabTaches, nbrTache);
//
//    // Ajout d'instructions de débogage
//    printf("Chargement des tâches terminé avec succès.\n");
//
//    return 0;
//}

//
// Precedences **chargerPrecedences(char* nomFichier, int *tPhysique, int *nbPrec)
// {
//    //Ajouter couleur sur les message d'erreur
//
//    FILE* fe;
//    char line[MAX_TRAVAUX];
//    *nbPrec = 0;
//    Precedences **tPrec, **tmp;
//
//    #ifdef DEBUG
//    printf("Nom du fichier donné : %s\n", nomFichier);
//    printf("Taille max actuel du tableau de pointeurs de précédences : %d\n", *tPhysique);
//    printf("Taille logique actuel (normalement = à 0) : %d\n", *nbPrec);
//    #endif
//
//    if ( (fe = fopen(nomFichier, "r")) == NULL ) {
//        perror("fopen");
//        exit(EXIT_FAILURE);
//    }
//
//    // Mallocs
//    if ( (tPrec = (Precedences**)malloc(sizeof(Precedences*) * (*tPhysique) )) == NULL)
//    {
//        perror("malloc tPrec");
//        exit(EXIT_FAILURE);
//    }
//
//    if ( (tmp = (Precedences**)malloc(sizeof(Precedences*) * (*tPhysique) )) == NULL)
//    {
//        perror("malloc tmp");
//        exit(EXIT_FAILURE);
//    }
//
//    // Lecture fichier
//    while( fgets(line, sizeof(Precedences), fe) != NULL)
//    {
//        if ( *nbPrec >= *tPhysique )
//        {
//            *tPhysique +=5;
//            if ( (tmp = realloc(tPrec, *tPhysique * sizeof(Precedences*))) == NULL)
//            {
//                perror("realloc tPrec");
//                exit(EXIT_FAILURE);
//            }
//            tPrec = tmp;
//        }
//        Precedences *prec;
//
//        if ( (tPrec[*nbPrec] = malloc(sizeof(Precedences))) == NULL )
//        {
//            perror("malloc prec");
//            exit(EXIT_FAILURE);
//        }
//        printf("ici\n");
//        if ( sscanf(line, "%s %s", tPrec[*nbPrec]->premier, tPrec[*nbPrec]->deuxieme ) == 2 )
//        {
//            ++(*nbPrec);
//        }
//        else
//        {
//            fprintf(stderr, "%sErreur lors du scan ligne %s\n", UNDERLINE RED, RESET);
//            exit(EXIT_FAILURE);
//        }
//    }
//
//    #ifdef DEBUG
//    printf("Fin fonction chargementPrecedence\n%s %s", UNDERLINE PURPLE, RESET);
//    #endif
//    fclose(fe);
//    return tPrec;
//}
//
//
//void affichageeeeee( char **nomTache, int tLogique )
//{
//    printf("Début affichage\n");
//    printf(" tLog : %d", tLogique);
//    for( int i = 0; i < tLogique; ++i )
//    {
//        printf(" %s\n", nomTache[i]);
//    }
//    printf("Fin affichage\n");
//}
//
//void rechercheTache(Tache **tabTache, int tLogique, char *val, int *trouve)
//{
//    if (tabTache == NULL)
//    {
//        fprintf(stderr, "1Problème chargement liste nomTache.");
//        exit(EXIT_FAILURE);
//    }
//
//    for ( int i = 0; i <tLogique; ++i)
//    {
//        if (tabTache[i] == NULL){
//            fprintf(stderr, "2Problème chargement liste nomTache.");
//            exit(EXIT_FAILURE);
//        }
//
//        printf("RechercheTache, iteration: %d\n", i);
//        printf("tLogique rechercheTache: %d\n", tLogique);
//        printf("val rechercheTache: %s\n", val);
//        printf("tabTache[i]->tache rechercheTache: %s\n", tabTache[i]->tache);
//
//        if ( strcmp(val, tabTache[i]->tache) == 0)
//        {
//            printf("Trouvé rechercheTache\n");
//            *trouve = 1;
//            return;
//        }
//    }
//    *trouve = 0;
//}
//
//Maillon* creerMaillon(char nom[MAX_LIGNE])
//{
//    Maillon* nouveauMaillon;
//    if ( (nouveauMaillon = (Maillon*)malloc(sizeof(Maillon))) == NULL )
//    {
//        perror("malloc");
//        exit(EXIT_FAILURE);
//    }
//    else
//    {
//        strcpy(nouveauMaillon->nom, nom);
//        nouveauMaillon->suivant = NULL;
//    }
//    return nouveauMaillon;
//}
//
//void ajouterSuccesseur(ListeSucc* liste, char nom[MAX_LIGNE])
//{
//
//    Maillon* nouveauMaillon = creerMaillon(nom);
//    if (*liste == NULL)
//    {
//        *liste = nouveauMaillon;
//    }
//    else
//    {
//        Maillon* courant = *liste;
//        while (courant->suivant != NULL)
//        {
//            courant = courant->suivant;
//        }
//        courant->suivant = nouveauMaillon;
//    }
//}
//
//ListeSucc creerListeSucc(void)
//{
//    return NULL;
//}
//
//
//ListeSucc chercherSuccesseur(Precedences** tPrecs, int tLogique, char predecesseur[MAX_LIGNE]) {
//    ListeSucc listeResultat = creerListeSucc();
//
//    for (int i = 0; i < tLogique; i++)
//    {
//        if (strcmp(tPrecs[i]->premier, predecesseur) == 0)
//        {
//            // Ajouter le successeur à la liste
//            ajouterSuccesseur(&listeResultat, tPrecs[i]->deuxieme);
//        }
//    }
//
//    return listeResultat;
//}
//
//int nombrePredecesseurs(Precedences** tPrecs, int tLogique, char successeur[MAX_LIGNE]) {
//    int comptePredecesseurs = 0;
//
//    for (int i = 0; i < tLogique; i++)
//    {
//        if (strcmp(tPrecs[i]->deuxieme, successeur) == 0)
//        {
//            comptePredecesseurs++;
//        }
//    }
//    return comptePredecesseurs;
//}
//
//Tache **listerTache( Precedences **tPrecs, int tLogPrecs, int *tLogique, int *tPhysique)
//{
//    Tache **tabTaches = (Tache**)malloc(sizeof(Tache*) * tLogPrecs);
//    *tLogique = tLogPrecs;
//    int trouve;
//
//    if ( tabTaches == NULL )
//    {
//        perror("malloc");
//        exit(EXIT_FAILURE);
//    }
//
//    for(int i = 0; i < tLogPrecs; ++i)
//    {
//        if ( (tabTaches[i] = malloc(sizeof(Tache))) == NULL)
//        {
//            perror("malloc");
//            exit(EXIT_FAILURE);
//        }
//
//        printf("Iteration: %d\n", i);
//
//        rechercheTache(tabTaches, *tLogique, tPrecs[i]->premier, &trouve);
//        printf("trouve après rechercheTache: %d\n", trouve);
//
//        if ( trouve == 0 )
//        {
//            if (*tLogique == *tPhysique - 1)
//            {
//                *tPhysique += 10;
//                tabTaches = realloc(tabTaches, (*tPhysique) * sizeof(Tache*));
//                if (tabTaches == NULL)
//                {
//                    perror("realloc");
//                    exit(EXIT_FAILURE);
//                }
//            }
//
//
//            strcpy(tabTaches[*tLogique]->tache, tPrecs[i]->premier);
//            tabTaches[*tLogique]->duree = 0;
//            tabTaches[*tLogique]->nbPred = nombrePredecesseurs(tPrecs, *tLogique, tabTaches[*tLogique]->tache);
//            tabTaches[*tLogique]->succ = chercherSuccesseur(tPrecs, *tLogique, tabTaches[*tLogique]->tache);
//            tabTaches[*tLogique]->dateDebut = 0;
//            tabTaches[*tLogique]->traite = false;
//            ++(*tLogique);
//        }
//
//        rechercheTache(tabTaches, *tLogique, tPrecs[i]->deuxieme, &trouve);
//        if ( trouve == 0 )
//        {
//            if ( (tabTaches[*tLogique] = malloc(sizeof(Tache))) == NULL)
//            {
//                perror("malloc");
//                exit(EXIT_FAILURE);
//            }
//            strcpy(tabTaches[*tLogique]->tache, tPrecs[i]->deuxieme);
//            ++(*tLogique);
//        }
//    }
//
//    return tabTaches;
//}

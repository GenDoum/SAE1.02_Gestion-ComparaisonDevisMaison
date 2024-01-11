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


 Precedences **chargerPrecedences(char* nomFichier, int *tPhysique, int *nbPrec) 
 {
    //Ajouter couleur sur les message d'erreur
    
    FILE* fe;
    char line[MAX_TRAVAUX];
    *nbPrec = 0;
    Precedences **tPrec, **tmp;
    
    #ifdef DEBUG 
    printf("Nom du fichier donné : %s\n", nomFichier);
    printf("Taille max actuel du tableau de pointeurs de précédences : %d\n", *tPhysique);
    printf("Taille logique actuel (normalement = à 0) : %d\n", *nbPrec);
    #endif

    if ( (fe = fopen(nomFichier, "r")) == NULL ) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    // Mallocs
    if ( (tPrec = (Precedences**)malloc(sizeof(Precedences*) * (*tPhysique) )) == NULL)
    {
        perror("malloc tPrec");
        exit(EXIT_FAILURE);
    }

    if ( (tmp = (Precedences**)malloc(sizeof(Precedences*) * (*tPhysique) )) == NULL)
    {
        perror("malloc tmp");
        exit(EXIT_FAILURE);
    }

    // Lecture fichier
    while( fgets(line, sizeof(Precedences), fe) != NULL)
    {
        if ( *nbPrec >= *tPhysique )
        {
            *tPhysique +=5;
            if ( (tmp = realloc(tPrec, *tPhysique * sizeof(Precedences*))) == NULL)
            {
                perror("realloc tPrec");
                exit(EXIT_FAILURE);
            }
            tPrec = tmp;            
        }
        Precedences *prec;

        if ( (tPrec[*nbPrec] = malloc(sizeof(Precedences))) == NULL )
        {
            perror("malloc prec");
            exit(EXIT_FAILURE);
        }
        printf("ici\n");
        if ( sscanf(line, "%s %[^\n]", tPrec[*nbPrec]->premier, tPrec[*nbPrec]->deuxieme ) == 2 )
        {
            ++(*nbPrec);
        }
        else
        {
            fprintf(stderr, "%sErreur lors du scan ligne %s\n", UNDERLINE RED, RESET);
            exit(EXIT_FAILURE);
        }
    }

    #ifdef DEBUG 
    printf("Fin fonction chargementPrecedence\n%s %s", UNDERLINE PURPLE, RESET);
    #endif
    fclose(fe);
    return tPrec;
}


void affichageeeeee( char **nomTache, int tLogique )
{
    printf("Début affichage\n");
    printf(" tLog : %d", tLogique);
    for( int i = 0; i < tLogique; ++i )
    {
        printf(" %s\n", nomTache[i]);
    }
    printf("Fin affichage\n");
}

void rechercheTache(Tache **tabTache, int tLogique, char *val, int *trouve)
{
    if (tabTache == NULL)
    {
        fprintf(stderr, "1Problème chargement liste nomTache.");
        exit(EXIT_FAILURE);
    }

    for ( int i = 0; i <tLogique; ++i)
    {
        if (tabTache[i] == NULL){
            fprintf(stderr, "2Problème chargement liste nomTache.");
            exit(EXIT_FAILURE);
        }

        printf("RechercheTache, iteration: %d\n", i);
        printf("tLogique rechercheTache: %d\n", tLogique);
        printf("val rechercheTache: %s\n", val);
        printf("tabTache[i]->tache rechercheTache: %s\n", tabTache[i]->tache);

        if ( strcmp(val, tabTache[i]->tache) == 0)
        {
            printf("Trouvé rechercheTache\n");
            *trouve = 1;
            return;
        }
    }
    *trouve = 0;
}

Maillon* creerMaillon(char nom[MAX_LIGNE]) 
{
    Maillon* nouveauMaillon;
    if ( (nouveauMaillon = (Maillon*)malloc(sizeof(Maillon))) == NULL )
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }  
    else 
    {
        strcpy(nouveauMaillon->nom, nom);
        nouveauMaillon->suivant = NULL;
    }
    return nouveauMaillon;
}

void ajouterSuccesseur(ListeSucc* liste, char nom[MAX_LIGNE]) 
{

    Maillon* nouveauMaillon = creerMaillon(nom);
    if (*liste == NULL) 
    {
        *liste = nouveauMaillon;
    } 
    else 
    {
        Maillon* courant = *liste;
        while (courant->suivant != NULL) 
        {
            courant = courant->suivant;
        }
        courant->suivant = nouveauMaillon;
    }
}

ListeSucc creerListeSucc(void) 
{
    return NULL;
}


ListeSucc chercherSuccesseur(Precedences** tPrecs, int tLogique, char predecesseur[MAX_LIGNE]) {
    ListeSucc listeResultat = creerListeSucc();

    for (int i = 0; i < tLogique; i++) 
    {
        if (strcmp(tPrecs[i]->premier, predecesseur) == 0) 
        {
            // Ajouter le successeur à la liste
            ajouterSuccesseur(&listeResultat, tPrecs[i]->deuxieme);
        }
    }

    return listeResultat;
}

int nombrePredecesseurs(Precedences** tPrecs, int tLogique, char successeur[MAX_LIGNE]) {
    int comptePredecesseurs = 0;

    for (int i = 0; i < tLogique; i++) 
    {
        if (strcmp(tPrecs[i]->deuxieme, successeur) == 0) 
        {
            comptePredecesseurs++;
        }
    }
    return comptePredecesseurs;
}

Tache **listerTache( Precedences **tPrecs, int tLogPrecs, int *tLogique, int *tPhysique)
{
    Tache **tabTaches = (Tache**)malloc(sizeof(Tache*) * tLogPrecs);
    *tLogique = tLogPrecs;
    int trouve;

    if ( tabTaches == NULL )
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < tLogPrecs; ++i)
    {
        if ( (tabTaches[i] = malloc(sizeof(Tache))) == NULL)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        printf("Iteration: %d\n", i);

        rechercheTache(tabTaches, *tLogique, tPrecs[i]->premier, &trouve);
        printf("trouve après rechercheTache: %d\n", trouve);

        if ( trouve == 0 )
        {
            if (*tLogique == *tPhysique - 1)
            {
                *tPhysique += 10;
                tabTaches = realloc(tabTaches, (*tPhysique) * sizeof(Tache*));
                if (tabTaches == NULL)
                {
                    perror("realloc");
                    exit(EXIT_FAILURE);
                }
            }

            if ( (tabTaches[*tLogique] = malloc(sizeof(Tache))) == NULL)
            {
                perror("malloc");
                exit(EXIT_FAILURE);
            }

            strcpy(tabTaches[*tLogique]->tache, tPrecs[i]->premier);
            tabTaches[*tLogique]->duree = 0;
            tabTaches[*tLogique]->nbPred = nombrePredecesseurs(tPrecs, *tLogique, tabTaches[*tLogique]->tache);
            tabTaches[*tLogique]->succ = chercherSuccesseur(tPrecs, *tLogique, tabTaches[*tLogique]->tache);
            tabTaches[*tLogique]->dateDebut = 0;
            tabTaches[*tLogique]->traite = false;
            ++(*tLogique);
        }

        rechercheTache(tabTaches, *tLogique, tPrecs[i]->deuxieme, &trouve);
        if ( trouve == 0 )
        {
            if ( (tabTaches[*tLogique] = malloc(sizeof(Tache))) == NULL)
            {
                perror("malloc");
                exit(EXIT_FAILURE);
            }
            strcpy(tabTaches[*tLogique]->tache, tPrecs[i]->deuxieme);
            ++(*tLogique);
        }
    }

    return tabTaches;
}

/*
char **listerNomTache(Precedences **tPrecs, int tLogPrecs, int *tLogique, int *tPhysique)
{
    char **nomTache;

    #ifdef DEBUG
    printf("Début de listerNomTache\n");
    #endif
    printf("ici ?\n");
    if ((nomTache = (char**)malloc(sizeof(char*) * tLogPrecs)) == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    printf("ici ?\n");
    // #ifdef DEBUG
    // printf("Allocation initiale de mémoire pour nomTache\n");
    // #endif
    
    
    for (int k = 0; k < tLogPrecs; ++k)
    {
        printf("ici ?\n");
        #ifdef DEBUG
        printf("Début de la boucle i=%d\n", k);
        #endif

        if (*tLogique == *tPhysique)
        {
            printf("icirealloc ?\n");
            if ((nomTache = (char**)realloc(nomTache, sizeof(char*) * (*tPhysique + 5))) == NULL)
            {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
            (*tPhysique) += 5;

            #ifdef DEBUG
            printf("Réallocation de mémoire pour nomTache, nouvelle taille : %d\n", *tPhysique);
            #endif
        }
        printf("ici ?\n");
        printf("ici ?\n");
        for( int i = 0; i < tLogPrecs; ++i )
        {
            printf("ici HSIFSUFHS: %d\n", i);

            for( int j = 0; j < *tLogique; ++j)
            {
                printf(" %s %s\n", tPrecs[k]->premier, nomTache[j]);
                if( strcmp(tPrecs[k]->premier, nomTache[j]) == 0 )
                {
                    printf(" %s Déjà présent\n", tPrecs[i]->premier);
                    break;
                }
                printf(" %s %s\n", tPrecs[k]->deuxieme, nomTache[i]);
                strcpy( nomTache[*tLogique], tPrecs[k]->premier );
                ++(*tLogique);
                printf("tlog : %d\n", *tLogique);

            }
            for( int j = 0; j < *tLogique; ++j)
            {
                if( strcmp(tPrecs[k]->deuxieme, nomTache[j]) == 0 )
                {
                    printf(" %s Déjà présent\n", tPrecs[k]->deuxieme);
                    break;
                }
                strcpy( nomTache[*tLogique], tPrecs[k]->deuxieme );
                *tLogique +=1;
                printf("tlog : %d\n", *tLogique);
            }
        }
        printf("ici\n");
    }
    printf("fini\n");
    return nomTache;
}



void compterPrecedences( Precedences **tPrecs, int tLogTabPrecedence, char **nomTache,int *tLogTabNomTache, Precedence **tPrec)
{
    int tPhysiqueNomTache;
    // #ifdef DEBUG
    // printf("\nDebug compterPrecedances\n choix : %d\ntaille logique, tLogique : %d\n %s %s", choix, tLogique, UNDERLINE PURPLE, RESET);
    // #endif 

    nomTache = listerNomTache(tPrecs, tLogTabPrecedence, tLogTabNomTache, &tPhysiqueNomTache);
    printf("\n%s %s %s\n", UNDERLINE RED, nomTache[0], RESET);
    printf("%d trcu\n", *tLogTabNomTache);
    affichageeeeee( nomTache, *tLogTabNomTache );

    if ( nomTache == NULL )
    {
        fprintf(stderr, "Problème chargement liste nomTache %s %s", UNDERLINE RED, RESET);
        exit(EXIT_FAILURE);
    }

    if ( (tPrec = (Precedence**)malloc(sizeof(Precedence*) * (*tLogTabNomTache)) ) == NULL )
    {
        perror("malloc tableauStrucPrecedence");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < *tLogTabNomTache; ++i)
    {
        if ( (tPrec[i] = (Precedence *)malloc(sizeof(Precedence))) == NULL )
        {
            perror("malloc tPrec[i]");
            exit(EXIT_FAILURE);
        }

        for ( int j = 0; j < tLogTabPrecedence; ++j)
        {
            strcpy(tPrec[j]->nom, nomTache[j]);
            
            if ( strcmp(tPrecs[j]->premier, nomTache[i]) == 0 )
            {
                ++(tPrec[j]->nbSuccesseur);
            }
            if ( strcmp(tPrecs[j]->deuxieme, nomTache[i]) == 0 )
            {
                ++(tPrec[j]->nbPredecesseur);
            }
        }
    }
}

Tache** chargerTaches(Precedences **tPrecs, int tLogTabPrecedence, char **nomTache, int *tLogTabNomTache, int *tLogTaches)
{
    Tache **taches;
    Precedence **tFichier;
    printf("dd\n");

    compterPrecedences(tPrecs, tLogTabPrecedence, nomTache, tLogTabNomTache, tFichier);
    
    if ( (taches = (Tache**)malloc(sizeof(Tache*) * (*tLogTabNomTache))) == NULL )
    {
        perror("malloc Tache");
        exit(EXIT_FAILURE);
    }
    printf("dd\n");

    for ( int i = 0; i < *tLogTabNomTache; ++i )
    {
        if ( (taches[i] = (Tache*)malloc(sizeof(Tache))) == NULL )
        {
            perror("Taches[i]");
            exit(EXIT_FAILURE);
        }

    }

    return taches;
}
*/
/*
Tache** chargerTaches(Precedences **tPrecs, int tLogTabPrecedence, char **nomTache, int *tLogTabNomTache, int *tLogTaches) 
{
    // realloc ?

    Tache **taches;
    Precedence **tPrecedence;
    printf("dd\n");
    if ( (taches = malloc(MAX_TACHES * sizeof(Tache*))) == NULL )
    {
        perror("malloc Taches");
        exit(EXIT_FAILURE);
    }
    printf("dd\n");

    if ( (tPrecedence = malloc(MAX_TACHES * sizeof(Precedence*))) == NULL )
    {
        perror("malloc Precedent");
        exit(EXIT_FAILURE);
    }
    printf("dd\n");
    
    if ( (tPrecs = malloc(MAX_TACHES * sizeof(Precedences*))) == NULL )
    {
        perror("malloc Precs");
        exit(EXIT_FAILURE);
    }
    printf("dd\n");

    compterPrecedences(tPrecs, tLogTabPrecedence, nomTache, tLogTabNomTache, tPrecedence);
    printf("ddddd\n");

    for ( int i = 0; i < *tLogTabNomTache; ++i )
    {

        ///if ( (taches[i] = (Tache**)malloc(sizeof(Tache*))) == NULL )
        ///{
        ///    perror("malloc Taches");
        ///    exit(EXIT_FAILURE);
        ///}
///
        taches[i]->dateDebut = 0;
        taches[i]->duree = 0;
        taches[i]->traite = false;
        for(int j = 0; j < *tLogTabNomTache; ++j)
        {
            if ( strcmp(tPrecedence[j]->nom, nomTache[i]) == 0 )
            {
                strcpy(taches[i]->tache, nomTache[i]);
                taches[i]->nbPred = tPrecedence[j]->nbPredecesseur;
            }
        }
    }

    return taches;
}
*/
/*
Tache** chargerTaches(char* nomFichier, Precedences **tPrecs, int tLogTabPrecedence, char **nomTache, int tLogTabNomTache) 
{
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur : impossible d'ouvrir le fichier %s\n%s %s", nomFichier, UNDERLINE RED, RESET);
        exit(EXIT_FAILURE);
    }

    Tache** taches;
    if ( (taches = malloc(MAX_TACHES * sizeof(Tache*))) == NULL )
    {
        perror("malloc Taches");
        exit(EXIT_FAILURE);
    }
    int nbTaches = 0;
    char ligne[MAX_LIGNE];
    Precedence **tPrec = NULL;
    compterPrecedences(tPrecs, tLogTabPrecedence, nomTache, tLogTabNomTache, tPrec);

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        Tache* tache;

        if ( (tache = malloc(sizeof(Tache*))) == NULL ) 
        {
            perror("malloc tache");
            exit(EXIT_FAILURE);
        }
        if ( sscanf(ligne, "%s %d", tache->tache, &(tache->duree)) != 2 )
        {
            fprintf(stderr, "Erreur lors du scan de la ligne%s %s", UNDERLINE RED, RESET);
            exit(EXIT_FAILURE);
        }
        else
        {

            tache->nbPred = 0; // à calculer à partir du fichier precedences.txt
            tache->succ = listeVide(); // à calculer à partir du fichier precedences.txt
            tache->dateDebut = 0;
            tache->traite = false;
        }
        

        taches[nbTaches] = tache;
        nbTaches++;
    }

    fclose(fichier);

    return taches;
}
*/

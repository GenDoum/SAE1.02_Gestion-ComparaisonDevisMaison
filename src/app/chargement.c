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

        if ( (prec = malloc(sizeof(Precedences))) == NULL )
        {
            perror("malloc prec");
            exit(EXIT_FAILURE);
        }

        if ( sscanf(line, "%s %[^\n]", prec->premier, prec->deuxieme ) == 2 )
        {
            tPrec[*nbPrec] = prec;
            ++(*nbPrec);
            



            #ifdef DEBUG
            printf("Ligne actuel : %s\n", line);
            printf("Première précédence : %s\nDeuxième précédence : %s\n", prec->premier, prec->deuxieme);
            printf("Nouveau nbPrec : %d\n\n\n", *nbPrec);
            #endif
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


void compterPrecedences( Precedences **tPrecs, int tLogTabPrecedence, char **nomTache,int tLogTabNomTache, Precedence **tPrec)
{
    #ifdef DEBUG
    printf("\nDebug compterPrecedances\n choix : %d\ntaille logique, tLogique : %d\n %s %s", choix, tLogique, UNDERLINE PURPLE, RESET);
    #endif 

    if ( (tPrec = (Precedence**)malloc(sizeof(Precedence*) * tLogTabNomTache) ) == NULL )
    {
        perror("malloc tableauStrucPrecedence");
        exit(EXIT_FAILURE);
    }

    int maxtLog = (tLogTabPrecedence > tLogTabNomTache) ? tLogTabPrecedence : tLogTabNomTache;
    // pour chaque ligne de precedences for chaque if de nom de tache ajouter !!!! for à cahnger ??
    for( int j = 0; j < maxtLog; ++j)
    {
        if ( (tPrec[j] = (Precedence *)malloc(sizeof(Precedence))) == NULL )
        {
            perror("malloc tPrec[j]");
            exit(EXIT_FAILURE);
        }

        if ( j < tLogTabNomTache ) // si il reste des tâches on continu
        {
            strcpy(tPrec[j]->nom, nomTache[j]);
        }

        if ( j < tLogTabPrecedence )
        {
            if ( strcmp(tPrecs[j]->premier, nomTache[j]) == 0 )
            {
                ++(tPrec[j]->nbSuccesseur);
            }
            if ( strcmp(tPrecs[j]->deuxieme, nomTache[j]) == 0 )
            {
                ++(tPrec[j]->nbPredecesseur);
            }
        }

    }
}

/* Version que j'ai demandé à caht pour paufiner ce qui allait pas trop

void compterPrecedences(Precedences **tPrecs, int tLogTabPrecedence, char **nomTache, int tLogTabNomTache, Precedence **tPrec)
{
    #ifdef DEBUG
    printf("\nDebug compterPrecedances\n choix : %d\ntaille logique, tLogique : %d\n %s %s", choix, tLogTabPrecedence, UNDERLINE_PURPLE, RESET_COLOR);
    #endif

    // Determine the maximum logical size
    int maxLogSize = (tLogTabPrecedence > tLogTabNomTache) ? tLogTabPrecedence : tLogTabNomTache;

    // Allocate memory for tPrec
    if ((tPrec = (Precedence **)malloc(sizeof(Precedence *) * maxLogSize)) == NULL)
    {
        perror("malloc tableauStrucPrecedence");
        exit(EXIT_FAILURE);
    }

    // Iterate over all elements in both arrays
    for (int j = 0; j < maxLogSize; ++j)
    {
        // Allocate memory for each tPrec element
        if ((tPrec[j] = (Precedence *)malloc(sizeof(Precedence))) == NULL)
        {
            perror("malloc tPrec[j]");
            exit(EXIT_FAILURE);
        }

        // Copy nomTache if it exists
        if (j < tLogTabNomTache)
        {
            strcpy(tPrec[j]->nom, nomTache[j]);
        }

        // Verify if nomTache is in tPrecs and update counts
        for (int k = 0; k < tLogTabPrecedence; ++k)
        {
            if (j < tLogTabNomTache && strcmp(tPrecs[k]->premier, nomTache[j]) == 0)
            {
                ++(tPrec[j]->nbSuccesseur);
            }

            if (j < tLogTabNomTache && strcmp(tPrecs[k]->deuxieme, nomTache[j]) == 0)
            {
                ++(tPrec[j]->nbPredecesseur);
            }
        }
    }
}

*/



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

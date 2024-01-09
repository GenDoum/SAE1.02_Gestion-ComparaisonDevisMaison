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

void calculerPrecedences(const char *nomFichier, int *nbPrec, Precedences ***tPrec) {
    FILE *fe;
    char line[MAX_LIGNE];
    *nbPrec = 0;

    if ((fe = fopen(nomFichier, "r")) == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    Precedences **tmp = NULL;
    while (fgets(line, sizeof(line), fe) != NULL) {
        (*nbPrec)++;
        tmp = realloc(tmp, *nbPrec * sizeof(Precedences *));
        if (tmp == NULL) {
            perror("Erreur lors de la réallocation du tableau");
            exit(EXIT_FAILURE);
        }
        tmp[*nbPrec - 1] = malloc(sizeof(Precedences));
        if (tmp[*nbPrec - 1] == NULL) {
            perror("Erreur lors de l'allocation de la structure");
            exit(EXIT_FAILURE);
        }
        sscanf(line, "%s %s", tmp[*nbPrec - 1]->premier, tmp[*nbPrec - 1]->deuxieme);
    }
    fclose(fe);
    *tPrec = tmp;
}

void construireListeSuccesseurs(Precedences **tPrec, int nbPrec) {
    printf("\nListe des noms de successeurs :\n");
    for (int i = 0; i < nbPrec; i++) {
        int count = 0;
        for (int j = 0; j < nbPrec; j++) {
            if (strcmp(tPrec[i]->premier, tPrec[j]->deuxieme) == 0) {
                count++;
                printf("%s -> %s\n", tPrec[j]->deuxieme, tPrec[j]->premier);
            }
        }
        if (count == 0) {
            printf("%s -> Aucun successeur\n", tPrec[i]->deuxieme);
        }
    }
}

Tache** chargerTaches(char* nomFichier/* apporter tableau des précédences*/) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        fprintf(stderr, "Erreur : impossible d'ouvrir le fichier %s\n", nomFichier);
        exit(EXIT_FAILURE);
    }

    Tache** taches;
    if ( (taches = malloc(MAX_TACHES * sizeof(Tache*))) == NULL )
    {
        perror("malloc Taches");
    }

    int nbTaches = 0;

    char ligne[100];
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        Tache* tache;

        if ( (tache = malloc(sizeof(Tache))) == NULL ) 
        {
            perror("malloc tache");
        }

        if ( sscanf(ligne, "%s %d", tache->tache, &(tache->duree)) != 2 )
        {
            fprintf(stderr, "\x1B[31mErreur lors du scan de la ligne:\x1B[0m ");
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

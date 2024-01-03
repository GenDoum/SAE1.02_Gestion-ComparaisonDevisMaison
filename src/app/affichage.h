//
// Created by Mathéo Hersan on 03/01/2024.
//

#ifndef SAE1_02_AFFICHAGE_H
#define SAE1_02_AFFICHAGE_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tache.h"

void afficherPrecedences(char* nomFichier);
void afficherOffres(Offre** tOffre, int nbOffres);
void afficherDevisParTypeTravaux(Offre** tOffre, int nbDevis);
void afficherUnTravaux(Offre* offre);
void afficherDevisEntrepriseType(Offre** tOffre, int nbDevis);


#endif //SAE1_02_AFFICHAGE_H

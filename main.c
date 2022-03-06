                /* ------------------------------------------------------------------------- */
                                        /* Nom du fichier : main.c */
                    /* Rôle : Le fichier contient la fonction main et les tests unitaires */
                /* ------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "code.h"

int main(int argc, char ** argv){
    FILE * fichier;
    FILE * file;
    listeS_t * liste;
    char * anneeSemaine, * jourHeure;
    char * lcoTete = NULL;
    char * lcoFin = NULL;
    char motif[10] ="TPs de SDD";

    anneeSemaine = (char *) malloc(sizeof(char));
    jourHeure = (char *) malloc(sizeof(char));

    if(argv[1]){
        fichier = fopen(argv[1], "r");

        if (!fichier){
            printf("Erreur : Ouverture du fichier impossible.");
            exit(0);
        }
        else{
            strcpy(anneeSemaine, "202215");
            strcpy(jourHeure, "108TPs de SDD");
            liste = creerListe(fichier);
            afficherListe(liste);
            //supprimerAction(&liste, anneeSemaine, jourHeure);

            file = fopen("sauvegarderSDD.txt", "w");
            if (file){
                sauvegarderSDD(file, liste);
            }
            creerLco(liste, motif, &lcoTete, &lcoFin);
            afficherLco(lcoTete, lcoFin);
            //libererListe(&liste);
            //printf("\n\n\n==== Suppression ===\n\n\n");
            //supprimerAction(&liste, anneeSemaine, jourHeure);
            //afficherListe(liste);
            fclose(file);
            /*
            */
            fclose(fichier);
        }
    }
    else{
        printf("Vous n'avez pas entré le nom du fichier qui contient votre agenda.\n");
    }

    return 0;
}
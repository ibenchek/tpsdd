                /* ----------------------------------------------------------------------- */
                                        /* Nom du fichier : code.c */
                        /* Rôle : Le fichier contient l'implémentation des fonctions */
                /* ----------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "code.h"

/* ----------------------------------------------------------------------- */
/* existe vérifie si une chaîne existe dans une liste chaînée ou non */
/* */
/* En entrée: chaine, lch Une chaîne de caractères */
/* et un pointeur (tête de la liste chaînée) */
/* */
/* En sortie: La valeur entière retournée est 1 si la chaîne existe */
/* dans la liste et 0 si la chaîne n'existe pas. */
/* ----------------------------------------------------------------------- */

int existe (char * chaine, listeS_t * lch){
    int           res = 0;
    semaine_t  *  cour;

    cour = lch->tete->suivant;

    while (cour != NULL){
        if(!strcmp(chaine, cour->anneeSemaine)){
            res = 1;
        }
        cour = cour->suivant;
    }
    
    return res;
}

/* ----------------------------------------------------------------------- */
/* Tri permet de trouver l'emplacement où on doit insérer la semaine */
/* pour avoir une liste triée */
/* */
/* En entrée: chaine, lch Une chaîne de caractères */
/* et un pointeur (tête de la liste chaînée) */
/* */
/* En sortie: La fonction retourne l'adresse de l'élément précédent */
/* l'emplacement où on souhaite insérer la nouvelle semaine */
/* ----------------------------------------------------------------------- */

semaine_t * Tri(char * chaine, listeS_t * lch){
    semaine_t * prec;
    semaine_t * cour;

    prec = lch->tete;
    cour = lch->tete->suivant;

    while((cour != NULL) && (strcmp(chaine, cour->anneeSemaine) > 0)){
        prec = prec->suivant;
        cour = cour->suivant;
    }

    return prec;
}

/* ----------------------------------------------------------------------- */
/* rechercheSemaine permet de trouver une semaine dans une liste chaînée */
/* */
/* En entrée: chaine, lch Une chaîne de caractères */
/* et un pointeur (tête de la liste chaînée) */
/* */
/* En sortie: La fonction retourne l'adresse du bloc qui contient */
/* la semaine entrée en paramètre */
/* ----------------------------------------------------------------------- */

semaine_t * rechercheSemaine(char * chaine, listeS_t * lch){
    semaine_t * cour;

    cour = lch->tete->suivant;

    while ((cour != NULL) && (strcmp(chaine, cour->anneeSemaine) != 0)){
        cour = cour->suivant;
    }

    return cour;
}

/* ----------------------------------------------------------------------- */
/* Tri2 permet de trouver l'emplacement où on doit insérer l'action */
/* pour avoir une liste triée */
/* */
/* En entrée: chaine, lch Une chaîne de caractères */
/* et un pointeur (tête de la liste chaînée) */
/* */
/* En sortie: La fonction retourne l'adresse de l'élément précédent */
/* l'emplacement où on souhaite insérer la nouvelle action */
/* ----------------------------------------------------------------------- */

action_t * Tri2(char * chaine, listeA_t * lch){
    action_t * prec;
    action_t * cour;

    prec = lch->tete;
    cour = lch->tete->suivant;

    while((cour != NULL) && (strcmp(chaine, cour->jourHeure) > 0)){
        prec = prec->suivant;
        cour = cour->suivant;
    }

    return prec;
}

/* ----------------------------------------------------------------------- */
/* creerListe permet de construire l'agenda (liste à deux niveaux) */
/* à partir d'un fichier */
/* */
/* En entrée: fichier (supposé ouvert) */
/* */
/* En sortie: La foction retourne l'adresse de tête de la liste */
/* qu'elle vient de construire. */
/* ----------------------------------------------------------------------- */

listeS_t * creerListe (FILE * fichier){
    listeS_t   *  lch;
    semaine_t  *  place;
    semaine_t  *  semaine_courante;
    action_t   *  place2;
    char       *  buffer;
    char       *  chaine;

    /* Quand le compilateur me dit :
       " x is used uninitialised in this fuction "
       c'est que je suis en train de manipuler un pointeur alors que je l'ai pas alloué
    */
    
    lch = (listeS_t *) malloc(sizeof(listeS_t));
    lch->tete = (semaine_t *) malloc(sizeof(semaine_t));

    place = (semaine_t *) malloc(sizeof(semaine_t));
    place2 = (action_t *) malloc(sizeof(action_t));
    semaine_courante = (semaine_t *) malloc(sizeof(semaine_t));

    lch->tete->suivant = NULL;

    buffer = (char *) malloc(25*sizeof(char));
    chaine = (char *) malloc(7*sizeof(char));

    if (!chaine || !buffer || !semaine_courante || !place2 || !place || !lch->tete || !lch){
        printf("Erreur : Allocation dynamique");
        exit(0);
    }

    fseek(fichier, 0, SEEK_SET);

    while (fgets(buffer, 25, fichier) != NULL){
        strncpy(chaine, buffer, 6);
        // Avant de creer un nouveau bloc de semaine, il faut verifier que celle-ci contient (ou pas) des actions
        if((strlen(buffer) > 9) && existe(chaine, lch) == 0){
            //printf("chaine = %s\n",chaine);

            semaine_t * semaine = (semaine_t *) malloc(sizeof(semaine_t));
            listeA_t  * lchA = (listeA_t *) malloc(sizeof(listeA_t));

            lchA->tete = (action_t *) malloc(sizeof(action_t));

            lchA->tete->suivant = NULL; 

            if(!semaine || !lchA || !lchA->tete) {
                printf("Erreur : Allocation dynamique echouee");
                exit(0);
            }

            strncpy(semaine->anneeSemaine, buffer, 6);
            //printf("anneeSemaine = %s\n", semaine->anneeSemaine);
            semaine->action = lchA;
            place = Tri(chaine, lch);
            semaine->suivant = place->suivant;
            place->suivant = semaine;
        }
    }

    fseek(fichier, 0, SEEK_SET);

    while(fgets(buffer, 25, fichier) != NULL) {
        if(strlen(buffer) > 9) {
            //printf("buffer = %s\n", buffer);
            strncpy(chaine, buffer, 6);
            semaine_courante = rechercheSemaine(chaine, lch);
            //printf("\nanneeSemaine = %s\n ",semaine_courante->anneeSemaine);
            //printf("anneeSemaine = %s\n",semaine->anneeSemaine);
            action_t * action = (action_t *) malloc(sizeof(action_t));

            if(!action){
                printf("Erreur : Allocation Dynamique echouee\n");
                exit(0);
            }

            strncpy(action->jourHeure, (buffer)+6, 3);
            printf("jourHeure = %s\n", action->jourHeure);
            strncpy(action->nom_action, (buffer)+9, 10);
            printf("action = %s\n", action->nom_action);
            place2 = Tri2(action->jourHeure, semaine_courante->action);
            action->suivant = place2->suivant;
            place2->suivant = action;
        }
    }

    return lch;
}

/* ----------------------------------------------------------------------- */
/* afficherListe permet d'afficher la liste d'adresse de début lch */
/* */
/* En entrée: lch Une chaîne de caractères */
/* */
/* En sortie: La fonction ne retourne rien (void) */
/* ----------------------------------------------------------------------- */

void afficherListe(listeS_t * lch) {
    semaine_t  * cour;
    action_t   * cour2;
    int        i = 1, j = 1;

    cour = lch->tete->suivant;
    printf("\n\n ================= AGENDA ================ \n\n");

    while(cour != NULL) {
        printf("%d. AnnéeSemaine : %s\n", i, cour->anneeSemaine);
        cour2 = cour->action->tete->suivant;
        j = 1;

        while(cour2 != NULL){
            //printf("\t%d. jourHeure : %s\n-> action : %s\n", j, cour2->jourHeure, cour2->nom_action);
            printf("\t%d. jourHeure : %s\n", j, cour2->jourHeure);
            j++;
            cour2 = cour2->suivant;
        }

        i++;
        cour = cour->suivant;
    }
}

/* ----------------------------------------------------------------------- */
/* sauvegarderSDD permet de stocker une liste dans un fichier */
/* */
/* En entrée: nomfichier, lch Une chaîne de caractères */
/* et un fichier (supposé ouvert) */
/* */
/* En sortie: La fonction ne retourne rien (void) */
/* ----------------------------------------------------------------------- */

void sauvegarderSDD(FILE * nomfichier, listeS_t * lch){
    semaine_t  * cour;
    action_t   * cour2;

    if(lch != NULL){
        cour = lch->tete->suivant;
        while(cour != NULL) {
            cour2 = cour->action->tete->suivant;

            while(cour2 != NULL){
                fprintf(nomfichier, "%s%s\n", cour->anneeSemaine, cour2->jourHeure);
                cour2= cour2->suivant;
            }

            cour = cour->suivant;
        }
    }
}

/* ----------------------------------------------------------------------- */
/* verifJour permet de verifier si le jour est deja present dans la lco */
/* */
/* En entrée: jour, lcoTete, lcofin Un caractere qui contient le jour   */
/* et deux pointeurs (tete et fin de la liste contigue) */
/* */
/* En sortie: La valeur entiere retournee est 1 si on trouve jour dans */
/* la liste contigue et 0 sinon. */
/* ----------------------------------------------------------------------- */

int verifJour(char * lcoTete, char * lcoFin, char jour){
    int trouve = 0;
    char * cour = lcoTete;

    while ((cour != lcoFin) && (!trouve)){
        if(strcmp(cour, &jour) == 0){
            trouve = 1;
        }
        cour++;
    }
    return trouve;
}

/* ----------------------------------------------------------------------- */
/* comparerChaine compare deux chaines de caractere de longueur n */
/* */
/* En entrée: motif, nomAction, n Deux chaines de caracteres et la   */
/* longueur du motif */
/* */
/* En sortie: La valeur entiere retournee est 0 si le motif est le nom  */
/* de l'action, 0 sinon.  */
/* ----------------------------------------------------------------------- */

int comparerChaine(char motif[], char nomAction[], int n){
    int res = 0;
    int cpt = 0;
    while((cpt < n) && (motif[cpt] == nomAction[cpt])){
        cpt++;
    }
    if (cpt < n){
        res = 1;
    }
    return res;
}

/* ----------------------------------------------------------------------- */
/* decalDroite decale les cases de la liste contigue vers la droite  */
/* suivant un pas qui est la valeur de saut. */
/* */ 
/* En entrée: premier, dernier, saut L'adresse du premier et du dernier */
/* decalage a faire et le pas du decalage */
/* */
/* En sortie: La fonction ne retourne rien (void)  */
/* ----------------------------------------------------------------------- */

void decalDroite(char * premier, char * dernier, int saut) {
    while (premier != dernier+saut) {
        *premier = *(premier+saut);
        premier--;
    }
}

/* ----------------------------------------------------------------------- */
/* creerLco cree une liste contigue des jours où une action contenant un */
/* un motif est presente*/
/* */
/* En entrée: motif, lch Une chaine de caractere et la liste chainee */
/* cree dans la question 1  */
/* */
/* En sortie: Le pointeur de tete de la liste contigue qu'on a cree  */
/* ----------------------------------------------------------------------- */

void creerLco (listeS_t * lch, char motif[], char ** lcoTete, char ** lcoFin){
    semaine_t * courLch; 
    action_t  * cour2;
    char      * courLco;

    courLch = lch->tete->suivant;

    *lcoTete = (char *) malloc(100*sizeof(char));
    *lcoFin = *lcoTete;
    courLco = *lcoTete;

    while(courLch != NULL){
        cour2 = courLch->action->tete->suivant;
        while(cour2 != NULL){
            if(comparerChaine(motif, cour2->nom_action, 10) == 0){
                if(!verifJour(*lcoTete, *lcoFin, cour2->jourHeure[0])){
                    strcpy(courLco, &(cour2->jourHeure[0]));
                    courLco++;
                    *lcoFin = courLco;
                }
            }
            cour2 = cour2->suivant;
        }
        courLch = courLch->suivant;
    }   
}

/* ----------------------------------------------------------------------- */
/* afficherListe permet d'afficher la liste d'adresse de début lch */
/* */
/* En entrée: lch Une chaîne de caractères */
/* */
/* En sortie: La fonction ne retourne rien (void) */
/* ----------------------------------------------------------------------- */

void afficherLco(char * lcoTete, char * lcoFin) {
    char * cour;

    cour = lcoTete;
    printf("\n\n ================= LCO ================ \n\n");

    while(cour != lcoFin) {
        printf("jour : %s\n", cour);
        cour++;
    }
}

/* ----------------------------------------------------------------------- */
/* recherche permet de chercher l'action correspondante à l'année, la */
/* semaine, le jour et l'heure passés en paramètre */
/* */
/* En entrée: a0, anneeSemaine, jourHeure Deux chaînes de caractères */
/* et un pointeur (adresse de tête de la liste) */
/* */
/* En sortie: La fonction retourne l'adresse de tête de la liste */
/* qu'elle vient de construire. */
/* ----------------------------------------------------------------------- */

action_t * recherche(listeS_t * a0, char * anneeSemaine, char * jourHeure){
    semaine_t  * cour;
    action_t   * cour2;
    action_t   * prec2;

    cour = a0->tete->suivant;
    
    while((cour != NULL) && (strcmp(cour->anneeSemaine, anneeSemaine) < 0)){
        cour = cour->suivant;
    }

    if(!strcmp(cour->anneeSemaine, anneeSemaine)){
        prec2 = cour->action->tete;
        cour2 = cour->action->tete->suivant;

        while((cour2 != NULL) && (strcmp(cour2->jourHeure, jourHeure) < 0)){
            prec2 = prec2->suivant;
            cour2 = cour2->suivant;
        }
    }
    else{
        printf("Les coordonnées que vous avez entré ne correspond pas à aucun elements de la liste\n");
        exit(0);
    }

    return prec2;
}


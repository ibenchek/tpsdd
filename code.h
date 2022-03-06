                /* ----------------------------------------------------------------------- */
                                        /* Nom du fichier : code.h */
                        /* Rôle : Le fichier contient les prototypes des fonctions */
                                    /* et la définition des structures */
                /* ----------------------------------------------------------------------- */

#ifndef CODE_H
# define CODE_H

// Structure représentant une action
typedef struct action {
    char jourHeure[3] ;
    char nom_action[10] ;
    struct action * suivant;
} action_t;

// pointeur de début et de fin de la liste des actions 
typedef struct listeA {
    action_t * tete;
} listeA_t;

// Structure représentant une semaine 
typedef struct semaine {
    char anneeSemaine[6];
    listeA_t * action;
    struct semaine * suivant;
} semaine_t;

// pointeur de début et de fin de la liste des semaines 
typedef struct listeS {
    semaine_t * tete;
} listeS_t;

// Déclaration des prototypes des fonctions 
int existe(char *, listeS_t *);
semaine_t * Tri(char *, listeS_t *);
semaine_t * rechercheSemaine(char *, listeS_t *);
action_t * Tri2(char * chaine, listeA_t * lch);
listeS_t * creerListe(FILE *);
void afficherListe(listeS_t *);
void sauvegarderSDD(FILE *, listeS_t *);
int verifJour(char *, char *, char);
int comparerChaine(char[], char[], int);
void creerLco(listeS_t *, char[], char **, char **);
void afficherLco(char *, char *);
action_t * recherche(listeS_t *, char *, char *);
void supprimerAction(listeS_t **, char *, char *);
void libererListe(listeS_t **);

#endif 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jeu.h"
#include "score.h"
#include "util.h"

#define FICHIER_SCORES "scores.txt"

int main() {
    char nom_joueur[NOM_MAX];
    int score = 0;
    int continuer = 1;

    srand(time(NULL)); // Initialisation du générateur aléatoire

    printf("Bienvenue dans Tech-tris !\n");
    printf("Entrez votre nom : ");
    lire_chaine(nom_joueur, NOM_MAX);

    while (continuer) {
        // Lancer une partie
        score = jouer_une_partie(); // Fonction principale du jeu (dans jeu.c)
        sauvegarder_score(FICHIER_SCORES, nom_joueur, score);

        printf("\nPartie terminée. Score obtenu : %d\n", score);

        // Charger et afficher les meilleurs scores
        Score meilleurs_scores[NB_SCORES_MAX];
        int nb_scores = charger_scores(FICHIER_SCORES, meilleurs_scores);
        afficher_scores(meilleurs_scores, nb_scores);

        // Demander si le joueur veut rejouer
        printf("Voulez-vous rejouer ? (1 = oui, 0 = non) : ");
        continuer = lire_entier();
    }

    printf("Merci d’avoir joué !\n");
    return 0;
}
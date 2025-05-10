#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "score.h"

void sauvegarder_score(const char* nom_fichier, const char* joueur, int points) {
    FILE* fichier = fopen(nom_fichier, "a");
    if (fichier == NULL) {
        printf("Erreur : impossible d’ouvrir le fichier des scores.\n");
        return;
    }
    fprintf(fichier, "%s %d\n", joueur, points);
    fclose(fichier);
}

int charger_scores(const char* nom_fichier, Score scores[NB_SCORES_MAX]) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Aucun score trouvé.\n");
        return 0;
    }

    int i = 0;
    while (i < NB_SCORES_MAX && fscanf(fichier, "%s %d", scores[i].nom, &scores[i].points) == 2) {
        i++;
    }

    fclose(fichier);
    return i;
}

void afficher_scores(Score scores[], int nb_scores) {
    printf("\n--- Meilleurs Scores ---\n");
    for (int i = 0; i < nb_scores; i++) {
        printf("%d. %s - %d points\n", i + 1, scores[i].nom, scores[i].points);
    }
    printf("------------------------\n");
}

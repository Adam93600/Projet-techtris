#ifndef SCORE_H
#define SCORE_H

#define NOM_MAX 50
#define NB_SCORES_MAX 10

// Structure pour représenter un score
typedef struct {
    char nom[NOM_MAX];
    int points;
} Score;

// Sauvegarde un score dans un fichier
void sauvegarder_score(const char* nom_fichier, const char* joueur, int points);

// Charge les scores depuis un fichier
int charger_scores(const char* nom_fichier, Score scores[NB_SCORES_MAX]);

// Affiche les scores chargés
void afficher_scores(Score scores[], int nb_scores);

#endif

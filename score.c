/**
 * Score.c - Implémentation des fonctions de gestion des scores
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "score.h"

#define FICHIER_SCORES "high_scores.txt"
#define MAX_SCORES 10

// Structure pour stocker un score élevé
typedef struct {
    char nomJoueur[50];
    int score;
    char date[20];
} ScoreEleve;

// Calculer le score en fonction des lignes effacées et de la difficulté
// Retourne un score basé sur le nombre de lignes effacées et le niveau de difficulté
int calculerScore(int lignesEffacees, int difficulte) {
    // Points de base par ligne
    int pointsBase = 100;
    
    // Multiplicateur de difficulté
    float multiplicateurDifficulte;
    switch (difficulte) {
        case 1: // Facile
            multiplicateurDifficulte = 1.0;
            break;
        case 2: // Moyen
            multiplicateurDifficulte = 1.5;
            break;
        case 3: // Difficile
            multiplicateurDifficulte = 2.0;
            break;
        default:
            multiplicateurDifficulte = 1.0;
    }
    
    // Bonus pour plusieurs lignes à la fois
    float multiplicateurLignes;
    switch (lignesEffacees) {
        case 1:
            multiplicateurLignes = 1.0;
            break;
        case 2:
            multiplicateurLignes = 2.5;
            break;
        case 3:
            multiplicateurLignes = 5.0;
            break;
        case 4:
            multiplicateurLignes = 10.0;
            break;
        default:
            multiplicateurLignes = 1.0;
    }
    
    return (int)(pointsBase * lignesEffacees * multiplicateurDifficulte * multiplicateurLignes);
}

// Sauvegarder le score dans un fichier
// Ajoute un nouveau score au fichier des scores et trie les scores par ordre décroissant
void sauvegarderScore(const char* nomJoueur, int score) {
    FILE* fichier;
    ScoreEleve scores[MAX_SCORES + 1];
    int nombreScores = 0;
    time_t maintenant = time(NULL);
    struct tm *t = localtime(&maintenant);
    char dateStr[20];
    
    strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", t);
    
    // Charger les scores existants
    fichier = fopen(FICHIER_SCORES, "r");
    if (fichier) {
        while (nombreScores < MAX_SCORES && 
               fscanf(fichier, "%49s %d %19s", scores[nombreScores].nomJoueur, 
                     &scores[nombreScores].score, scores[nombreScores].date) == 3) {
            nombreScores++;
        }
        fclose(fichier);
    }
    
    // Ajouter le nouveau score
    strncpy(scores[nombreScores].nomJoueur, nomJoueur, sizeof(scores[nombreScores].nomJoueur) - 1);
    scores[nombreScores].nomJoueur[sizeof(scores[nombreScores].nomJoueur) - 1] = '\0';
    scores[nombreScores].score = score;
    strncpy(scores[nombreScores].date, dateStr, sizeof(scores[nombreScores].date) - 1);
    scores[nombreScores].date[sizeof(scores[nombreScores].date) - 1] = '\0';
    nombreScores++;
    
    // Trier les scores par ordre décroissant
    for (int i = 0; i < nombreScores - 1; i++) {
        for (int j = i + 1; j < nombreScores; j++) {
            if (scores[i].score < scores[j].score) {
                ScoreEleve temp = scores[i];
                scores[i] = scores[j];
                scores[j] = temp;
            }
        }
    }
    
    // Sauvegarder les meilleurs scores
    fichier = fopen(FICHIER_SCORES, "w");
    if (fichier) {
        for (int i = 0; i < nombreScores && i < MAX_SCORES; i++) {
            fprintf(fichier, "%s %d %s\n", scores[i].nomJoueur, scores[i].score, scores[i].date);
        }
        fclose(fichier);
    } else {
        perror("Erreur lors de l'ouverture du fichier des scores pour écriture");
    }
}

// Afficher les scores élevés
// Lit le fichier des scores et affiche les meilleurs scores dans un format lisible
void afficherScoresEleves() {
    FILE* fichier;
    ScoreEleve scores[MAX_SCORES];
    int nombreScores = 0;
    
    printf("\n\u2554\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2557\n");
    printf("\u2551            SCORES                    \u2551\n");
    printf("\u2560\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2566\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2566\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2563\n");
    printf("\u2551 Joueur         \u2551 Score     \u2551 Date       \u2551\n");
    printf("\u2560\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u256c\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u256c\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2563\n");
    
    fichier = fopen(FICHIER_SCORES, "r");
    if (fichier) {
        while (nombreScores < MAX_SCORES && 
               fscanf(fichier, "%49s %d %19s", scores[nombreScores].nomJoueur, 
                     &scores[nombreScores].score, scores[nombreScores].date) == 3) {
            printf("\u2551 %-14s \u2551 %-9d \u2551 %-10s \u2551\n", 
                   scores[nombreScores].nomJoueur, 
                   scores[nombreScores].score, 
                   scores[nombreScores].date);
            nombreScores++;
        }
        fclose(fichier);
    }
    
    if (nombreScores == 0) {
        printf("\u2551 Aucun score pour l'instant !                           \u2551\n");
    }
    
    printf("\u255a\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2569\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2569\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u2550\u255d\n");
}

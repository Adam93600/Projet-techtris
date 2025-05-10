#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jeu.h"
#include "pieces.h"

// Fonction principale pour jouer une partie
int jouer_une_partie() {
    char grille[LIGNES][COLONNES];
    initialiser_grille(grille);

    int score = 0;
    int jeu_en_cours = 1;

    printf("Début de la partie !\n");

    while (jeu_en_cours) {
        afficher_grille(grille);

        // Générer une nouvelle pièce
        Piece piece;
        generer_piece(&piece);

        printf("Nouvelle pièce générée :\n");
        for (int i = 0; i < TAILLE_PIECE; i++) {
            printf("%s\n", piece.forme[i]);
        }

        // Demander la position de placement
        int ligne = 0, colonne;
        printf("Entrez la colonne pour placer la pièce (0-%d) : ", COLONNES - 1);
        scanf("%d", &colonne);

        // Vérifier si le placement est valide
        if (verifier_placement(grille, &piece, ligne, colonne)) {
            placer_piece(grille, &piece, ligne, colonne);
            printf("Pièce placée avec succès !\n");

            // Supprimer les lignes complètes et mettre à jour le score
            int lignes_supprimees = supprimer_lignes_completes(grille);
            score += lignes_supprimees * 10;
            printf("Lignes supprimées : %d, Score actuel : %d\n", lignes_supprimees, score);
        } else {
            printf("Placement invalide. Essayez une autre colonne.\n");
        }

        // Vérifier si le jeu est terminé
        if (jeu_termine(grille)) {
            printf("Le jeu est terminé !\n");
            jeu_en_cours = 0;
        }
    }

    return score;
}

// Initialise la grille à vide
void initialiser_grille(char grille[LIGNES][COLONNES]) {
    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            grille[i][j] = ' ';
        }
    }
}

// Affiche la grille dans le terminal
void afficher_grille(char grille[LIGNES][COLONNES]) {
    printf("\n+");
    for (int j = 0; j < COLONNES; j++) printf("-");
    printf("+\n");

    for (int i = 0; i < LIGNES; i++) {
        printf("|");
        for (int j = 0; j < COLONNES; j++) {
            printf("%c", grille[i][j]);
        }
        printf("|\n");
    }

    printf("+");
    for (int j = 0; j < COLONNES; j++) printf("-");
    printf("+\n");
}

// Vérifie si une pièce peut être placée à une position donnée
int verifier_placement(char grille[LIGNES][COLONNES], Piece* piece, int ligne, int colonne) {
    for (int i = 0; i < TAILLE_PIECE; i++) {
        for (int j = 0; j < TAILLE_PIECE; j++) {
            if (piece->forme[i][j] != ' ') {
                int x = ligne + i;
                int y = colonne + j;
                if (x < 0 || x >= LIGNES || y < 0 || y >= COLONNES || grille[x][y] != ' ') {
                    return 0; // impossible de placer ici
                }
            }
        }
    }
    return 1; // possible
}

// Place une pièce sur la grille à une position donnée
void placer_piece(char grille[LIGNES][COLONNES], Piece* piece, int ligne, int colonne) {
    for (int i = 0; i < TAILLE_PIECE; i++) {
        for (int j = 0; j < TAILLE_PIECE; j++) {
            if (piece->forme[i][j] != ' ') {
                grille[ligne + i][colonne + j] = piece->forme[i][j];
            }
        }
    }
}

// Vérifie si une ligne est complète
int ligne_complete(char grille[LIGNES][COLONNES], int ligne) {
    for (int j = 0; j < COLONNES; j++) {
        if (grille[ligne][j] == ' ') return 0;
    }
    return 1;
}

// Supprime une ligne complète et décale les lignes au-dessus
void supprimer_ligne(char grille[LIGNES][COLONNES], int ligne) {
    for (int i = ligne; i > 0; i--) {
        for (int j = 0; j < COLONNES; j++) {
            grille[i][j] = grille[i - 1][j];
        }
    }
    for (int j = 0; j < COLONNES; j++) {
        grille[0][j] = ' ';
    }
}

// Supprime toutes les lignes complètes et retourne le nombre supprimé
int supprimer_lignes_completes(char grille[LIGNES][COLONNES]) {
    int lignes_supprimees = 0;
    for (int i = 0; i < LIGNES; i++) {
        if (ligne_complete(grille, i)) {
            supprimer_ligne(grille, i);
            lignes_supprimees++;
            i--; // re-vérifie la même ligne
        }
    }
    return lignes_supprimees;
}

// Vérifie si le jeu est terminé (si une pièce dépasse)
int jeu_termine(char grille[LIGNES][COLONNES]) {
    for (int j = 0; j < COLONNES; j++) {
        if (grille[0][j] != ' ') return 1;
    }
    return 0;
}
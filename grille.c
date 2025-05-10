#include <stdio.h>
#include <string.h>

void initialiser_grille(char grille[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            grille[i][j] = ' ';
        }
    }
}

void afficher_grille(char grille[10][10]) {
    printf("\n  0123456789\n");
    for (int i = 0; i < 10; i++) {
        printf("%d|", i);
        for (int j = 0; j < 10; j++) {
            printf("%c", grille[i][j]);
        }
        printf("|\n");
    }
    printf("  ----------\n");
}

// Place une pièce dans la grille à la colonne donnée
// Retourne -1 si la pièce dépasse la grille (fin du jeu), 0 sinon
int placer_piece(char grille[10][10], char piece[5][5], int colonne) {
    int ligne_debut = 0;

    // Trouver la ligne la plus basse où la pièce peut tenir
    for (int ligne = 0; ligne <= 10 - 5; ligne++) {
        int peut_placer = 1;
        for (int i = 0; i < 5 && peut_placer; i++) {
            for (int j = 0; j < 5 && peut_placer; j++) {
                if (piece[i][j] != ' ') {
                    int x = ligne + i;
                    int y = colonne + j;
                    if (x >= 10 || y >= 10 || grille[x][y] != ' ') {
                        peut_placer = 0;
                    }
                }
            }
        }
        if (!peut_placer) break;
        ligne_debut = ligne;
    }

    // Vérifier que la pièce ne déborde pas
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (piece[i][j] != ' ') {
                int x = ligne_debut + i;
                int y = colonne + j;
                if (x >= 10 || y >= 10) {
                    return -1;
                }
            }
        }
    }

    // Placer la pièce dans la grille
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (piece[i][j] != ' ') {
                grille[ligne_debut + i][colonne + j] = piece[i][j];
            }
        }
    }

    return 0;
}

int verifier_lignes(char grille[10][10]) {
    int lignes_completees = 0;

    for (int i = 0; i < 10; i++) {
        int complete = 1;
        for (int j = 0; j < 10; j++) {
            if (grille[i][j] == ' ') {
                complete = 0;
                break;
            }
        }
        if (complete) {
            lignes_completees++;
        }
    }

    return lignes_completees;
}

void supprimer_lignes(char grille[10][10]) {
    for (int i = 9; i >= 0; i--) {
        int complete = 1;
        for (int j = 0; j < 10; j++) {
            if (grille[i][j] == ' ') {
                complete = 0;
                break;
            }
        }

        if (complete) {
            // Décaler toutes les lignes au-dessus vers le bas
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < 10; j++) {
                    grille[k][j] = grille[k - 1][j];
                }
            }

            // Vider la première ligne
            for (int j = 0; j < 10; j++) {
                grille[0][j] = ' ';
            }

            // Re-vérifie la même ligne après décalage
            i++;
        }
    }
}
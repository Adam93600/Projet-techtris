/**
 * Display.c - Implémentation des fonctions d'affichage terminal
 */

#include <stdio.h>
#include <string.h>
#include "display.h"
#include "jeu.h"
#include "piece.h"

// Efface l'écran du terminal en utilisant des séquences d'échappement ANSI
void effacerEcran() {
    printf("\033[2J\033[H");
}

// Affiche un message de bienvenue et les instructions du jeu
void afficherBienvenue() {
    effacerEcran();
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║                       TECH-TRIS                            ║\n");
    printf("╠════════════════════════════════════════════════════════════╣\n");
    printf("║ Bienvenue dans Tech-tris, un jeu de Tetris en terminal !   ║\n");
    printf("║                                                            ║\n");
    printf("║ Instructions :                                             ║\n");
    printf("║ - Vous devez placer les pièces pour créer des lignes       ║\n");
    printf("║   complètes                                                ║\n");
    printf("║ - Lorsqu'une ligne est complète, elle disparaît et vous    ║\n");
    printf("║   gagnez des points                                        ║\n");
    printf("║ - Le jeu se termine lorsqu'une pièce ne rentre pas dans    ║\n");
    printf("║   la grille                                                ║\n");
    printf("║ - Vous avez un temps limité pour choisir la colonne et     ║\n");
    printf("║   la rotation                                              ║\n");
    printf("║                                                            ║\n");
    printf("║ Contrôles :                                                ║\n");
    printf("║ - Entrez le numéro de colonne (0-%d) pour placer la pièce   ║\n", LARGEUR_GRILLE - 1);
    printf("║ - Entrez la rotation (0-3) pour tourner la pièce           ║\n");
    printf("║                                                            ║\n");
    printf("║ Bonne chance !                                             ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    printf("\nAppuyez sur Entrée pour commencer...");
    getchar();
    effacerEcran();
}

// Retourne la couleur ANSI associée à un symbole donné
char* obtenirCouleurPourSymbole(char symbole) {
    switch (symbole) {
        case '@': return COULEUR_ROUGE;
        case '#': return COULEUR_VERT;
        case '$': return COULEUR_JAUNE;
        case '%': return COULEUR_BLEU;
        case '&': return COULEUR_MAGENTA;
        case '+': return COULEUR_CYAN;
        case '*': return COULEUR_BLANC;
        default: return COULEUR_RESET;
    }
}

// Affiche l'état actuel du jeu, y compris la grille et la prochaine pièce
void afficherJeu(Jeu* jeu, Piece* prochainePiece) {
    // Afficher les informations du jeu avec des améliorations esthétiques
    printf("\033[1;34m╔══════════════════════╗\033[0m\n");
    printf("\033[1;34m║\033[1;33m TECH-TRIS            \033[1;34m║\033[0m\n");
    printf("\033[1;34m╠══════════════════════╣\033[0m\n");
    printf("\033[1;34m║\033[1;32m Score : %-12d \033[1;34m║\033[0m\n", jeu->score);
    printf("\033[1;34m║\033[1;32m Niveau : %-11d \033[1;34m║\033[0m\n", jeu->niveau);
    printf("\033[1;34m╚══════════════════════╝\033[0m\n\n");
    
    // Afficher la prochaine pièce avec des améliorations esthétiques
    printf("\033[1;35mProchaine pièce :\033[0m\n");
    printf("\033[1;35m╔═══════════╗\033[0m\n");
    for (int i = 0; i < TAILLE_PIECE; i++) {
        printf("\033[1;35m║ \033[0m");
        for (int j = 0; j < TAILLE_PIECE; j++) {
            if (prochainePiece->forme[i][j] != ' ') {
                printf("%s%c%s ", obtenirCouleurPourSymbole(prochainePiece->symbole), prochainePiece->symbole, COULEUR_RESET);
            } else {
                printf("  ");
            }
        }
        printf("\033[1;35m║\033[0m\n");
    }
    printf("\033[1;35m╚═══════════╝\033[0m\n\n");
    
    // Afficher la grille du jeu avec des améliorations esthétiques
    printf("\033[1;36mGrille de jeu :\033[0m\n");
    printf("\033[1;36m╔");
    for (int j = 0; j < LARGEUR_GRILLE * 2; j++) {
        printf("═");
    }
    printf("╗\033[0m\n");
    
    for (int i = 0; i < HAUTEUR_GRILLE; i++) {
        printf("\033[1;36m║\033[0m");
        for (int j = 0; j < LARGEUR_GRILLE; j++) {
            if (jeu->grille[i][j] != ' ') {
                printf("%s%c%s", obtenirCouleurPourSymbole(jeu->grille[i][j]), jeu->grille[i][j], COULEUR_RESET);
                printf(" ");
            } else {
                printf("  ");
            }
        }
        printf("\033[1;36m║\033[0m\n");
    }
    
    printf("\033[1;36m╚");
    for (int j = 0; j < LARGEUR_GRILLE * 2; j++) {
        printf("═");
    }
    printf("╝\033[0m\n");

    // Ajouter un pied de page ou des informations supplémentaires si nécessaire
    printf("\n");
}
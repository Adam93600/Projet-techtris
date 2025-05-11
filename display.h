/**
 * Display.h - Fonctions d'affichage terminal
 */

#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "jeu.h"
#include "piece.h"

// Définitions des codes de couleur ANSI pour styliser l'affichage dans le terminal
#define COULEUR_RESET "\033[0m"
#define COULEUR_NOIR "\033[30m"
#define COULEUR_ROUGE "\033[31m"
#define COULEUR_VERT "\033[32m"
#define COULEUR_JAUNE "\033[33m"
#define COULEUR_BLEU "\033[34m"
#define COULEUR_MAGENTA "\033[35m"
#define COULEUR_CYAN "\033[36m"
#define COULEUR_BLANC "\033[37m"
#define COULEUR_BG_NOIR "\033[40m"
#define COULEUR_BG_ROUGE "\033[41m"
#define COULEUR_BG_VERT "\033[42m"
#define COULEUR_BG_JAUNE "\033[43m"
#define COULEUR_BG_BLEU "\033[44m"
#define COULEUR_BG_MAGENTA "\033[45m"
#define COULEUR_BG_CYAN "\033[46m"
#define COULEUR_BG_BLANC "\033[47m"

// Prototypes des fonctions d'affichage
// Efface l'écran du terminal
void effacerEcran();

// Affiche l'état du jeu, y compris la grille et la prochaine pièce
void afficherJeu(Jeu* jeu, Piece* prochainePiece);

// Affiche un message de bienvenue et les instructions du jeu
void afficherBienvenue();

// Retourne la couleur ANSI associée à un symbole donné
char* obtenirCouleurPourSymbole(char symbole);

#endif /* AFFICHAGE_H */

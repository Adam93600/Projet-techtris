/**
 * Piece.h - Gestion des pièces de Tetris
 */

#ifndef PIECE_H
#define PIECE_H

#include "jeu.h"

// Structure représentant une pièce de Tetris
// Contient la forme de la pièce et son symbole pour l'affichage
typedef struct Piece {
    char forme[TAILLE_PIECE][TAILLE_PIECE]; // Matrice représentant la forme de la pièce
    char symbole;  // Symbole utilisé pour cette pièce dans la grille
} Piece;

// Charge les pièces à partir des fichiers dans un répertoire donné
// Retourne 1 si le chargement est réussi, 0 sinon
int chargerPieces(const char* repertoire);

// Libère la mémoire allouée pour les pièces
void libererPieces();

// Retourne un pointeur vers une pièce en fonction de son index
Piece* obtenirPiece(int index);

// Retourne le nombre total de pièces chargées
int obtenirNombrePieces();

// Applique une rotation à une pièce et retourne la version tournée
void obtenirPieceTournee(Piece* piece, int rotation, char pieceTournee[TAILLE_PIECE][TAILLE_PIECE]);

#endif /* PIECE_H */

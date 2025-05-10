#ifndef PIECES_H
#define PIECES_H

#define TAILLE_PIECE 5
#define DOSSIER_PIECES "pieces"

#include <dirent.h>

// Structure représentant une pièce de Tetris
typedef struct {
    char forme[TAILLE_PIECE][TAILLE_PIECE + 1]; // Chaque ligne de la pièce (avec '\0')
} Piece;

// Charge une pièce à partir d’un fichier texte
Piece* charger_piece_depuis_fichier(const char* nom_fichier);

// Libère la mémoire allouée pour une pièce
void liberer_piece(Piece* piece);

// Affiche une pièce dans le terminal
void afficher_piece(Piece* piece);

// Crée une nouvelle pièce correspondant à la rotation de la pièce originale
Piece* rotation_piece(Piece* piece);

// Liste les fichiers de pièces dans le dossier "pieces" (retourne un tableau de noms de fichiers)
char** lister_fichiers_pieces(int* nb_pieces);

// Libère la mémoire allouée à la liste des fichiers
void liberer_liste_fichiers(char** liste, int nb);

// Choisit et retourne une pièce aléatoire à partir de la liste de fichiers
Piece* choisir_piece_aleatoire(char** fichiers, int nb);

// Déclaration de la fonction generer_piece
void generer_piece(Piece* piece);

#endif
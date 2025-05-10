#ifndef JEU_H
#define JEU_H

#include "pieces.h"

// Constantes de la grille
#define LIGNES 10
#define COLONNES 10

// Fonction principale pour jouer une partie
int jouer_une_partie();

// Initialise la grille à vide
void initialiser_grille(char grille[LIGNES][COLONNES]);

// Affiche la grille dans le terminal
void afficher_grille(char grille[LIGNES][COLONNES]);

// Vérifie si une pièce peut être placée à une position donnée
int verifier_placement(char grille[LIGNES][COLONNES], Piece* piece, int ligne, int colonne);

// Place une pièce dans la grille à une position donnée
void placer_piece(char grille[LIGNES][COLONNES], Piece* piece, int ligne, int colonne);

// Vérifie si une ligne est complète
int ligne_complete(char grille[LIGNES][COLONNES], int ligne);

// Supprime une ligne complète et décale les lignes au-dessus
void supprimer_ligne(char grille[LIGNES][COLONNES], int ligne);

// Supprime toutes les lignes complètes et retourne le nombre de lignes supprimées
int supprimer_lignes_completes(char grille[LIGNES][COLONNES]);

// Vérifie si le jeu est terminé (si une pièce dépasse la grille)
int jeu_termine(char grille[LIGNES][COLONNES]);

#endif
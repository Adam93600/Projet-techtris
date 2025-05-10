#ifndef GRILLE_H
#define GRILLE_H

// Initialise la grille avec des espaces vides
void initialiser_grille(char grille[10][10]);

// Affiche la grille dans le terminal
void afficher_grille(char grille[10][10]);

// Place une pièce dans la grille à une colonne donnée
// Retourne -1 si la pièce dépasse la grille, 0 sinon
int placer_piece(char grille[10][10], char piece[5][5], int colonne);

// Vérifie combien de lignes sont complètes
int verifier_lignes(char grille[10][10]);

// Supprime les lignes complètes et décale les lignes au-dessus
void supprimer_lignes(char grille[10][10]);

#endif


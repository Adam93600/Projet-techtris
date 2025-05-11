#ifndef JEU_H
#define JEU_H

// Définit les dimensions de la grille et la taille des pièces
#define LARGEUR_GRILLE 10
#define HAUTEUR_GRILLE 10
#define TAILLE_PIECE 5

// Déclaration anticipée de la structure Piece
typedef struct Piece Piece;

// Structure représentant l'état du jeu
typedef struct {
    char grille[HAUTEUR_GRILLE][LARGEUR_GRILLE]; // Grille de jeu
    int score; // Score actuel du joueur
    int niveau; // Niveau actuel du jeu
    int lignesTotalesEffacees; // Nombre total de lignes effacées
    int dernieresPieces[2]; // Indices des deux dernières pièces utilisées
} Jeu;

// Initialise la grille et les variables du jeu
void initialiserJeu(Jeu* jeu);

// Place une pièce sur la grille
// Retourne 1 si la pièce a été placée avec succès, 0 sinon
int placerPiece(Jeu* jeu, Piece* piece, int colonne, int rotation);

// Vérifie les lignes complètes et les supprime
// Retourne le nombre de lignes effacées
int verifierLignes(Jeu* jeu);

// Sélectionne une pièce aléatoire tout en évitant les deux dernières pièces utilisées
int obtenirPieceAleatoire(Jeu* jeu);

// Calcule la limite de temps pour un coup en fonction de la difficulté et du niveau
int obtenirLimiteTemps(int difficulte, int niveau);

// Permet au joueur de choisir un niveau de difficulté
int choisirDifficulte();

#endif /* JEU_H */

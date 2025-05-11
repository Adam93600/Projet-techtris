/**
 * Jeu.c - Implémentation de la logique du jeu
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jeu.h"
#include "piece.h"

// Fonction pour initialiser la grille et les variables du jeu
// Cette fonction est appelée au début pour préparer l'état initial du jeu
void initialiserJeu(Jeu* jeu) {
    for (int i = 0; i < HAUTEUR_GRILLE; i++) {
        for (int j = 0; j < LARGEUR_GRILLE; j++) {
            jeu->grille[i][j] = ' ';
        }
    }
    jeu->score = 0;
    jeu->niveau = 1;
    jeu->lignesTotalesEffacees = 0;
    jeu->dernieresPieces[0] = -1;
    jeu->dernieresPieces[1] = -1;
}

// Fonction pour placer une pièce sur la grille
// Vérifie si la pièce peut être placée à l'endroit spécifié
// Si oui, elle est ajoutée à la grille, sinon la fonction retourne 0
int placerPiece(Jeu* jeu, Piece* piece, int rotation, int colonne) {
    char pieceTournee[TAILLE_PIECE][TAILLE_PIECE];
    obtenirPieceTournee(piece, rotation, pieceTournee);

    int ligneHaut = 0;
    while (ligneHaut < TAILLE_PIECE) {
        int aContenu = 0;
        for (int j = 0; j < TAILLE_PIECE; j++) {
            if (pieceTournee[ligneHaut][j] != ' ') {
                aContenu = 1;
                break;
            }
        }
        if (aContenu) break;
        ligneHaut++;
    }

    int colonneGauche = 0;
    while (colonneGauche < TAILLE_PIECE) {
        int aContenu = 0;
        for (int i = 0; i < TAILLE_PIECE; i++) {
            if (pieceTournee[i][colonneGauche] != ' ') {
                aContenu = 1;
                break;
            }
        }
        if (aContenu) break;
        colonneGauche++;
    }

    int largeurPiece = 0, hauteurPiece = 0;
    for (int i = 0; i < TAILLE_PIECE; i++) {
        for (int j = 0; j < TAILLE_PIECE; j++) {
            if (pieceTournee[i][j] != ' ') {
                if (i - ligneHaut + 1 > hauteurPiece) hauteurPiece = i - ligneHaut + 1;
                if (j - colonneGauche + 1 > largeurPiece) largeurPiece = j - colonneGauche + 1;
            }
        }
    }

    if (colonne < 0 || colonne + largeurPiece > LARGEUR_GRILLE) {
        printf("La pièce ne rentre pas horizontalement !\n");
        return 0;
    }

    int ligne = 0;
    int derniereLigneValide = -1;

    while (ligne + hauteurPiece <= HAUTEUR_GRILLE) {
        int peutPlacer = 1;
        for (int i = 0; i < hauteurPiece && peutPlacer; i++) {
            for (int j = 0; j < largeurPiece && peutPlacer; j++) {
                int cellulePiece = pieceTournee[ligneHaut + i][colonneGauche + j];
                if (cellulePiece != ' ') {
                    if (ligne + i >= HAUTEUR_GRILLE || 
                        (ligne + i >= 0 && jeu->grille[ligne + i][colonne + j] != ' ')) {
                        peutPlacer = 0;
                        break;
                    }
                }
            }
        }

        if (!peutPlacer) {
            break;
        }

        derniereLigneValide = ligne;
        ligne++;
    }

    ligne = derniereLigneValide;

    if (ligne < 0) {
        printf("Partie terminée ! La pièce ne peut pas être placée en haut de la grille.\n");
        return 0;
    }

    for (int i = 0; i < hauteurPiece; i++) {
        for (int j = 0; j < largeurPiece; j++) {
            if (pieceTournee[ligneHaut + i][colonneGauche + j] != ' ') {
                jeu->grille[ligne + i][colonne + j] = piece->symbole;
            }
        }
    }

    return 1;
}

// Fonction pour vérifier les lignes complètes dans la grille
// Supprime les lignes complètes et déplace les lignes au-dessus vers le bas
// Retourne le nombre de lignes effacées
int verifierLignes(Jeu* jeu) {
    int lignesEffacees = 0;

    for (int i = 0; i < HAUTEUR_GRILLE; i++) {
        int complete = 1;
        for (int j = 0; j < LARGEUR_GRILLE; j++) {
            if (jeu->grille[i][j] == ' ') {
                complete = 0;
                break;
            }
        }

        if (complete) {
            lignesEffacees++;

            for (int k = i; k > 0; k--) {
                for (int j = 0; j < LARGEUR_GRILLE; j++) {
                    jeu->grille[k][j] = jeu->grille[k-1][j];
                }
            }

            for (int j = 0; j < LARGEUR_GRILLE; j++) {
                jeu->grille[0][j] = ' ';
            }
        }
    }

    return lignesEffacees;
}

// Fonction pour obtenir une pièce aléatoire
// Évite de sélectionner les deux dernières pièces utilisées pour plus de variété
int obtenirPieceAleatoire(Jeu* jeu) {
    int nombrePieces = obtenirNombrePieces();
    if (nombrePieces <= 2) {
        return rand() % nombrePieces;
    }

    int indexPiece;
    do {
        indexPiece = rand() % nombrePieces;
    } while (indexPiece == jeu->dernieresPieces[0] || indexPiece == jeu->dernieresPieces[1]);

    jeu->dernieresPieces[1] = jeu->dernieresPieces[0];
    jeu->dernieresPieces[0] = indexPiece;

    return indexPiece;
}

// Fonction pour calculer la limite de temps pour un coup
// La limite dépend de la difficulté choisie et du niveau actuel
int obtenirLimiteTemps(int difficulte, int niveau) {
    int tempsBase;
    switch (difficulte) {
        case 1:
            tempsBase = 10;
            break;
        case 2:
            tempsBase = 7;
            break;
        case 3:
            tempsBase = 5;
            break;
        default:
            tempsBase = 7;
    }

    int temps = tempsBase - (niveau - 1) / 2;
    if (temps < 2) temps = 2;

    return temps;
}

// Fonction pour permettre au joueur de choisir un niveau de difficulté
// Affiche les options et valide l'entrée utilisateur
int choisirDifficulte() {
    int difficulte;

    printf("Choisissez la difficulté :\n");
    printf("1. Facile (10 secondes par coup)\n");
    printf("2. Moyen (7 secondes par coup)\n");
    printf("3. Difficile (5 secondes par coup)\n");

    do {
        printf("Entrez la difficulté (1-3) : ");
        scanf("%d", &difficulte);
        getchar();
    } while (difficulte < 1 || difficulte > 3);

    return difficulte;
}
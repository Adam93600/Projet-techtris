/**
 * Piece.c - Implémentation du chargement et de la gestion des pièces
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include "piece.h"

// Tableau global des pièces
static Piece* pieces = NULL;
static int nombrePieces = 0;

// Symboles pour les pièces (pour les différencier dans la grille)
static const char symboles[] = {'@', '#', '$', '%', '&', '+', '*'};

// Fonction pour charger les pièces à partir des fichiers
// Parcourt un répertoire pour lire les fichiers de pièces et les charger en mémoire
int chargerPieces(const char* repertoire) {
    DIR* dir;
    struct dirent* entree;
    
    dir = opendir(repertoire);
    if (!dir) {
        perror("Échec de l'ouverture du répertoire des pièces");
        return 0;
    }
    
    // Compter le nombre de fichiers de pièces
    nombrePieces = 0;
    while ((entree = readdir(dir)) != NULL) {
        if (entree->d_name[0] != '.' && strstr(entree->d_name, ".txt")) {
            nombrePieces++;
        }
    }
    
    // Limiter à 7 pièces maximum
    if (nombrePieces > 7) {
        nombrePieces = 7;
    }
    
    // Allouer de la mémoire pour les pièces
    pieces = (Piece*)malloc(nombrePieces * sizeof(Piece));
    if (!pieces) {
        perror("Échec de l'allocation de mémoire pour les pièces");
        closedir(dir);
        return 0;
    }
    
    // Réinitialiser le flux du répertoire
    rewinddir(dir);
    
    // Charger chaque pièce
    int indexPiece = 0;
    while ((entree = readdir(dir)) != NULL && indexPiece < nombrePieces) {
        if (entree->d_name[0] != '.' && strstr(entree->d_name, ".txt")) {
            // Construire le chemin complet vers le fichier de la pièce
            char cheminFichier[256];
            int ecrit = snprintf(cheminFichier, sizeof(cheminFichier), "%s/%s", repertoire, entree->d_name);
            if (ecrit < 0 || (size_t)ecrit >= sizeof(cheminFichier)) {
                fprintf(stderr, "Chemin de fichier trop long : %s/%s\n", repertoire, entree->d_name);
                continue;
            }
            
            // Ouvrir le fichier
            FILE* fichier = fopen(cheminFichier, "r");
            if (!fichier) {
                fprintf(stderr, "Échec de l'ouverture du fichier de la pièce : %s\n", cheminFichier);
                continue;
            }
            
            // Lire la pièce
            memset(pieces[indexPiece].forme, ' ', TAILLE_PIECE * TAILLE_PIECE);
            for (int i = 0; i < TAILLE_PIECE; i++) {
                char ligne[TAILLE_PIECE * 2 + 1]; // Espace supplémentaire pour le saut de ligne et le terminateur null
                if (fgets(ligne, sizeof(ligne), fichier) == NULL) break;
                
                for (int j = 0; j < TAILLE_PIECE && (size_t)j < strlen(ligne); j++) {
                    if (ligne[j] != ' ' && ligne[j] != '\n' && ligne[j] != '\r') {
                        pieces[indexPiece].forme[i][j] = 'X'; // Convertir tout caractère non-espace en 'X'
                    }
                }
            }
            
            // Assigner un symbole à cette pièce
            pieces[indexPiece].symbole = symboles[indexPiece % 7];
            
            fclose(fichier);
            indexPiece++;
        }
    }
    
    closedir(dir);
    
    // Si aucune pièce n'a été chargée, créer des pièces par défaut
    if (indexPiece == 0) {
        printf("Aucun fichier de pièce trouvé. Création de pièces par défaut.\n");
        
        // Limiter à 5 pièces uniques
        nombrePieces = 5;
        free(pieces);
        pieces = (Piece*)malloc(nombrePieces * sizeof(Piece));
        if (!pieces) {
            perror("Échec de l'allocation de mémoire pour les pièces par défaut");
            return 0;
        }

        // Initialiser toutes les pièces avec des espaces
        for (int p = 0; p < nombrePieces; p++) {
            memset(pieces[p].forme, ' ', TAILLE_PIECE * TAILLE_PIECE);
            pieces[p].symbole = symboles[p];
        }

        // Pièce I
        for (int i = 0; i < 4; i++) {
            pieces[0].forme[1][i+1] = 'X';
        }

        // Pièce O
        pieces[1].forme[1][1] = 'X';
        pieces[1].forme[1][2] = 'X';
        pieces[1].forme[2][1] = 'X';
        pieces[1].forme[2][2] = 'X';

        // Pièce T
        pieces[2].forme[1][1] = 'X';
        pieces[2].forme[1][2] = 'X';
        pieces[2].forme[1][3] = 'X';
        pieces[2].forme[2][2] = 'X';

        // Pièce L
        pieces[3].forme[1][1] = 'X';
        pieces[3].forme[2][1] = 'X';
        pieces[3].forme[3][1] = 'X';
        pieces[3].forme[3][2] = 'X';

        // Pièce Z
        pieces[4].forme[1][1] = 'X';
        pieces[4].forme[1][2] = 'X';
        pieces[4].forme[2][2] = 'X';
        pieces[4].forme[2][3] = 'X';
    }
    
    printf("%d pièces chargées avec succès.\n", nombrePieces);
    return 1;
}

// Fonction pour libérer la mémoire allouée pour les pièces
// Libère les ressources utilisées par les pièces chargées
void libererPieces() {
    if (pieces) {
        free(pieces);
        pieces = NULL;
        nombrePieces = 0;
    }
}

// Obtenir une pièce par son index
// Retourne un pointeur vers la pièce correspondante ou NULL si l'index est invalide
Piece* obtenirPiece(int index) {
    if (index >= 0 && index < nombrePieces) {
        return &pieces[index];
    }
    return NULL;
}

// Obtenir le nombre de pièces chargées
// Retourne le nombre total de pièces actuellement en mémoire
int obtenirNombrePieces() {
    return nombrePieces;
}

// Fonction pour tourner une pièce et retourner la version tournée
// Applique une rotation (0, 90, 180, ou 270 degrés) à une pièce donnée
void obtenirPieceTournee(Piece* piece, int rotation, char pieceTournee[TAILLE_PIECE][TAILLE_PIECE]) {
    // Initialiser avec des espaces
    memset(pieceTournee, ' ', TAILLE_PIECE * TAILLE_PIECE);
    
    // Tourner en fonction de la valeur de rotation
    switch (rotation % 4) {
        case 0: // Pas de rotation
            memcpy(pieceTournee, piece->forme, TAILLE_PIECE * TAILLE_PIECE);
            break;
            
        case 1: // 90 degrés dans le sens horaire
            for (int i = 0; i < TAILLE_PIECE; i++) {
                for (int j = 0; j < TAILLE_PIECE; j++) {
                    pieceTournee[j][TAILLE_PIECE - 1 - i] = piece->forme[i][j];
                }
            }
            break;
            
        case 2: // 180 degrés
            for (int i = 0; i < TAILLE_PIECE; i++) {
                for (int j = 0; j < TAILLE_PIECE; j++) {
                    pieceTournee[TAILLE_PIECE - 1 - i][TAILLE_PIECE - 1 - j] = piece->forme[i][j];
                }
            }
            break;
            
        case 3: // 270 degrés dans le sens horaire (90 antihoraire)
            for (int i = 0; i < TAILLE_PIECE; i++) {
                for (int j = 0; j < TAILLE_PIECE; j++) {
                    pieceTournee[TAILLE_PIECE - 1 - j][i] = piece->forme[i][j];
                }
            }
            break;
    }
}

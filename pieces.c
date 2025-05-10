#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include "pieces.h"

// Charge une pièce depuis un fichier
Piece* charger_piece_depuis_fichier(const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", nom_fichier);
        return NULL;
    }

    Piece* piece = malloc(sizeof(Piece));
    if (piece == NULL) {
        printf("Erreur : allocation mémoire échouée.\n");
        fclose(fichier);
        return NULL;
    }

    for (int i = 0; i < TAILLE_PIECE; i++) {
        fgets(piece->forme[i], TAILLE_PIECE + 2, fichier); // +2 pour '\n' et '\0'
        piece->forme[i][strcspn(piece->forme[i], "\n")] = '\0'; // Enlève le '\n'
    }

    fclose(fichier);
    return piece;
}

// Libère la mémoire allouée pour une pièce
void liberer_piece(Piece* piece) {
    if (piece != NULL) {
        free(piece);
    }
}

// Affiche une pièce dans le terminal
void afficher_piece(Piece* piece) {
    for (int i = 0; i < TAILLE_PIECE; i++) {
        printf("%s\n", piece->forme[i]);
    }
}

// Effectue une rotation de la pièce (90° dans le sens horaire)
Piece* rotation_piece(Piece* piece) {
    Piece* nouvelle = malloc(sizeof(Piece));
    if (nouvelle == NULL) {
        printf("Erreur : allocation mémoire échouée.\n");
        return NULL;
    }

    for (int i = 0; i < TAILLE_PIECE; i++) {
        for (int j = 0; j < TAILLE_PIECE; j++) {
            nouvelle->forme[i][j] = piece->forme[TAILLE_PIECE - j - 1][i];
        }
        nouvelle->forme[i][TAILLE_PIECE] = '\0';
    }

    return nouvelle;
}

// Liste les fichiers de pièces dans le dossier spécifié
char** lister_fichiers_pieces(int* nb_pieces) {
    DIR* dir = opendir(DOSSIER_PIECES);
    struct dirent* entry;
    int capacite = 10;
    int compteur = 0;
    char** liste = malloc(capacite * sizeof(char*));

    if (liste == NULL || dir == NULL) {
        printf("Erreur de lecture du dossier de pièces.\n");
        return NULL;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') { // Ignore les fichiers cachés
            if (compteur >= capacite) {
                capacite *= 2;
                liste = realloc(liste, capacite * sizeof(char*));
            }
            liste[compteur] = malloc(strlen(entry->d_name) + 1);
            strcpy(liste[compteur], entry->d_name);
            compteur++;
        }
    }

    closedir(dir);
    *nb_pieces = compteur;
    return liste;
}

// Libère la mémoire allouée pour la liste des fichiers
void liberer_liste_fichiers(char** liste, int nb) {
    for (int i = 0; i < nb; i++) {
        free(liste[i]);
    }
    free(liste);
}

// Choisit une pièce aléatoire parmi les fichiers disponibles
Piece* choisir_piece_aleatoire(char** fichiers, int nb) {
    if (nb == 0) return NULL;

    int indice = rand() % nb;
    char chemin[100];
    snprintf(chemin, sizeof(chemin), "%s/%s", DOSSIER_PIECES, fichiers[indice]);
    return charger_piece_depuis_fichier(chemin);
}

// Ajout de la fonction generer_piece
void generer_piece(Piece* piece) {
    const char* fichiers_pieces[] = {
        "pieces/piece_I.txt",
        "pieces/piece_J.txt",
        "pieces/piece_L.txt",
        "pieces/piece_O.txt",
        "pieces/piece_S.txt",
        "pieces/piece_T.txt",
        "pieces/piece_Z.txt"
    };

    srand(time(NULL));
    int index = rand() % 7;
    Piece* nouvelle_piece = charger_piece_depuis_fichier(fichiers_pieces[index]);

    if (nouvelle_piece != NULL) {
        *piece = *nouvelle_piece;
        free(nouvelle_piece);
    } else {
        printf("Erreur lors de la génération de la pièce.");
    }
}
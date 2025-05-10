#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> // pour sleep
#include "util.h"

// Vide le buffer d'entrée
void vider_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Lit une chaîne de caractères depuis l'entrée standard
void lire_chaine(char* chaine, int taille_max) {
    fgets(chaine, taille_max, stdin);
    chaine[strcspn(chaine, "\n")] = '\0'; // Enlève le retour à la ligne
}

// Lit un entier depuis l'entrée standard
int lire_entier() {
    int entier;
    while (scanf("%d", &entier) != 1) {
        printf("Entrée invalide. Veuillez entrer un nombre : ");
        vider_buffer();
    }
    vider_buffer();
    return entier;
}

// Génère un entier aléatoire entre min et max (inclus)
int entier_aleatoire(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Met le programme en pause pendant un certain nombre de secondes
void pause_seconds(int secondes) {
    sleep(secondes);
}

// Vérifie si un fichier existe
int fichier_existe(const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier != NULL) {
        fclose(fichier);
        return 1;
    }
    return 0;
}
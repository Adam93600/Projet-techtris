#ifndef UTIL_H
#define UTIL_H

// Nettoie l’entrée standard
void vider_buffer();

// Lit une ligne de texte depuis l'entrée utilisateur
void lire_chaine(char* chaine, int taille_max);

// Lit un entier depuis l'utilisateur
int lire_entier();

// Génère un nombre aléatoire entre min et max (inclus)
int entier_aleatoire(int min, int max);

// Met le programme en pause pour une durée en secondes
void pause_seconds(int secondes);

// Vérifie si un fichier existe
int fichier_existe(const char* nom_fichier);

#endif
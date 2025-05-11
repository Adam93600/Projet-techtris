/**
 * Score.h - Fonctions de gestion des scores
 */

#ifndef SCORE_H
#define SCORE_H

// Calculer le score en fonction des lignes effacées et de la difficulté
// Retourne un score basé sur le nombre de lignes effacées et le niveau de difficulté
int calculerScore(int lignesEffacees, int difficulte);

// Sauvegarder le score dans un fichier
// Ajoute un nouveau score au fichier des scores et trie les scores par ordre décroissant
void sauvegarderScore(const char* nomJoueur, int score);

// Afficher les scores élevés
// Lit le fichier des scores et affiche les meilleurs scores dans un format lisible
void afficherScoresEleves();

#endif /* SCORE_H */

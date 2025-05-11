# Tech-Tris

Un jeu de Tetris en terminal développé en C.


## Description

Tech-Tris est une implémentation du jeu classique Tetris fonctionnant dans un terminal. Le jeu utilise des caractères ASCII colorés pour représenter 
les pièces et la grille, offrant une expérience visuelle agréable même dans un environnement console.

## Fonctionnalités

- Interface utilisateur en terminal avec couleurs ANSI
- Rotation des pièces (0°, 90°, 180°, 270°)
- Système de score basé sur le nombre de lignes complétées
- Plusieurs niveaux de difficulté
- Augmentation progressive de la vitesse avec le niveau
- Tableau des meilleurs scores
- Pièces personnalisables via des fichiers texte

## Prérequis

- Compilateur C (GCC recommandé)
- Environnement POSIX (Linux, macOS, ou Windows avec WSL)
- Terminal supportant les séquences d'échappement ANSI pour les couleurs

## Compilation

```bash
gcc -o tech-tris main.c jeu.c piece.c display.c score.c -std=c99
```

## Utilisation

```bash
./tech-tris
```

Au lancement, le jeu vous demandera :
1. Votre nom pour le tableau des scores
2. Le niveau de difficulté souhaité

## Contrôles

- Entrez un chiffre pour sélectionner la colonne (0-9)
- Entrez un chiffre pour choisir la rotation (0-3)
- Attention : Vous disposez d'un temps limité pour faire vos choix !

## Structure des fichiers

- `main.c` : Point d'entrée du programme, gestion des événements
- `jeu.c/h` : Gestion de la logique du jeu (pièces, grille, niveaux)
- `piece.c/h` : Définition et manipulation des pièces
- `display.c/h` : Affichage dans le terminal avec couleurs
- `score.c/h` : Gestion des scores et classements

## Pièces personnalisées

Vous pouvez créer vos propres pièces en ajoutant des fichiers texte dans le dossier `pieces/`. Chaque fichier doit contenir une matrice 5x5 où les caractères non-espaces représentent les blocs de la pièce.

Exemple de pièce en forme de T :
```
     
 XXX 
  X  
     
     
```

## Auteurs

- **Adam** - *Développement complet*
- **Anes** - *Développement complet*

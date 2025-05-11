

#define _POSIX_C_SOURCE 200809L // Assurer la conformité POSIX pour usleep

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> // Pour usleep
#include <termios.h>
#include <fcntl.h>
#include <sys/time.h>
#include <signal.h>
#include "jeu.h" 
#include "display.h"
#include "piece.h"
#include "score.h"
#include <time.h> // Pour nanosleep

// Variable globale pour savoir si le temps est écoulé
volatile int tempsEcoule = 0;

// Gestionnaire de signal pour le minuteur
// Déclenché lorsque le temps est écoulé, met à jour la variable globale tempsEcoule
void gestionnaireMinuteur(int sig) {
    (void)sig; // Marquer le paramètre comme inutilisé
    tempsEcoule = 1;
}

// Configure un minuteur pour une durée donnée en secondes
// Utilise les signaux pour détecter la fin du délai
void configurerMinuteur(int secondes) {
    struct itimerval minuteur;
    signal(SIGALRM, gestionnaireMinuteur);
    
    minuteur.it_value.tv_sec = secondes;
    minuteur.it_value.tv_usec = 0;
    minuteur.it_interval.tv_sec = 0;
    minuteur.it_interval.tv_usec = 0;
    
    setitimer(ITIMER_REAL, &minuteur, NULL);
}

// Remplace la fonction usleep par nanosleep pour une meilleure précision
// Permet de dormir pendant un certain nombre de millisecondes
void dormirMillisecondes(int millisecondes) {
    struct timespec ts;
    ts.tv_sec = millisecondes / 1000;
    ts.tv_nsec = (millisecondes % 1000) * 1000000;
    nanosleep(&ts, NULL);
}

// Lit une entrée clavier avec un délai spécifié
// Retourne la touche pressée ou -1 si le délai est écoulé
int lireAvecDelai(int delai_sec) {
    struct termios ancien, nouveau;
    int touche;
    int ancienf;
    
    tcgetattr(STDIN_FILENO, &ancien);
    nouveau = ancien;
    nouveau.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &nouveau);
    ancienf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, ancienf | O_NONBLOCK);
    
    // Configurer le minuteur
    tempsEcoule = 0;
    configurerMinuteur(delai_sec);
    
    // Attendre l'entrée ou le délai
    while (!tempsEcoule) {
        touche = getchar();
        if (touche != EOF) {
            // Annuler le minuteur
            configurerMinuteur(0);
            // Réinitialiser le mode terminal
            tcsetattr(STDIN_FILENO, TCSANOW, &ancien);
            fcntl(STDIN_FILENO, F_SETFL, ancienf);
            return touche;
        }
        dormirMillisecondes(100);  // Dormir pendant 100ms pour éviter de surcharger le CPU
    }
    
    // Réinitialiser le mode terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &ancien);
    fcntl(STDIN_FILENO, F_SETFL, ancienf);
    return -1;  // Délai écoulé
}

// Fonction principale du programme
// Initialise le jeu, gère la boucle principale et la logique du jeu
int main(int argc, char *argv[]) {
    (void)argc; // Marquer le paramètre comme inutilisé
    (void)argv; // Marquer le paramètre comme inutilisé
    srand(time(NULL));  // Initialiser la graine aléatoire
    
    // Message de bienvenue
    afficherBienvenue();
    
    // Obtenir le nom du joueur
    char nomJoueur[50];
    printf("Entrez votre nom : ");
    scanf("%49s", nomJoueur);
    getchar();  // Consommer le retour à la ligne
    
    // Choisir le niveau de difficulté
    int niveauDifficulte = choisirDifficulte();
    
    // Initialiser le jeu
    Jeu jeu;
    initialiserJeu(&jeu);
    
    // Charger les pièces
    if (!chargerPieces("pieces")) {
        printf("Erreur lors du chargement des pièces. Utilisation des pièces par défaut.\n");
    }
    
    // Boucle de jeu
    int enCours = 1;
    effacerEcran();
    
    while (enCours) {
        // Choisir la prochaine pièce
        int indexPiece = obtenirPieceAleatoire(&jeu);
        Piece* pieceActuelle = obtenirPiece(indexPiece);
        
        // Afficher l'état du jeu
        afficherJeu(&jeu, pieceActuelle);
        
        // Obtenir la limite de temps en fonction de la difficulté et du niveau actuel
        int limiteTemps = obtenirLimiteTemps(niveauDifficulte, jeu.niveau);
        
        // Demander la colonne et la rotation
        printf("Vous avez %d secondes pour choisir...\n", limiteTemps);
        
        int colonne, rotation;
        
        // Obtenir la colonne avec délai
        printf("Entrez la colonne (0-%d) : ", LARGEUR_GRILLE - 1);
        fflush(stdout);
        int entree = lireAvecDelai(limiteTemps);
        
        if (entree == -1) {
            printf("\nTemps écoulé ! Un placement aléatoire sera utilisé.\n");
            colonne = rand() % LARGEUR_GRILLE;
            rotation = rand() % 4;
        } else {
            colonne = entree - '0';
            if (colonne < 0 || colonne >= LARGEUR_GRILLE) {
                colonne = rand() % LARGEUR_GRILLE;
                printf("Colonne invalide ! Colonne aléatoire %d sera utilisée.\n", colonne);
            }
            
            // Obtenir la rotation avec délai
            printf("Entrez la rotation (0-3) : ");
            fflush(stdout);
            entree = lireAvecDelai(limiteTemps);
            
            if (entree == -1) {
                printf("\nTemps écoulé ! Une rotation aléatoire sera utilisée.\n");
                rotation = rand() % 4;
            } else {
                rotation = entree - '0';
                if (rotation < 0 || rotation > 3) {
                    rotation = rand() % 4;
                    printf("Rotation invalide ! Rotation aléatoire %d sera utilisée.\n", rotation);
                }
            }
        }
        
        // Placer la pièce
        int succes = placerPiece(&jeu, pieceActuelle, rotation, colonne);
        if (!succes) {
            printf("Partie terminée ! Votre pièce n'a pas pu être placée.\n");
            dormirMillisecondes(2000);
            enCours = 0;
            break;
        }
        
        // Vérifier les lignes complètes
        int lignesEffacees = verifierLignes(&jeu);
        if (lignesEffacees > 0) {
            int points = calculerScore(lignesEffacees, niveauDifficulte);
            jeu.score += points;
            printf("%d lignes effacées ! +%d points\n", lignesEffacees, points);
            
            // Augmenter le niveau tous les 10 lignes
            jeu.lignesTotalesEffacees += lignesEffacees; // Correction du membre de la structure
            jeu.niveau = jeu.lignesTotalesEffacees / 10 + 1; // Correction du membre de la structure
            
            dormirMillisecondes(1000);
        }
        
        effacerEcran();
    }
    
    // Fin de partie, sauvegarder le score
    sauvegarderScore(nomJoueur, jeu.score);
    afficherScoresEleves(); // Correction du nom de la fonction
    
    // Nettoyer
    libererPieces();
    
    return 0;
}
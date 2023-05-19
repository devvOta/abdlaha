#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define HAUTEUR 8
#define LONGUEUR 8
#define NUM_SYMBOLS 6

const char SYMBOLS[NUM_SYMBOLS] = {'♦', '♣', '♥', '♠', '●', '▲'};

void initialiserPlateau(char plateau[HAUTEUR][LONGUEUR]) {
    srand(time(NULL));

    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LONGUEUR; j++) {
            int randomIndex = rand() % NUM_SYMBOLS;
            plateau[i][j] = SYMBOLS[randomIndex];
        }
    }
}

void afficherPlateau(char plateau[HAUTEUR][LONGUEUR]) {
    printf("\n");
    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LONGUEUR; j++) {
            printf("%c ", plateau[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

bool estMatch(char plateau[HAUTEUR][LONGUEUR], int ligne, int colonne) {
    char symbole = plateau[ligne][colonne];

    // Vérification des matchs horizontaux
    if (colonne < LONGUEUR - 2 && plateau[ligne][colonne + 1] == symbole && plateau[ligne][colonne + 2] == symbole) {
        return true;
    }

    // Vérification des matchs verticaux
    if (ligne < HAUTEUR - 2 && plateau[ligne + 1][colonne] == symbole && plateau[ligne + 2][colonne] == symbole) {
        return true;
    }

    return false;
}

void supprimerSymboles(char plateau[HAUTEUR][LONGUEUR], bool symbolesASupprimer[HAUTEUR][LONGUEUR]) {
    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LONGUEUR; j++) {
            if (symbolesASupprimer[i][j]) {
                plateau[i][j] = ' ';
            }
        }
    }
}

void remplirCasesVides(char plateau[HAUTEUR][LONGUEUR]) {
    for (int j = 0; j < LONGUEUR; j++) {
        int k = HAUTEUR - 1;

        for (int i = HAUTEUR - 1; i >= 0; i--) {
            if (plateau[i][j] != ' ') {
                plateau[k][j] = plateau[i][j];
                k--;
            }
        }

        for (int i = k; i >= 0; i--) {
            int randomIndex = rand() % NUM_SYMBOLS;
            plateau[i][j] = SYMBOLS[randomIndex];
        }
    }
}

void jouer() {
    char plateau[HAUTEUR][LONGUEUR];
    bool symbolesASupprimer[HAUTEUR][LONGUEUR];
    int nbCoups = 0;
    char choixContinuer = 'o';

    printf("=== Bienvenue dans le jeu ===\n\n");

    while (choixContinuer == 'o' || choixContinuer == 'O') {
        printf("=== Tour %d ===\n", nbCoups + 1);
        initialiserPlateau(plateau);
        afficherPlateau(plateau);

        // Suppression des symboles correspondants à des matchs
        supprimerSymboles(plateau, symbolesASupprimer);

        // Remplissage des cases vides
        remplirCasesVides(plateau);

        afficherPlateau(plateau);

        nbCoups++;

        printf("Voulez-vous continuer la partie (o/n) ? ");
        scanf(" %c", &choixContinuer);
    }

    printf("\n=== Fin du jeu ===\n");
}

int main() {
    jouer();
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HAUTEUR 5
#define LARGEUR 5
#define NB_SYMBOLES 3

typedef struct {
    int ligne;
    int colonne;
} Position;

void initialiserPlateau(int plateau[HAUTEUR][LARGEUR]) {
    srand(time(NULL));
    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            plateau[i][j] = rand() % NB_SYMBOLES;
        }
    }
}

void afficherPlateau(int plateau[HAUTEUR][LARGEUR]) {
    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            printf("%d ", plateau[i][j]);
        }
        printf("\n");
    }
}

int estAdjacent(Position pos1, Position pos2) {
    int diffLigne = abs(pos1.ligne - pos2.ligne);
    int diffColonne = abs(pos1.colonne - pos2.colonne);
    return (diffLigne == 1 && diffColonne == 0) || (diffLigne == 0 && diffColonne == 1);
}

void echangerSymboles(int plateau[HAUTEUR][LARGEUR], Position pos1, Position pos2) {
    int temp = plateau[pos1.ligne][pos1.colonne];
    plateau[pos1.ligne][pos1.colonne] = plateau[pos2.ligne][pos2.colonne];
    plateau[pos2.ligne][pos2.colonne] = temp;
}

int estMatchPresent(int plateau[HAUTEUR][LARGEUR]) {
    for (int i = 0; i < HAUTEUR; i++) {
        for (int j = 0; j < LARGEUR - 2; j++) {
            int symbole = plateau[i][j];
            if (plateau[i][j + 1] == symbole && plateau[i][j + 2] == symbole) {
                return 1;
            }
        }
    }

    for (int i = 0; i < HAUTEUR - 2; i++) {
        for (int j = 0; j < LARGEUR; j++) {
            int symbole = plateau[i][j];
            if (plateau[i + 1][j] == symbole && plateau[i + 2][j] == symbole) {
                return 1;
            }
        }
    }

    return 0;
}

void supprimerSymboles(int plateau[8][8]) {
    int symbolesSupprimes = 0;

    do {
        symbolesSupprimes = 0;

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                int symbole = plateau[i][j];
                int count = 1;

                // Vérifier les groupes horizontaux
                while (j + count < 8 && plateau[i][j + count] == symbole) {
                    count++;
                }

                if (count >= 3) {
                    for (int k = 0; k < count; k++) {
                        plateau[i][j + k] = -1;
                    }
                    symbolesSupprimes += count;
                }

                // Vérifier les groupes verticaux
                count = 1;
                while (i + count < 8 && plateau[i + count][j] == symbole) {
                    count++;
                }

                if (count >= 3) {
                    for (int k = 0; k < count; k++) {
                        plateau[i + k][j] = -1;
                    }
                    symbolesSupprimes += count;
                }
            }
        }

        // Tasser les symboles vers le bas
        for (int j = 0; j < 8; j++) {
            int count = 0;
            for (int i = 8 - 1; i >= 0; i--) {
                if (plateau[i][j] != -1) {
                    plateau[8 - 1 - count][j] = plateau[i][j];
                    count++;
                }
            }
            for (int i = 0; i < count; i++) {
                plateau[i][j] = -1;
            }
        }
    } while (symbolesSupprimes > 0);
}

void remplirCasesVides(int plateau[8][8]) {
    for (int j = 0; j < 8; j++) {
        for (int i = 0; i < 8; i++) {
            if (plateau[i][j] == -1) {
                plateau[i][j] = rand() % NB_SYMBOLES;
            }
        }
    }
}

void jouerPartie() {
    int plateau[HAUTEUR][LARGEUR];
    int score = 0;
    int coups = 0;

    initialiserPlateau(plateau);
    afficherPlateau(plateau);

    while (1) {
        Position pos1, pos2;

        printf("Coup %d : Entrez les coordonnées (ligne colonne) du premier symbole à échanger : ", coups + 1);
        scanf("%d %d", &pos1.ligne, &pos1.colonne);

        printf("Coup %d : Entrez les coordonnées (ligne colonne) du deuxième symbole à échanger : ", coups + 1);
        scanf("%d %d", &pos2.ligne, &pos2.colonne);

        if (pos1.ligne < 0 || pos1.ligne >= HAUTEUR || pos1.colonne < 0 || pos1.colonne >= LARGEUR ||
            pos2.ligne < 0 || pos2.ligne >= HAUTEUR || pos2.colonne < 0 || pos2.colonne >= LARGEUR) {
            printf("Les coordonnées saisies sont hors limites du plateau. Réessayez.\n");
            continue;
        }

        if (!estAdjacent(pos1, pos2)) {
            printf("Les deux symboles ne sont pas adjacents. Réessayez.\n");
            continue;
        }

        echangerSymboles(plateau, pos1, pos2);

        if (estMatchPresent(plateau)) {
            score += 10;
            printf("Match trouvé ! Vous avez gagné 10 points.\n");

            supprimerSymboles(plateau);
            remplirCasesVides(plateau);

            afficherPlateau(plateau);

            // Vérification de la condition de victoire
            if (!estMatchPresent(plateau)) {
                printf("Félicitations ! Vous avez gagné la partie.\n");
                break;
            }
        } else {
            printf("Aucun match trouvé. Essayez à nouveau.\n");

            echangerSymboles(plateau, pos1, pos2);
        }
        coups++;

        if (coups >= 10) {
            printf("Nombre maximum de coups atteint. Fin de la partie.\n");
            break;
        }
        
    }

    printf("Score final : %d\n", score);
}

int main() {
    jouerPartie();

    return 0;
}


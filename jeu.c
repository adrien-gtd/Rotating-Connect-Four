#include "jeu.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int fgetint (void) {
    int i; 
    int c;

    if (ia.isBot[game.player-1]) {
        return randomMoove();
    }
    i = getchar () - '1';
    while ((c = getchar()) != EOF && c != '\n');
    return i;
}

char mygetchar (void) {
    char i;
    char c;
    i = getchar ();
    while ((c = getchar()) != EOF && c != '\n');
    return i;
}


void display () {                   //affiche la matrice "board" 
    int i = 0;
    int j = 0;

    printf ("_______________\n");

    for (i = 6; i >= 0; i--) {
        for (j = 0; j < 7; j++) {
            printf ("|");
            if (game.board[i][j] == 1) {
                printf ("O");
            } else if (game.board[i][j] == 2) {
                printf ("X");
            } else {
                printf (" ");
            }
        }
        printf ("|\n");
    }
    printf ("_______________\n");
}

int isPossible (int x) {        //prend en paramètre un numero de colonne (commence à 0) et revoie 1 si on peut jouer
    if (x > 6 || x < 0) {       //dans cette colonne et 0 sinon
        return 0;
    }

    if (game.height [x] > 6) {
        return 0;
    }
    return 1;
}


void displayWin (int winner) {      //Affichage quand le joueur 'winner' gagne la partie
    printf ("\n\n");
    display ();
    printf ("Le joeur %d remporte la partie !\n",winner);
}

void displayDraw () {               //Affichage en cas d'égalité
    printf ("\n\n");
    display ();
    printf ("Egalité ! \n");
}


int play (int x) {              //prend en paramètre un entier tapé par l'utilisateur et effectue une action
    int temp = 0;               //correspondant à ce nombre (jouer ou retourner la grille)

    if (isPossible (x)) {       
        if (win (x, game.board, game.height[x], game.player)) {              
            game.board[game.height[x]][x] = game.player;
            displayWin (game.player);
            return 2;
        }
        printf ("\n\n");
        game.board[game.height[x]][x] = game.player;
        game.height [x]++;
        game.turn ++;
        goto next;
    }

    if (x == 54) {    //le joueur a appuié sur g
        printf ("\n\n");
        leftRotation ();
        if ((temp = checkBoard (game.board))) {
            if (temp == 3) {
                displayDraw ();
                return 2;
            }
            else {
                displayWin (temp);
                return 2;
            }
        }
        goto next;
    }

    if (x == 51) {    //le joueur a appuié sur d
        printf ("\n\n");
        rightRotation ();
        goto next;
    }

    if (x == 67) {    //le joueuer a appuié sur t
        printf ("\n\n");
        fullRotation ();
        goto next;
    }

    if (x == 66) {     //le joueur a appuié sur s
        save ();
    }
    printf ("Erreur, entrez un autre choix : ");
    return 0;
    next :     
    if (game.turn == 49) {
        displayDraw ();
        return 2;
    }         
    game.player = game.player %2 + 1;
    display ();
    printf (" 1 2 3 4 5 6 7 \n g : rotation a gauche, d : rotation a droite, t : rotation complète, s : sauvgarder la partie\n");
    printf ("Joeur %d à toi ! ", game.player);
    return 1;
}

int checkVertical (int x, char methode, int hauteur, int caseX, int grille[7][7]) { 
    int i = 1;
    int count = 0;

    if (!caseX) {
        return 0;
    }

    while (grille [hauteur - i][x] == caseX && hauteur - i >= 0) {
        count ++;
        i++;
    }
    i = 1;
    while (grille [hauteur + i][x] == caseX && hauteur + i <= 6) {
        count ++;
        i++;
    } 
    if (count >= 3) {
        return caseX;
    } 
    else {
        return 0;
    }
}

int checkHorizontal (int x, char methode, int hauteur, int caseX, int grille[7][7]) {
    int i = 1;
    int count = 0;

    if (!caseX) {
        return 0;
    }

    while (grille [hauteur][x-i] == caseX && x-i >= 0) {
        count ++;
        i++;
    }

    i = 1;
    while (grille [hauteur][x + i] == caseX && x + i <= 6) {
        count ++;
        i++;
    } 
    if (count >= 3) {
        return caseX;
    } 
    else {
        return 0;
    }
}

int checkDiagonal1 (int x, char methode, int hauteur, int caseX, int grille[7][7]) {
    int i = 1;
    int count = 0;

    if (!caseX) {
        return 0;
    }

    while (grille [hauteur-i][x-i] == caseX && hauteur - i >= 0 && x - i >= 0) {
        count ++;
        i++;
    }

    i = 1;
    while (grille [hauteur + i][x + i] == caseX && hauteur + i <= 6 && x + i <= 6) {
        count ++;
        i++;
    } 
    if (count >= 3) {
        return caseX;
    } 
    else {
        return 0;
    }
}

int checkDiagonal2 (int x, char methode, int hauteur, int caseX, int grille[7][7]) {
    int i = 1;
    int count = 0;

    if (!caseX) {
        return 0;
    }

    while (grille [hauteur+i][x-i] == caseX && hauteur + i <= 6 && x - i >= 0) {
        count ++;
        i++;
    }

    i = 1;
    while (grille [hauteur - i][x + i] == caseX && hauteur - i >= 0 && x + i <= 6) {
        count ++;
        i++;
    } 
    if (count >= 3) {
        return caseX;
    } 
    else {
        return 0;
    }
}

int win (int x, int grille [7][7], int height, int currentPlayer) {                   // revoie 1 si le prochain joeur gagne en jouant sur la case x, 0 sinon
    if (checkVertical (x, 'a', height, currentPlayer, grille)) {
        return 1;
    }
    
    if (checkHorizontal (x, 'a', height, currentPlayer, grille)) {
        return 1;
    }

    if (checkDiagonal1 (x, 'a', height, currentPlayer, grille)) {
        return 1;
    }

    if (checkDiagonal2 (x, 'a', height, currentPlayer, grille)) {
        return 1;
    }

    return 0; // aucun des cas precedents, donc revoie faux
}

void leftRotation () {              //fait une rotation a 90° vers la gauche
    int boardCopy [7][7] = {0};
    int i = 0;
    int j = 0;
    int e = 0;

    for (e = 0; e < 7; e++) {       // on va mettre a jour le teableau "hight", on commence par le réinitialiser
        game.height [e] = 0;
    }

    for (i = 0; i < 7; i++) {
        for (j=0; j < 7; j++) {
            if (game.board[i][j] != 0) {
                boardCopy [game.height[6-i]][6-i] = game.board[i][j];
                game.height[6-i] ++;
            }
        }
    }
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 7; j++) {
            game.board[i][j] = boardCopy[i][j];
        }
    }
}

void rightRotation () {             //fait une rotation a 90° vers la droite
    int boardCopy [7][7] = {0};
    int i = 0;
    int j = 0;
    int e = 0;

    for (e = 0; e < 7; e++) {       // on va mettre a jour le teableau "hight", on commence par le réinitialiser
        game.height [e] = 0;
    }

    for (i = 0; i < 7; i++) {
        for (j=0; j < 7; j++) {
            if (game.board[i][6-j] != 0) {
                boardCopy [game.height[i]][i] = game.board[i][6-j];
                game.height[i] ++;
            }
        }
    }

    for (i = 0; i < 7; i++) {
        for (j = 0; j < 7; j++) {
            game.board[i][j] = boardCopy[i][j];
        }
    }
}


void fullRotation () {
    int boardCopy[7][7] = {0};
    int i = 0;
    int j = 0;
    int e = 0;

    for (e = 0; e < 7; e++) {       // on va mettre a jour le teableau "hight", on commence par le réinitialiser
        game.height [e] = 0;
    }

    for (i=6; i >= 0; i--) {
        for (j=0; j < 7; j++) {
            if (game.board[i][j] != 0) {
                boardCopy[game.height[j]][j] = game.board[i][j];
                game.height[j] ++;
            }
        }
    }

    for (i = 0; i < 7; i++) {
        for (j = 0; j < 7; j++) {
            game.board[i][j] = boardCopy[i][j];
        }
    }
}


int checkBoard (int grille [7][7]) {         //verifie si 4 jetons de la même couleurs sont alignés 
    int res = 0;                             //renvoie 1 ou 2 si le joueur 1 ou 2 a 4 jetons alignés 
    int temp = 0;                            //revoie 0 si aucune n'a 4 jetons alignés
    int i = 0;                               //revoie 3 si les 2 joueurs ont 4 jetons alignés

    for (i = 0; i < 7; i++) {
        if ((temp = checkVertical (i, 'b', 3, game.board [3][i], grille))) {
            if (!res) {
                res = temp;
            }
            else if (temp != 3) {
                return 3;
            }
        }

        if ((temp = checkDiagonal1 (i, 'b', 3, game.board[3][i], grille))) {
            if (!res) {
                res = temp;
            }
            else if (temp != res) {
                return 3;
            }
        }

        if ((temp = checkDiagonal2 (i, 'b', 3, game.board[3][i], grille))) {
            if (!res) {
                res = temp;
            } 
            else if (temp != res) {
                return 3;
            }
        }
    }

    for (i = 0; i < 7; i++) {
        if ((temp = checkHorizontal (i, 'b', i, game.board[i][3], grille))) {
            if (!res) {
                res = temp;
            } 
            else if (temp != res) {
                return 3;
            }
        }
    }

    return res;
}

void save () {
    int i = 0;
    int j = 0;

    FILE* f = NULL;
    if ((f = fopen ("save.txt", "w")) == NULL) {
        printf ("Erreur de chargement du fichier save.txt\n");
        exit (EXIT_FAILURE);
    }

    for (i = 0; i < 7; i++) {
        for (j = 0; j < 7; j++) {
            fputc (game.board [i][j], f);
        }
    }

    for (i = 0;  i < 7; i++) {
        fputc (game.height [i], f);
    }

    fputc (game.player, f);
    fputc (game.turn, f);

    fclose (f);
    printf ("Partie sauvgardé !\n");
    exit (EXIT_SUCCESS);
}

void load () {
    int i = 0; 
    int j = 0;

    FILE * save = NULL;

    if ((save = fopen ("save.txt", "r")) == NULL) {
        printf ("Pas de sauvegarde trouvé, début d'une nouvelle partie ! \n");
        return;
    }

    for (i = 0; i < 7; i++) {
        for (j = 0; j < 7; j++) {
            game.board [i][j] = fgetc (save);
        }
    }

    for (i = 0; i < 7; i++) {
        game.height[i] = fgetc (save); 
    }
    game.player = fgetc(save);
    game.turn = fgetc(save);
    fclose (save);
}





void changeIaValue (int value, int player) {
    ia.isBot [player - 1]= value;
    return;
}

int randomMoove () {
    int i = 0; 
    int count = 0;
    int r = rand();
    int res = 0;
    int notPossible [7] = {0};

    for (i = 0; i < 7; i++) {
        if (!isPossible (i)) {
            notPossible [i] = 1;
        }
        else {
            count ++;
        }
    }
    
    r %= count + 3;

    if (r - count == 0) {
        return 54;
    } 
    else if (r - count == 1) {
        return 51;
    }
    else if (r - count == 2) {
        return 67;
    }
    i = 0;
    while (res < r) {
        if (!notPossible[i]) {
            res++;
        }
        i++;
    }
    
    return res;
}


// J'avais essayer d'implémenter un joueur intelligent mais je n'ai pas eu le temps de corriger les erreurs,
//je laisse le code ici au cas où vous souhaiteriez y jeter un rapide coup d'oeuil

// int nextBestMoove (int grille [7][7], int nbTurn, int currP, int currH[7], int notPossible[7]) {
//     int i = 0;
//     int grilleCopy [7][7] = {0};
//     int currHCopy [7] = {0};
//     int res = 0;
//     int best = 0;
//     int temp = 0;
//     int diff = ia.isBot[game.player - 1];


//     for (i = 0; i < 7; i++) {   //fait une copie de la matrice et du tableau passées en paramètres
//         while (currHCopy[i] < currH[i]) {
//             grilleCopy [currHCopy[i]][i] = grille [currHCopy[i]][i];
//             currHCopy [i]++;
//         }
//     }

//     if (nbTurn == 0) {
//         return 0;
//     }
    

//     for (i = 0; i < 7; i++) {
//         if (!isPossible (i)) {
//             continue;
//         }

//         if (win (i, grilleCopy, currH[i], currP)) {
//             if (currP == game.player) {
//                 return nbTurn;
//             }
//             else { 
//                 return 0;
//             }
//         }

//         grilleCopy [currHCopy[i]][i] = currP;
//         currHCopy [i] ++;
//         temp  = nextBestMoove (grilleCopy, nbTurn - 1, currP % 2 + 1, currHCopy, notPossible);
        
//         if (temp > best) {
//             best = temp;
//             res = i;
//         }
//     }


//     if (nbTurn != diff) {
//         return best;
//     }


//     if (best == 0) {
//         return randomMoove (notPossible);
//     }

//     return res;
// }

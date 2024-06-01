#ifndef JEU
#define JEU

typedef struct Board {      //structure : contient l'état de la partie 
    int board [7][7];       //matrice 7x7, représente la grille du jeu
    int height [7];         //permet de savoir dans chaque colonne a quel ligne il faut jouer le prochain pion
    int player;             //change entre 1 et 2 a chaque tour, permet de savoir quel joueur va jouer
    int turn;               //compte le nombre de jeton sur la grille
} Board;

typedef struct Ia {           //Permet de garder en mémoire quel joueur est un bot ou non
    int isBot[2]; 
} Ia;

static Board game = {{0}, {0}, 1, 0};

static Ia ia = {0};

int fgetint (void);
/*  Renvoie un nombre correspondant a une colonne ou a une action (tourner la grille / sauvegarder la partie en cours) entré
    par l'utilisateur sur l'entré standard ou généré aléatoirement si c'est au tour d'un bot de jouer et vide le buffer */

char mygetchar (void);
/* Renvoie un caratère lu sur l'entré standard et vide le buffer*/

void display (); 
/*  Affiche la grille de la partie en cours */


int isPossible (int x);
/*  Paramètre : -x, numéro de colonne
    Return : vrai (1) ou faux (0)
    Renvoie vrai si on peut jouer dans la colonne x, faux sinon */


void displayDraw ();
/*  Affichage dans le cas d'une égalité */


void displayWin (int winner);
/*  Paramètre : -winner, numéro du joueur (1 ou 2)
    Affichage si le joueur 'winner' gagne la partie */


int play (int x);
/*  Paramètre : -x, choix de l'utilisateur
    Return : -1, la partie continue
             -2, la partie est finie
             -0, erreur, l'utilisateur a entré une mauvaise valeur
    Prends en paramètre soit un numéro de colonne, soit un chiffre correspondant aux lettres t, g, d, ou s;
    effectue un tour, soit met un jeton dans la colonne passée en paramètre, soit fait une rotation de la grille de 90°
    sur la droite (d), sur la gauche (g), retourne la grille (t) ou sauvegarde la partie (s) modifie également l'état de la
    partie représenté par la variable de la structure Board en conséquent*/

int checkVertical (int x, char methode, int hauteur, int caseX, int grille[7][7]);
/*  Paramètre : -x, numéro de colonne de la matrice
                -methode, soit 'a', soit 'b'
                -hauteur, ligne de la matrice 
                -caseX, valeur de la case de coordonnée (x, hauteur) de la matrice (donc un numéro de joueur ou 0)
    Return : -0, faux
             -1 ou 2, vrai, numéro de joueur
    Renvoie vrai si le joueur (caseX) a 4 jeton alignés contenant celui qui est sur la ligne (hauteur) et la colonne (x), 
    et renvoie faux si ce n'est pas le cas.
    Si la fonction renvoie vrai, elle précise de quelle joueur il s'agit car on ne connait pas forcément la valeur de la case
    testé. */


int checkHorizontal (int x, char methode, int hauteur, int caseX, int grille[7][7]);
/*  Paramètre : -x, numéro de colonne de la matrice
                -methode, soit 'a', soit 'b'
                -hauteur, ligne de la matrice 
                -caseX, valeur de la case de coordonnée (x, hauteur) de la matrice (donc un numéro de joueur ou 0)
    Return : -0, faux
             -1 ou 2, vrai, numéro de joueur
    Même chose mais sur vérifie s'il y a une alignement horizontal.*/


int checkDiagonal1 (int x, char methode, int hauteur, int caseX, int grille[7][7]);
/* Même chose mais sur la diagonale de gauche a droite :
       *
     *
   *
 *          */


int checkDiagonal2 (int x, char methode, int hauteur, int caseX, int grille[7][7]);
/* Vérifie l'autre diagonale : 
*
  *
     *
        *    */


int win (int x, int grille [7][7], int height, int currentPlayer);
/*  Paramètre : -x, numéro de colonne
    Return : -vrai ou faux (1 ou 0)
    Renvoie vrai si le prochain joueur gagne la partie en jouant dans la colonne x, faux sinon*/


void leftRotation ();
/*  Fait une rotation de 90° sur la gauche de la grille de jeu, met également a jour le tableau "hight" de la variable "game"*/


void fullRotation ();
/*  Retourne la grille */


void rightRotation ();
/*  Rotation de 90° sur la droite */


int checkBoard ();
/*  Vérifie si 4 jeton du même joueur sont alignées sur dans la grille */


void load ();
/*  Charge la dérnière partie sauvegardée dans la variable "game" */


void save ();
/*  Sauvegarde la partie dans le fichier "save.txt" et le créer s'il n'éxiste pas avant de quitter le programme*/

void changeIaValue (int value, int player);
/*  Paramètre : -value, 1 ou 0
                -player, joueur 1 ou joueur 2
    Permet de changer la valeur du tableau ia qui indique si le joueur 1 ou (et) le joueur 2 est (sont) un (des) bot */

int randomMoove ();
/*  Renvoie un coups aléatoire */
#endif

#include "jeu.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>




int main (void) {
    srand(time(NULL));

    printf ("Entrer 'l' pour charcher la dérnière partie sauvgardée, ou n'importe quel autre caractère pour commencer une nouvelle partie : ");
    if (mygetchar () == 'l') {
        load ();
    }
    else {
        printf ("Nouvelle partie \n");
    }


    printf ("Voulez vous que le joueur 1 joue automatiquement ? [y/n] ");
    if (mygetchar () == 'y') {
        changeIaValue (1, 1);
    }


    printf ("Voulez vous que le joueur 2 joue automatiquement ? [y/n] ");
    if (mygetchar () == 'y') {
        changeIaValue (1, 2);
    }


    display ();
    printf (" 1 2 3 4 5 6 7 \n");
    printf ("Début de la partie; joueur 1 commence ! ");
    while (play (fgetint ()) != 2);
}


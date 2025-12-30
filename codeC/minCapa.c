#include "graphe/graphe.c"
#include <stdlib.h>
#include <stdio.h>

int minCapa (Chemin* chemin){
    Maillon *maillon = chemin->tete;
    int min = maillon->capacite;
    while (maillon != NULL) {
        int capa = maillon->capacite;
        if (capa < min) {
            min = capa;
        }
        maillon = maillon->suivant;
    }
    return min;
}

int main (){
    return 0;
}

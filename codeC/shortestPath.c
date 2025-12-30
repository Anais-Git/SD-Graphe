#include <stdlib.h>
#include <stdio.h>
#include "graphe/graphe.h"
#include "file/file.h"

// Fonction pour trouver le plus court chemin en nombre d'arcs
Chemin* shortestPath(Chemin *RG, int s, int p) {

    int n = 0;
    // Calculer le nombre de sommets dans RG
    while (RG[n].tete != NULL) {
        n++;
    }

    int *Visite = (int*)calloc(n, sizeof(int));
    int *Prédécesseur = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        Prédécesseur[i] = -1;
    }

    File* F = createFile(n);
    enqueue(F, s);
    Visite[s] = 1;

    while (!isEmpty(F)) {
        int u = dequeue(F);

        if (u == p) {
            Chemin *chemin = (Chemin*)malloc(sizeof(Chemin));
            chemin->tete = NULL;
            chemin->taille = 0;

            int v = p;
            while (v != -1) {
                Maillon *maillon = buildMaillon(v, 0, 0, chemin->tete);
                Maillon *maillon_original = RG[u].tete;
                while (maillon_original != NULL) {
                    if (maillon_original->valeur == v) {
                        maillon->capacite = maillon_original->capacite;
                        break;
                    }
                    maillon_original = maillon_original->suivant;
                }
                maillon->suivant = chemin->tete;
                chemin->tete = maillon;
                chemin->taille++;
                v = Prédécesseur[v];
            }
            freeFile(F);
            free(Visite);
            free(Prédécesseur);
            return chemin;
        }

        Maillon *maillon = RG[u].tete;
        while (maillon != NULL) {
            int v = maillon->valeur;
            if (Visite[v] == 0 && maillon->capacite > 0) {
                Visite[v] = 1;
                Prédécesseur[v] = u;
                enqueue(F, v);
            }
            maillon = maillon->suivant;
        }
    }

    freeFile(F);
    free(Visite);
    free(Prédécesseur);
    return NULL;
}

int main () {
    return 0;
}

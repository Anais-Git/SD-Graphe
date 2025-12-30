#include "graphe/graphe.c"
#include <stdlib.h>
#include <stdio.h>


// Construit et retourne le graphe d'écart RG à partir de Graphe et nombre de sommets n
Chemin* buildRG(int n) {
    // Allocation du graphe d'écart
    Chemin *RG = (Chemin*) malloc((n + 1) * sizeof(Chemin));
    if (!RG) {
        fprintf(stderr, "Erreur allocation mémoire pour RG\n");
        exit(EXIT_FAILURE);
    }

    // Initialisation des listes
    for (int i = 0; i <= n; i++) {
        RG[i].tete = NULL;
        RG[i].taille = 0;
    }

    // Parcours du réseau initial Graphe
    for (int u = 1; u <= n; u++) {
        Maillon *m = Graphe[u].tete;
        while (m != NULL) {
            int capacite_residuelle = m->capacite - m->flot;
            if (capacite_residuelle > 0) {
                // Arc direct (u -> m->valeur) avec capacité résiduelle
                Maillon *arc_direct = createMaillon(m->valeur, capacite_residuelle, 0, RG[u].tete);
                RG[u].tete = arc_direct;
                RG[u].taille++;
            }

            if (m->flot > 0) {
                // Arc inverse (m->valeur -> u) avec capacité = flot sur arc direct
                Maillon *arc_inverse = createMaillon(u, m->flot, 0, RG[m->valeur].tete);
                RG[m->valeur].tete = arc_inverse;
                RG[m->valeur].taille++;
            }

            m = m->suivant;
        }
    }

    return RG;
}


#include "graphe/graphe.c"


void updateFlowInNet(Chemin* RG, Chemin* reseau, int n) {
    for (int u = 1; u <= n; u++) {
        Maillon* maillon = RG[u].tete;
        while (maillon != NULL) {
            int v = maillon->valeur;

            Maillon* arc_direct = reseau[u].tete;
            while (arc_direct != NULL && arc_direct->valeur != v) {
                arc_direct = arc_direct->suivant;
            }
            if (arc_direct != NULL) {
                int capacite_init = arc_direct->capacite + arc_direct->flot;
                arc_direct->flot = capacite_init - maillon->capacite;
            }

            if (maillon->suivant != NULL) {
                Maillon* arc_inverse_RG = maillon->suivant;
                Maillon* arc_inverse_reseau = reseau[v].tete;
                while (arc_inverse_reseau != NULL && arc_inverse_reseau->valeur != u) {
                    arc_inverse_reseau = arc_inverse_reseau->suivant;
                }
                if (arc_inverse_reseau != NULL) {
                    int capacite_init_inv = arc_inverse_reseau->capacite + arc_inverse_reseau->flot;
                    arc_inverse_reseau->flot += arc_inverse_RG->capacite - capacite_init_inv;
                }
            }

            maillon = maillon->suivant;
        }
    }
}

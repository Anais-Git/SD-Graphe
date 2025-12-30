
#include "graphe/graphe.c"

void updateFlowInRG(Chemin *chemin, int k) {
    Maillon *m = chemin->tete;
    while (m->suivant != NULL) {
        int u = m->valeur;
        int v = m->suivant->valeur;

        Maillon *arc_uv = Graphe[u].tete;
        while (arc_uv && arc_uv->valeur != v) arc_uv = arc_uv->suivant;
        if (arc_uv) arc_uv->capacite -= k;

        Maillon *arc_vu = Graphe[v].tete;
        while (arc_vu && arc_vu->valeur != u) arc_vu = arc_vu->suivant;
        if (arc_vu) arc_vu->capacite += k;

        m = m->suivant;
    }
}

int main() {
    return 0;
}

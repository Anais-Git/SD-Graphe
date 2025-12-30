#include <stdio.h>
#include <stdlib.h>
#include "codeC/graphe/graphe.h"

// Déclarations des variables globales
extern Chemin *Graphe;
extern int source;
extern int puits;
extern int n_nodes;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <fichier_reseau>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // 1. Construction du graphe à partir du fichier
    buildGraph(argv[1]);

    if (source == -1 || puits == -1) {
        fprintf(stderr, "Erreur : Source ou puits non défini.\n");
        freeGraph(Graphe, n_nodes);
        return EXIT_FAILURE;
    }

    int flot_total = 0;

    while (1) {
        // 2. Construction du graphe résiduel
        Chemin *RG = buildRG(Graphe);

        // 3. Recherche d'un chemin augmentant dans RG
        Chemin *chemin = shortestPath(RG, source, puits);
        if (chemin == NULL) {
            freeGraph(RG, n_nodes);
            break; // Plus de chemin augmentant, flot maximum atteint
        }

        // 4. Affichage du chemin trouvé
        printf("Chemin augmentant : ");
        Maillon *m = chemin->tete;
        while (m != NULL) {
            printf("%d ", m->valeur);
            m = m->suivant;
        }
        printf("\n");

        // 5. Capacité minimale du chemin
        int k = minCapa(chemin);
        printf("Capacité minimale : %d\n", k);

        // 6. Mise à jour du graphe résiduel
        updateFlowInRG(chemin, k,RG);

        // 7. Mise à jour du réseau principal
        updateFlowInNet(RG, Graphe);

        // 8. Ajout au flot total
        flot_total += k;
        printf("Flot total : %d\n", flot_total);

        // Nettoyage mémoire temporaire
        freeChemin(chemin);
        freeGraph(RG, n_nodes);

    }

    // 9. Écriture du résultat dans un fichier
    FILE *f = fopen("resultat.txt", "w");
    if (f == NULL) {
        perror("Erreur lors de l'ouverture du fichier resultat.txt");
        freeGraph(Graphe, n_nodes);
        return EXIT_FAILURE;
    }

    fprintf(f, "Flot maximum: %d\n", flot_total);
    for (int i = 1; i <= n_nodes; i++) {
        Maillon *m = Graphe[i].tete;
        while (m != NULL) {
            if (m->capacite > 0 || m->flot > 0) {
                fprintf(f, "Arc %d -> %d : flot = %d\n", i, m->valeur, m->flot);
            }
            m = m->suivant;
        }
    }

    fclose(f);
    printf("Flot maximum: %d\nRésultats écrits dans resultat.txt\n", flot_total);

    // Libération mémoire
    freeGraph(Graphe, n_nodes);
    return EXIT_SUCCESS;
}

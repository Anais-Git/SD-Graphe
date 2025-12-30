#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphe/graphe.h"

#define MAX_LINE_SIZE 256

// Graphe global
Chemin *Graphe = NULL;

void buildGraph(char *file_name) {
    char ligne[MAX_LINE_SIZE];
    int n_nodes, m_arcs, source, puits;

    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {
        fprintf(stderr, "%s non accessible\n", file_name);
        exit(1);
    }

    fgets(ligne, MAX_LINE_SIZE, fp); // commentaire
    fgets(ligne, MAX_LINE_SIZE, fp); // commentaire

    getc(fp); getc(fp); // 'p '
    fscanf(fp, "%d", &n_nodes);
    fscanf(fp, "%d", &m_arcs);
    fgets(ligne, MAX_LINE_SIZE, fp); // fin ligne
    printf("%d nodes\n", n_nodes);
    printf("%d arcs\n", m_arcs);

    fgets(ligne, MAX_LINE_SIZE, fp); // commentaire
    getc(fp); getc(fp); // 'n '
    fscanf(fp, "%d", &source);
    fgets(ligne, MAX_LINE_SIZE, fp); // fin ligne
    printf("source=%d\n", source);

    fgets(ligne, MAX_LINE_SIZE, fp); // commentaire
    getc(fp); getc(fp); // 'n '
    fscanf(fp, "%d", &puits);
    fgets(ligne, MAX_LINE_SIZE, fp); // fin ligne
    printf("puits=%d\n", puits);

    fgets(ligne, MAX_LINE_SIZE, fp); // commentaire des arcs

    // Initialisation du graphe
    Graphe = (Chemin *)malloc((n_nodes + 1) * sizeof(Chemin));
    for (int i = 0; i <= n_nodes; i++) {
        Graphe[i].tete = NULL;
        Graphe[i].taille = 0;
    }

    int src, dst, cap;
    for (int a = 1; a <= m_arcs; a++) {
        getc(fp); getc(fp); // 'a '
        fscanf(fp, "%d", &src);
        fscanf(fp, "%d", &dst);
        fscanf(fp, "%d", &cap);
        printf("arc %d de %d à %d, capa=%d\n", a, src, dst, cap);

        // Création du maillon pour l'arc (src → dst)
        Maillon *maillon = (Maillon *)malloc(sizeof(Maillon));
        maillon->valeur = dst;
        maillon->capacite = cap;
        maillon->flot = 0;
        maillon->suivant = Graphe[src].tete;
        Graphe[src].tete = maillon;
        Graphe[src].taille++;

        // Création du maillon pour l'arc inverse (dst → src) capacité 0
        Maillon *inverse = (Maillon *)malloc(sizeof(Maillon));
        inverse->valeur = src;
        inverse->capacite = 0;
        inverse->flot = 0;
        inverse->suivant = Graphe[dst].tete;
        Graphe[dst].tete = inverse;
        Graphe[dst].taille++;
    }

    fclose(fp);

    // Affichage du graphe
    printf("\nGraphe construit :\n");
    for (int i = 1; i <= n_nodes; i++) {
        printf("Successeurs de %d :", i);
        Maillon *courant = Graphe[i].tete;
        while (courant != NULL) {
            printf(" -> %d (cap=%d, flot=%d)", courant->valeur, courant->capacite, courant->flot);
            courant = courant->suivant;
        }
        printf("\n");
    }
}

// Main de test
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s fichier_DIMACS\n", argv[0]);
        return 1;
    }
    buildGraph(argv[1]);
    return 0;
}

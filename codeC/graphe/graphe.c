#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "graphe.h"
#include "file.h"

#define MAX_LINE_SIZE 256

// Variables globales
Chemin *Graphe = NULL;   // Réseau original
Chemin *RG = NULL;       // Graphe d'écart
int source = -1; // Sommet source
int puits = -1; // Sommet puits
int n_nodes = 0; // Nombre de sommets





// Fonction libérant le réseau ou le graphe d'écart
void freeGraph(Chemin* graphe, int n) {
    for (int i = 0; i <= n; ++i) {
        freeMaillon(graphe[i].tete);
    }
    free(graphe);
}

// Fonction auxiliaire : création d'un maillon
Maillon* buildMaillon(int val, int cap, int flot, Maillon* suiv) {
    Maillon *m = (Maillon*) malloc(sizeof(Maillon));
    if (!m) {
        fprintf(stderr, "Erreur allocation memoire\n");
        exit(EXIT_FAILURE);
    }
    m->valeur = val;
    m->capacite = cap;
    m->flot = flot;
    m->suivant = suiv;
    return m;
}

// Fonction pour ajouter un arc en tête d'une liste
void addArc(Chemin *liste, int dst, int cap, int flot) {
    Maillon *m = buildMaillon(dst, cap, flot, liste->tete);
    liste->tete = m;
    liste->taille++;
}

// Destructeur de chemin 
void freeChemin(Chemin *chemin) {
    freeMaillon(chemin->tete);
    free(chemin);
}

// Libérer une liste chainee de Maillon
void freeMaillon(Maillon *m) {
    while (m != NULL) {
        Maillon *tmp = m;
        m = m->suivant;
        free(tmp);
    }
}
  
// Fonction pour construire le graphe d'écart à partir du réseau
Chemin* buildRG(Chemin *reseau) {

    // Allocation du graphe d'écart
    Chemin *RG = (Chemin*)malloc((n_nodes + 1) * sizeof(Chemin));
    if (!RG) {
        fprintf(stderr, "Erreur allocation mémoire pour RG\n");
        exit(EXIT_FAILURE);
    }

    // Initialisation des listes chaînées dans RG
    for (int i = 0; i <= n_nodes; i++) {
        RG[i].tete = NULL;
        RG[i].taille = 0;
    }

    // Parcours du réseau initial pour construire RG
    for (int u = 1; u <= n_nodes; u++) {
        Maillon *maillon = reseau[u].tete;
        while (maillon != NULL) {
            int v = maillon->valeur;

            // Ajouter un arc résiduel dans RG
            Maillon *arc_residuel = buildMaillon(v, maillon->capacite - maillon->flot, 0, RG[u].tete);
            RG[u].tete = arc_residuel;
            RG[u].taille++;

            // Ajouter un arc résiduel inverse dans RG
            Maillon *arc_inverse = buildMaillon(u, maillon->flot, 0, RG[v].tete);
            RG[v].tete = arc_inverse;
            RG[v].taille++;

            maillon = maillon->suivant;  // Passer à l'arc suivant
        }
    }

    return RG;  // Retourner le graphe d'écart
}



void buildGraph(char *file_name) {
    char ligne[MAX_LINE_SIZE];
    int m_arcs;

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

int minCapa(Chemin* chemin) {
    Maillon* maillon = chemin->tete;
    // Trouver le premier maillon avec une capacité non nulle
    while (maillon != NULL && maillon->capacite == 0) {
        maillon = maillon->suivant;
    }
    // Si tous les maillons ont une capacité nulle ou la liste est vide, retourne 0
    if (maillon == NULL) {
        return 0;
    }
    int min = maillon->capacite;
    maillon = maillon->suivant;
    // Parcours le reste des maillons pour trouver la capacité minimale non nulle
    while (maillon != NULL) {
        int capa = maillon->capacite;
        if (capa != 0 && capa < min) {
            min = capa;
        }
        maillon = maillon->suivant;
    }
    return min;
}

void updateFlowInNet(Chemin *RG, Chemin *reseau) {
    for (int u = 1; u <= n_nodes; u++) {
        Maillon *m = RG[u].tete;
        while (m != NULL) {
            int v = m->valeur;

            // Chercher arc direct u → v dans le réseau d'origine
            Maillon *arc_direct = reseau[u].tete;
            while (arc_direct && arc_direct->valeur != v) {
                arc_direct = arc_direct->suivant;
            }

            if (arc_direct) {
                // Calcul du flot : capacité initiale (reseau) - capacité résiduelle (RG)
                arc_direct->flot = arc_direct->capacite - m->capacite;
            }
            // Pas besoin de gérer arcs inverses ici

            m = m->suivant;
        }
    }
}

void updateFlowInRG(Chemin *chemin, int k, Chemin *RG) {
    Maillon *m = chemin->tete;
    while (m->suivant != NULL) {
        int u = m->valeur;
        int v = m->suivant->valeur;

        Maillon *arc_uv = RG[u].tete;
        while (arc_uv && arc_uv->valeur != v) arc_uv = arc_uv->suivant;
        if (arc_uv) {
            arc_uv->capacite -= k;
        }

        Maillon *arc_vu = RG[v].tete;
        while (arc_vu && arc_vu->valeur != u) arc_vu = arc_vu->suivant;
        if (arc_vu) {
            arc_vu->capacite += k;
        }

        m = m->suivant;
    }
}

Chemin* shortestPath(Chemin *RG, int s, int p) {
    int *visite = (int*)calloc(n_nodes + 1, sizeof(int));
    int *pred = (int*)malloc((n_nodes + 1) * sizeof(int));
    for (int i = 0; i <= n_nodes; ++i) pred[i] = -1;

    File *f = createFile(n_nodes + 1);
    enqueue(f, s);
    visite[s] = 1;

    while (!isEmpty(f)) {
        int u = dequeue(f);
        for (Maillon *m = RG[u].tete; m; m = m->suivant) {
            int v = m->valeur;
            if (!visite[v] && m->capacite > 0) {
                visite[v] = 1;
                pred[v] = u;
                enqueue(f, v);
            }
        }
    }

    if (!visite[p]) {
        free(visite);
        free(pred);
        freeFile(f);
        return NULL;
    }

    // Reconstruct path from p to s
    Chemin *chemin = (Chemin*)malloc(sizeof(Chemin));
    chemin->tete = NULL;
    chemin->taille = 0;

    for (int v = p; v != s; v = pred[v]) {
        int u = pred[v];
        Maillon *arc = RG[u].tete;
        while (arc && arc->valeur != v) arc = arc->suivant;
        if (!arc) continue;  // sécurité
        chemin->tete = buildMaillon(v, arc->capacite, 0, chemin->tete);
        chemin->taille++;
    }

    chemin->tete = buildMaillon(s, 0, 0, chemin->tete);
    chemin->taille++;

    free(visite);
    free(pred);
    freeFile(f);
    return chemin;
}

#ifndef GRAPH_H
#define GRAPH_H

// Structure d’un maillon (un arc)
typedef struct maillon {
    int valeur;                  // sommet destination
    int capacite;                // capacité de l’arc
    int flot;                    // flot initial (souvent 0)
    struct maillon *suivant;     // pointeur vers le prochain maillon
} Maillon;

// Structure d’une liste chaînée de successeurs (ou d'un chemin)
typedef struct chemin {
    Maillon *tete;   // pointeur vers la tête de la liste ou du chemin
    int taille;      // nombre de maillons (successeurs)
} Chemin;

// Déclaration de la variable globale Graphe
extern Chemin *Graphe;
// Déclaration des variables globales S et P pour la source et le puit du réseau
extern int source;
extern int puits;
extern int n_nodes;


// Déclaration de la fonction construisant un maillon
extern Maillon* buildMaillon (int val, int cap, int flot, Maillon *suiv);

// Déclaration de la fonction ajoutant un maillon à la liste
extern void addMaillon(Chemin* liste, int dst, int cap, int flot);

// Déclaration de la fonction construisant le graphe représentant le réseau
extern void buildGraph(char *file_name);

// Déclaration de la fonction construisant le graphe d'écart
extern Chemin* buildRG (Chemin *reseau);

// Déclaration de la fonction cherchant le plus court chemin en nombre d'arcs'
extern Chemin* shortestPath(Chemin *RG, int s, int p);

// Déclaration de la fonction trouvant la capacité minimal des arcs d'un chemin
extern int minCapa(Chemin *chemin);

// Déclaration de la fonction mettant à jour le graphe d'écart
extern void updateFlowInRG(Chemin *chemin, int k, Chemin *RG);

// Déclaration de la fonction mettant à jour le graphe du réseau
extern void updateFlowInNet(Chemin *RG, Chemin *reseau);

// Déclaration de la fonction destructrice de liste chainee de maillon
extern void freeMaillon(Maillon *m);

// Déclaration de la fonction destructrice de chemin
extern void freeChemin(Chemin *chemin);

// Déclaration de le fonction libérant un graphe (réseau ou graphe d'écart)
extern void freeGraph(Chemin* graphe, int n);

#endif

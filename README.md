# Projet Dinic - Calcul du flot maximum dans un réseau

## Description :

Ce programme implémente l'algorithme de Dinic pour calculer le flot maximum dans un réseau de transport.
Le réseau est lu depuis un fichier texte au format spécifié.

## Fichiers :

- main.c         : point d'entrée du programme
- graphe.c/h     : gestion du graphe et du réseau
- file.c/h       : structure file utilisée pour la recherche de chemin
- Makefile       : script pour compiler le projet

## Compilation :

Pour compiler le programme, exécute la commande :

`make`

## Exécution :

Pour lancer le programme, tape :

`./dinic <fichier_reseau>`

où `<fichier_reseau>` est le fichier contenant la description du réseau.

## Format du fichier réseau :

Le fichier doit respecter le format suivant (extrait d’un exemple) :

- Première(s) ligne(s) de commentaires
- Ligne `p <nombre_sommets> <nombre_arcs>`
- Ligne `n <source>`
- Ligne `n <puits>`
- Suivi des arcs `a <source> <destination> <capacité>`

## Exemple d'entrée :

```
p 6 8
n 1
n 6
a 1 2 10
a 1 3 10
a 2 4 15
...
```

## Sortie :

Le programme génère un fichier `resultat.txt` contenant :

- Le flot maximum
- Le flot sur chaque arc du réseau

## Nettoyage :

Pour supprimer les fichiers objets et l’exécutable, tape :

`make clean`



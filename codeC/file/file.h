#ifndef FILE_H
#define FILE_H

// Structure pour la file
typedef struct {
    int *elements;
    int front, rear, size, capacity;
} File;

// Fonction pour creer une file
File* createFile(int capacity);

// Fonction pour verifier si la file est pleine
int isFull(File* file);

// Fonction pour verifier si la file est vide
int isEmpty(File* file);

// Fonction pour ajouter un element a la file
void enqueue(File* file, int item);

// Fonction pour retirer un element de la file
int dequeue(File* file);

// Fonction pour liberer la memoire de la file
void freeFile(File* file);

#endif // FILE_H

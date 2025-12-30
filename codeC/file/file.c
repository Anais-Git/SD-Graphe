#include <stdlib.h>
#include "file.h"

// Fonction pour créer une file
File* createFile(int capacity) {
    File* file = (File*)malloc(sizeof(File));
    file->capacity = capacity;
    file->front = file->size = 0;
    file->rear = capacity - 1;
    file->elements = (int*)malloc(file->capacity * sizeof(int));
    return file;
}

// Fonction pour vérifier si la file est pleine
int isFull(File* file) {
    return (file->size == file->capacity);
}

// Fonction pour vérifier si la file est vide
int isEmpty(File* file) {
    return (file->size == 0);
}

// Fonction pour ajouter un élément à la file
void enqueue(File* file, int item) {
    if (isFull(file))
        return;
    file->rear = (file->rear + 1) % file->capacity;
    file->elements[file->rear] = item;
    file->size = file->size + 1;
}

// Fonction pour retirer un élément de la file
int dequeue(File* file) {
    if (isEmpty(file))
        return -1;
    int item = file->elements[file->front];
    file->front = (file->front + 1) % file->capacity;
    file->size = file->size - 1;
    return item;
}

// Fonction pour libérer la mémoire de la file
void freeFile(File* file) {
    free(file->elements);
    free(file);
}


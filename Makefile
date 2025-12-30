# Compilateur et options
CC = gcc
CFLAGS = -Wall -Wextra -g
INCLUDES = -IcodeC/graphe -IcodeC/file

# Nom de l'exécutable
TARGET = main

# Fichiers sources
SRCS = main.c \
       codeC/updateFlowinRG.c \
       codeC/minCapa.c \
       codeC/buildRG.c \
       codeC/buildGraph.c \
       codeC/updateFlowinNet.c \
       codeC/shortestPath.c \
       codeC/graphe/graphe.c \
       codeC/file/file.c

# Fichiers objets
OBJS = $(SRCS:.c=.o)

# Règle par défaut
all: $(TARGET)

# Création de l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Compilation des fichiers .c en .o
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJS)

# Nettoyage complet
mrproper: clean
	rm -f $(TARGET)

.PHONY: all clean mrproper

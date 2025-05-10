CC = gcc
CFLAGS = -Wall -std=c99
OBJ = main.o jeu.o score.o pieces.o util.o
EXEC = techtris

# Règle par défaut
all: $(EXEC)

# Compilation de l'exécutable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Compilation des fichiers .o à partir des fichiers .c
main.o: main.c jeu.h score.h pieces.h util.h
	$(CC) $(CFLAGS) -c main.c

jeu.o: jeu.c jeu.h pieces.h util.h
	$(CC) $(CFLAGS) -c jeu.c

score.o: score.c score.h
	$(CC) $(CFLAGS) -c score.c

pieces.o: pieces.c pieces.h
	$(CC) $(CFLAGS) -c pieces.c

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c

# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -f $(OBJ) $(EXEC)

# Nettoyage complet, y compris les fichiers temporaires
fclean: clean
	rm -f $(EXEC)

# Recompilation complète
re: fclean all

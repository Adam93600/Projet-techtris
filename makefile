CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -D_POSIX_C_SOURCE=200809L
LDFLAGS = 

SOURCES = main.c jeu.c piece.c display.c score.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

pieces:
	mkdir -p pieces
	echo "X    \nXXXX \n     \n     \n     " > pieces/piece1.txt
	echo "XX   \nXX   \n     \n     \n     " > pieces/piece2.txt
	echo "XXX  \n X   \n     \n     \n     " > pieces/piece3.txt
	echo "X    \nX    \nXX   \n     \n     " > pieces/piece4.txt
	echo " X   \n X   \nXX   \n     \n     " > pieces/piece5.txt
	echo " XX  \nXX   \n     \n     \n     " > pieces/piece6.txt
	echo "XX   \n XX  \n     \n     \n     " > pieces/piece7.txt

.PHONY: all clean run pieces

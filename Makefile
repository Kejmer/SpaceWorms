TARGET: space-worms

CC 				= g++
CFLAGS 		= -c -Wall -O3
LFLAGS		= -Wall
ODIR 			= ./bin/
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

./bin/game.o: ./src/game.cpp
	$(CC) $(CFLAGS) $^ -o $@

space-worms: ./bin/game.o
	$(CC) $(LFLAGS) $(SFMLFLAGS) $^ -o $(ODIR)$@
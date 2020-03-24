TARGET = space-worms
SRCPTH = src
SRC = $(notdir $(wildcard $(SRCPTH)/*.cpp))
LIBPTH = bin
OBJ = $(addprefix $(LIBPTH)/,$(SRC:.cpp=.o))
DEP = $(addprefix $(LIBPTH)/,$(SRC:.cpp=.d))
FLAGS = -Wall -O3 -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system

all: main

main: $(OBJ)
	g++ $(OBJ) -o $(LIBPTH)/$(TARGET) $(FLAGS)

debug: $(OBJ)
	g++ -g $(OBJ) -o $(LIBPTH)/$(TARGET) $(FLAGS)

$(LIBPTH)/%.o: $(SRCPTH)/%.cpp
	g++ -c $(FLAGS) $< -o $(LIBPTH)/$(basename $(notdir $<)).o

clear:
	rm -f $(LIBPTH)/$(TARGET) $(OBJ)

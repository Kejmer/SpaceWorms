TARGET = space-worms
SRCPTH = src
SRC = $(notdir $(wildcard $(SRCPTH)/*.cpp))
LIBPTH = bin
OBJ = $(addprefix $(LIBPTH)/,$(SRC:.cpp=.o))
DEP = $(addprefix $(LIBPTH)/,$(SRC:.cpp=.d))
FLAGS = -Wall -O3 -std=c++11
LINK = -lsfml-graphics -lsfml-window -lsfml-system

all: main

main: $(OBJ)
	clang++ $(FLAGS) $(OBJ) -o $(LIBPTH)/$(TARGET)  $(LINK)

debug: $(OBJ)
	clang++ -g $(FLAGS) $(OBJ) -o $(LIBPTH)/$(TARGET) $(LINK)

$(LIBPTH)/%.o: $(SRCPTH)/%.cpp
	clang++ -c $(FLAGS) $< -o $(LIBPTH)/$(basename $(notdir $<)).o

clear:
	rm -f $(LIBPTH)/$(TARGET) $(OBJ)

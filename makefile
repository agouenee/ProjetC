# $(BIN) est la nom du binaire genere
BIN = bin/imagimp
# FLAG
FLAGS = -Wall -g
# INCLUDES
INC = lib/include
# INCLUDES
LIBDIR = lib/lib
# Librairies
LIBS =  -lglimagimp -lglut -lGL -lGLU
# Compilateur
CC = gcc
# Compilateur
SRC = src/image.c src/main.c

all:
	@echo "**** TEST ****"
	$(CC) -o $(BIN) $(FLAGS) -I$(INC) $(SRC) -L$(LIBDIR) $(LIBS) 

clean:
	rm -f $(BIN)

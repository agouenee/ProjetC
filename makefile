# $(BIN) est la nom du binaire genere
BIN = bin/imagimp
# FLAG
FLAGS = -Wall -g
# INCLUDES
INC = lib/glimagimp/include
# INCLUDES
LIBDIR = lib/glimagimp/lib
# Librairies
LIBS =  -lglimagimp -lglut -lGL -lGLU
# Compilateur
CC = gcc
# Compilateur
SRC = src/image.c src/layer.c src/lut.c src/historique.c src/main.c

all:
	@echo "**** TEST ****"
	$(CC) -o $(BIN) $(FLAGS) -I$(INC) $(SRC) -L$(LIBDIR) $(LIBS) 

clean:
	rm -f $(BIN)

# $(BIN) est la nom du binaire genere
BIN = sample
# FLAG
FLAGS = -Wall -g
# INCLUDES
INC = ../include
# INCLUDES
LIBDIR = ../lib
# Librairies
LIBS =  -lglimagimp -lglut -lGL -lGLU
# Compilateur
CC = gcc
# Compilateur
SRC = main.c

all:
	@echo "**** TEST ****"
	$(CC) -o $(BIN) $(FLAGS) -I$(INC) $(SRC) -L$(LIBDIR) $(LIBS) 

clean:
	rm -f $(BIN)

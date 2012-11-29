# UTILISATION
# Dans le dossier contenant le makefile :
#	make nom_exectuable (compilation)
#	./nom_executable (exécution)

# SYNTAXE
# cible: dépendance
#	commande
# cible = nom du fichier que l'on veut générer
# dépendance = sous-cible (fichier source .c ou objet .o)
# commande = action à mener pour générer la cible à partir des dépendances

# VARIABLES INTERNES AU MAKEFILE
# $@ = nom de la cible
# $< = première dépendance de la liste des dépendances
# $^ = toutes les dépendances
# $? = dépendances plus récentes que la cible

# AUTRES VARIABLES (créées)
# Utilisation : $(nom_variable)
# Compilateur C
CC = gcc
# Options de compilation
FLAGS = -W -Wall -ansi -pedantic
# Options de l'édition des liens
LDFLAGS =
# Nom de l'exécutable à générer
EXEC = hello
# Liste des fichiers sources du projet
SRC = src/hello.c src/main.c
# Liste des fichiers objets
OBJ = $(SRC:.c =.o)


# Ensemble des exécutables à produire
all: $(EXEC)

# Génération de l'exécutable hello, qui dépend des objets hello.o et main.o
hello: $(OBJ)
	$(CC) -o $@ $^
#hello: hello.o main.o
	#gcc -o hello hello.o main.o

# Génération de l'objet hello.o, qui dépend du fichier source hello.c
hello.o: hello.c
	$(CC) -o $@ -c $< $(FLAGS)
	#gcc -o hello.o -c hello.c -W -Wall -ansi -pedantic

# Génération de l'objet main.o, qui dépend du fichier source main.c et du fichier d'entête hello.h (inclu dans main.c)
main.o: main.c hello.h
	$(CC) -o $@ -c $< $(FLAGS)
	#gcc -o main.o -c main.c -W -Wall -ansi -pedantic

# Suppression des fichiers intermédiaires générés par make
clean:
	rm -rf *.o

# Suppression de tout ce qui peut être régénéré, permet une reconstruction complète du projet
mrproper: clean
	rm -rf $(EXEC)

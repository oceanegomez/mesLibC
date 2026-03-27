#Définition des constantes
LIB_DIR = ../mesLibC

#Exercice 14
SRC = src
BUILD = build

#Exercice 10 : 
help : 
	@echo '=== Cible disponible ==='
	@echo '  === lib : compile la librairie util_string'
	@echo "  === help : affichage de l'aide"
	@echo '  === init : Création des dossiers src et build ==='

#alias pour simplifier l'accès à la cible
lib : $(LIB_DIR)/util_string.o

#Exercice 3 : compilation de la librairie util string
$(LIB_DIR)/util_string.o : $(LIB_DIR)/util_string.c 
	@echo '=== Compilation de .o de util_string ==='
	gcc -c -Wall $(LIB_DIR)/util_string.c -o $(LIB_DIR)/util_string.o

# Règle demandée à l'exercice 14
init :
	@echo '=== Création des dossiers src et build ==='
	mkdir -p $(SRC) $(BUILD)




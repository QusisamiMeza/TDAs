CC = gcc
CFLAGS = -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g

VALGRIND = valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all

FORMAT = clang-format -i -style=file

ZIP = zip tp_lista.zip

ARCHIVO_EJEMPLO = ejemplos/largo.csv

ARGS_BUSCAR_NOMBRE = $(ARCHIVO_EJEMPLO) buscar nombre A
ARGS_BUSCAR_ID = $(ARCHIVO_EJEMPLO) buscar id 1

LISTA = src/lista.c
LISTA_H = src/lista.h
COLA = src/cola.c
COLA_H = src/cola.h
PILA = src/pila.c
PILA_H = src/pila.h
AUX = src/auxiliares_tp1.c
AUX_H = src/auxiliares_tp1.h
BUSCAR_POKEMONES_H = src/busqueda_pokemones.h
BUSCAR_POKEMONES = src/busqueda_pokemones.c
POKEMON_UTILS = src/pokemon_utils.c
POKEMON_UTILS_H = src/pokemon_utils.h
COMANDOS = src/comandos.c
COMANDOS_H = src/comandos.h
TP1 = src/tp1.c
TP1_H = src/tp1.h
EJEMPLOS_CSV = ejemplos/*.csv

MAIN = main.c
TEST = pruebas_alumno.c

PA2= pa2m.h
MAKE = makefile
README = README.md
IMG = img/*
ENUNCIADO = Enunciado.md

TEST_BIN = test
MAIN_BIN = main

compilar-tp:
	$(CC) $(CFLAGS) $(MAIN) $(COMANDOS) $(TP1) $(AUX) $(LISTA) $(BUSCAR_POKEMONES) $(POKEMON_UTILS) -o $(MAIN_BIN)


buscar-nombre: compilar-tp
	./$(MAIN_BIN) $(ARGS_BUSCAR_NOMBRE)

buscar-id: compilar-tp
	./$(MAIN_BIN) $(ARGS_BUSCAR_ID)

valgrind-buscar-nombre: compilar-tp
	$(VALGRIND) ./$(MAIN_BIN) $(ARGS_BUSCAR_NOMBRE)

valgrind-buscar-id: compilar-tp
	$(VALGRIND) ./$(MAIN_BIN) $(ARGS_BUSCAR_ID)

compilar-test:
	$(CC) $(CFLAGS) $(TEST) $(LISTA) $(COLA) $(PILA) -o $(TEST_BIN)

test: compilar-test	
	$(VALGRIND) ./$(TEST_BIN)

format:
	$(FORMAT) $(TEST) $(MAIN) $(LISTA) $(COLA) $(PILA) $(COMANDOS) $(COMANDOS_H) $(BUSCAR_POKEMONES) $(BUSCAR_POKEMONES_H) $(POKEMON_UTILS) $(POKEMON_UTILS_H)

zip:
	$(ZIP) $(EJEMPLOS_CSV) $(LISTA) $(LISTA_H) $(TP1) $(TP1_H) $(COLA) $(COLA_H) $(PILA) $(PILA_H) $(AUX) $(AUX_H) $(COMANDOS) $(COMANDOS_H) $(BUSCAR_POKEMONES) $(POKEMON_UTILS) $(BUSCAR_POKEMONES_H) $(POKEMON_UTILS_H) $(IMG) $(MAIN) $(PA2) $(ENUNCIADO) $(MAKE) $(README) $(TEST)

CC = gcc
CFLAGS = -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g
VALGRIND = valgrind --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes
FORMAT = clang-format -i -style=file
ZIP = zip tp_abb.zip


ARGS_BUSCAR_NOMBRE = $(archivo) buscar nombre $(nombre) 
ARGS_BUSCAR_ID = $(archivo) buscar id $(id)

ABB = src/abb.c
ABB_H = src/abb.h
ABB_PRIV_H = src/abb_estructura_privada.h
NODO = src/nodo_abb.c
NODO_H = src/nodo_abb.h

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

ARCHIVOS_TP1 = $(TP1) $(TP1_H) $(AUX) $(AUX_H)
ARCHIVOS_TP_ACTUAL = $(NODO) $(NODO_H) $(ABB) $(ABB_H) $(ABB_PRIV_H)
ARCHIVOS_CTX = $(EJEMPLOS_CSV) $(IMG)  $(PA2) $(ENUNCIADO) $(MAKE) $(README) $(TEST)
ARCHIVOS_MAIN = $(MAIN) $(COMANDOS) $(COMANDOS_H) $(BUSCAR_POKEMONES) $(POKEMON_UTILS) $(BUSCAR_POKEMONES_H) $(POKEMON_UTILS_H) 

compilar-tp:
	$(CC) $(CFLAGS) $(MAIN) src/*.c -o $(MAIN_BIN)

buscar-nombre: compilar-tp
	./$(MAIN_BIN) $(ARGS_BUSCAR_NOMBRE)

buscar-id: compilar-tp
	./$(MAIN_BIN) $(ARGS_BUSCAR_ID)

valgrind-buscar-nombre: compilar-tp
	$(VALGRIND) ./$(MAIN_BIN) $(ARGS_BUSCAR_NOMBRE)

valgrind-buscar-id: compilar-tp
	$(VALGRIND) ./$(MAIN_BIN) $(ARGS_BUSCAR_ID)

compilar-test:
	$(CC) $(CFLAGS) $(TEST) $(ABB) $(NODO) -o $(TEST_BIN)

test: compilar-test	
	$(VALGRIND) ./$(TEST_BIN)

format:
	$(FORMAT) $(TEST) $(MAIN) $(ABB) $(NODO) $(NODO_H) $(COMANDOS) $(COMANDOS_H) $(BUSCAR_POKEMONES) $(BUSCAR_POKEMONES_H) $(POKEMON_UTILS) $(POKEMON_UTILS_H)

zip: format
	$(ZIP) $(ARCHIVOS_TP_ACTUAL) $(ARCHIVOS_TP1) $(ARCHIVOS_MAIN) $(ARCHIVOS_CTX)

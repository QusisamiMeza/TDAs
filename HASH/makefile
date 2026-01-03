VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes
CFLAGS =-std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g
CC = gcc

TEST_BIN = pruebas_alumno
MAIN_BIN = main

FORMAT = clang-format -i -style=file
ZIP = zip tp_hash.zip

TEST_C = pruebas_alumno.c

ARCH_HASH = src/hash.c src/tabla_pares.c src/tabla_pares.h
ARCH_CTX_MAIN = src/comandos.c src/busqueda_pokemones.c
ARGS_BUSCAR_NOMBRE = $(archivo) buscar nombre $(nombre) 
ARGS_BUSCAR_ID = $(archivo) buscar id $(id)
ARCH_VARIOS = Enunciado.md README.md makefile pa2m.h pruebas_alumno.c

all: clean valgrind-alumno

valgrind-alumno: pruebas_alumno
	valgrind $(VALGRIND_FLAGS) ./pruebas_alumno

pruebas_alumno: src/*.c pruebas_alumno.c
	$(CC) $(CFLAGS) src/*.c $(TEST_C) -o pruebas_alumno

clean:
	rm -f pruebas_alumno 

format:
	$(FORMAT) $(TEST_C) main.c $(ARCH_HASH) $(ARCH_CTX_MAIN)

zip: src/*.c src/*.h format
	$(ZIP) src/*.c src/*.h img/* ejemplos/*.csv main.c $(ARCH_VARIOS)

compilar-tp:
	$(CC) $(CFLAGS) main.c src/*.c -o $(MAIN_BIN)

buscar-nombre: compilar-tp
	./$(MAIN_BIN) $(ARGS_BUSCAR_NOMBRE)

buscar-id: compilar-tp
	./$(MAIN_BIN) $(ARGS_BUSCAR_ID)

valgrind-buscar-nombre: compilar-tp
	$(VALGRIND) ./$(MAIN_BIN) $(ARGS_BUSCAR_NOMBRE)

valgrind-buscar-id: compilar-tp
	$(VALGRIND) ./$(MAIN_BIN) $(ARGS_BUSCAR_ID)
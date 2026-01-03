#ifndef POKEMON_UTILS_H
#define POKEMON_UTILS_H
#define FORMATO_POKEMON          \
	"===== Pokémon =====\n" \
	"ID      : %d\n"         \
	"Nombre  : %s\n"         \
	"Tipo    : %s\n"         \
	"Ataque  : %d\n"         \
	"Defensa : %d\n"         \
	"Velocidad: %d\n"        \
	"==================\n"

#include "tp1.h"
#include <stdbool.h>

/**
 * POST:
 * Convierte todos los caracteres de 'string' a minúsculas.
 */
char *convertir_string_a_minusculas(char *string);

/**
 * PRE:
 * `pokemon` debe ser valida
 * POST:
 * Imprime el pokemon por pantalla
 */
void imprimir_pokemon(struct pokemon *pokemon);

// Compara dos pokemones por su nombre. Cero en caso de ser iguales.
int comparar_nombre(const void *a, const void *b);

// Compara dos elementos por su ID. Cero en caso de ser iguales.
int comparar_id(const void *a, const void *b);

#endif
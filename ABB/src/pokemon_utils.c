#include "pokemon_utils.h"
#include <ctype.h>
#include <stdio.h>
#include "auxiliares_tp1.h"

char *convertir_string_a_minusculas(char *string)
{
	if (!string) {
		return NULL;
	}
	for (int i = 0; string[i] != '\0'; i++) {
		string[i] = (char)tolower((unsigned char)string[i]);
	}
	return string;
}

void imprimir_pokemon(struct pokemon *pokemon)
{
	if (!pokemon) {
		return;
	}

	printf(FORMATO_POKEMON, pokemon->id, pokemon->nombre,
	       obtener_string_tipo(pokemon->tipo), pokemon->ataque,
	       pokemon->defensa, pokemon->velocidad);
}

int comparar_nombre(const void *a, const void *b)
{
	const struct pokemon *pok_1 = a;
	const struct pokemon *pok_2 = b;
	return strcmp(pok_1->nombre, pok_2->nombre);
}

int comparar_id(const void *a, const void *b)
{
	const struct pokemon *pok_1 = a;
	const struct pokemon *pok_2 = b;
	return pok_1->id - pok_2->id;
}
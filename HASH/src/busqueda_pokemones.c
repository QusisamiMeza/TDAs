#include "busqueda_pokemones.h"
#include "pokemon_utils.h"
#include "hash.h"
#include <string.h>
#include <stdio.h>

struct buscar {
	hash_t *hash_pokemones;
	tp1_t *tp1;
	tipo_seleccion_t tipo_seleccion;
	char *valor_buscado;
};

tipo_seleccion_t asignar_tipo_seleccion(char *seleccion)
{
	if (!seleccion) {
		return SELECCION_INVALIDA;
	}
	char *seleccion_string = convertir_string_a_minusculas(seleccion);
	if (strcmp(seleccion_string, COD_ID) == 0) {
		return ID;
	} else if (strcmp(seleccion_string, COD_NOMBRE) == 0) {
		return NOMBRE;
	}
	return SELECCION_INVALIDA;
}

bool agregar_pokemon_hash_nombre(struct pokemon *p, void *extra)
{
	hash_t *hash = extra;
	return hash_insertar(hash, p->nombre, p, NULL);
}

bool agregar_pokemon_hash_id(struct pokemon *p, void *extra)
{
	hash_t *hash = extra;
	char clave_id[32];
	snprintf(clave_id, sizeof(clave_id), "%d", p->id);
	return hash_insertar(hash, clave_id, p, NULL);
}

size_t rellenar_hash(tipo_seleccion_t seleccion, hash_t *hash, tp1_t *tp1)
{
	size_t cantidad_añadidos = 0;
	switch (seleccion) {
	case ID:
		cantidad_añadidos = tp1_con_cada_pokemon(
			tp1, agregar_pokemon_hash_id, hash);
		break;
	case NOMBRE:
		cantidad_añadidos = tp1_con_cada_pokemon(
			tp1, agregar_pokemon_hash_nombre, hash);
		break;
	case SELECCION_INVALIDA:
		break;
	}
	return cantidad_añadidos;
}

void *crear_datos_buscar(char *arch_tp1, char *seleccion, char *valor_buscado)
{
	if (!arch_tp1 || !seleccion) {
		return NULL;
	}

	buscar_t *datos = malloc(sizeof(buscar_t));
	if (!datos) {
		return NULL;
	}

	datos->tp1 = tp1_leer_archivo(arch_tp1);
	if (!datos->tp1) {
		free(datos);
		return NULL;
	}

	datos->tipo_seleccion = asignar_tipo_seleccion(seleccion);
	datos->hash_pokemones = hash_crear(tp1_cantidad(datos->tp1));
	if (!datos->hash_pokemones) {
		tp1_destruir(datos->tp1);
		free(datos);
		return NULL;
	}

	if (rellenar_hash(datos->tipo_seleccion, datos->hash_pokemones,
			  datos->tp1) != tp1_cantidad(datos->tp1)) {
		tp1_destruir(datos->tp1);
		hash_destruir(datos->hash_pokemones);
		free(datos);
		return NULL;
	}

	datos->valor_buscado = valor_buscado;
	return datos;
}

struct pokemon *realizar_busqueda(buscar_t *datos)
{
	if (!datos) {
		return NULL;
	}

	return (struct pokemon *)hash_buscar(datos->hash_pokemones,
					     datos->valor_buscado);
}

void destruir_busqueda(buscar_t *datos)
{
	if (!datos) {
		return;
	}

	tp1_destruir(datos->tp1);
	hash_destruir(datos->hash_pokemones);
	free(datos);
}
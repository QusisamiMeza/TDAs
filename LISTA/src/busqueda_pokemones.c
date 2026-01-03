#include "busqueda_pokemones.h"
#include "pokemon_utils.h"
#include <string.h>

bool agregar_pokemon_lista(struct pokemon *p, void *extra)
{
	lista_t *lista = extra;
	return lista_agregar(lista, p);
}

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

	datos->lista_pokemones = lista_crear();
	if (!datos->lista_pokemones) {
		tp1_destruir(datos->tp1);
		free(datos);
		return NULL;
	}

	size_t cant_pok_lista = tp1_con_cada_pokemon(
		datos->tp1, agregar_pokemon_lista, datos->lista_pokemones);
	if (cant_pok_lista != tp1_cantidad(datos->tp1)) {
		tp1_destruir(datos->tp1);
		lista_destruir(datos->lista_pokemones);
		free(datos);
		return NULL;
	}

	datos->tipo_seleccion = asignar_tipo_seleccion(seleccion);
	datos->valor_buscado = valor_buscado;
	return datos;
}

struct pokemon *realizar_busqueda(buscar_t *datos)
{
	if (!datos) {
		return NULL;
	}

	int posicion = -1;
	if (datos->tipo_seleccion == ID) {
		int id = atoi(datos->valor_buscado);
		posicion = lista_buscar_posicion(datos->lista_pokemones, &id,
						 es_id_igual);
	} else if (datos->tipo_seleccion == NOMBRE) {
		posicion = lista_buscar_posicion(datos->lista_pokemones,
						 datos->valor_buscado,
						 es_nombre_igual);
	} else if (datos->tipo_seleccion == SELECCION_INVALIDA) {
		return NULL;
	}

	if (posicion == -1) {
		return NULL;
	}

	return (struct pokemon *)lista_buscar_elemento(datos->lista_pokemones,
						       (size_t)posicion);
}

void destruir_busqueda(buscar_t *datos)
{
	if (!datos) {
		return;
	}

	tp1_destruir(datos->tp1);
	lista_destruir(datos->lista_pokemones);
	free(datos);
}
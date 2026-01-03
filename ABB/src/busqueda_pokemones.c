#include "busqueda_pokemones.h"
#include "pokemon_utils.h"
#include "abb.h"
#include <string.h>

struct buscar {
	abb_t *abb_pokemones;
	tp1_t *tp1;
	tipo_seleccion_t tipo_seleccion;
	char *valor_buscado;
};

bool agregar_pokemon_abb(struct pokemon *p, void *extra)
{
	abb_t *abb = extra;
	return abb_insertar(abb, p);
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
	datos->tipo_seleccion = asignar_tipo_seleccion(seleccion);
	switch (datos->tipo_seleccion) {
	case ID:
		datos->abb_pokemones = abb_crear(comparar_id);
		break;
	case NOMBRE:
		datos->abb_pokemones = abb_crear(comparar_nombre);
		break;
	case SELECCION_INVALIDA:
		datos->abb_pokemones = NULL;
		break;
	}

	if (!datos->abb_pokemones) {
		tp1_destruir(datos->tp1);
		free(datos);
		return NULL;
	}

	size_t cant_pok = tp1_con_cada_pokemon(datos->tp1, agregar_pokemon_abb,
					       datos->abb_pokemones);
	if (cant_pok != tp1_cantidad(datos->tp1)) {
		tp1_destruir(datos->tp1);
		abb_destruir(datos->abb_pokemones);
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

	struct pokemon pokemon_buscado;

	if (datos->tipo_seleccion == ID) {
		pokemon_buscado.id = atoi(datos->valor_buscado);
		return (struct pokemon *)abb_buscar(datos->abb_pokemones,
						    &pokemon_buscado);
	}

	pokemon_buscado.nombre = datos->valor_buscado;
	return (struct pokemon *)abb_buscar(datos->abb_pokemones,
					    &pokemon_buscado);
}

void destruir_busqueda(buscar_t *datos)
{
	if (!datos) {
		return;
	}

	tp1_destruir(datos->tp1);
	abb_destruir(datos->abb_pokemones);
	free(datos);
}
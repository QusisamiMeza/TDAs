#include "comandos.h"
#include "auxiliares_tp1.h"
#include "busqueda_pokemones.h"
#include "pokemon_utils.h"

const int CANT_TOTAL_ARG_BUSCAR = 5;
const int INDX_ARCH = 1;
const int INDX_OPERACION = 2;
const int INDX_SELECCION = 3;
const int INDX_VALOR_BUSCADO = 4;

enum operacion_t { BUSCAR, OP_INVALIDA };

/**
 * PRE:
 * 'operacion' debe ser un puntero válido a una cadena de caracteres.
 * POST:
 * Devuelve el valor de tipo `operacion_t` correspondiente al string. 
 * Devuelve `OP_INVALIDA` si el string no coincide con ninguna operación conocida.
 */
operacion_t asignar_operacion(char *operacion)
{
	if (!operacion) {
		return OP_INVALIDA;
	}

	char *operacion_string = convertir_string_a_minusculas(operacion);
	if (strcmp(operacion_string, COD_BUSCAR) == 0) {
		return BUSCAR;
	}

	return OP_INVALIDA;
}

comando_t *crear_comando(int argc, char *argv[])
{
	comando_t *comando = malloc(sizeof(comando_t));
	if (!comando) {
		return NULL;
	}

	comando->operacion = asignar_operacion(argv[INDX_OPERACION]);

	if (comando->operacion == BUSCAR && argc == CANT_TOTAL_ARG_BUSCAR) {
		char *arch_tp1 = argv[INDX_ARCH];
		char *seleccion = argv[INDX_SELECCION];
		char *valor_buscado = argv[INDX_VALOR_BUSCADO];
		comando->datos =
			crear_datos_buscar(arch_tp1, seleccion, valor_buscado);
	} else if (comando->operacion == OP_INVALIDA) {
		free(comando);
		return NULL;
	}

	if (!comando->datos) {
		free(comando);
		return NULL;
	}

	return comando;
}

bool ejecutar_comando(comando_t *comando)
{
	if (!comando) {
		return false;
	}

	if (comando->operacion == BUSCAR) {
		struct pokemon *pokemon_buscado =
			realizar_busqueda((buscar_t *)comando->datos);
		if (pokemon_buscado != NULL) {
			imprimir_pokemon(pokemon_buscado);
		} else {
			printf("No se encontró pokemon.\n");
		}
		return true;
	}

	return false;
}

void destruir_comando(comando_t *comando)
{
	if (!comando) {
		return;
	}

	if (comando->operacion == BUSCAR) {
		destruir_busqueda((buscar_t *)comando->datos);
	}

	free(comando);
}
#ifndef BUSQUEDA_POKEMONES_H_
#define BUSQUEDA_POKEMONES_H_
#define COD_BUSCAR "buscar"
#define COD_ID "id"
#define COD_NOMBRE "nombre"
#include "tp1.h"
#include "lista.h"

typedef enum tipo_seleccion { ID, NOMBRE, SELECCION_INVALIDA } tipo_seleccion_t;

typedef struct buscar {
	lista_t *lista_pokemones;
	tp1_t *tp1;
	tipo_seleccion_t tipo_seleccion;
	char *valor_buscado;
} buscar_t;

/**
 * PRE:
 * 
 * POST:
 * Devuelve un puntero a una estructura `buscar_t` con los datos inicializados o NULL en caso de error.
 */
void *crear_datos_buscar(char *arch_tp1, char *seleccion, char *valor_buscado);

/**
 * PRE:
 * 'seleccion' debe ser un puntero válido a una cadena de caracteres.
 * POST:
 * Devuelve el valor de tipo `tipo_seleccion_t` correspondiente al string.
 * Devuelve `INVALIDA` si el string no coincide con ningún tipo válido o si es nula.
 */
tipo_seleccion_t asignar_tipo_seleccion(char *seleccion);

/**
 * PRE:
 * 'datos' debe ser un puntero válido a `buscar_t`.
 * POST:
 * Busca un Pokémon en la lista según el tipo de selección y lo devuelve si se encuentra.
 */
struct pokemon *realizar_busqueda(buscar_t *datos);

/**
 * POST:
 * Destruye toda la informacion relacionada con buscar_t
 */
void destruir_busqueda(buscar_t *datos);

#endif // BUSQUEDA_POKEMONES_H_
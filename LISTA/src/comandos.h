#ifndef COMANDOS_H_
#define COMANDOS_H_
#include "tp1.h"
#include "lista.h"

typedef int operacion_t;

typedef struct comando {
	operacion_t operacion;
	void *datos;
} comando_t;

/**
 * PRE:
 * 'argc' y 'argv' deben ser válidos.
 * POST:
 * Crea un comando (`comando_t`) con la operación y los datos asignados. Devuelve NULL si la operación es inválida.
 */
comando_t *crear_comando(int argc, char *argv[]);

/**
 * PRE:
 * Para una ejecucion exitosa `comando` debe estar creado correctamente.
 * POST:
 * Realiza la operacion segun el campo `operacion_t operacion`, retorna true si se realizó con exito, caso
 * contrario retorna false.
 */
bool ejecutar_comando(comando_t *comando);

/**
 * POST:
 * Destruye toda la informacion relacionada con comando_t
 */
void destruir_comando(comando_t *comando);

#endif // COMANDOS_H_
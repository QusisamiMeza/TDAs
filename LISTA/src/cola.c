#include "cola.h"
#include "lista.h"

struct cola {
	lista_t *elementos; //primer elemento = frente
}; //ultimo elemento = final

cola_t *cola_crear()
{
	cola_t *nueva_cola = malloc(sizeof(cola_t));
	if (!nueva_cola) {
		return NULL;
	}
	nueva_cola->elementos = lista_crear();
	if (!nueva_cola->elementos) {
		free(nueva_cola);
		return NULL;
	}
	return nueva_cola;
}

bool cola_encolar(cola_t *cola, void *elemento)
{
	if (!cola) {
		return false;
	}
	return lista_agregar(cola->elementos, elemento);
}

void *cola_desencolar(cola_t *cola)
{
	if (!cola || lista_vacia(cola->elementos)) {
		return NULL;
	}
	return lista_eliminar_elemento(cola->elementos, 0);
}

void *cola_ver_primero(cola_t *cola)
{
	if (!cola || lista_vacia(cola->elementos)) {
		return NULL;
	}
	return lista_buscar_elemento(cola->elementos, 0);
}

size_t cola_cantidad(cola_t *cola)
{
	if (!cola) {
		return 0;
	}
	return lista_cantidad(cola->elementos);
}

void cola_destruir(cola_t *cola)
{
	if (!cola) {
		return;
	}
	lista_destruir(cola->elementos);
	free(cola);
}
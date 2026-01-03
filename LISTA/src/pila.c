#include "pila.h"
#include "lista.h"

struct pila {
	lista_t *elementos; //primer elemento = tope (ultimo agregado)
}; //ultimo elemento = primer elemento

pila_t *pila_crear()
{
	pila_t *nueva_pila = malloc(sizeof(pila_t));
	if (!nueva_pila) {
		return NULL;
	}
	nueva_pila->elementos = lista_crear();
	if (!nueva_pila->elementos) {
		free(nueva_pila);
		return NULL;
	}
	return nueva_pila;
}

bool pila_apilar(pila_t *pila, void *elemento)
{
	if (!pila) {
		return false;
	}
	if (lista_vacia(pila->elementos)) {
		return lista_agregar(pila->elementos, elemento);
	}
	return lista_insertar(pila->elementos, elemento, 0);
}

void *pila_desapilar(pila_t *pila)
{
	if (!pila || lista_vacia(pila->elementos)) {
		return NULL;
	}
	return lista_eliminar_elemento(pila->elementos, 0);
}

void *pila_ver_primero(pila_t *pila)
{
	if (!pila || lista_vacia(pila->elementos)) {
		return NULL;
	}
	return lista_buscar_elemento(pila->elementos, 0);
}

size_t pila_cantidad(pila_t *pila)
{
	if (!pila) {
		return 0;
	}
	return lista_cantidad(pila->elementos);
}

void pila_destruir(pila_t *pila)
{
	if (!pila) {
		return;
	}
	lista_destruir(pila->elementos);
	free(pila);
}
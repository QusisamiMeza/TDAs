#include "nodo_abb.h"

// Devuelve el nodo con el mayor valor del subárbol dado (predecesor inorden).
nodo_t *reemplazar_por_predecesor(nodo_t *nodo)
{
	if (!nodo) {
		return NULL;
	}
	if (!nodo->der) {
		return nodo;
	}

	return reemplazar_por_predecesor(nodo->der);
}

nodo_t *nodo_insertar(nodo_t *nodo,
		      int (*comparador)(const void *, const void *), void *dato)
{
	if (nodo == NULL) {
		nodo_t *nodo_nuevo = calloc(1, sizeof(nodo_t));
		if (!nodo_nuevo) {
			return NULL;
		}
		nodo_nuevo->dato = dato;
		return nodo_nuevo;
	}

	int resultado_cmp = comparador(nodo->dato, dato);
	if (resultado_cmp > 0) {
		nodo->izq = nodo_insertar(nodo->izq, comparador, dato);
	} else {
		nodo->der = nodo_insertar(nodo->der, comparador, dato);
	}
	return nodo;
}

nodo_t *obtener_nodo(nodo_t *nodo,
		     int (*comparador)(const void *, const void *), void *dato)
{
	if (!nodo || !comparador) {
		return NULL;
	}
	int resultado_cmp = comparador(nodo->dato, dato);

	if (resultado_cmp == 0) {
		return nodo;
	}

	if (resultado_cmp > 0) {
		return obtener_nodo(nodo->izq, comparador, dato);
	} else {
		return obtener_nodo(nodo->der, comparador, dato);
	}
}

nodo_t *eliminar_nodo(nodo_t *nodo,
		      int (*comparador)(const void *, const void *), void *dato)
{
	if (!comparador || !nodo) {
		return NULL;
	}

	int resul_cmp = comparador(nodo->dato, dato);

	if (resul_cmp == 0) {
		if (nodo->izq != NULL && nodo->der != NULL) {
			nodo_t *nodo_predecesor =
				reemplazar_por_predecesor(nodo->izq);
			nodo->dato = nodo_predecesor->dato;
			nodo->izq = eliminar_nodo(nodo->izq, comparador,
						  nodo_predecesor->dato);
			return nodo;
		}

		nodo_t *unico_hijo = nodo->der;
		if (!unico_hijo) {
			unico_hijo = nodo->izq;
		}
		free(nodo);
		return unico_hijo;
	}

	if (resul_cmp > 0) {
		nodo->izq = eliminar_nodo(nodo->izq, comparador, dato);
	} else {
		nodo->der = eliminar_nodo(nodo->der, comparador, dato);
	}
	return nodo;
}

bool recorrer_nodos_inorden(nodo_t *nodo, bool (*f)(void *, void *),
			    void *extra, size_t *afectados)
{
	if (!nodo || !f) {
		return true;
	}

	if (recorrer_nodos_inorden(nodo->izq, f, extra, afectados) == false) {
		return false;
	}

	(*afectados)++;
	if (!f(nodo->dato, extra)) {
		return false;
	}

	if (recorrer_nodos_inorden(nodo->der, f, extra, afectados) == false) {
		return false;
	}

	return true;
}

bool recorrer_nodos_preorden(nodo_t *nodo, bool (*f)(void *, void *),
			     void *extra, size_t *afectados)
{
	if (!nodo || !f) {
		return true;
	}

	(*afectados)++;
	if (!f(nodo->dato, extra)) {
		return false;
	}
	if (!recorrer_nodos_preorden(nodo->izq, f, extra, afectados) ||
	    !recorrer_nodos_preorden(nodo->der, f, extra, afectados)) {
		return false;
	}

	return true;
}

bool recorrer_nodos_postorden(nodo_t *nodo, bool (*f)(void *, void *),
			      void *extra, size_t *afectados)
{
	if (!nodo || !f) {
		return true;
	}

	if (!recorrer_nodos_postorden(nodo->izq, f, extra, afectados) ||
	    !recorrer_nodos_postorden(nodo->der, f, extra, afectados)) {
		return false;
	}

	(*afectados)++;
	if (!f(nodo->dato, extra)) {
		return false;
	}

	return true;
}

void destruir_nodo(nodo_t *nodo, void (*destructor)(void *))
{
	if (!nodo) {
		return;
	}

	destruir_nodo(nodo->izq, destructor);
	destruir_nodo(nodo->der, destructor);

	if (destructor) {
		destructor(nodo->dato);
	}

	free(nodo);
}
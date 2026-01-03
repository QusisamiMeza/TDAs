#include "abb.h"
#include "abb_estructura_privada.h"
#include "nodo_abb.h"

typedef struct vector_aux {
	void **vector;
	size_t i;
	size_t maximo;
} vector_aux_t;

abb_t *abb_crear(int (*comparador)(const void *, const void *))
{
	if (!comparador) {
		return NULL;
	}

	abb_t *abb = calloc(1, sizeof(abb_t));
	if (!abb) {
		return NULL;
	}

	abb->comparador = comparador;
	return abb;
}

bool abb_esta_vacio(abb_t *abb)
{
	if (!abb) {
		return true;
	}

	return abb->cantidad == 0 && abb->raiz == NULL;
}

bool abb_insertar(abb_t *abb, void *dato)
{
	if (!abb) {
		return false;
	}

	abb->raiz = nodo_insertar(abb->raiz, abb->comparador, dato);

	if (abb->raiz == NULL) {
		return false;
	}

	abb->cantidad++;

	return true;
}

bool abb_existe(abb_t *abb, void *dato)
{
	if (abb_esta_vacio(abb)) {
		return false;
	}

	if (!obtener_nodo(abb->raiz, abb->comparador, dato)) {
		return false;
	}

	return true;
}

void *abb_buscar(abb_t *abb, void *dato)
{
	if (!abb_existe(abb, dato)) {
		return NULL;
	}

	nodo_t *nodo_buscado = obtener_nodo(abb->raiz, abb->comparador, dato);

	return nodo_buscado->dato;
}

void *abb_eliminar(abb_t *abb, void *dato)
{
	if (!abb) {
		return NULL;
	}

	nodo_t *nodo = obtener_nodo(abb->raiz, abb->comparador, dato);
	if (!nodo) {
		return NULL;
	}

	void *dato_aux = nodo->dato;
	abb->raiz = eliminar_nodo(abb->raiz, abb->comparador, dato);
	abb->cantidad--;

	return dato_aux;
}

void *abb_raiz(abb_t *abb)
{
	if (abb_esta_vacio(abb)) {
		return NULL;
	}

	return abb->raiz->dato;
}

size_t abb_cantidad(abb_t *abb)
{
	if (!abb) {
		return 0;
	}

	return abb->cantidad;
}

size_t abb_con_cada_elemento(abb_t *abb, enum abb_recorrido tipo_recorrido,
			     bool (*f)(void *, void *), void *extra)
{
	if (!f || abb_esta_vacio(abb)) {
		return 0;
	}

	size_t nodos_afectados = 0;

	switch (tipo_recorrido) {
	case ABB_INORDEN:
		recorrer_nodos_inorden(abb->raiz, f, extra, &nodos_afectados);
		break;
	case ABB_PREORDEN:
		recorrer_nodos_preorden(abb->raiz, f, extra, &nodos_afectados);
		break;
	case ABB_POSTORDEN:
		recorrer_nodos_postorden(abb->raiz, f, extra, &nodos_afectados);
		break;
	}
	return nodos_afectados;
}

//Devuelve true si se pudo agregar el dato al vector, false en caso contrario
bool agregar_dato_en_vector(void *dato, void *vector)
{
	if (!vector) {
		return false;
	}

	vector_aux_t *aux = vector;
	if (aux->i >= aux->maximo) {
		return false;
	}
	aux->vector[aux->i] = dato;
	aux->i++;
	return true;
}

size_t abb_vectorizar(abb_t *abb, enum abb_recorrido tipo_recorrido,
		      size_t cant, void **vector)
{
	if (abb_esta_vacio(abb) || cant == 0 || !vector) {
		return 0;
	}

	vector_aux_t aux;
	aux.vector = vector;
	aux.i = 0;
	aux.maximo = cant;
	abb_con_cada_elemento(abb, tipo_recorrido, agregar_dato_en_vector,
			      &aux);

	return aux.i;
}

void abb_destruir(abb_t *abb)
{
	abb_destruir_todo(abb, NULL);
}

void abb_destruir_todo(abb_t *abb, void (*destructor)(void *))
{
	if (!abb) {
		return;
	}
	destruir_nodo(abb->raiz, destructor);
	free(abb);
}

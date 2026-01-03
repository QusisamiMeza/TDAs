#ifndef NODO_ABB_H_
#define NODO_ABB_H_
#include "abb_estructura_privada.h"
#include <stdlib.h>
#include <stdbool.h>

// Inserta un dato en el árbol según el comparador y devuelve la nueva raíz.
nodo_t *nodo_insertar(nodo_t *nodo,
		      int (*comparador)(const void *, const void *),
		      void *dato);

// Busca un nodo que contenga el dato y lo devuelve. Devuelve NULL si no existe o por error.
nodo_t *obtener_nodo(nodo_t *nodo,
		     int (*comparador)(const void *, const void *), void *dato);

// Recorre los nodos en orden inorden aplicando la función f a cada dato.
bool recorrer_nodos_inorden(nodo_t *nodo, bool (*f)(void *, void *),
			    void *extra, size_t *afectados);

// Recorre los nodos en orden preorden aplicando la función f a cada dato.
bool recorrer_nodos_preorden(nodo_t *nodo, bool (*f)(void *, void *),
			     void *extra, size_t *afectados);

// Recorre los nodos en orden postorden aplicando la función f a cada dato.
bool recorrer_nodos_postorden(nodo_t *nodo, bool (*f)(void *, void *),
			      void *extra, size_t *afectados);

// Elimina el nodo que contiene el dato y devuelve la nueva raíz del árbol.
nodo_t *eliminar_nodo(nodo_t *nodo,
		      int (*comparador)(const void *, const void *),
		      void *dato);

// Libera la memoria del nodo y destruye su dato con el destructor (si existe).
void destruir_nodo(nodo_t *nodo, void (*destructor)(void *));

#endif // NODO_ABB_H_
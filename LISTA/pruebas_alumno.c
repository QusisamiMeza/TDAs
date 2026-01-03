#include "pa2m.h"
#include "src/lista.h"
#include "src/cola.h"
#include "src/pila.h"

void lista_recien_creada_se_crea_exitosamente_y_vacia()
{
	lista_t *nueva_lista = lista_crear();
	pa2m_afirmar(nueva_lista != NULL, "Se creó exitosamente una lista.");
	pa2m_afirmar(lista_vacia(nueva_lista) &&
			     lista_cantidad(nueva_lista) == 0,
		     "La lista recien creada está vacía.");
	lista_destruir(nueva_lista);
}

void dada_lista_vacia_se_verifica_que_esta_vacia()
{
	lista_t *nueva_lista = lista_crear();
	pa2m_afirmar(lista_vacia(nueva_lista) &&
			     lista_cantidad(nueva_lista) == 0,
		     "En una lista vacia, lista_vacia() da true");
	lista_destruir(nueva_lista);
}

void dada_lista_nula_se_verifica_que_es_vacio()
{
	lista_t *lista_nula = NULL;
	pa2m_afirmar(lista_vacia(lista_nula),
		     "Una lista nula siempre es vacia.");
}

void dada_lista_con_un_elemento_no_da_vacio()
{
	lista_t *nueva_lista = lista_crear();
	int valor = 1;
	lista_agregar(nueva_lista, &valor);
	pa2m_afirmar(!lista_vacia(nueva_lista),
		     "Una lista con un elemento no es vacia.");
	lista_destruir(nueva_lista);
}

void dada_lista_con_varios_elementos_no_da_vacio()
{
	lista_t *nueva_lista = lista_crear();
	int primer_valor = 1;
	char *segundo_valor = "hola";
	bool tercer_valor = true;
	double cuarto_valor = 12343.4;

	lista_agregar(nueva_lista, &primer_valor);
	lista_agregar(nueva_lista, &segundo_valor);
	lista_agregar(nueva_lista, &tercer_valor);
	lista_agregar(nueva_lista, &cuarto_valor);
	pa2m_afirmar(!lista_vacia(nueva_lista),
		     "Una lista con varios elementos no es vacia.");
	lista_destruir(nueva_lista);
}

void dada_lista_vacia_da_cero_en_cantidad_de_elementos()
{
	lista_t *nueva_lista = lista_crear();
	pa2m_afirmar(lista_cantidad(nueva_lista) == 0,
		     "Una lista vacia, lista_cantidad() da cero elementos.");
	lista_destruir(nueva_lista);
}

void dada_lista_con_un_elemento_da_uno_en_cantidad()
{
	lista_t *nueva_lista = lista_crear();
	int valor = 1;
	lista_agregar(nueva_lista, &valor);
	pa2m_afirmar(
		lista_cantidad(nueva_lista) == 1,
		"Una lista con solo un elemento, lista_cantidad() da un elemento.");
	lista_destruir(nueva_lista);
}

void dada_lista_con_10_elementos_da_10_en_cantidad()
{
	lista_t *nueva_lista = lista_crear();
	int valor = 1;
	for (int i = 0; i < 10; i++) {
		lista_agregar(nueva_lista, &valor);
	}
	pa2m_afirmar(
		lista_cantidad(nueva_lista) == 10,
		"Una lista con 10 elementos, lista_cantidad() da 10 elementos.");
	lista_destruir(nueva_lista);
}

void dada_lista_vacia_se_agrega_un_elemento_exitosamente_y_se_verifica_su_cantidad_sea_1_y_elemento_sea_el_esperado()
{
	lista_t *nueva_lista = lista_crear();
	int valor = 1;
	lista_agregar(nueva_lista, &valor);
	size_t cantidad = lista_cantidad(nueva_lista);
	size_t cantidad_esperada = 1;
	void *elemento = lista_buscar_elemento(nueva_lista, 0);

	pa2m_afirmar(lista_agregar(nueva_lista, &valor),
		     "Se agrega un elemento exitosamente a una lista vacia.");
	pa2m_afirmar(cantidad == cantidad_esperada,
		     "La cantidad es la esperada. (recibida: %i,esperada: %i)",
		     cantidad, cantidad_esperada);
	pa2m_afirmar(
		elemento == &valor,
		"El elemento agregado es el esperado (recibido: %p, esperado: %p)",
		elemento, (void *)&valor);

	lista_destruir(nueva_lista);
}

void dada_lista_con_un_elemento_se_agrega_un_elemento_y_se_verifica_su_cantidad_sea_2_y_orden_correcto()
{
	lista_t *nueva_lista = lista_crear();
	int valor = 1;
	char letra = 'a';
	lista_agregar(nueva_lista, &valor);
	lista_agregar(nueva_lista, &letra);
	size_t cantidad = lista_cantidad(nueva_lista);
	size_t cantidad_esperada = 2;
	void *elemento_1 = lista_buscar_elemento(nueva_lista, 0);
	void *elemento_a = lista_buscar_elemento(nueva_lista, 1);

	pa2m_afirmar(
		lista_agregar(nueva_lista, &valor),
		"Se agrega un elemento exitosamente a una lista con un elemento.");
	pa2m_afirmar(cantidad == cantidad_esperada,
		     "La cantidad es la esperada. (recibida: %i,esperada: %i)",
		     cantidad, cantidad_esperada);
	pa2m_afirmar(
		elemento_1 == &valor,
		"El primer elemento es el mismo (recibido: %p, esperado: %p)",
		elemento_1, (void *)&valor);
	pa2m_afirmar(
		elemento_a == &letra,
		"El elemento agregado es el esperado (recibido: %p, esperado: %p)",
		elemento_a, (void *)&letra);

	lista_destruir(nueva_lista);
}

void dada_lista_con_varios_elementos_se_agrega_elemento_estatico_y_se_verifica_orden()
{
	lista_t *nueva_lista = lista_crear();
	int valor_1 = 1;
	int valor_2 = 2;
	int valor_3 = 3;
	int valor_4 = 4;
	lista_agregar(nueva_lista, &valor_1);
	lista_agregar(nueva_lista, &valor_2);
	lista_agregar(nueva_lista, &valor_3);
	bool es_agregado = lista_agregar(nueva_lista, &valor_4);
	size_t cantidad = lista_cantidad(nueva_lista);
	size_t cantidad_esperada = 4;

	void *elemento_1 = lista_buscar_elemento(nueva_lista, 0);
	void *elemento_2 = lista_buscar_elemento(nueva_lista, 1);
	void *elemento_3 = lista_buscar_elemento(nueva_lista, 2);
	void *elemento_4_ultimo =
		lista_buscar_elemento(nueva_lista, cantidad - 1);

	pa2m_afirmar(
		es_agregado,
		"Se agrega un elemento estático exitosamente a una lista con varios elementos.");
	pa2m_afirmar(cantidad == cantidad_esperada,
		     "La cantidad es la esperada (recibida: %i, esperada: %i).",
		     cantidad, cantidad_esperada);
	pa2m_afirmar(
		elemento_1 == &valor_1,
		"El primer elemento es el mismo (recibido: %p, esperado: %p)",
		elemento_1, (void *)&valor_1);
	pa2m_afirmar(
		elemento_2 == &valor_2,
		"El segundo elemento es el mismo (recibido: %p, esperado: %p)",
		elemento_2, (void *)&valor_2);
	pa2m_afirmar(
		elemento_3 == &valor_3,
		"El tercero elemento es el mismo (recibido: %p, esperado: %p)",
		elemento_3, (void *)&valor_3);
	pa2m_afirmar(
		elemento_4_ultimo == &valor_4,
		"El elemento agregado es el esperado (recibido: %p, esperado: %p).",
		elemento_4_ultimo, (void *)&valor_4);

	lista_destruir(nueva_lista);
}

void dada_lista_con_varios_elementos_se_agrega_elemento_dinamico_y_se_verifica_posiciones()
{
	lista_t *nueva_lista = lista_crear();
	int valor_1 = 10;
	int valor_2 = 20;
	int *valor_3 = malloc(sizeof(int));
	*valor_3 = 30;
	lista_agregar(nueva_lista, &valor_1);
	lista_agregar(nueva_lista, &valor_2);
	bool es_agregado = lista_agregar(nueva_lista, valor_3);
	size_t cantidad = lista_cantidad(nueva_lista);
	size_t cantidad_esperada = 3;
	void *elemento_1 = lista_buscar_elemento(nueva_lista, 0);
	void *elemento_2 = lista_buscar_elemento(nueva_lista, 1);
	void *ultimo_elemento =
		lista_buscar_elemento(nueva_lista, cantidad - 1);

	pa2m_afirmar(
		es_agregado,
		"Se agrega un elemento dinámico exitosamente a una lista con varios elementos.");
	pa2m_afirmar(cantidad == cantidad_esperada,
		     "La cantidad es la esperada (recibida: %i, esperada: %i).",
		     cantidad, cantidad_esperada);
	pa2m_afirmar(
		elemento_1 == &valor_1,
		"El primer elemento es el mismo (recibido: %p, esperado: %p)",
		elemento_1, (void *)&valor_1);
	pa2m_afirmar(
		elemento_2 == &valor_2,
		"El segundo elemento es el mismo (recibido: %p, esperado: %p)",
		elemento_2, (void *)&valor_2);
	pa2m_afirmar(
		ultimo_elemento == valor_3,
		"El elemento agregado es el esperado (recibido: %p, esperado: %p).",
		ultimo_elemento, valor_3);

	free(valor_3);
	lista_destruir(nueva_lista);
}

void dada_lista_con_varios_elementos_se_agrega_elemento_null_y_se_verifica_posiciones()
{
	lista_t *nueva_lista = lista_crear();
	int valor_1 = 100;
	int valor_2 = 200;
	lista_agregar(nueva_lista, &valor_1);
	lista_agregar(nueva_lista, &valor_2);
	bool es_agregado = lista_agregar(nueva_lista, NULL);
	size_t cantidad = lista_cantidad(nueva_lista);
	size_t cantidad_esperada = 3;
	void *elemento_1 = lista_buscar_elemento(nueva_lista, 0);
	void *elemento_2 = lista_buscar_elemento(nueva_lista, 1);
	void *ultimo_elemento =
		lista_buscar_elemento(nueva_lista, cantidad - 1);

	pa2m_afirmar(
		es_agregado,
		"Se agrega un elemento NULL exitosamente a una lista con varios elementos.");
	pa2m_afirmar(cantidad == cantidad_esperada,
		     "La cantidad es la esperada (recibida: %i, esperada: %i).",
		     cantidad, cantidad_esperada);
	pa2m_afirmar(
		elemento_1 == &valor_1,
		"El primer elemento es el mismo (recibido: %p, esperado: %p)",
		elemento_1, (void *)&valor_1);
	pa2m_afirmar(
		elemento_2 == &valor_2,
		"El segundo elemento es el mismo (recibido: %p, esperado: %p)",
		elemento_2, (void *)&valor_2);
	pa2m_afirmar(ultimo_elemento == NULL,
		     "El elemento agregado es NULL como se esperaba.");

	lista_destruir(nueva_lista);
}

void dada_lista_vacia_no_se_puede_insertar()
{
	lista_t *nueva_lista = lista_crear();
	int valor = 1;

	pa2m_afirmar(!lista_insertar(nueva_lista, &valor, 0),
		     "No se puede insertar en una lista vacía en posición 0.");

	lista_destruir(nueva_lista);
}

void dada_lista_con_varios_elementos_se_inserta_en_posicion_0_y_se_verifica_cantidad_y_posiciones()
{
	lista_t *nueva_lista = lista_crear();
	int valor_1 = 1;
	int valor_2 = 2;
	int valor_3 = 3;
	int valor_nuevo = 10;

	lista_agregar(nueva_lista, &valor_1);
	lista_agregar(nueva_lista, &valor_2);
	lista_agregar(nueva_lista, &valor_3);

	pa2m_afirmar(lista_insertar(nueva_lista, &valor_nuevo, 0),
		     "Se inserta en la primera posición correctamente.");

	pa2m_afirmar(lista_cantidad(nueva_lista) == 4,
		     "La cantidad es la esperada (recibida: %i, esperada: 4).",
		     lista_cantidad(nueva_lista));

	pa2m_afirmar(lista_buscar_elemento(nueva_lista, 0) == &valor_nuevo,
		     "El primer elemento es el recien insertado.");

	pa2m_afirmar(lista_buscar_elemento(nueva_lista, 1) == &valor_1,
		     "El segundo elemento es esperado.");

	pa2m_afirmar(lista_buscar_elemento(nueva_lista, 2) == &valor_2,
		     "El tercer elemento es esperado.");

	pa2m_afirmar(lista_buscar_elemento(nueva_lista, 3) == &valor_3,
		     "El cuarto elemento es esperado.");

	lista_destruir(nueva_lista);
}

void dada_lista_con_varios_elementos_se_inserta_en_posicion_1_y_se_verifica_cantidad_y_posiciones()
{
	lista_t *nueva_lista = lista_crear();
	int valor_1 = 1;
	int valor_2 = 2;
	int valor_3 = 3;
	int valor_nuevo = 20;

	lista_agregar(nueva_lista, &valor_1);
	lista_agregar(nueva_lista, &valor_2);
	lista_agregar(nueva_lista, &valor_3);

	pa2m_afirmar(lista_insertar(nueva_lista, &valor_nuevo, 1),
		     "Se inserta en la segunda posición correctamente.");

	pa2m_afirmar(lista_cantidad(nueva_lista) == 4,
		     "La cantidad es la esperada (recibida: %i, esperada: 4).",
		     lista_cantidad(nueva_lista));

	pa2m_afirmar(lista_buscar_elemento(nueva_lista, 0) == &valor_1,
		     "El primer elemento es esperado.");

	pa2m_afirmar(lista_buscar_elemento(nueva_lista, 1) == &valor_nuevo,
		     "El segundo elemento es el recien insertado.");

	pa2m_afirmar(lista_buscar_elemento(nueva_lista, 2) == &valor_2,
		     "El tercer elemento es esperado.");

	pa2m_afirmar(lista_buscar_elemento(nueva_lista, 3) == &valor_3,
		     "El cuarto elemento es esperado.");

	lista_destruir(nueva_lista);
}

void dada_lista_con_varios_elementos_se_inserta_en_posicion_2_y_se_verifica_cantidad_y_posiciones()
{
	lista_t *nueva_lista = lista_crear();
	int valor_1 = 1;
	int valor_2 = 2;
	int valor_3 = 3;
	int valor_nuevo = 30;

	lista_agregar(nueva_lista, &valor_1);
	lista_agregar(nueva_lista, &valor_2);
	lista_agregar(nueva_lista, &valor_3);

	pa2m_afirmar(lista_insertar(nueva_lista, &valor_nuevo, 2),
		     "Se inserta en la tercera posición correctamente.");

	pa2m_afirmar(lista_cantidad(nueva_lista) == 4,
		     "La cantidad es la esperada (recibida: %i, esperada: 4).",
		     lista_cantidad(nueva_lista));

	pa2m_afirmar(lista_buscar_elemento(nueva_lista, 0) == &valor_1,
		     "El primer elemento es esperado.");

	pa2m_afirmar(lista_buscar_elemento(nueva_lista, 1) == &valor_2,
		     "El segundo elemento es esperado.");

	pa2m_afirmar(lista_buscar_elemento(nueva_lista, 2) == &valor_nuevo,
		     "El tercer elemento es el recien insertado.");

	pa2m_afirmar(lista_buscar_elemento(nueva_lista, 3) == &valor_3,
		     "El cuarto elemento es esperado.");

	lista_destruir(nueva_lista);
}

void dada_lista_con_varios_elementos_se_inserta_en_posicion_3_y_se_verifica_cantidad_y_posiciones()
{
	lista_t *nueva_lista = lista_crear();
	int valor_1 = 1;
	int valor_2 = 2;
	int valor_3 = 3;
	int valor_4 = 4;
	int valor_nuevo = 40;

	lista_agregar(nueva_lista, &valor_1);
	lista_agregar(nueva_lista, &valor_2);
	lista_agregar(nueva_lista, &valor_3);
	lista_agregar(nueva_lista, &valor_4);

	pa2m_afirmar(lista_insertar(nueva_lista, &valor_nuevo, 3),
		     "Se inserta en la cuarta posición correctamente.");

	pa2m_afirmar(lista_cantidad(nueva_lista) == 5,
		     "La cantidad es la esperada (recibida: %i, esperada: 4).",
		     lista_cantidad(nueva_lista));

	pa2m_afirmar(lista_buscar_elemento(nueva_lista, 0) == &valor_1,
		     "Primer elemento es esperado.");
	pa2m_afirmar(lista_buscar_elemento(nueva_lista, 1) == &valor_2,
		     "Segundo elemento es esperado.");
	pa2m_afirmar(lista_buscar_elemento(nueva_lista, 2) == &valor_3,
		     "Tercer elemento es esperado.");
	pa2m_afirmar(lista_buscar_elemento(nueva_lista, 3) == &valor_nuevo,
		     "Cuarto elemento es el recien insertado.");

	lista_destruir(nueva_lista);
}

void dada_lista_con_cinco_elementos_se_inserta_en_decima_posicion_y_no_se_puede()
{
	lista_t *nueva_lista = lista_crear();
	int valores[5];
	for (int i = 0; i < 5; i++) {
		valores[i] = i + 1;
	}
	int valor_nuevo = 100;
	for (int i = 0; i < 5; i++) {
		lista_agregar(nueva_lista, &valores[i]);
	}

	pa2m_afirmar(
		!lista_insertar(nueva_lista, &valor_nuevo, 9),
		"En una lista de cinco elementos no se puede insertar en la décima posición (fuera del rango).");

	lista_destruir(nueva_lista);
}

void dada_lista_con_varios_elementos_se_inserta_en_cantidad_mas_uno_y_no_se_puede()
{
	lista_t *nueva_lista = lista_crear();
	int valor_1 = 1;
	int valor_2 = 2;
	int valor_nuevo = 60;

	lista_agregar(nueva_lista, &valor_1);
	lista_agregar(nueva_lista, &valor_2);

	size_t cantidad = lista_cantidad(nueva_lista);

	pa2m_afirmar(!lista_insertar(nueva_lista, &valor_nuevo, cantidad + 1),
		     "No se puede insertar en la posición cantidad + 1.");

	lista_destruir(nueva_lista);
}

void dada_lista_con_5_elementos_se_elimina_el_ultimo_y_devuelve_el_elemento_y_verifica_cantidad()
{
	lista_t *nueva_lista = lista_crear();
	int valor_1 = 1;
	int valor_2 = 2;
	int valor_3 = 3;
	int valor_4 = 4;
	int valor_5 = 5;

	lista_agregar(nueva_lista, &valor_1);
	lista_agregar(nueva_lista, &valor_2);
	lista_agregar(nueva_lista, &valor_3);
	lista_agregar(nueva_lista, &valor_4);
	lista_agregar(nueva_lista, &valor_5);

	void *eliminado = lista_eliminar_elemento(nueva_lista, 4);

	pa2m_afirmar(
		eliminado == &valor_5,
		"Se elimina el último elemento correctamente (recibido: %p, esperado: %p).",
		eliminado, &valor_5);
	pa2m_afirmar(lista_cantidad(nueva_lista) == 4,
		     "La cantidad se reduce en 1 (ahora: %i, antes: 5).",
		     lista_cantidad(nueva_lista));

	lista_destruir(nueva_lista);
}

void dada_lista_con_5_elementos_se_elimina_el_3ro_y_devuelve_el_elemento_y_verifica_cantidad()
{
	lista_t *nueva_lista = lista_crear();
	int valor_1 = 1;
	int valor_2 = 2;
	int valor_3 = 3;
	int valor_4 = 4;
	int valor_5 = 5;

	lista_agregar(nueva_lista, &valor_1);
	lista_agregar(nueva_lista, &valor_2);
	lista_agregar(nueva_lista, &valor_3);
	lista_agregar(nueva_lista, &valor_4);
	lista_agregar(nueva_lista, &valor_5);

	void *eliminado = lista_eliminar_elemento(nueva_lista, 2);

	pa2m_afirmar(
		eliminado == &valor_3,
		"Se elimina el tercer elemento correctamente (recibido: %p, esperado: %p).",
		eliminado, &valor_3);
	pa2m_afirmar(lista_cantidad(nueva_lista) == 4,
		     "La cantidad se reduce en 1 (ahora: %i, antes: 5).",
		     lista_cantidad(nueva_lista));

	lista_destruir(nueva_lista);
}

void dada_lista_con_5_elementos_se_elimina_el_primero_y_devuelve_el_elemento_y_verifica_cantidad()
{
	lista_t *nueva_lista = lista_crear();
	int valor_1 = 1;
	int valor_2 = 2;
	int valor_3 = 3;
	int valor_4 = 4;
	int valor_5 = 5;

	lista_agregar(nueva_lista, &valor_1);
	lista_agregar(nueva_lista, &valor_2);
	lista_agregar(nueva_lista, &valor_3);
	lista_agregar(nueva_lista, &valor_4);
	lista_agregar(nueva_lista, &valor_5);

	void *eliminado = lista_eliminar_elemento(nueva_lista, 0);

	pa2m_afirmar(
		eliminado == &valor_1,
		"Se elimina el primer elemento correctamente (recibido: %p, esperado: %p).",
		eliminado, &valor_1);
	pa2m_afirmar(lista_cantidad(nueva_lista) == 4,
		     "La cantidad se reduce en 1 (ahora: %i, antes: 5).",
		     lista_cantidad(nueva_lista));

	lista_destruir(nueva_lista);
}

void dada_lista_con_5_elementos_se_elimina_10mo_elemento_y_devuelve_null_y_cantidad_es_la_misma()
{
	lista_t *nueva_lista = lista_crear();
	int valor_1 = 1;
	int valor_2 = 2;
	int valor_3 = 3;
	int valor_4 = 4;
	int valor_5 = 5;

	lista_agregar(nueva_lista, &valor_1);
	lista_agregar(nueva_lista, &valor_2);
	lista_agregar(nueva_lista, &valor_3);
	lista_agregar(nueva_lista, &valor_4);
	lista_agregar(nueva_lista, &valor_5);

	void *eliminado = lista_eliminar_elemento(nueva_lista, 9);

	pa2m_afirmar(
		eliminado == NULL,
		"Intentar eliminar un elemento inexistente devuelve NULL.");
	pa2m_afirmar(lista_cantidad(nueva_lista) == 5,
		     "La cantidad permanece igual (recibida: %i, esperada: 5).",
		     lista_cantidad(nueva_lista));

	lista_destruir(nueva_lista);
}

void dada_lista_con_un_elemento_se_elimina_el_elemento_y_queda_vacia()
{
	lista_t *nueva_lista = lista_crear();
	int valor_1 = 1;

	lista_agregar(nueva_lista, &valor_1);

	void *eliminado = lista_eliminar_elemento(nueva_lista, 0);

	pa2m_afirmar(
		eliminado == &valor_1,
		"Se elimina el único elemento correctamente (recibido: %p, esperado: %p).",
		eliminado, &valor_1);
	pa2m_afirmar(lista_cantidad(nueva_lista) == 0,
		     "La lista queda vacía (cantidad: %i).",
		     lista_cantidad(nueva_lista));

	lista_destruir(nueva_lista);
}

void dada_lista_vacia_no_se_puede_eliminar_elementos_y_da_null()
{
	lista_t *nueva_lista = lista_crear();
	size_t posicion = 0;

	void *eliminado = lista_eliminar_elemento(nueva_lista, posicion);

	pa2m_afirmar(
		eliminado == NULL,
		"No se puede eliminar elementos de una lista vacía, devuelve NULL.");
	pa2m_afirmar(
		lista_cantidad(nueva_lista) == 0,
		"La cantidad sigue siendo 0 en la lista vacía (recibida: %i).",
		lista_cantidad(nueva_lista));

	lista_destruir(nueva_lista);
}

int comparador_enteros(const void *a, const void *b)
{
	return *(int *)a - *(int *)b;
}

void dada_lista_vacia_no_hay_elementos_por_buscar()
{
	lista_t *nueva_lista = lista_crear();
	int valor = 1;

	int posicion =
		lista_buscar_posicion(nueva_lista, &valor, comparador_enteros);

	pa2m_afirmar(posicion == -1, "Buscar en lista vacía devuelve -1.");

	lista_destruir(nueva_lista);
}

void dada_lista_con_3_elementos_busca_cada_elemento_y_devuelve_su_posicion_correctamente()
{
	lista_t *nueva_lista = lista_crear();
	int valor_1 = 10;
	int valor_2 = 20;
	int valor_3 = 30;

	lista_agregar(nueva_lista, &valor_1);
	lista_agregar(nueva_lista, &valor_2);
	lista_agregar(nueva_lista, &valor_3);

	int pos1 = lista_buscar_posicion(nueva_lista, &valor_1,
					 comparador_enteros);
	int pos2 = lista_buscar_posicion(nueva_lista, &valor_2,
					 comparador_enteros);
	int pos3 = lista_buscar_posicion(nueva_lista, &valor_3,
					 comparador_enteros);

	pa2m_afirmar(pos1 == 0, "El valor_1 se encuentra en la posición 0.");
	pa2m_afirmar(pos2 == 1, "El valor_2 se encuentra en la posición 1.");
	pa2m_afirmar(pos3 == 2, "El valor_3 se encuentra en la posición 2.");

	lista_destruir(nueva_lista);
}

void dada_lista_se_busca_elemento_no_existente()
{
	lista_t *nueva_lista = lista_crear();
	int valor_1 = 5;
	int valor_2 = 10;
	int valor_3 = 15;
	int valor_no_existe = 20;

	lista_agregar(nueva_lista, &valor_1);
	lista_agregar(nueva_lista, &valor_2);
	lista_agregar(nueva_lista, &valor_3);

	int posicion = lista_buscar_posicion(nueva_lista, &valor_no_existe,
					     comparador_enteros);

	pa2m_afirmar(posicion == -1,
		     "Buscar un elemento que no existe devuelve -1.");

	lista_destruir(nueva_lista);
}

void dada_lista_con_elementos_repetidos_devuelve_la_primera_posicion()
{
	lista_t *nueva_lista = lista_crear();
	int valor_1 = 7;
	int valor_2 = 8;
	int valor_repetido = 9;

	lista_agregar(nueva_lista, &valor_1);
	lista_agregar(nueva_lista, &valor_repetido);
	lista_agregar(nueva_lista, &valor_2);
	lista_agregar(nueva_lista, &valor_repetido);

	int pos_repetido = lista_buscar_posicion(nueva_lista, &valor_repetido,
						 comparador_enteros);

	pa2m_afirmar(pos_repetido == 1,
		     "Devuelve la primera posición del elemento repetido.");

	lista_destruir(nueva_lista);
}

bool sumar_valores(void *elemento, void *extra)
{
	int *val = (int *)elemento;
	int *suma = (int *)extra;
	*suma += *val;
	return true;
}

bool sumar_hasta_limite(void *elemento, void *extra)
{
	int *val = (int *)elemento;
	int *limite = (int *)extra;
	if (*val > *limite)
		return false;
	return true;
}

void dada_lista_vacia_no_se_aplica_funcion()
{
	lista_t *nueva_lista = lista_crear();
	int suma = 0;

	size_t procesados =
		lista_con_cada_elemento(nueva_lista, sumar_valores, &suma);

	pa2m_afirmar(procesados == 0,
		     "Lista vacía no se procesa ningún elemento.");

	lista_destruir(nueva_lista);
}

void dada_lista_con_3_elementos_se_aplica_funcion_a_todos_y_se_verifica_la_respuesta()
{
	lista_t *nueva_lista = lista_crear();
	int valor_1 = 1;
	int valor_2 = 2;
	int valor_3 = 3;
	int suma = 0;

	lista_agregar(nueva_lista, &valor_1);
	lista_agregar(nueva_lista, &valor_2);
	lista_agregar(nueva_lista, &valor_3);

	size_t procesados =
		lista_con_cada_elemento(nueva_lista, sumar_valores, &suma);

	pa2m_afirmar(procesados == 3, "Se procesaron los 3 elementos.");
	pa2m_afirmar(
		suma == 6,
		"La suma de los elementos es correcta (esperada=6, recibida: %i).",
		suma);

	lista_destruir(nueva_lista);
}

void dada_lista_se_detiene_cuando_funcion_da_false_y_se_incluye_el_elemento_que_da_false()
{
	lista_t *nueva_lista = lista_crear();
	int valor_1 = 1;
	int valor_2 = 5;
	int valor_3 = 10;
	int valor_4 = 15;
	int valor_5 = 20;
	int limite = 5;

	lista_agregar(nueva_lista, &valor_1);
	lista_agregar(nueva_lista, &valor_2);
	lista_agregar(nueva_lista, &valor_3);
	lista_agregar(nueva_lista, &valor_4);
	lista_agregar(nueva_lista, &valor_5);

	size_t procesados = lista_con_cada_elemento(
		nueva_lista, sumar_hasta_limite, &limite);

	pa2m_afirmar(
		procesados == 3,
		"Se procesaron los elementos hasta que se dio false y se incluye el ultimo.",
		procesados);

	lista_destruir(nueva_lista);
}

void dada_lista_con_un_elemento_se_aplica_funcion_a_solo_ese()
{
	lista_t *nueva_lista = lista_crear();
	int valor_1 = 7;
	int suma = 0;

	lista_agregar(nueva_lista, &valor_1);

	size_t procesados =
		lista_con_cada_elemento(nueva_lista, sumar_valores, &suma);

	pa2m_afirmar(procesados == 1,
		     "Se procesó el único elemento de la lista.");
	pa2m_afirmar(suma == 7,
		     "La suma del elemento único es correcta (recibida: %i).",
		     suma);

	lista_destruir(nueva_lista);
}

void dado_lista_vacia_el_iterador_no_tiene_elementos_donde_iterar()
{
	lista_t *nueva_lista = lista_crear();
	lista_iterador_t *iterador = lista_iterador_crear(nueva_lista);

	pa2m_afirmar(
		!lista_iterador_hay_mas_elementos(iterador),
		"Iterador sobre lista vacía no tiene elementos para iterar.");

	lista_iterador_destruir(iterador);
	lista_destruir(nueva_lista);
}

void dada_lista_con_3_elementos_iterador_recorre_todos_correctamente()
{
	lista_t *nueva_lista = lista_crear();
	int valor_1 = 10;
	int valor_2 = 20;
	int valor_3 = 30;

	lista_agregar(nueva_lista, &valor_1);
	lista_agregar(nueva_lista, &valor_2);
	lista_agregar(nueva_lista, &valor_3);

	lista_iterador_t *iterador = lista_iterador_crear(nueva_lista);

	int *elementos_esperados[3] = { &valor_1, &valor_2, &valor_3 };
	size_t indice = 0;

	while (lista_iterador_hay_mas_elementos(iterador)) {
		int *elemento_actual = lista_iterador_obtener_actual(iterador);
		pa2m_afirmar(elemento_actual == elementos_esperados[indice],
			     "Elemento %i es el esperado.", indice);
		indice++;
		lista_iterador_siguiente(iterador);
	}

	pa2m_afirmar(indice == 3, "Se recorrieron todos los elementos.");

	lista_iterador_destruir(iterador);
	lista_destruir(nueva_lista);
}

void dada_lista_nula_la_cantidad_es_cero()
{
	lista_t *lista = NULL;

	pa2m_afirmar(lista_cantidad(lista) == 0,
		     "Cantidad de lista nula es 0.");
}

void dada_lista_nula_da_false_al_agregar_elemento()
{
	lista_t *lista = NULL;
	int valor = 1;

	pa2m_afirmar(!lista_agregar(lista, &valor),
		     "Agregar a lista nula devuelve false.");
}

void dada_lista_nula_no_se_puede_insertar_elemnto_y_da_false()
{
	lista_t *lista = NULL;
	int valor = 1;

	pa2m_afirmar(!lista_insertar(lista, &valor, 0),
		     "Insertar en lista nula devuelve false.");
}

void dada_lista_nula_no_se_puede_eliminar_elemento_y_da_null()
{
	lista_t *lista = NULL;

	void *elemento = lista_eliminar_elemento(lista, 0);
	pa2m_afirmar(elemento == NULL, "Eliminar de lista nula devuelve NULL.");
}

void dada_lista_nula_no_se_puede_buscar_posicion_y_da_menos_uno()
{
	lista_t *lista = NULL;
	int valor = 1;

	int pos = lista_buscar_posicion(lista, &valor, NULL);
	pa2m_afirmar(pos == -1, "Buscar posición en lista nula devuelve -1.");
}

void dada_lista_nula_no_se_puede_buscar_elemento_y_da_null()
{
	lista_t *lista = NULL;
	void *elem = lista_buscar_elemento(lista, 0);

	pa2m_afirmar(elem == NULL,
		     "Buscar elemento en lista nula devuelve NULL.");
}

void dada_lista_vacia_no_e_aplica_funcion_y_retorna_cero()
{
	lista_t *lista = lista_crear();
	int extra = 0;
	size_t procesados = lista_con_cada_elemento(lista, NULL, &extra);

	pa2m_afirmar(procesados == 0,
		     "Lista vacía no aplica función y retorna 0.");

	lista_destruir(lista);
}

void dada_lista_nula_no_se_puede_crear_iterador_ni_se_puede_iterar()
{
	lista_t *lista = NULL;

	lista_iterador_t *iterador = lista_iterador_crear(lista);
	pa2m_afirmar(iterador == NULL,
		     "No se puede crear iterador sobre lista nula.");
	pa2m_afirmar(
		iterador == NULL || !lista_iterador_hay_mas_elementos(iterador),
		"No se puede iterar sobre lista nula (hay_mas_elementos devuelve false).");
	pa2m_afirmar(
		iterador == NULL ||
			lista_iterador_obtener_actual(iterador) == NULL,
		"No se puede obtener elemento actual de iterador nulo (devuelve NULL).");
}

void dada_funcion_null_no_se_aplica_nada_a_la_lista_y_devuelve_0()
{
	lista_t *lista = lista_crear();
	int valor_1 = 1;
	int valor_2 = 2;

	lista_agregar(lista, &valor_1);
	lista_agregar(lista, &valor_2);

	size_t procesados = lista_con_cada_elemento(lista, NULL, NULL);

	pa2m_afirmar(
		procesados == 0,
		"Función NULL no se aplica nada a la lista y lista_con_cada_elemento devuelve 0.");

	lista_destruir(lista);
}

void dada_comparador_null_no_se_aplica_nada_a_la_lista_y_devuelve_menos_uno()
{
	lista_t *lista = lista_crear();
	int valor_1 = 1;
	int valor_2 = 2;

	lista_agregar(lista, &valor_1);
	lista_agregar(lista, &valor_2);

	int pos = lista_buscar_posicion(lista, &valor_1, NULL);

	pa2m_afirmar(
		pos == -1,
		"Comparador NULL no se puede buscar y lista_buscar_posicion devuelve -1.");

	lista_destruir(lista);
}

void dada_cola_recien_creada_es_vacia_y_cantidad_es_cero()
{
	cola_t *cola = cola_crear();

	pa2m_afirmar(cola != NULL, "Se creó la cola correctamente.");
	pa2m_afirmar(cola_cantidad(cola) == 0,
		     "La cantidad de una cola nueva es 0.");

	cola_destruir(cola);
}

void dada_cola_vacia_no_se_puede_encolar_ni_desencolar_devuelven_null()
{
	cola_t *cola = cola_crear();

	pa2m_afirmar(cola_ver_primero(cola) == NULL,
		     "Ver primero en cola vacía devuelve NULL.");
	pa2m_afirmar(cola_desencolar(cola) == NULL,
		     "Desencolar cola vacía devuelve NULL.");

	cola_destruir(cola);
}

void se_encola_varios_elementos_y_se_verifica_cantidad_y_primero()
{
	cola_t *cola = cola_crear();
	int valor_1 = 10;
	int valor_2 = 20;
	int valor_3 = 30;

	pa2m_afirmar(cola_encolar(cola, &valor_1),
		     "Se encoló el primer elemento.");
	pa2m_afirmar(cola_encolar(cola, &valor_2),
		     "Se encoló el segundo elemento.");
	pa2m_afirmar(cola_encolar(cola, &valor_3),
		     "Se encoló el tercer elemento.");

	pa2m_afirmar(cola_cantidad(cola) == 3, "Cantidad de elementos es 3.");
	pa2m_afirmar(cola_ver_primero(cola) == &valor_1,
		     "Primer elemento es valor_1.");

	cola_destruir(cola);
}

void dada_cola_con_varios_elementos_se_desencola_en_orden_correcto()
{
	cola_t *cola = cola_crear();
	int valor_1 = 10;
	int valor_2 = 20;
	int valor_3 = 30;

	cola_encolar(cola, &valor_1);
	cola_encolar(cola, &valor_2);
	cola_encolar(cola, &valor_3);

	void *elem = cola_desencolar(cola);
	pa2m_afirmar(elem == &valor_1, "Primer desencolado es valor_1.");

	elem = cola_desencolar(cola);
	pa2m_afirmar(elem == &valor_2, "Segundo desencolado es valor_2.");

	elem = cola_desencolar(cola);
	pa2m_afirmar(elem == &valor_3, "Tercer desencolado es valor_3.");

	pa2m_afirmar(
		cola_cantidad(cola) == 0,
		"Cola queda vacía después de desencolar todos los elementos.");
	pa2m_afirmar(cola_ver_primero(cola) == NULL,
		     "Ver primero en cola vacía devuelve NULL.");
	pa2m_afirmar(cola_desencolar(cola) == NULL,
		     "Desencolar cola vacía devuelve NULL.");

	cola_destruir(cola);
}

void dada_cola_se_encola_y_desencola_alternando_correctamente()
{
	cola_t *cola = cola_crear();
	int valor_1 = 5;
	int valor_2 = 15;
	int valor_3 = 25;

	pa2m_afirmar(cola_encolar(cola, &valor_1), "Se encoló valor_1.");
	pa2m_afirmar(cola_ver_primero(cola) == &valor_1,
		     "Primer elemento es valor_1.");

	pa2m_afirmar(cola_encolar(cola, &valor_2), "Se encoló valor_2.");
	void *elem = cola_desencolar(cola);
	pa2m_afirmar(elem == &valor_1, "Primer desencolado es valor_1.");

	pa2m_afirmar(cola_ver_primero(cola) == &valor_2,
		     "Ahora el primer elemento es valor_2.");

	pa2m_afirmar(cola_encolar(cola, &valor_3), "Se encoló valor_3.");
	elem = cola_desencolar(cola);
	pa2m_afirmar(elem == &valor_2, "Segundo desencolado es valor_2.");

	elem = cola_desencolar(cola);
	pa2m_afirmar(elem == &valor_3, "Tercer desencolado es valor_3.");

	pa2m_afirmar(cola_cantidad(cola) == 0, "Cola queda vacía al final.");

	cola_destruir(cola);
}

void dada_cola_nula_no_se_puede_usar_funciones()
{
	cola_t *cola = NULL;
	int valor = 1;

	pa2m_afirmar(!cola_encolar(cola, &valor),
		     "No se puede encolar en cola nula.");
	pa2m_afirmar(cola_desencolar(cola) == NULL,
		     "Desencolar cola nula devuelve NULL.");
	pa2m_afirmar(cola_ver_primero(cola) == NULL,
		     "Ver primero en cola nula devuelve NULL.");
	pa2m_afirmar(cola_cantidad(cola) == 0, "Cantidad de cola nula es 0.");
}

void dada_pila_recien_creada_es_vacia_y_cantidad_es_cero()
{
	pila_t *pila = pila_crear();

	pa2m_afirmar(pila != NULL, "Se creó la pila correctamente.");
	pa2m_afirmar(pila_cantidad(pila) == 0,
		     "La cantidad de una pila nueva es 0.");

	pila_destruir(pila);
}

void dada_pila_vacia_no_se_puede_apilar_ni_desapilar_devuelven_null()
{
	pila_t *pila = pila_crear();

	pa2m_afirmar(pila_ver_primero(pila) == NULL,
		     "Ver primero en pila vacía devuelve NULL.");
	pa2m_afirmar(pila_desapilar(pila) == NULL,
		     "Desapilar pila vacía devuelve NULL.");

	pila_destruir(pila);
}

void se_apila_varios_elementos_se_verifica_cantidad_y_primero()
{
	pila_t *pila = pila_crear();
	int valor_1 = 10;
	int valor_2 = 20;
	int valor_3 = 30;

	pa2m_afirmar(pila_apilar(pila, &valor_1),
		     "Se apiló el primer elemento.");
	pa2m_afirmar(pila_apilar(pila, &valor_2),
		     "Se apiló el segundo elemento.");
	pa2m_afirmar(pila_apilar(pila, &valor_3),
		     "Se apiló el tercer elemento.");

	pa2m_afirmar(pila_cantidad(pila) == 3, "Cantidad de elementos es 3.");
	pa2m_afirmar(pila_ver_primero(pila) == &valor_3,
		     "Primer elemento es valor_3.");

	pila_destruir(pila);
}

void dada_pila_con_varios_elementos_se_desapila_en_orden_correcto()
{
	pila_t *pila = pila_crear();
	int valor_1 = 10;
	int valor_2 = 20;
	int valor_3 = 30;

	pila_apilar(pila, &valor_1);
	pila_apilar(pila, &valor_2);
	pila_apilar(pila, &valor_3);

	void *elem = pila_desapilar(pila);
	pa2m_afirmar(elem == &valor_3, "Primer desapilado es valor_3.");

	elem = pila_desapilar(pila);
	pa2m_afirmar(elem == &valor_2, "Segundo desapilado es valor_2.");

	elem = pila_desapilar(pila);
	pa2m_afirmar(elem == &valor_1, "Tercer desapilado es valor_1.");

	pa2m_afirmar(
		pila_cantidad(pila) == 0,
		"Pila queda vacía después de desapilar todos los elementos.");

	pila_destruir(pila);
}

void dada_pila_se_apila_y_desapila_alternando()
{
	pila_t *pila = pila_crear();
	int valor_1 = 5;
	int valor_2 = 15;
	int valor_3 = 25;

	pa2m_afirmar(pila_apilar(pila, &valor_1), "Se apiló valor_1.");
	pa2m_afirmar(pila_ver_primero(pila) == &valor_1,
		     "Primer elemento es valor_1.");

	pa2m_afirmar(pila_apilar(pila, &valor_2), "Se apiló valor_2.");
	void *elem = pila_desapilar(pila);
	pa2m_afirmar(elem == &valor_2, "Primer desapilado es valor_2.");

	pa2m_afirmar(pila_ver_primero(pila) == &valor_1,
		     "Ahora el primer elemento es valor_1.");

	pa2m_afirmar(pila_apilar(pila, &valor_3), "Se apiló valor_3.");
	elem = pila_desapilar(pila);
	pa2m_afirmar(elem == &valor_3, "Segundo desapilado es valor_3.");

	elem = pila_desapilar(pila);
	pa2m_afirmar(elem == &valor_1, "Tercer desapilado es valor_1.");

	pa2m_afirmar(pila_cantidad(pila) == 0, "Pila queda vacía al final.");

	pila_destruir(pila);
}

void dada_pila_nula_no_se_puede_usar_funciones()
{
	pila_t *pila = NULL;
	int valor = 1;

	pa2m_afirmar(!pila_apilar(pila, &valor),
		     "No se puede apilar en pila nula.");
	pa2m_afirmar(pila_desapilar(pila) == NULL,
		     "Desapilar pila nula devuelve NULL.");
	pa2m_afirmar(pila_ver_primero(pila) == NULL,
		     "Ver primero en pila nula devuelve NULL.");
	pa2m_afirmar(pila_cantidad(pila) == 0, "Cantidad de pila nula es 0.");
}

int main()
{
	pa2m_nuevo_grupo("============== LISTA ===============");
	pa2m_nuevo_grupo("Pruebas de creacion:");
	lista_recien_creada_se_crea_exitosamente_y_vacia();

	pa2m_nuevo_grupo("Pruebas de vaciedad:");
	dada_lista_vacia_se_verifica_que_esta_vacia();

	dada_lista_con_un_elemento_no_da_vacio();
	dada_lista_con_varios_elementos_no_da_vacio();

	pa2m_nuevo_grupo("Pruebas de cantidad:");
	dada_lista_vacia_da_cero_en_cantidad_de_elementos();
	dada_lista_con_un_elemento_da_uno_en_cantidad();
	dada_lista_con_10_elementos_da_10_en_cantidad();

	pa2m_nuevo_grupo("Pruebas de agregacion de elementos:");
	dada_lista_vacia_se_agrega_un_elemento_exitosamente_y_se_verifica_su_cantidad_sea_1_y_elemento_sea_el_esperado();
	dada_lista_con_un_elemento_se_agrega_un_elemento_y_se_verifica_su_cantidad_sea_2_y_orden_correcto();
	dada_lista_con_varios_elementos_se_agrega_elemento_estatico_y_se_verifica_orden();
	dada_lista_con_varios_elementos_se_agrega_elemento_dinamico_y_se_verifica_posiciones();
	dada_lista_con_varios_elementos_se_agrega_elemento_null_y_se_verifica_posiciones();

	pa2m_nuevo_grupo("Pruebas de insercion de elementos:");
	dada_lista_vacia_no_se_puede_insertar();
	dada_lista_con_varios_elementos_se_inserta_en_posicion_0_y_se_verifica_cantidad_y_posiciones();
	dada_lista_con_varios_elementos_se_inserta_en_posicion_1_y_se_verifica_cantidad_y_posiciones();
	dada_lista_con_varios_elementos_se_inserta_en_posicion_2_y_se_verifica_cantidad_y_posiciones();
	dada_lista_con_varios_elementos_se_inserta_en_posicion_3_y_se_verifica_cantidad_y_posiciones();
	dada_lista_con_cinco_elementos_se_inserta_en_decima_posicion_y_no_se_puede();
	dada_lista_con_varios_elementos_se_inserta_en_cantidad_mas_uno_y_no_se_puede();

	pa2m_nuevo_grupo("Pruebas de eliminacion de elementos:");
	dada_lista_con_5_elementos_se_elimina_el_ultimo_y_devuelve_el_elemento_y_verifica_cantidad();
	dada_lista_con_5_elementos_se_elimina_el_3ro_y_devuelve_el_elemento_y_verifica_cantidad();
	dada_lista_con_5_elementos_se_elimina_el_primero_y_devuelve_el_elemento_y_verifica_cantidad();
	dada_lista_con_5_elementos_se_elimina_10mo_elemento_y_devuelve_null_y_cantidad_es_la_misma();
	dada_lista_con_un_elemento_se_elimina_el_elemento_y_queda_vacia();
	dada_lista_vacia_no_se_puede_eliminar_elementos_y_da_null();

	pa2m_nuevo_grupo("Pruebas de busqueda de posicion:");
	dada_lista_vacia_no_hay_elementos_por_buscar();
	dada_lista_con_3_elementos_busca_cada_elemento_y_devuelve_su_posicion_correctamente();
	dada_lista_con_elementos_repetidos_devuelve_la_primera_posicion();
	dada_lista_se_busca_elemento_no_existente();

	pa2m_nuevo_grupo("Pruebas de funcion con cada elemento:");
	dada_lista_vacia_no_se_aplica_funcion();
	dada_lista_con_3_elementos_se_aplica_funcion_a_todos_y_se_verifica_la_respuesta();
	dada_lista_se_detiene_cuando_funcion_da_false_y_se_incluye_el_elemento_que_da_false();
	dada_lista_con_un_elemento_se_aplica_funcion_a_solo_ese();

	pa2m_nuevo_grupo("Pruebas con lista iteradora externa:");
	dado_lista_vacia_el_iterador_no_tiene_elementos_donde_iterar();
	dada_lista_con_3_elementos_iterador_recorre_todos_correctamente();

	pa2m_nuevo_grupo("Pruebas con null:");
	dada_lista_nula_se_verifica_que_es_vacio();
	dada_lista_nula_la_cantidad_es_cero();
	dada_lista_nula_da_false_al_agregar_elemento();
	dada_lista_nula_no_se_puede_insertar_elemnto_y_da_false();
	dada_lista_nula_no_se_puede_eliminar_elemento_y_da_null();
	dada_lista_nula_no_se_puede_buscar_posicion_y_da_menos_uno();
	dada_lista_nula_no_se_puede_buscar_elemento_y_da_null();
	dada_lista_vacia_no_e_aplica_funcion_y_retorna_cero();
	dada_lista_nula_no_se_puede_crear_iterador_ni_se_puede_iterar();
	dada_funcion_null_no_se_aplica_nada_a_la_lista_y_devuelve_0();
	dada_comparador_null_no_se_aplica_nada_a_la_lista_y_devuelve_menos_uno();

	pa2m_nuevo_grupo("============== COLA ===============");
	dada_cola_recien_creada_es_vacia_y_cantidad_es_cero();
	dada_cola_vacia_no_se_puede_encolar_ni_desencolar_devuelven_null();
	se_encola_varios_elementos_y_se_verifica_cantidad_y_primero();
	dada_cola_con_varios_elementos_se_desencola_en_orden_correcto();
	dada_cola_se_encola_y_desencola_alternando_correctamente();
	dada_cola_nula_no_se_puede_usar_funciones();

	pa2m_nuevo_grupo("============== PILA ===============");
	dada_pila_recien_creada_es_vacia_y_cantidad_es_cero();
	dada_pila_vacia_no_se_puede_apilar_ni_desapilar_devuelven_null();
	se_apila_varios_elementos_se_verifica_cantidad_y_primero();
	dada_pila_con_varios_elementos_se_desapila_en_orden_correcto();
	dada_pila_se_apila_y_desapila_alternando();
	dada_pila_nula_no_se_puede_usar_funciones();

	return pa2m_mostrar_reporte();
}

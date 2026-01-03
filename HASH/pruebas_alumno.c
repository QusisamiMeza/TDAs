#include "pa2m.h"
#include "src/hash.h"
#include <stdlib.h>

void crear_hash_con_capacidad_20_es_valido()
{
	size_t cap_inicial = 20;
	hash_t *hash = hash_crear(cap_inicial);
	size_t cant_obtenida = hash_cantidad(hash);

	pa2m_afirmar(
		hash != NULL,
		"Se creó exitosamente el hash pasandole capacidad mayor a 3. (capacidad_inicial = %zu)",
		cap_inicial);
	pa2m_afirmar(
		cant_obtenida == 0,
		"Está vacio, su cantidad es cero (esperado: %zu, obtenido: %zu)",
		0, cant_obtenida);

	hash_destruir(hash);
}

void crear_hash_con_capacidad_3_es_valido()
{
	size_t cap_inicial = 3;
	hash_t *hash = hash_crear(cap_inicial);
	size_t cant_obtenida = hash_cantidad(hash);

	pa2m_afirmar(
		hash != NULL,
		"Se creó exitosamente el hash pasandole capacidad igual a 3. (capacidad_inicial = %zu)",
		cap_inicial);
	pa2m_afirmar(
		cant_obtenida == 0,
		"Está vacio, su cantidad es cero (esperado: %zu, obtenido: %zu)",
		0, cant_obtenida);

	hash_destruir(hash);
}

void crear_hash_con_capacidad_1_es_valido()
{
	size_t cap_inicial = 1;
	hash_t *hash = hash_crear(cap_inicial);
	size_t cant_obtenida = hash_cantidad(hash);

	pa2m_afirmar(
		hash != NULL,
		"Se creó exitosamente el hash pasandole capacidad menor a  3. (capacidad_inicial = %zu)",
		cap_inicial);
	pa2m_afirmar(
		cant_obtenida == 0,
		"Está vacio, su cantidad es cero (esperado: %zu, obtenido: %zu)",
		0, cant_obtenida);

	hash_destruir(hash);
}

void hash_valido_se_inserta_elemento_exitosamente()
{
	hash_t *hash = hash_crear(3);
	size_t cant_inicial = hash_cantidad(hash);
	char *CLAVE_1 = "aaa";
	int valor_1 = 1;

	pa2m_afirmar(
		hash_insertar(hash, CLAVE_1, &valor_1, NULL),
		"Se pudo insertar una clave-valor valida con encontrado nulo.");
	pa2m_afirmar(hash_cantidad(hash) == cant_inicial + 1,
		     "Su cantidad aumento en uno.");
	pa2m_afirmar(hash_contiene(hash, CLAVE_1),
		     "El elemento se encuentra en el hash.");
	pa2m_afirmar(hash_buscar(hash, CLAVE_1) == &valor_1,
		     "Se busca el valor y es el mismo.");

	hash_destruir(hash);
}

void hash_cantidad_devuelve_cero_dado_hash_nulo()
{
	pa2m_afirmar(hash_cantidad(NULL) == 0,
		     "Se pasa hash nulo en hash_cantidad y da cero.");
}

void hash_insertar_devuelve_false_dado_punteros_null()
{
	int valor_1 = 1;
	pa2m_afirmar(!hash_insertar(NULL, "no_existe", &valor_1, NULL),
		     "Se pasa hash nulo en hash_insertar y devuelvue false.");

	hash_t *hash = hash_crear(3);
	pa2m_afirmar(!hash_insertar(hash, NULL, &valor_1, NULL),
		     "Dado clave NULL, no se puede insertar valor.");
	hash_destruir(hash);
}

void hash_vacio_se_inserta_elemento_exitosamente()
{
	hash_t *hash = hash_crear(5);
	size_t cant_inicial = hash_cantidad(hash);
	char *clave_1 = "primero";
	int valor_1 = 1;

	pa2m_afirmar(
		cant_inicial == 0 &&
			hash_insertar(hash, clave_1, &valor_1, NULL),
		"Se puede insertar exitosamente un elemento en un hash vacio.");
	void *recibido = hash_buscar(hash, clave_1);
	pa2m_afirmar(
		recibido == &valor_1,
		"El valor recien insertado es el esperado (insertado: %p, esperado: %p)",
		&valor_1, recibido);
	pa2m_afirmar(hash_cantidad(hash) == cant_inicial + 1,
		     "Su cantidad subio en uno.");

	hash_destruir(hash);
}

void se_insertan_varios_elementos_sin_rehash()
{
	size_t cantidad = 10;
	hash_t *hash = hash_crear(cantidad);
	int valores[cantidad];
	char *claves[10] = { "primero", "segundo", "tercero", "cuarto",
			     "quinto",	"sexto",   "septimo", "octavo",
			     "noveno",	"decimo" };

	for (int i = 0; i < cantidad; i++) {
		size_t cant_inicial = hash_cantidad(hash);
		valores[i] = i;

		pa2m_afirmar(hash_insertar(hash, claves[i], &valores[i], NULL),
			     "Se inserto elemento %i", i);
		void *recibido = hash_buscar(hash, claves[i]);
		pa2m_afirmar(
			recibido == &valores[i],
			"El valor recien insertado es el esperado (insertado: %p, esperado: %p)",
			&valores[i], recibido);
		pa2m_afirmar(hash_cantidad(hash) == cant_inicial + 1,
			     "Su cantidad subio en uno.");
	}

	hash_destruir(hash);
}

void hash_con_10_elementos_tiene_cantidad_10()
{
	size_t cantidad = 10;
	hash_t *hash = hash_crear(cantidad);
	int valores[cantidad];
	char *claves[10] = { "primero", "segundo", "tercero", "cuarto",
			     "quinto",	"sexto",   "septimo", "octavo",
			     "noveno",	"decimo" };

	for (int i = 0; i < cantidad; i++) {
		valores[i] = i;
		hash_insertar(hash, claves[i], &valores[i], NULL);
	}

	size_t recibido = hash_cantidad(hash);

	pa2m_afirmar(
		recibido == cantidad,
		"La cantidad del hash es la esperada (recibido: %zu, esperado: %zu)",
		recibido, cantidad);

	hash_destruir(hash);
}

void hash_con_5_elementos_se_busca_cada_uno_y_se_validan()
{
	hash_t *hash = hash_crear(5);

	char *claves[] = { "a", "b", "c", "d", "e" };
	int valores[] = { 10, 20, 30, 40, 50 };
	size_t cantidad = 5;

	for (size_t i = 0; i < cantidad; i++) {
		bool insertado =
			hash_insertar(hash, claves[i], &valores[i], NULL);
		pa2m_afirmar(insertado,
			     "Se insertó correctamente la clave '%s'.",
			     claves[i]);
	}

	for (size_t i = 0; i < cantidad; i++) {
		pa2m_afirmar(hash_contiene(hash, claves[i]),
			     "El hash contiene la clave '%s'.", claves[i]);

		void *recibido = hash_buscar(hash, claves[i]);
		pa2m_afirmar(
			recibido == &valores[i],
			"El valor con clave '%s' es el esperado (esperado: %d, recibido: %d).",
			claves[i], valores[i], *(int *)recibido);
	}

	hash_destruir(hash);
}

bool contador(char *clave, void *valor, void *ctx)
{
	size_t *contador = ctx;
	(*contador)++;
	return true;
}
void hash_con_10_elementos_se_itera_en_cada_uno()
{
	hash_t *hash = hash_crear(10);
	char *claves[] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j" };
	int valores[10];

	for (int i = 0; i < 10; i++) {
		valores[i] = i;
		hash_insertar(hash, claves[i], &valores[i], NULL);
	}

	size_t cantidad_iterada = 0;

	hash_iterar(hash, contador, &cantidad_iterada);

	pa2m_afirmar(cantidad_iterada == 10,
		     "Se iteraron los 10 elementos del hash.");

	hash_destruir(hash);
}

void hash_con_elementos_se_quita_uno_y_se_valida()
{
	hash_t *hash = hash_crear(5);
	char *claves[] = { "uno", "dos", "tres", "cuatro", "cinco" };
	int valores[] = { 1, 2, 3, 4, 5 };

	for (int i = 0; i < 5; i++)
		hash_insertar(hash, claves[i], &valores[i], NULL);

	size_t cant_inicial = hash_cantidad(hash);
	void *quitado = hash_quitar(hash, "tres");

	pa2m_afirmar(quitado == &valores[2],
		     "Se quita el valor correcto (esperado: %d).", valores[2]);
	pa2m_afirmar(!hash_contiene(hash, "tres"),
		     "El hash ya no contiene la clave 'tres'.");
	pa2m_afirmar(hash_cantidad(hash) == cant_inicial - 1,
		     "La cantidad se redujo en uno.");

	hash_destruir(hash);
}
bool contador_con_limite(char *clave, void *valor, void *ctx)
{
	size_t *contador = ctx;
	(*contador)++;
	return *contador < 5;
}

void hash_con_10_elementos_se_itera_hasta_la_mitad()
{
	hash_t *hash = hash_crear(10);
	char *claves[] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j" };
	int valores[10];

	for (int i = 0; i < 10; i++) {
		valores[i] = i;
		hash_insertar(hash, claves[i], &valores[i], NULL);
	}

	size_t cantidad_iterada = 0;

	hash_iterar(hash, contador_con_limite, &cantidad_iterada);

	pa2m_afirmar(cantidad_iterada == 5,
		     "Se itera correctamente hasta la mitad (5 elementos).");

	hash_destruir(hash);
}

void insertar_buscar_quitar_insertar_quitar_todo()
{
	hash_t *hash = hash_crear(3);
	int v1 = 10, v2 = 20, v3 = 30;

	hash_insertar(hash, "a", &v1, NULL);
	hash_insertar(hash, "b", &v2, NULL);
	hash_insertar(hash, "c", &v3, NULL);

	pa2m_afirmar(hash_cantidad(hash) == 3,
		     "Se insertaron 3 elementos correctamente.");

	void *quitado_b = hash_quitar(hash, "b");
	pa2m_afirmar(quitado_b == &v2,
		     "Se elimino la clave b y se devuelve el mismo.");
	pa2m_afirmar(!hash_contiene(hash, "b"),
		     "Se pregunta si contiene la clave b y no esta.");

	hash_insertar(hash, "d", &v1, NULL);
	pa2m_afirmar(hash_contiene(hash, "d"),
		     "Se inserto nuevamente un elemento tras quitar otro.");

	hash_quitar(hash, "a");
	hash_quitar(hash, "c");
	hash_quitar(hash, "d");

	pa2m_afirmar(hash_cantidad(hash) == 0,
		     "Se quitaron todos los elementos correctamente.");

	hash_destruir(hash);
}

void insertar_500_elementos_en_hash_de_3()
{
	size_t cantidad = 500;
	hash_t *hash = hash_crear(3);
	char clave[20];
	int valores[500];

	for (size_t i = 0; i < cantidad; i++) {
		valores[i] = (int)i;
		snprintf(clave, sizeof(clave), "clave_%zu", i);
		hash_insertar(hash, clave, &valores[i], NULL);
	}

	pa2m_afirmar(hash_cantidad(hash) == cantidad,
		     "Se insertaron correctamente los 500 elementos.");

	for (size_t i = 0; i < cantidad; i += 100) {
		snprintf(clave, sizeof(clave), "clave_%zu", i);
		int *recibido = hash_buscar(hash, clave);
		pa2m_afirmar(recibido && *recibido == (int)i,
			     "La clave '%s' tiene el valor esperado (%d).",
			     clave, (int)i);
	}

	hash_destruir(hash);
}

void hash_buscar_devuelve_null_dado_punteros_nulos()
{
	pa2m_afirmar(!hash_buscar(NULL, "hola"),
		     "Dado hash nulo, hash_buscar devuelve NULL.");

	hash_t *hash = hash_crear(3);
	pa2m_afirmar(!hash_buscar(hash, NULL),
		     "Dada clave nula, hash_buscar devuelve NULL.");
	hash_destruir(hash);
}

void hash_contiene_devuelve_false_dado_punteros_nulos()
{
	pa2m_afirmar(!hash_contiene(NULL, "hola"),
		     "Dado hash nulo, hash_contiene devuelve false.");

	hash_t *hash = hash_crear(3);
	pa2m_afirmar(!hash_buscar(hash, NULL),
		     "Dada clave nula, hash_contiene devuelve false.");
	hash_destruir(hash);
}

void hash_quitar_devuelve_cero_dado_punteros_nulos()
{
	pa2m_afirmar(!hash_quitar(NULL, "hola"),
		     "Dado hash nulo, hash_quitar devuelve NULL.");

	hash_t *hash = hash_crear(3);
	pa2m_afirmar(!hash_quitar(hash, NULL),
		     "Dada clave nula, hash_quitar devuelve NULL.");
	hash_destruir(hash);
}

void se_insertan_varios_elementos_se_reemplazan_algunos_y_se_verifica_puntero_encontrado()
{
	size_t cantidad = 10;
	hash_t *hash = hash_crear(cantidad);
	int valores[cantidad];
	char *claves[10] = { "primero", "segundo", "tercero", "cuarto",
			     "quinto",	"sexto",   "septimo", "octavo",
			     "noveno",	"decimo" };

	for (int i = 0; i < cantidad; i++) {
		valores[i] = i;
		hash_insertar(hash, claves[i], &valores[i], NULL);
	}

	pa2m_afirmar(hash_cantidad(hash) == cantidad,
		     "Se insertaron 10 elementos.");

	int nuevo_valor1 = 888;
	int nuevo_valor1_2 = 4322;
	int *anterior_valor1;

	pa2m_afirmar(hash_insertar(hash, claves[1], &nuevo_valor1,
				   (void **)&anterior_valor1),
		     "Se reemplazó el valor de clave1.");
	pa2m_afirmar(*anterior_valor1 == valores[1],
		     "Se devolvió correctamente el antiguo valor.");
	pa2m_afirmar(hash_buscar(hash, claves[1]) == &nuevo_valor1,
		     "Se busca el valor1 y está correctamente reemplazado.");
	pa2m_afirmar(hash_insertar(hash, claves[1], &nuevo_valor1_2,
				   (void **)&anterior_valor1),
		     "Se reemplazó el valor de clave1.");
	pa2m_afirmar(*anterior_valor1 == nuevo_valor1,
		     "Se devolvió correctamente el antiguo valor.");
	pa2m_afirmar(hash_buscar(hash, claves[1]) == &nuevo_valor1_2,
		     "Se busca el valor1 y está correctamente reemplazado.");

	hash_destruir(hash);
}

void se_insertan_varios_elementos_se_verifica_puntero_encontrado_sea_null_dado_que_no_hay_valor_a_reemplazar()
{
	size_t cantidad = 10;
	hash_t *hash = hash_crear(cantidad);
	int valores[cantidad];
	char *claves[10] = { "primero", "segundo", "tercero", "cuarto",
			     "quinto",	"sexto",   "septimo", "octavo",
			     "noveno",	"decimo" };

	for (int i = 0; i < cantidad; i++) {
		valores[i] = i;
		hash_insertar(hash, claves[i], &valores[i], NULL);
	}

	pa2m_afirmar(hash_cantidad(hash) == cantidad,
		     "Se insertaron 10 elementos.");

	int nuevo_valor = 888;
	char *nueva_clave = "nuevo";
	int *anterior_valor;

	pa2m_afirmar(hash_insertar(hash, nueva_clave, &nuevo_valor,
				   (void **)&anterior_valor),
		     "Se insertó un nuevo par clave-valor.");

	pa2m_afirmar(
		anterior_valor == NULL,
		"Como no habia otra clave igual anteriormente, se modifica el puntero `encontrado` a NULL.");

	hash_destruir(hash);
}

int main()
{
	pa2m_nuevo_grupo("============== CREACION ===============");
	crear_hash_con_capacidad_20_es_valido();
	crear_hash_con_capacidad_3_es_valido();
	crear_hash_con_capacidad_1_es_valido();

	pa2m_nuevo_grupo("============== INSERTADO ===============");
	hash_vacio_se_inserta_elemento_exitosamente();
	se_insertan_varios_elementos_sin_rehash();
	se_insertan_varios_elementos_se_reemplazan_algunos_y_se_verifica_puntero_encontrado();
	se_insertan_varios_elementos_se_verifica_puntero_encontrado_sea_null_dado_que_no_hay_valor_a_reemplazar();

	pa2m_nuevo_grupo("============== CANTIDAD ===============");
	hash_con_10_elementos_tiene_cantidad_10();

	pa2m_nuevo_grupo("============== BUSQUEDA Y CONTENIDO ===============");
	hash_con_5_elementos_se_busca_cada_uno_y_se_validan();

	pa2m_nuevo_grupo("============== QUITADO ===============");
	hash_con_elementos_se_quita_uno_y_se_valida();

	pa2m_nuevo_grupo("============== ITERACION ===============");
	hash_con_10_elementos_se_itera_en_cada_uno();
	hash_con_10_elementos_se_itera_hasta_la_mitad();

	pa2m_nuevo_grupo("============== PUNTEROS NULL ===============");
	hash_cantidad_devuelve_cero_dado_hash_nulo();
	hash_insertar_devuelve_false_dado_punteros_null();
	hash_buscar_devuelve_null_dado_punteros_nulos();
	hash_contiene_devuelve_false_dado_punteros_nulos();
	hash_quitar_devuelve_cero_dado_punteros_nulos();

	pa2m_nuevo_grupo("============== VARIOS ===============");
	insertar_buscar_quitar_insertar_quitar_todo();

	pa2m_nuevo_grupo(
		"============== INSERCION DE VARIOS ELEMENTOS (REHASH)  ===============");
	insertar_500_elementos_en_hash_de_3();

	return pa2m_mostrar_reporte();
}

#include "pa2m.h"
#include "src/abb.h"

#include <string.h>

int comparador_letras(const void *a, const void *b)
{
	const char *a_ = a;
	const char *b_ = b;
	return (int)(*a_ - *b_);
}

int comparador_numeros(const void *a, const void *b)
{
	const int *a_ = a;
	const int *b_ = b;
	return *a_ - *b_;
}

abb_t *crear_abb_con_3_letras()
{
	abb_t *abb = abb_crear(comparador_letras);
	char a = 'a';
	char c = 'c';
	char b = 'b';
	abb_insertar(abb, &b);
	abb_insertar(abb, &a);
	abb_insertar(abb, &c);
	return abb;
}

abb_t *crear_abb_con_7_letras(char *a, char *b, char *c, char *d, char *e,
			      char *f, char *g)
{
	abb_t *abb = abb_crear(comparador_letras);
	abb_insertar(abb, &d);
	abb_insertar(abb, &b);
	abb_insertar(abb, &f);
	abb_insertar(abb, &a);
	abb_insertar(abb, &c);
	abb_insertar(abb, &e);
	abb_insertar(abb, &g);
	return abb;
}

void se_crea_abb_con_comparador_de_letras_vacio_exitosamente_y_se_verifica_datos()
{
	abb_t *abb = abb_crear(comparador_letras);
	bool exito = false;
	if (abb) {
		exito = true;
	}
	pa2m_afirmar(exito,
		     "Se pudo crear abb valido con un comparador valido.");
	pa2m_afirmar(abb_esta_vacio(abb), "El abb recien creado está vacio.");
	pa2m_afirmar(abb_raiz(abb) == NULL,
		     "El abb recien creado no tiene raiz");
	pa2m_afirmar(abb_cantidad(abb) == 0, "Su cantidad es 0");

	abb_destruir(abb);
}

void se_intenta_crear_abb_con_comparador_null_y_no_se_puede()
{
	abb_t *abb = abb_crear(NULL);
	bool exito = false;
	if (abb) {
		exito = true;
	}
	pa2m_afirmar(!exito, "No se crea abb con un comparador NULL.");
}

void abb_vacio_se_inserta_un_dato()
{
	abb_t *abb = abb_crear(comparador_letras);
	char a = 'a';
	pa2m_afirmar(abb_insertar(abb, &a),
		     "Se inserta exitosamente en una lista vacia");
	pa2m_afirmar(abb_raiz(abb) == &a,
		     "El dato es el esperado(recibido: %p, esperado: %p)",
		     abb_raiz(abb), &a);
	pa2m_afirmar(abb_cantidad(abb) == 1, "Se aumenta la cantidad en uno");
	abb_destruir(abb);
}

void abb_con_un_elemento_se_inserta_otro_exitosamente()
{
	abb_t *abb = abb_crear(comparador_letras);
	char c = 'c';
	char d = 'd';
	pa2m_afirmar(abb_insertar(abb, &c),
		     "Se inserta exitosamente en un arbol vacio");
	pa2m_afirmar(abb_raiz(abb) == &c,
		     "El dato es el esperado(recibido: %p, esperado: %p)",
		     abb_raiz(abb), &c);
	pa2m_afirmar(abb_insertar(abb, &d),
		     "Se inserta exitosamente en un arbol con un elemento");
	pa2m_afirmar(abb_buscar(abb, &d) == &d,
		     "El dato es el esperado(recibido: %p, esperado: %p)",
		     abb_buscar(abb, &d), &d);
	pa2m_afirmar(abb_cantidad(abb) == 2, "Se aumenta la cantidad en uno");
	abb_destruir(abb);
}

void abb_vacio_su_cantidad_es_cero()
{
	abb_t *abb = abb_crear(comparador_letras);

	pa2m_afirmar(abb_cantidad(abb) == 0,
		     "Un abb vacio tiene cantidad 0 de elementos");

	abb_destruir(abb);
}

void abb_con_7_elementos_su_cantidad_es_correcta()
{
	abb_t *abb = abb_crear(comparador_letras);
	char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e', f = 'f', g = 'g';
	abb_insertar(abb, &d);
	abb_insertar(abb, &b);
	abb_insertar(abb, &f);
	abb_insertar(abb, &a);
	abb_insertar(abb, &c);
	abb_insertar(abb, &e);
	abb_insertar(abb, &g);

	pa2m_afirmar(abb_cantidad(abb) == 7,
		     "Un abb con elementos su cantidad es la esperada.");

	abb_destruir(abb);
}

void abb_null_su_cantidad_es_cero()
{
	pa2m_afirmar(abb_cantidad(NULL) == 0,
		     "Un abb NULL su cantidad es cero.");
}

void abb_vacio_da_vacio()
{
	abb_t *abb = abb_crear(comparador_letras);
	pa2m_afirmar(abb_esta_vacio(abb),
		     "Dado abb vacio abb_esta_vacio da true.");
	abb_destruir(abb);
}

void abb_no_vacio_da_false()
{
	abb_t *abb = abb_crear(comparador_letras);
	char a = 'a';
	char c = 'c';
	char b = 'b';
	abb_insertar(abb, &b);
	abb_insertar(abb, &a);
	abb_insertar(abb, &c);
	pa2m_afirmar(!abb_esta_vacio(abb),
		     "Dado abb con elementos abb_esta_vacio da false.");
	abb_destruir(abb);
}

void abb_null_da_vacio()
{
	pa2m_afirmar(abb_esta_vacio(NULL),
		     "Dado abb NULL abb_esta_vacio da true.");
}

void abb_con_5_elementos_se_consulta_existencia_cada_elemento_y_todos_existen()
{
	abb_t *abb = abb_crear(comparador_letras);
	char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';
	abb_insertar(abb, &d);
	abb_insertar(abb, &b);
	abb_insertar(abb, &a);
	abb_insertar(abb, &c);
	abb_insertar(abb, &e);

	bool a_buscado = abb_existe(abb, &a);
	bool b_buscado = abb_existe(abb, &b);
	bool c_buscado = abb_existe(abb, &c);
	bool d_buscado = abb_existe(abb, &d);
	bool e_buscado = abb_existe(abb, &e);

	bool todos_son_encontrados =
		(a_buscado && b_buscado && c_buscado && d_buscado && e_buscado);

	pa2m_afirmar(
		todos_son_encontrados,
		"Dado abb con 5 elementos, se consulta su existencia de cada uno y abb_existe da true en cada uno.");

	abb_destruir(abb);
}

void abb_con_5_elementos_se_consulta_existencia_uno_que_no_existe()
{
	abb_t *abb = abb_crear(comparador_letras);
	char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';
	abb_insertar(abb, &d);
	abb_insertar(abb, &b);
	abb_insertar(abb, &a);
	abb_insertar(abb, &c);
	abb_insertar(abb, &e);
	char z = 'z';

	bool es_inexistente = !abb_existe(abb, &z);

	pa2m_afirmar(
		es_inexistente,
		"Dado abb con 5 elementos, se consulta un elemento que no existe y abb_existe da false.");

	abb_destruir(abb);
}

void abb_con_5_elementos_se_busca_cada_elemento_y_todos_son_los_esperados()
{
	abb_t *abb = abb_crear(comparador_letras);
	char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';
	abb_insertar(abb, &d);
	abb_insertar(abb, &b);
	abb_insertar(abb, &a);
	abb_insertar(abb, &c);
	abb_insertar(abb, &e);

	char *a_buscado = abb_buscar(abb, &a);
	char *b_buscado = abb_buscar(abb, &b);
	char *c_buscado = abb_buscar(abb, &c);
	char *d_buscado = abb_buscar(abb, &d);
	char *e_buscado = abb_buscar(abb, &e);

	bool todos_son_encontrados = (*a_buscado == a && *b_buscado == b &&
				      *c_buscado == c && *d_buscado == d &&
				      *e_buscado == e);

	pa2m_afirmar(
		todos_son_encontrados,
		"Dado abb con 5 elementos, se busca cada uno y se retorna el dato esperado.");

	abb_destruir(abb);
}

void abb_con_5_elementos_se_busca_uno_que_no_existe()
{
	abb_t *abb = abb_crear(comparador_letras);
	char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e';
	abb_insertar(abb, &d);
	abb_insertar(abb, &b);
	abb_insertar(abb, &a);
	abb_insertar(abb, &c);
	abb_insertar(abb, &e);
	char z = 'z';

	pa2m_afirmar(
		abb_buscar(abb, &z) == NULL,
		"Dado abb con 5 elementos, se busca un elemento que no existe y da NULL.");

	abb_destruir(abb);
}

bool contar_completo(void *dato, void *extra)
{
	size_t *contador = extra;
	(*contador)++;
	return true;
}

bool cortar_hasta(void *elemento, void *extra)
{
	int *val = elemento;
	int *limite = extra;
	if (*val == *limite)
		return false;
	return true;
}

void abb_con_tres_letras_itera_inorden()
{
	abb_t *abb = crear_abb_con_3_letras();

	size_t contador = 0;
	size_t afectados = abb_con_cada_elemento(abb, ABB_INORDEN,
						 contar_completo, &contador);

	pa2m_afirmar(
		contador == afectados,
		"El numero de afectados INORDEN es correcta.(esperado:%i ,realidad: %i)",
		contador, afectados);

	abb_destruir(abb);
}

void abb_con_tres_elementos_itera_inorden_hasta_que_de_false_en_segundo_elemento()
{
	abb_t *abb = abb_crear(comparador_letras);
	int raiz = 2;
	int izq = 1;
	int der = 3;
	int corte = 2;
	abb_insertar(abb, &raiz);
	abb_insertar(abb, &izq);
	abb_insertar(abb, &der);

	size_t afectados =
		abb_con_cada_elemento(abb, ABB_INORDEN, cortar_hasta, &corte);

	pa2m_afirmar(
		afectados == 2,
		"El numero de afectados INORDEN es correcta cuando la funcion dio false a la mitad.(esperado:2 ,realidad: %i)",
		afectados);

	abb_destruir(abb);
}

void abb_con_tres_elementos_itera_preorden_hasta_que_de_false_en_segundo_elemento()
{
	abb_t *abb = abb_crear(comparador_letras);
	int raiz = 2;
	int izq = 1;
	int der = 3;
	int corte = 1;
	abb_insertar(abb, &raiz);
	abb_insertar(abb, &izq);
	abb_insertar(abb, &der);

	size_t afectados =
		abb_con_cada_elemento(abb, ABB_PREORDEN, cortar_hasta, &corte);

	pa2m_afirmar(
		afectados == 2,
		"El numero de afectados PREORDEN es correcta cuando la funcion dio false a la mitad.(esperado:2 ,realidad: %i)",
		afectados);

	abb_destruir(abb);
}

void abb_con_tres_elementos_itera_postorden_hasta_que_de_false_en_segundo_elemento()
{
	abb_t *abb = abb_crear(comparador_letras);
	int raiz = 2;
	int izq = 1;
	int der = 3;
	int corte = 3;
	abb_insertar(abb, &raiz);
	abb_insertar(abb, &izq);
	abb_insertar(abb, &der);

	size_t afectados =
		abb_con_cada_elemento(abb, ABB_POSTORDEN, cortar_hasta, &corte);

	pa2m_afirmar(
		afectados == 2,
		"El numero de afectados POSTORDEN es correcta cuando la funcion dio false a la mitad.(esperado:2 ,realidad: %i)",
		afectados);

	abb_destruir(abb);
}

void abb_con_tres_letras_itera_preorden()
{
	abb_t *abb = crear_abb_con_3_letras();

	size_t contador = 0;

	size_t afectados = abb_con_cada_elemento(abb, ABB_PREORDEN,
						 contar_completo, &contador);

	pa2m_afirmar(
		contador == afectados,
		"El numero de afectados PREORDEN es correcta.(esperado:3 ,realidad: %i)",
		afectados);

	abb_destruir(abb);
}

void abb_con_tres_letras_itera_postorden()
{
	abb_t *abb = abb_crear(comparador_letras);
	char a = 'a';
	char c = 'c';
	char b = 'b';
	abb_insertar(abb, &b);
	abb_insertar(abb, &a);
	abb_insertar(abb, &c);
	size_t contador = 0;
	size_t afectados = abb_con_cada_elemento(abb, ABB_POSTORDEN,
						 contar_completo, &contador);

	pa2m_afirmar(
		contador == afectados,
		"El numero de afectados POSTORDEN es correcta.(esperado:3 ,realidad: %i)",
		afectados);

	abb_destruir(abb);
}

void abb_con_tres_elementos_se_agregan_a_un_vector_con_tres_espacios_INORDEN()
{
	abb_t *abb = abb_crear(comparador_letras);
	char a = 'a';
	char c = 'c';
	char b = 'b';
	abb_insertar(abb, &b);
	abb_insertar(abb, &a);
	abb_insertar(abb, &c);

	char *vector[3];
	size_t afectados = abb_vectorizar(abb, ABB_INORDEN, 3, (void **)vector);
	pa2m_afirmar(
		afectados == 3,
		"Se agregan datos de un abb con 3 elementos a un vector con un maximo de 3 elementos. INORDEN (esperado:3 ,datos agregados: %i)",
		afectados);
	pa2m_afirmar(*vector[0] == a, "El primer elemento es correcto %c",
		     *vector[0]);
	pa2m_afirmar(*vector[1] == b, "El segundo elemento es correcto %c",
		     *vector[1]);
	pa2m_afirmar(*vector[2] == c, "El tercero elemento es correcto %c",
		     *vector[2]);
	abb_destruir(abb);
}

void abb_con_tres_elementos_se_agregan_a_un_vector_con_tres_espacios_POSTORDEN()
{
	abb_t *abb = abb_crear(comparador_letras);
	char a = 'a';
	char c = 'c';
	char b = 'b';
	abb_insertar(abb, &b);
	abb_insertar(abb, &a);
	abb_insertar(abb, &c);

	char *vector[3];
	size_t afectados =
		abb_vectorizar(abb, ABB_POSTORDEN, 3, (void **)vector);
	pa2m_afirmar(
		afectados == 3,
		"El numero elementos agregados POSTORDEN es correcta.(esperado:3 ,realidad: %i)",
		afectados);
	pa2m_afirmar(*vector[0] == a, "El primer elemento es correcto %c",
		     *vector[0]);
	pa2m_afirmar(*vector[1] == c, "El segundo elemento es correcto %c",
		     *vector[1]);
	pa2m_afirmar(*vector[2] == b, "El tercero elemento es correcto %c",
		     *vector[2]);
	abb_destruir(abb);
}

void abb_con_dos_elementos_se_agregan_a_un_vector_con_tres_espacios_INORDEN()
{
	abb_t *abb = abb_crear(comparador_letras);
	char a = 'a';
	char b = 'b';
	char z = 'z';
	abb_insertar(abb, &b);
	abb_insertar(abb, &a);
	size_t max_vec = 3;
	char *vector[max_vec];
	vector[2] = &z;
	size_t afectados =
		abb_vectorizar(abb, ABB_INORDEN, max_vec, (void **)vector);
	pa2m_afirmar(
		afectados == 2,
		"Se piden menos elementos para el vector y retorna cantidad correcta. INORDEN (esperado:2 ,realidad: %i)",
		afectados);
	pa2m_afirmar(*vector[0] == a, "El primer elemento es correcto %c",
		     *vector[0]);
	pa2m_afirmar(*vector[1] == b, "El segundo elemento es correcto %c",
		     *vector[1]);
	pa2m_afirmar(*vector[2] == z,
		     "El tercer elemento no se modifico es correcto %c",
		     *vector[2]);
	abb_destruir(abb);
}

void abb_balanceado_con_7_elementos_se_agregan_a_un_vector_con_capacidad_de_4_INORDEN()
{
	abb_t *abb = abb_crear(comparador_letras);

	char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e', f = 'f', g = 'g';
	abb_insertar(abb, &d);
	abb_insertar(abb, &b);
	abb_insertar(abb, &f);
	abb_insertar(abb, &a);
	abb_insertar(abb, &c);
	abb_insertar(abb, &e);
	abb_insertar(abb, &g);

	size_t max_vec = 4;
	char *vector[max_vec];

	char temp = 'x';
	for (size_t i = 0; i < max_vec; i++)
		vector[i] = &temp;

	size_t afectados =
		abb_vectorizar(abb, ABB_INORDEN, max_vec, (void **)vector);

	pa2m_afirmar(
		afectados == max_vec,
		"Dado un arbol con muchos elementos, se llena un vector hasta su maxima capacidad.",
		max_vec, afectados);
	pa2m_afirmar(
		afectados == max_vec,
		"Se retorna la cantidad correcta (esperado:%i ,realidad: %i)",
		max_vec, afectados);
	pa2m_afirmar(*vector[0] == 'a', "Primer elemento INORDEN correcto: %c",
		     *vector[0]);
	pa2m_afirmar(*vector[1] == 'b', "Segundo elemento INORDEN correcto: %c",
		     *vector[1]);
	pa2m_afirmar(*vector[2] == 'c', "Tercer elemento INORDEN correcto: %c",
		     *vector[2]);
	pa2m_afirmar(*vector[3] == 'd', "Cuarto elemento INORDEN correcto: %c",
		     *vector[3]);

	abb_destruir(abb);
}

void abb_balanceado_con_7_elementos_se_agregan_solo_4_a_un_vector_de_10_INORDEN()
{
	abb_t *abb = abb_crear(comparador_letras);

	char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e', f = 'f', g = 'g';
	abb_insertar(abb, &d);
	abb_insertar(abb, &b);
	abb_insertar(abb, &f);
	abb_insertar(abb, &a);
	abb_insertar(abb, &c);
	abb_insertar(abb, &e);
	abb_insertar(abb, &g);

	size_t max_vec = 10;
	char *vector[max_vec];

	char temp = 'x';
	for (size_t i = 0; i < max_vec; i++)
		vector[i] = &temp;

	size_t elementos_a_guardar = 4;
	size_t afectados = abb_vectorizar(abb, ABB_INORDEN, elementos_a_guardar,
					  (void **)vector);

	pa2m_afirmar(
		afectados == elementos_a_guardar,
		"Dado vector con capacidad de 10, solo se piden 4 y no se modifican el resto. INORDEN ",
		elementos_a_guardar, afectados);

	pa2m_afirmar(
		afectados == elementos_a_guardar,
		"El numero elementos agregados INORDEN es correcta.(esperado:%i ,realidad: %i)",
		elementos_a_guardar, afectados);
	pa2m_afirmar(*vector[0] == 'a', "Primer elemento INORDEN correcto: %c",
		     *vector[0]);
	pa2m_afirmar(*vector[1] == 'b', "Segundo elemento INORDEN correcto: %c",
		     *vector[1]);
	pa2m_afirmar(*vector[2] == 'c', "Tercer elemento INORDEN correcto: %c",
		     *vector[2]);
	pa2m_afirmar(*vector[3] == 'd', "Cuarto elemento INORDEN correcto: %c",
		     *vector[3]);

	for (size_t i = 4; i < max_vec; i++)
		pa2m_afirmar(*vector[i] == 'x', "Elemento %i no modificado", i);

	abb_destruir(abb);
}

void abb_con_tres_elementos_se_agregan_a_un_vector_con_tres_espacios_PREORDEN()
{
	abb_t *abb = abb_crear(comparador_letras);
	char a = 'a';
	char c = 'c';
	char b = 'b';
	abb_insertar(abb, &b);
	abb_insertar(abb, &a);
	abb_insertar(abb, &c);

	char *vector[3];
	size_t afectados =
		abb_vectorizar(abb, ABB_PREORDEN, 3, (void **)vector);
	pa2m_afirmar(
		afectados == 3,
		"El numero elementos agregados PREORDEN es correcta.(esperado:3 ,realidad: %i)",
		afectados);
	pa2m_afirmar(*vector[0] == b, "El primer elemento es correcto %c",
		     *vector[0]);
	pa2m_afirmar(*vector[1] == a, "El segundo elemento es correcto %c",
		     *vector[1]);
	pa2m_afirmar(*vector[2] == c, "El tercero elemento es correcto %c",
		     *vector[2]);
	abb_destruir(abb);
}

void abb_con_dos_elementos_se_agregan_a_un_vector_con_tres_espacios_PREORDEN()
{
	abb_t *abb = abb_crear(comparador_letras);
	char a = 'a';
	char b = 'b';
	char z = 'z';
	abb_insertar(abb, &b);
	abb_insertar(abb, &a);
	size_t max_vec = 3;
	char *vector[max_vec];
	vector[2] = &z;
	size_t afectados =
		abb_vectorizar(abb, ABB_PREORDEN, max_vec, (void **)vector);
	pa2m_afirmar(
		afectados == 2,
		"El numero elementos agregados PREORDEN es correcta.(esperado:2 ,realidad: %i)",
		afectados);
	pa2m_afirmar(*vector[0] == b, "El primer elemento es correcto %c",
		     *vector[0]);
	pa2m_afirmar(*vector[1] == a, "El segundo elemento es correcto %c",
		     *vector[1]);
	pa2m_afirmar(*vector[2] == z,
		     "El tercer elemento no se modifico es correcto %c",
		     *vector[2]);
	abb_destruir(abb);
}

void abb_con_dos_elementos_se_agregan_a_un_vector_con_tres_espacios_POSTORDEN()
{
	abb_t *abb = abb_crear(comparador_letras);
	char a = 'a';
	char b = 'b';
	char z = 'z';
	abb_insertar(abb, &b);
	abb_insertar(abb, &a);
	size_t max_vec = 3;
	char *vector[max_vec];
	vector[2] = &z;
	size_t afectados =
		abb_vectorizar(abb, ABB_POSTORDEN, max_vec, (void **)vector);
	pa2m_afirmar(
		afectados == 2,
		"El numero elementos agregados POSTORDEN es correcta.(esperado:2 ,realidad: %i)",
		afectados);
	pa2m_afirmar(*vector[0] == a, "El primer elemento es correcto %c",
		     *vector[0]);
	pa2m_afirmar(*vector[1] == b, "El segundo elemento es correcto %c",
		     *vector[1]);
	pa2m_afirmar(*vector[2] == z,
		     "El tercer elemento no se modifico es correcto %c",
		     *vector[2]);
	abb_destruir(abb);
}

void abb_valido_se_obtiene_el_dato_de_raiz()
{
	abb_t *abb = abb_crear(comparador_letras);
	char a = 'a';

	abb_insertar(abb, &a);

	char *dato_raiz = abb_raiz(abb);
	pa2m_afirmar(
		*dato_raiz == a,
		"Dado abb con elementos se obtiene el dato de raiz y es el esperado");

	abb_destruir(abb);
}

void abb_recien_creado_se_obtiene_raiz_pero_da_null()
{
	abb_t *abb = abb_crear(comparador_letras);

	pa2m_afirmar(
		abb_raiz(abb) == NULL,
		"Dado abb recien creado da NULL al querer la raiz porque no tiene.");

	abb_destruir(abb);
}

void abb_null_al_obtener_raiz_da_null()
{
	void *dato_raiz = abb_raiz(NULL);
	bool es_valido = !dato_raiz;
	pa2m_afirmar(es_valido,
		     "Se quiere obtener raiz de un abb NULL y da NULL.");
}

void abb_null_se_busca_elemento_pero_da_null()
{
	int tres = 3;
	pa2m_afirmar(abb_buscar(NULL, &tres) == NULL,
		     "Dado abb nulo, abb_buscar da NULL.");
}

void abb_con_3_elementos_se_eliminan_solo_una_hoja()
{
	abb_t *abb = abb_crear(comparador_letras);
	char izq = 'a';
	char der = 'c';
	char raiz = 'b';
	char sin_elemento = 'x';
	abb_insertar(abb, &raiz);
	abb_insertar(abb, &izq);
	abb_insertar(abb, &der);
	size_t cantidad_anterior = abb_cantidad(abb);
	char *eliminado = abb_eliminar(abb, &izq);

	size_t max_vec = 3;
	char *vector[max_vec];
	vector[2] = &sin_elemento;
	size_t afectados =
		abb_vectorizar(abb, ABB_PREORDEN, max_vec, (void **)vector);
	bool conserva_su_forma = (afectados == abb_cantidad(abb) &&
				  *vector[0] == raiz && *vector[1] == der &&
				  *vector[2] == sin_elemento);

	pa2m_afirmar(
		*eliminado == izq,
		"Dado abb se elimina una hoja y se retorna el dato esperado.");
	pa2m_afirmar(abb_cantidad(abb) == cantidad_anterior - 1,
		     "La cantidad baja en uno.");
	pa2m_afirmar(abb_buscar(abb, eliminado) == NULL,
		     "Se intenta buscar el elemento eliminado y da NULL");
	pa2m_afirmar(conserva_su_forma, "El arbol conserva su forma.");

	abb_destruir(abb);
}

void abb_con_3_elementos_se_elimina_nodo_con_un_hijo()
{
	abb_t *abb = abb_crear(comparador_letras);
	char raiz = 'b';
	char hijo_der = 'c';
	char nieto_der = 'd';
	char sin_elemento = 'x';

	abb_insertar(abb, &raiz);
	abb_insertar(abb, &hijo_der);
	abb_insertar(abb, &nieto_der);

	size_t cantidad_anterior = abb_cantidad(abb);
	char *eliminado = abb_eliminar(abb, &hijo_der);

	size_t max_vec = 3;
	char *vector[max_vec];
	vector[2] = &sin_elemento;
	size_t afectados =
		abb_vectorizar(abb, ABB_PREORDEN, max_vec, (void **)vector);
	bool conserva_su_forma =
		(afectados == abb_cantidad(abb) && *vector[0] == raiz &&
		 *vector[1] == nieto_der && *vector[2] == sin_elemento);

	pa2m_afirmar(
		*eliminado == hijo_der,
		"Dado abb se elimina un nodo con un hijo y se retorna el dato esperado.");
	pa2m_afirmar(abb_cantidad(abb) == cantidad_anterior - 1,
		     "La cantidad baja en uno.");
	pa2m_afirmar(abb_buscar(abb, eliminado) == NULL,
		     "Se intenta buscar el elemento eliminado y da NULL.");
	pa2m_afirmar(conserva_su_forma,
		     "El árbol conserva su forma (nieto se enlaza con raíz).");

	abb_destruir(abb);
}

void abb_con_5_elementos_se_elimina_nodo_con_dos_hijos()
{
	abb_t *abb = abb_crear(comparador_letras);
	char raiz = 'd';
	char izq = 'b';
	char der = 'f';
	char izq_izq = 'a';
	char izq_der = 'c';
	char sin_elemento = 'x';

	abb_insertar(abb, &raiz);
	abb_insertar(abb, &izq);
	abb_insertar(abb, &der);
	abb_insertar(abb, &izq_izq);
	abb_insertar(abb, &izq_der);

	size_t cantidad_anterior = abb_cantidad(abb);
	char *eliminado = abb_eliminar(abb, &izq);

	size_t max_vec = 5;
	char *vector[max_vec];
	vector[4] = &sin_elemento;
	size_t afectados =
		abb_vectorizar(abb, ABB_PREORDEN, max_vec, (void **)vector);
	bool conserva_su_forma = (afectados == abb_cantidad(abb) &&
				  *vector[0] == raiz && *vector[1] == izq_izq &&
				  *vector[2] == izq_der && *vector[3] == der &&
				  *vector[4] == sin_elemento);

	pa2m_afirmar(
		*eliminado == izq,
		"Dado abb se elimina un nodo con dos hijos y se retorna el dato esperado.");
	pa2m_afirmar(abb_cantidad(abb) == cantidad_anterior - 1,
		     "La cantidad baja en uno.");
	pa2m_afirmar(abb_buscar(abb, eliminado) == NULL,
		     "Se intenta buscar el elemento eliminado y da NULL.");
	pa2m_afirmar(
		conserva_su_forma,
		"El árbol conserva su forma (se reemplaza con el predecesor inorden).");

	abb_destruir(abb);
}

void abb_null_no_se_puede_eliminar_y_da_null()
{
	int algo = 1;
	pa2m_afirmar(
		abb_eliminar(NULL, &algo) == NULL,
		"Se intenta eliminar un elemento de un abb NULL y no se puede.");
}

void abb_null_no_se_iterada_y_devuelve_cero()
{
	size_t contador = 0;
	size_t afectados = abb_con_cada_elemento(NULL, ABB_PREORDEN,
						 contar_completo, &contador);
	pa2m_afirmar(contador == afectados,
		     "No se itera con iterador interno si abb es NULL");
}

void abb_nulo_no_se_puede_insertar()
{
	pa2m_afirmar(!abb_insertar(NULL, NULL),
		     "Dado ABB nulo, abb_insertar da false");
}

void abb_nulo_no_existe_ningun_elemento()
{
	pa2m_afirmar(!abb_existe(NULL, NULL),
		     "Dado ABB nulo, abb_existe da false");
}

void abb_nulo_no_se_puede_vectorizar()
{
	size_t max_vec = 1;
	char sin_elemento = 'x';
	char *vector[max_vec];
	vector[0] = &sin_elemento;
	pa2m_afirmar(abb_vectorizar(NULL, ABB_PREORDEN, max_vec,
				    (void **)vector) == 0,
		     "Dado ABB nulo, abb_vectorizar da cero");
	pa2m_afirmar(*vector[0] == sin_elemento, "No cambia el vector");
}

void abb_valido_no_se_puede_vectorizar_con_vector_null()
{
	abb_t *abb = crear_abb_con_3_letras();
	pa2m_afirmar(abb_vectorizar(abb, ABB_PREORDEN, 3, NULL) == 0,
		     "Dado vector nulo, abb_vectorizar da cero");
	abb_destruir(abb);
}

char **crear_datos_5()
{
	char **datos = malloc(sizeof(char *) * 5);
	char valores[] = { 'a', 'b', 'c', 'd', 'e' };
	for (int i = 0; i < 5; i++) {
		datos[i] = malloc(sizeof(char));
		*datos[i] = valores[i];
	}
	return datos;
}

void destructor(void *dato)
{
	free(dato);
}

void insertar_eliminar_buscar_abb()
{
	char **datos = crear_datos_5();
	abb_t *abb = abb_crear(comparador_letras);

	for (int i = 0; i < 5; i++) {
		pa2m_afirmar(abb_insertar(abb, datos[i]),
			     "Se inserta un elemento");
	}
	pa2m_afirmar(abb_cantidad(abb) == 5, "Cantidad correcta de elementos");

	char *dato_raiz = abb_raiz(abb);
	char *eliminado = abb_eliminar(abb, dato_raiz);
	pa2m_afirmar(eliminado != NULL, "Se eliminó la raíz correctamente");
	pa2m_afirmar(abb_buscar(abb, eliminado) == NULL,
		     "La raíz ya no existe");

	pa2m_afirmar(abb_insertar(abb, eliminado), "Se reinserta la raíz");
	pa2m_afirmar(abb_buscar(abb, eliminado) != NULL,
		     "Se puede buscar el elemento reinsertado");
	char *nueva_raiz = abb_raiz(abb);
	pa2m_afirmar(nueva_raiz != eliminado,
		     "La nueva raíz no apunta al mismo puntero eliminado");

	abb_destruir_todo(abb, destructor);
	free(datos);
}

int main()
{
	pa2m_nuevo_grupo("============== CREACION EN ABB ===============");
	se_crea_abb_con_comparador_de_letras_vacio_exitosamente_y_se_verifica_datos();

	pa2m_nuevo_grupo("============== INSERCION EN ABB ===============");
	abb_vacio_se_inserta_un_dato();
	abb_con_un_elemento_se_inserta_otro_exitosamente();

	pa2m_nuevo_grupo("============== EXISTENCIA DE ABB ===============");
	abb_con_5_elementos_se_consulta_existencia_cada_elemento_y_todos_existen();
	abb_con_5_elementos_se_consulta_existencia_uno_que_no_existe();

	pa2m_nuevo_grupo("============== BUSQUEDA EN ABB ===============");
	abb_con_5_elementos_se_busca_cada_elemento_y_todos_son_los_esperados();
	abb_con_5_elementos_se_busca_uno_que_no_existe();

	pa2m_nuevo_grupo("============== ELIMINACION EN ABB ===============");
	abb_con_3_elementos_se_eliminan_solo_una_hoja();
	abb_con_3_elementos_se_elimina_nodo_con_un_hijo();
	abb_con_5_elementos_se_elimina_nodo_con_dos_hijos();

	pa2m_nuevo_grupo("============== RAIZ DE ABB ===============");
	abb_valido_se_obtiene_el_dato_de_raiz();
	abb_recien_creado_se_obtiene_raiz_pero_da_null();

	pa2m_nuevo_grupo("============== CANTIDAD DE ABB ===============");
	abb_vacio_su_cantidad_es_cero();
	abb_con_7_elementos_su_cantidad_es_correcta();

	pa2m_nuevo_grupo("============== VACIEDAD DE ABB ===============");
	abb_vacio_da_vacio();
	abb_no_vacio_da_false();

	pa2m_nuevo_grupo(
		"============== ITERADOR Y VECTORIZACION ABB ===============");

	abb_con_tres_elementos_se_agregan_a_un_vector_con_tres_espacios_INORDEN();
	abb_con_tres_elementos_se_agregan_a_un_vector_con_tres_espacios_PREORDEN();
	abb_con_tres_elementos_se_agregan_a_un_vector_con_tres_espacios_POSTORDEN();
	abb_con_tres_letras_itera_inorden();
	abb_con_tres_letras_itera_postorden();
	abb_con_tres_letras_itera_preorden();
	abb_con_tres_elementos_itera_inorden_hasta_que_de_false_en_segundo_elemento();
	abb_con_tres_elementos_itera_preorden_hasta_que_de_false_en_segundo_elemento();
	abb_con_tres_elementos_itera_postorden_hasta_que_de_false_en_segundo_elemento();
	abb_con_dos_elementos_se_agregan_a_un_vector_con_tres_espacios_INORDEN();
	abb_con_dos_elementos_se_agregan_a_un_vector_con_tres_espacios_PREORDEN();
	abb_con_dos_elementos_se_agregan_a_un_vector_con_tres_espacios_POSTORDEN();
	abb_balanceado_con_7_elementos_se_agregan_a_un_vector_con_capacidad_de_4_INORDEN();
	abb_balanceado_con_7_elementos_se_agregan_solo_4_a_un_vector_de_10_INORDEN();

	pa2m_nuevo_grupo("============== PUNTEROS NULL ===============");

	se_intenta_crear_abb_con_comparador_null_y_no_se_puede();
	abb_nulo_no_se_puede_insertar();
	abb_nulo_no_existe_ningun_elemento();
	abb_nulo_no_se_puede_vectorizar();
	abb_valido_no_se_puede_vectorizar_con_vector_null();
	abb_null_su_cantidad_es_cero();
	abb_null_da_vacio();
	abb_null_al_obtener_raiz_da_null();
	abb_null_se_busca_elemento_pero_da_null();
	abb_null_no_se_puede_eliminar_y_da_null();
	abb_null_no_se_iterada_y_devuelve_cero();

	pa2m_nuevo_grupo(
		"============== INSERTAR-ELIMINAR-BUSCAR ===============");

	insertar_eliminar_buscar_abb();

	return pa2m_mostrar_reporte();
}

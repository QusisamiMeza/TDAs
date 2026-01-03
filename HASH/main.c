#include "src/comandos.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	comando_t *comando = crear_comando(argc, argv);
	if (!comando) {
		printf("Ingrese el comando de forma ./mi_ejecutable mi_archivo.csv buscar id_o_nombre dato_buscado.\n");
		return 1;
	}

	if (!ejecutar_comando(comando)) {
		printf("No se pudo realizar la operacion deseada.\n");
	}

	destruir_comando(comando);

	return 0;
}

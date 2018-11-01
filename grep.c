#define _POSIX_C_SOURCE 200809L 
#include "cola.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>
#define BASE 10
#define OP_PARAM_1 3
#define OP_PARAM_2 4
#define I_CADENA 1
#define I_CANT_LINEAS 2
#define I_RUTA_ARCH 3
#define ERROR -1

/* Dada una cadena de caracteres,
 * devuelve true si es un número,
 * false caso contrario.
 */
bool es_numero(const char *cadena);

/* Dado una cantidad de argumentos y un
 * vector de argumentos, la función devuelva
 * true si la cantidad y tipo de parametros es
 * correcta, false caso contrario.
 * En caso de error lo imprimirá a stderr.
 */
bool verificar_entrada(int argc, char * argv[]);

/* Dado un archivo abierto, la función muestra 
 * en pantalla las líneas del archivo que contangan 
 * la cadena y las cantidad_lineas anteriores a 
 * la aparición de la misma.
 */
void procesar_archivo(FILE * archivo, char * cadena, size_t cant_lineas);

/* Dada una cadena de caractes y una subcadena,
 * devuelve true si la subcadena está contenida
 * en cadena, false caso contrario.
 */
bool contiene_sub(char *cadena, char *sub_cadena);

/* Muestra en pantalla todos los
 * elementos de la cola.
 * Pre: La cola fue creada y contiene 
 * cadena de caracteres.
 * Post: La cola quedará vacia.
 */
void imprimir_cola(cola_t* cola);

/* Función principal del programa grep.
 * Recibe parametros por consola:
 *   Una cadena, que va a ser la que se usará 
 *	para ver si esa cadena está contenida en 
 *	cada línea del archivo o entrada estándar.
 *   Un numero entero N que será la cantidad 
 *	de líneas a mostrar por consola antes del
 *	“match” de la cadena y la línea leída.
 *   Opcionalmente un nombre de archivo que 
 *	va a ser el archivo que grep va a tener 
 *	que leer, si no recibe este parámetro, 
 *	tiene que leer de entrada estándar.
 * Devuelve -1 en caso de error, 0 en caso de 
 * que la ejecución haya sido exitosa.
 */
int main(int argc, char *argv[]) {
	char *cadena = NULL;
	size_t cant_lineas = 0;
	char *ruta_archivo = NULL;
	
	if(!verificar_entrada(argc, argv)) return ERROR;

	cadena = argv[I_CADENA];
	cant_lineas = (size_t) atoi(argv[I_CANT_LINEAS]);
	
	if(argc == OP_PARAM_2) ruta_archivo = argv[I_RUTA_ARCH];
	
	FILE * archivo = NULL;
	
	if(ruta_archivo && !(archivo = fopen(argv[I_RUTA_ARCH], "r"))) {
		fprintf(stderr, "No se pudo leer el archivo indicado\n");
		return ERROR;
	} 
	if(!ruta_archivo) archivo = stdin;

	procesar_archivo(archivo, cadena, cant_lineas);

	fclose(archivo);
	return 0;
}

bool contiene_sub(char *cadena, char *sub_cadena) {
	size_t lon_sub = strlen(sub_cadena);
	size_t lon_cad = strlen(cadena);
	if(lon_sub > lon_cad)
		return false;
	for(size_t i = 0; i < (lon_cad - lon_sub + 1); i++) {
		if(strncmp(cadena, sub_cadena, lon_sub) == 0) return true;
		cadena++;
	}
	return false;
}

bool verificar_entrada(int argc, char *argv[]) {
	if(argc != OP_PARAM_1 && argc != OP_PARAM_2) {
		fprintf(stderr, "Cantidad de parametros erronea\n");
		return false;
	}
	if(!es_numero(argv[I_CANT_LINEAS])){
		fprintf(stderr, "Tipo de parametro incorrecto\n");
		return false;
	}
	return true;
}

void procesar_archivo(FILE * archivo, char * cadena, size_t cant_lineas) {
	char *linea = NULL;
	size_t tam = 0;
	cola_t* lineas = cola_crear();
	if(!lineas) return;
	size_t lineas_cargadas = 0;

	while(getline(&linea, &tam, archivo) > 0) {
		
		if(contiene_sub(linea, cadena)) {
			imprimir_cola(lineas);
			lineas_cargadas = 0;
			fprintf(stdout, "%s", linea);
		}else {
			char *linea_e = strdup(linea);
			cola_encolar(lineas, linea_e);
			lineas_cargadas++;
		}
		if(lineas_cargadas > cant_lineas) {
			free(cola_desencolar(lineas));
			lineas_cargadas--;
		}

	}
	cola_destruir(lineas, free);
	free(linea);
}

bool es_numero(const char *cadena) {
	int i = 0;
	while(cadena[i]) {
		if(!isdigit(cadena[i]))
			return false;
		i++;
	}
	return true;
}

void imprimir_cola(cola_t* cola) {
	while(!cola_esta_vacia(cola)) {
		char *linea_d = cola_desencolar(cola);
		fprintf(stdout, "%s", linea_d);
		free(linea_d);
	}
}
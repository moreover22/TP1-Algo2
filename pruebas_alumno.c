#include "strutil.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

/* *****************************************************************
 *                  PRUEBAS UNITARIAS DEL ALUMNO
 * *****************************************************************/
void mostrar_vector(char ** vector) {
	int i = 0;
	printf("[");
	while(vector[i]) {
		printf("\"%s\"", vector[i]);
		i++;
		if(vector[i])
			printf(", ");
	}
	printf("]\n");
}
void prueba_split() {
	char **vector1 = split("asd,asd", ',');
	char **vector2 = split(",", ',');
	char **vector3 = split("abc,,def", ',');
	char **vector4 = split("abc,def,", ',');
	char **vector5 = split(",abc,def", ',');
	char **vector6 = split("abc", '\0');
	char **vector7 = split("", ',');
	char **vector8 = split("hola,more\n", ',');

	mostrar_vector(vector1);
	mostrar_vector(vector2);
	mostrar_vector(vector3);
	mostrar_vector(vector4);
	mostrar_vector(vector5);
	mostrar_vector(vector6);
	mostrar_vector(vector7);
	mostrar_vector(vector8);

	char * jvec1 = join(vector7, ',');
	printf("%s\n", jvec1);
	char * jvec2 = join(vector6, ',');
	printf("%s\n", jvec2);
	char * jvec3 = join(vector8, ',');
	printf("%s\n", jvec3);
	char * jvec4 = join(NULL, ',');
	printf("\"%s\"\n", jvec4);

	free_strv(vector1);
	free_strv(vector2);
	free_strv(vector3);
	free_strv(vector4);
	free_strv(vector5);
	free_strv(vector6);
	free_strv(vector7);
	free_strv(vector8);

	free(jvec1);
	free(jvec2);
	free(jvec3);
	free(jvec4);
}

/*
 * Se ejecutan todas las pruebas.
 */
void pruebas_tp1_alumno() {
	prueba_split();
}

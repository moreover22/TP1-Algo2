#include "operaciones.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int _raizEnt(int valor, int inicio, int final, int anterior) {
	if (inicio >= final)
		return anterior;

	int medio = (inicio + final) / 2;

	if (medio * medio == valor)
		return medio;

	if (medio * medio < valor)
		return _raizEnt(valor, medio + 1, final, medio);

	return _raizEnt(valor, inicio, medio, anterior);
}
int log_n(int n, int base) {
	if (n > base - 1) 
		return 1 + log_n(n / base, base);
	else return 0;
}
int raizEnt(int numero) {
	if(numero <= 1)
		return numero;
	return _raizEnt(numero, 1, numero, numero);
}

int potencia(int base, int exponente) {
	if(exponente <= 0)
		return 1;
	int med_potencia;
	if(exponente % 2 == 0){
		med_potencia = potencia(base, exponente / 2 );
		return med_potencia * med_potencia;
	}
	med_potencia = potencia(base, (exponente - 1) / 2);
	return med_potencia * med_potencia * base;
}
bool es_numero(char *cadena) {
	if(!cadena) return false;
	int i = 0;
	size_t len = strlen(cadena);
	if (len > 1 && (cadena[i] == '+' || cadena[i] == '-'))
		i = 1;
	for(int j = i; j < len; j++)
		if(!isdigit(cadena[j]))
			return false;
	return true;
}

int obtener_numero(char * str) {
	int numero = atoi(str);
	free(str);
	return numero;
}
int obtener_operacion(char * operador) {
	if(!strcmp(operador, "+")) return SUMA;
	if(!strcmp(operador, "-")) return RESTA;
	if(!strcmp(operador, "*")) return MULT;
	if(!strcmp(operador, "/")) return DIVI;
	if(!strcmp(operador, "^")) return POTENCIA;
	if(!strcmp(operador, "sqrt")) return RAIZ;
	if(!strcmp(operador, "?")) return TERNARIO;
	if(!strcmp(operador, "log")) return LOG;
	return -1;
}

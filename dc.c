#define _POSIX_C_SOURCE 200809L 
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include "pila.h"
#include "strutil.h"
#include "operaciones.h"

/* Dada una pila se desapilan dos elementos y 
 * se los almacena en operando_1 y operando_2
 * en ese orden. 
 * En caso de que la pila tenga los suficientes 
 * elementos (2) y ambos son números enteros,
 * la función devuelve true, en caso contrario 
 * devuelve false.
 * Pre: pila fue creada.
 * Post: la pila contará con 2 elementos menos 
 * luego de la ejecución.
 */
bool obtener_dos_operandos(pila_t * pila, int * operando_1, int * operando_2);

/***********************************************************
 * Las siguientes funciones: _raiz, _suma, _resta,         *
 * _multiplicacion, _division, _potencia, _logaritmo,      *
 * _ternario. Reciben una pila donde se sacarán los        *
 * operandos para poder realizar la operación de cada      *
 * función y se el se guardará su solución en resultado.   *
 * Las funciones devolverán true en caso de que hayan po-  *
 * dido operar correctamente (suficientes operandos y      *
 * operaciones válidas) o false en caso contrario.         *
 * Pre: pila fue creado.                                   *
 * Post: se eliminaran hasta tres elementos de pila,       *
 * resultado contendrá el valor de la operación en caso de *
 * éxito.                                                  *
 ***********************************************************/
bool _raiz(pila_t * pila, int * resultado);
bool _suma(pila_t * pila, int * resultado);
bool _resta(pila_t * pila, int * resultado);
bool _multiplicacion(pila_t * pila, int * resultado);
bool _division(pila_t * pila, int * resultado);
bool _potencia(pila_t * pila, int * resultado);
bool _logaritmo(pila_t * pila, int * resultado);
bool _ternario(pila_t * pila, int * resultado);

/* Dado un string operador que puede ser:
 * operador = "+"|"-"|"*"|"/"|"log"|"sqrt"|"^"|"^"
 * Un puntero a un entero resultado, la cantidad
 * de operandos que necesita el operador, y una pila
 * con los operandos la función almacena el resultado 
 * del operador aplicados en los operandos en resultado
 * y devuelve true en caso exito o false en caso de error.
 * Pre: pila fue creada.
 */
bool operar(char * operador, int* resultado, pila_t * pila);

/* Dada una pila, se eliminan todos 
 * los elementos de la misma y se libera
 * la memoria asociada a los elementos.
 * Pre: pila fue creada.
 * Post: pila quedará vacía y todos los
 * elementos fueron liberados.
 */
void pila_vaciar(pila_t * pila);

/* Dado un string con una expresión en
 * la notación polaca inversa, almacena
 * el resultado de dicha operación en resultado
 * y devuvelve true en caso de éxito o bien false
 * en caso de error.
 */
bool resolver(char** entrada, int* resultado);

/*
 * Función principal del programa dc.
 */
int main(void) {
	char* linea = NULL;
	size_t tam = 0;
	ssize_t len = 0;
	int resultado = 0;
	bool opero = false;

	while((len = getline(&linea, &tam, stdin)) > 0) {
		linea[len - 1] = '\0';
		char ** entrada = split(linea, ' ');
		if(resolver(entrada, &resultado))
			printf("%d\n", resultado);
		else 
			printf("ERROR\n");
		free_strv(entrada);
		opero = true;
	}

	if(!opero)//Por si el archivo está vacio
		printf("ERROR\n");

	free(linea);
	return 0;
}

/******************************************************
 *              FUNCIONES AUXILIARES                  *
 ******************************************************/
void pila_vaciar(pila_t * pila) {
	while(!pila_esta_vacia(pila)) 
		free(pila_desapilar(pila));
}

bool operar(char * operador, int* resultado, pila_t * pila) {
	switch(obtener_operacion(operador)) {
		case RAIZ: return _raiz(pila, resultado);
		case SUMA: return _suma(pila, resultado);
		case RESTA: return _resta(pila, resultado);
		case MULT: return _multiplicacion(pila, resultado); 
		case DIVI: return _division(pila, resultado);
		case POTENCIA: return _potencia(pila, resultado);
		case LOG: return _logaritmo(pila, resultado);
		case TERNARIO: return _ternario(pila, resultado);
		default: return false;
	}
}

bool resolver(char** entrada, int* resultado) {
	pila_t* pila = pila_crear();
	bool opera = false;
	size_t i = 0;
	while (entrada[i]) {
		if(strcmp(entrada[i], "") == 0) {
			i++;
			continue;
		}
		if(es_numero(entrada[i])) {
			char * numero = strdup(entrada[i]);
			pila_apilar(pila, numero);
			i++;
			continue;
		}
		opera = operar(entrada[i], resultado, pila);
		if(!opera) break;
		char buffer[BUFFER_INT];
		sprintf(buffer, "%d", *resultado);
		pila_apilar(pila, strdup(buffer));
		i++;
	}
	char * ultimo = pila_desapilar(pila);
	if((opera &= es_numero(ultimo)))
		*resultado = obtener_numero(ultimo); // obtener numero libera la memoria
	else
		free(ultimo);

	opera &= pila_esta_vacia(pila); 
	pila_vaciar(pila);
	pila_destruir(pila);
	return opera;
}

bool obtener_dos_operandos(pila_t * pila, int * operando_1, int * operando_2) {
	char * operando_1_c = pila_desapilar(pila);
	char * operando_2_c = pila_desapilar(pila);
	if(!es_numero(operando_1_c) || !es_numero(operando_2_c)) {
		free(operando_1_c);
		free(operando_2_c);
		return false;
	}
	*operando_1 = obtener_numero(operando_1_c);
	*operando_2 = obtener_numero(operando_2_c);
	return true;
}

/**********************************************
 *          FUNCIONES AUX. DE OPERACIONES     *
 **********************************************/
bool _raiz(pila_t * pila, int * resultado) {
	char * operando_c = pila_desapilar(pila);
	if(!es_numero(operando_c)) {
		free(operando_c);
		return false;
	}
	int operando = obtener_numero(operando_c);
	if(operando < 0) return false;
	*resultado = raizEnt(operando); 
	return true;
}
bool _suma(pila_t * pila, int * resultado) {
	int operando_1;
	int operando_2;
	if(!obtener_dos_operandos(pila, &operando_1, &operando_2))
		return false;
	*resultado = operando_1 + operando_2;
	return true;
}

bool _resta(pila_t * pila, int * resultado) {
	int operando_1;
	int operando_2;
	if(!obtener_dos_operandos(pila, &operando_1, &operando_2))
		return false;
	*resultado = -operando_1 + operando_2;
	return true;
}
bool _multiplicacion(pila_t * pila, int * resultado) {
	int operando_1;
	int operando_2;
	if(!obtener_dos_operandos(pila, &operando_1, &operando_2))
		return false;
	*resultado = operando_1 * operando_2;
	return true;
}

bool _division(pila_t * pila, int * resultado) {
	int divisor;
	int dividendo;
	if(!obtener_dos_operandos(pila, &divisor, &dividendo))
		return false;
	if(dividendo == 0) return false;

	*resultado = divisor / dividendo;
	return true;
}

bool _potencia(pila_t * pila, int * resultado) {
	int base;
	int exponente;
	if(!obtener_dos_operandos(pila, &base, &exponente))
		return false;
	if(base < 0 || exponente < 0) return false;
	*resultado = potencia(base, exponente);
	return true;
}

bool _logaritmo(pila_t * pila, int * resultado) {
	int argumento;
	int base;
	if(!obtener_dos_operandos(pila, &argumento, &base))
		return false;
	if(argumento <= 0 || base <= 1) return false;
	*resultado = log_n(argumento, base);
	return true;
}
bool _ternario(pila_t * pila, int * resultado) {
	char * condicion_c = pila_desapilar(pila);
	char * operando_1_c = pila_desapilar(pila);
	char * operando_2_c = pila_desapilar(pila);

	if(!es_numero(condicion_c) || !es_numero(operando_1_c) || !es_numero(operando_2_c)) {
		free(condicion_c);
		free(operando_1_c);
		free(operando_2_c);
		return false;
	}
	int condicion = obtener_numero(condicion_c);
	int operando_1 = obtener_numero(operando_1_c);
	int operando_2 = obtener_numero(operando_2_c);
	*resultado = (condicion)? operando_1 : operando_2; 
	return true;
}
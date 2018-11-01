#ifndef OPERACIONES_H
#define OPERACIONES_H
#include <stdbool.h>
enum{
	SUMA,
	RESTA,
	MULT,
	DIVI,
	RAIZ,
	POTENCIA,
	LOG,
	TERNARIO
};
#define OP_1 1
#define OP_2 2
#define OP_3 3
#define BUFFER_INT 12
/*
 * Devuelve la parte entera de 
 * la raiz cuadrade de numero.
 */
int raizEnt(int numero);
int _raizEnt(int valor, int inicio, int final, int anterior);

/*
 * Devuelve la parte entera del
 * logaritmo en base base de n.
 */

int log_n(int n, int base);
/*
 * Dado un número entero base y 
 * un número entero exponente,
 * devuelve base ^ exponente.
 * Se espera que ambos sean positivos.
 */
int potencia(int base, int exponente);
/*
 * Devuelve el hash de un String.
 */
unsigned long hash(char *str);
/* 
 * Dada una cadena de caracteres,
 * devuelve true si es un número,
 * false caso contrario.
 */
bool es_numero(char *cadena);

int obtener_numero(char * str);

int obtener_operacion(char * operador);

#endif  // OPERACIONES_H

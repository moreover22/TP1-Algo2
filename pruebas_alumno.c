#include "lista.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#define VOLUMEN_1 1000
#define VOLUMEN_2 10000
#define CANT_NULLS 500
#define CANT_LISTAS 50
#define LISTA_VACIAR_OP_ARGS 3
#define N_ELEMENTOS_MOSTRAR 10

/* *****************************************************************
 *                  PRUEBAS UNITARIAS DEL ALUMNO
 * *****************************************************************/

/* *****************************************************************
 *                  PRUEBAS PRIMITIVAS LISTA
 * *****************************************************************/
/*
 * Prueba de creación de múltiples listas.
 */
void prueba_lista_crear() {
	printf("\n[ ] INICIO DE PRUEBAS CON CREACION DE LISTAS \n\n");
	
	lista_t* l1 = lista_crear();
	print_test("\tSe creo lista1", lista_esta_vacia(l1));

	lista_t* l2 = lista_crear();
	print_test("\tSe creo lista2", lista_esta_vacia(l2));

	lista_destruir(l1, NULL);
	print_test("\tDestruyo lista2", true);
	lista_destruir(l2, NULL);
	print_test("\tDestruyo lista2", true);
}
/*
 * Prueba de crear y borrar una lista vacia.
 */
void prueba_lista_vacia() {
	printf("\n[ ] INICIO DE PRUEBAS CON LISTAS VACIAS\n\n");

	lista_t* l = lista_crear();
	print_test("\tSe creo lista vacia", lista_esta_vacia(l));
	print_test("\tLargo cero", lista_esta_vacia(l) && lista_largo(l) == 0);
	print_test("\tPrimero es NULL", lista_esta_vacia(l) && lista_ver_primero(l) == NULL);
	print_test("\tUltimo es NULL", lista_esta_vacia(l) && lista_ver_ultimo(l) == NULL);
	print_test("\tLargo cero", lista_esta_vacia(l) && lista_largo(l) == 0);
	print_test("\tIntento borrar primero", lista_esta_vacia(l) && lista_borrar_primero(l) == 0);

	lista_destruir(l, NULL);
	print_test("\tDestruyo lista", true);
}
/*
 * Prueba de agregar y borrar pocos elementos a partir de una lista vacia.
 */
void prueba_lista_pocos_elementos() {
	printf("\n[ ] INICIO DE PRUEBAS CON 1 ELEMENTO\n\n");
	lista_t* l = lista_crear();

	int elemento = 5;
	print_test("\tAgrego un elemento al principio", lista_insertar_primero(l, &elemento) && lista_ver_primero(l) == &elemento);
	print_test("\tElimino el elemento del principio", lista_borrar_primero(l) == &elemento);
	print_test("\tLa lista queda vacia", lista_esta_vacia(l));
	print_test("\tAgrego un elemento al final", lista_insertar_ultimo(l, &elemento) && lista_ver_primero(l) == &elemento);
	print_test("\tElimino el elemento del principio", lista_borrar_primero(l) == &elemento);
	print_test("\tLa lista queda vacia", lista_esta_vacia(l));

	printf("\n[ ] INICIO DE PRUEBAS CON 2 ELEMENTOS\n\n");

	int el1 = 10, el2 = 15;
	// inserto el1 al principio y a el2 al final
	print_test("\tAgrego A al principio - [ A ] ", lista_insertar_primero(l, &el1) && lista_ver_primero(l) == &el1);
	print_test("\tAgrego B al final - [ A , B ] ", lista_insertar_ultimo(l, &el2) && lista_ver_ultimo(l) == &el2);
	print_test("\tElimino A del principio - [ B ] ", lista_borrar_primero(l) == &el1);
	print_test("\tElimino B del principio - [ ] ", lista_borrar_primero(l) == &el2);
	print_test("\tLa lista queda vacia", lista_esta_vacia(l));


	// inserto el2 al principio y a el1 al principio

	print_test("\tAgrego B al principio - [ B ] ", lista_insertar_primero(l, &el2) && lista_ver_primero(l) == &el2);
	print_test("\tAgrego A al principio - [ A , B ] ", lista_insertar_primero(l, &el1) && lista_ver_primero(l) == &el1 && lista_ver_ultimo(l) == &el2);
	print_test("\tElimino A del principio - [ B ] ", lista_borrar_primero(l) == &el1);
	print_test("\tElimino B del principio - [ ] ", lista_borrar_primero(l) == &el2);
	print_test("\tLa lista queda vacia", lista_esta_vacia(l));
	// inserto el1 al final y a el2 al final
	print_test("\tAgrego A al final - [ A ] ", lista_insertar_ultimo(l, &el1) && lista_ver_primero(l) == &el1 && lista_ver_ultimo(l) == &el1);
	print_test("\tAgrego B al final - [ A , B ] ", lista_insertar_ultimo(l, &el2) && lista_ver_ultimo(l) == &el2);
	print_test("\tElimino A del principio - [ B ] ", lista_borrar_primero(l) == &el1);
	print_test("\tElimino B del principio - [ ] ", lista_borrar_primero(l) == &el2);
	print_test("\tLa lista queda vacia", lista_esta_vacia(l));

	lista_destruir(l, NULL);
	print_test("\tDestruyo lista", true);
}



/* Prueba sobre multiples listas donde se almacenan
 * distindos tipos de datos.
 */
void prueba_lista_tipos() {
	printf("\n[ ] INICIO DE PRUEBAS CON DISTINTOS TIPOS DE ELEMENTOS\n\n");
	lista_t *l1, *l2, *l3;

	int enteros[] = {1, 2, 3, 4, 5};
	char caracteres[] = {'a', 'b', 'c', 'd', 'e'};
	float flotantes[] = {1.0, 2.0, 3.0, 4.0, 5.0};

	int longitud = 5;
	bool ok = true;

	l1 = lista_crear();
	for(int i = 0; i < longitud; i++){
		ok &= lista_insertar_ultimo(l1, &enteros[i]) &&
		lista_ver_ultimo(l1) == &enteros[i];
	}
	print_test("\tSe insertaron los elementos enteros", ok);

	ok = true;
	l2 = lista_crear();
	for(int i = 0; i < longitud; i++){
		ok &= lista_insertar_ultimo(l2, &caracteres[i]) &&
		lista_ver_ultimo(l2) == &caracteres[i];
	}
	print_test("\tSe insertaron los elementos caracteres", ok);

	ok = true;
	l3 = lista_crear();
	for(int i = 0; i < longitud; i++){
		ok &= lista_insertar_ultimo(l3, &flotantes[i]) &&
		lista_ver_ultimo(l3) == &flotantes[i];
	}
	print_test("\tSe insertaron los elementos flotantes", ok);

	lista_destruir(l1, NULL);
	lista_destruir(l2, NULL);
	lista_destruir(l3, NULL);
	print_test("\tSe destruyeron las listas", true);	
}
/*
 * Pruebas sobre una lista con volumen de datos.
 * volumen va a ser la cantidad de datos que se van a usar.
 */

void prueba_lista_volumen(size_t volumen) {     
	printf("\n[ ] INICIO DE PRUEBAS DE VOLUMEN [%ld] \n\n", volumen);     
	lista_t* l = lista_crear();
	int* elementos = malloc(volumen * sizeof(int));     
	if(!elementos) return;
	bool ok = true;

	for(int i = 0; i < volumen; i++) {
		elementos[i] = i;
		ok &= lista_insertar_ultimo(l, &elementos[i]) &&
		lista_ver_ultimo(l) == &elementos[i];
	}
	print_test("\tSe insertaron todos los elementos", ok);
	for(int i = 0; i < volumen; i++) {
		ok &= lista_borrar_primero(l) == &elementos[i];
		if(!ok) break;
	}
	print_test("\tSe vacio la lista correctamente", ok);
	free(elementos);
	lista_destruir(l, NULL);
	print_test("\tSe destruyo la lista", true);	

}
/*
 * Pruebas sobre una lista con NULLs.
 */
void prueba_lista_null() {
	printf("\n[ ] INICIO DE PRUEBAS DE NULLs \n\n");
	lista_t* l = lista_crear();
	bool ok = true;

	for(int i = 0; i < CANT_NULLS; i++){
		ok &= 
		lista_insertar_ultimo(l, NULL) &&
		!lista_esta_vacia(l) &&
		lista_ver_ultimo(l) == NULL;
	}
	print_test("\tSe insertaron todos los NULLs", ok);
	for(int i = 0; i < CANT_NULLS; i++) {
		ok &= !lista_esta_vacia(l) && lista_borrar_primero(l) == NULL;
		if(!ok) break;
	}
	print_test("\tSe vacio la lista correctamente", ok);	

	lista_destruir(l, NULL);
	print_test("\tSe destruyo la lista", true);	
}
/*
 * Destruye lista correctamente, siempre y cuando
 * sus elementos no deban ser eliminados.
 * Pre: lista fue creada y sus elementos no deben ser destruido.
 * Post: la lista será destruída.
 */
void lista_destruir_wrapper(void* lista) {
	lista_destruir((lista_t*) lista, NULL);
}
/*
 * Pruebo destruir una lista, cuyos elementos
 * deben ser eliminados manualmente
 */

void prueba_lista_destruir() {
	printf("\n[ ] INICIO DE PRUEBAS DE DESTRUIR \n\n");
	lista_t** lista = malloc(sizeof(lista_t*) * CANT_LISTAS);
	lista_t* listas = lista_crear();
	bool ok = true;
	for(int i = 0; i < CANT_LISTAS; i++){ 
		lista[i] = lista_crear();
		ok &= lista_insertar_ultimo(listas, lista[i]);
	}
	print_test("\tSe insertaron todos los elementos", ok && lista_largo(listas) == CANT_LISTAS);
	
	lista_destruir(listas, lista_destruir_wrapper);
	
	print_test("\tSe destruyo la lista", true);	
	free(lista);
}

/* *****************************************************************
 *                  PRUEBAS UNITARIAS ITERADOR
 * *****************************************************************/


/*
 * Pruebo correcto funcionamiento del iterador interno.
 */
bool contar_elementos(void* elemento, void* extra) {
	size_t* contador = extra;
	(*contador)++;
	return true;
}
bool sumar_elementos(void* elemento, void* extra) {
	int* acumulador = extra;
	int* numero = elemento;
	(*acumulador) += *numero;
	return true;
}
bool imprimir_un_elemento(void* elemento, void* extra) {
	printf("%d, ", *(int *) elemento);
	return true;
}
bool imprimir_n_elementos(void* elemento, void* extra) {
	printf("%d, ", *(int *) elemento);
	return ++(*(int *) extra) < N_ELEMENTOS_MOSTRAR;
}
/*
 * Pruebo iterador interno con distintas funciones.
 */
void prueba_lista_iter_interno() {
	printf("\n[ ] INICIO DE PRUEBAS DE ITERADOR INTERNO \n\n");
	lista_t* lista = lista_crear();
	lista_iterar(lista, NULL, NULL);
	print_test("\tItero sobre lista vacia.", true);

	int PRIMOS[] = {
		2, 3, 5, 7, 11, 13, 
		17, 19, 23, 29, 37, 
		43, 47, 53, 59, 67, 
		73, 79, 83, 89, 97
	};
	size_t cantidad = 21;
	int suma = 0;
	
	for(int i = 0; i < cantidad; i++) suma += PRIMOS[i];
	bool ok = true;
	for(int i = 0; i < cantidad; i++){ 
		ok &= lista_insertar_ultimo(lista, &PRIMOS[i]) &&
		lista_ver_ultimo(lista) == &PRIMOS[i];
	}
	print_test("\tSe insertaron todos los numeros primos menores a 100", ok);
	// Cuento los numeros con un iterador.
	size_t cantidad_calculada = 0;
	lista_iterar(lista, contar_elementos, &cantidad_calculada);
	print_test("\tLa cantidad de numeros primos menor a 100 \n\tcalculada con iterador es correcta.", cantidad == cantidad_calculada);

	// Sumo los elementos con un iterador.
	int suma_calculada = 0;
	lista_iterar(lista, sumar_elementos, &suma_calculada);
	printf("\tLa suma de los numeros primos menor a 100 es %d", suma_calculada);
	print_test("", suma_calculada == suma);

	// Imprimo lista por pantalla con iterador.
	printf("\t[ ");
	lista_iterar(lista, imprimir_un_elemento, NULL);
	printf(" ] \n");

	// Muestro los primeros N_ELEMENTOS_MOSTRAR elementos
	int contador = 0;
	printf("\t[ ");
	lista_iterar(lista, imprimir_n_elementos, &contador);
	printf(" ] \n");

	lista_destruir(lista, NULL);
	print_test("\tSe destruyo la lista", true);	

}
/*
 * Dada una lista, muestra una representación
 * gráfica en pantalla.
 * Pre: lista fue creada.
 */
void imprimir_lista(lista_t* lista) {
	printf("\t[ ");
	lista_iterar(lista, imprimir_un_elemento, NULL);
	printf(" ] \n");
}
/*
 * Pruebo correcto funcionamiento del iterador externo.
 */
void prueba_lista_iter_externo() {
	printf("\n[ ] INICIO DE PRUEBAS DE ITERADOR EXTERNO \n\n");
	lista_t* lista = lista_crear();
	lista_iter_t* iterador = lista_iter_crear(lista);
	// Elementos de prueba.
	int A = 1, B = 2, C = 3, D = 4, E = 5;
	size_t pocos_elementos = 3, total = 5;
	// Lista vacia.
	print_test("\tSe crea iterador", iterador);
	print_test("\tAvanzar en iterador sobre lista vacia", !lista_iter_avanzar(iterador) && lista_esta_vacia(lista));
	print_test("\tInsertar un elemento en la posicion de iterador recien creado.", !lista_iter_avanzar(iterador) && lista_esta_vacia(lista));
	print_test("\tElemento actual de iterador.", !lista_iter_ver_actual(iterador));
	// Pocos elementos.
	print_test("\tSe inserto elemento A", lista_iter_insertar(iterador, &A));
	imprimir_lista(lista);
	print_test("\tSe inserto elemento B", lista_iter_insertar(iterador, &B));
	imprimir_lista(lista);
	print_test("\tSe inserto elemento C", lista_iter_insertar(iterador, &C));
	imprimir_lista(lista);
	print_test("\tActual igual al ultimo insertado", lista_iter_ver_actual(iterador) == &C);
	print_test("\tPrimero de la lista igual al ultimo insertado", lista_ver_primero(lista) == &C);
	print_test("\tUltimo de la lista igual al primero insertado", lista_ver_ultimo(lista) == &A);
	print_test("\tLargo de la lista igual a 3", lista_largo(lista) == pocos_elementos);

	// Borro 1 elemento.
	print_test("\tAvanzo el iterador", lista_iter_avanzar(iterador));
	print_test("\tActual igual a B", lista_iter_ver_actual(iterador) == &B);
	print_test("\tBorro elemento actual (B)", lista_iter_borrar(iterador) == &B);
	imprimir_lista(lista);
	print_test("\tLargo de la lista igual a 2", lista_largo(lista) == pocos_elementos - 1);
	print_test("\tActual igual al siguiente (A)", lista_iter_ver_actual(iterador) == &A);
	print_test("\tPrimero de la lista igual al ultimo insertado", lista_ver_primero(lista) == &C);
	print_test("\tUltimo de la lista igual al primero insertado", lista_ver_ultimo(lista) == &A);


	// Agrego más elementos.
	print_test("\tSe inserto elemento D", lista_iter_insertar(iterador, &D));
	imprimir_lista(lista);
	print_test("\tSe inserto elemento E", lista_iter_insertar(iterador, &E));
	imprimir_lista(lista);
	print_test("\tActual igual al ultimo insertado", lista_iter_ver_actual(iterador) == &E);
	print_test("\tUltimo de la lista igual al primero insertado (A)", lista_ver_ultimo(lista) == &A);
	print_test("\tLargo de la lista igual a 4", lista_largo(lista) == total - 1);

	lista_iter_destruir(iterador);
	print_test("\tSe destruyo el iterador", true);
	// Vacio lista con iterador.

	int* actual = NULL;
	bool ok = true;
	
	lista_iter_t* iterador_borrar = lista_iter_crear(lista);
	print_test("\tSe crea iterador_borrar", iterador_borrar);
	while(!lista_iter_al_final(iterador_borrar)) {
		actual = lista_iter_ver_actual(iterador_borrar);
		ok &= actual == lista_iter_borrar(iterador);
	}
	print_test("\tSe borraron todos los elementos de la lista", ok);

	lista_iter_destruir(iterador);
	print_test("\tSe destruyo el iterador", true);
	lista_iter_destruir(iterador_borrar);
	print_test("\tSe destruyo el iterador_borrar", true);
	lista_destruir(lista, NULL);
	print_test("\tSe destruyo la lista", true);	
}
/*
 * Pruebas sobre un iterador de lista con volumen de datos.
 * volumen va a ser la cantidad de datos que se van a usar.
 */
void prueba_lista_iter_externo_volumen(size_t volumen) {
	printf("\n[ ] INICIO DE PRUEBAS DE VOLUMEN ITERADOR [%ld] \n\n", volumen);     
	lista_t* l = lista_crear();
	print_test("\tSe creo lista vacia", lista_esta_vacia(l));

	lista_iter_t* iterador = lista_iter_crear(l);
	print_test("\tSe crea iterador", iterador);

	int* elementos = malloc(volumen * sizeof(int));     
	if(!elementos) return;

	bool ok = true;
	//print_test("\nSe inserto 1 elemento",lista_iter_insertar(iterador, &ok));
	//lista_iter_avanzar(iterador);
	for(int i = 0; i < volumen; i++) {
		elementos[i] = i;
		ok &= lista_iter_insertar(iterador, &elementos[i]) &&
		lista_iter_ver_actual(iterador) == &elementos[i];
		if(!(i % 1000))print_test("\tSe inserto 1 elemento", ok);
	}
	print_test("\tSe insertaron todos los elementos", ok);
	lista_iter_destruir(iterador);
	print_test("\tSe destruyo el iterador", !iterador);

	lista_iter_t* iterador_borrar = lista_iter_crear(l);
/*
	for(int i = 0; i < volumen; i++) {
		ok &= lista_iter_borrar(iterador_borrar) == &elementos[i];
		if(!ok) break;
	}*/
	print_test("\tSe vacio la lista correctamente", ok);
	lista_iter_destruir(iterador_borrar);
	print_test("\tSe destruyo el iterador_borrar", !iterador_borrar);
	free(elementos);
	lista_destruir(l, NULL);
	print_test("\tSe destruyo la lista", true);	

}
/* *****************************************************************
 *               EJEMPLOS PROPUESTOS POR LA CÁTEDRA
 * *****************************************************************/

//
// Imprimir una lista con iterador externo
//
void imprimir_iter_externo(lista_t *lista) {
    lista_iter_t *iter = lista_iter_crear(lista);
    int num_items = 0;

    while (!lista_iter_al_final(iter)) {
        char *elemento = lista_iter_ver_actual(iter);
        printf("%d. %s\n", ++num_items, elemento);

        lista_iter_avanzar(iter);
    }
    printf("Tengo que comprar %d ítems\n", num_items);
    lista_iter_destruir(iter);
}


//
// Imprimir una lista con iterador interno
//

bool imprimir_un_item(void *elemento, void *extra) {
    // Sabemos que ‘extra’ es un entero, por tanto le podemos hacer un cast.
    int *contador = extra;
    printf("%d. %s\n", ++(*contador), (char*) elemento);

    return true; // seguir iterando
}

void imprimir_iter_interno(lista_t *lista) {
    int num_items = 0;
    lista_iterar(lista, imprimir_un_item, &num_items);
    printf("Tengo que comprar %d ítems\n", num_items);
}

//
// Ejemplo de uso
//
void ejemplo_iteradores() {
	printf("[ Ejemplos propuestos por la catedra ]\n");
    lista_t *super = lista_crear();

    lista_insertar_ultimo(super, "leche");
    lista_insertar_ultimo(super, "huevos");
    lista_insertar_ultimo(super, "pan");
    lista_insertar_ultimo(super, "mermelada");
    imprimir_iter_externo(super);
    imprimir_iter_interno(super);

    lista_destruir(super, NULL);
}

/*
 * Se ejecutan todas las pruebas de lista.
 */
void pruebas_lista_alumno() {
	// Ejemplos propuestos por la cátedra.
	ejemplo_iteradores();
	// Pruebas unitarias primitivas de lista.
	prueba_lista_crear();
	prueba_lista_vacia();
	prueba_lista_pocos_elementos();
	prueba_lista_tipos();
	prueba_lista_volumen(VOLUMEN_1);
	prueba_lista_volumen(VOLUMEN_2);
	prueba_lista_null();
	prueba_lista_destruir();
	// Pruebas unitarias iteradores.
	prueba_lista_iter_interno();
	prueba_lista_iter_externo();
	//prueba_lista_iter_externo_volumen(VOLUMEN_1);
	//prueba_lista_iter_externo_volumen(VOLUMEN_2);
}

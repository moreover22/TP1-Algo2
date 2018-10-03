#ifndef LISTA_H
#define LISTA_H

#include <unistd.h>
#include <stdbool.h>
/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La lista está planteada como una lista de punteros genéricos. */
typedef struct lista lista_t;

/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t *lista_crear(void);

// Devuelve verdadero o falso, según si la lista tiene o no elementos
// insertados.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento al principio de la lista. Devuelve falso en 
// caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento al principio de la lista, 
// valor se encuentra al principio de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un nuevo elemento al final de la lista. Devuelve falso en 
// caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento al final de la lista, 
// valor se encuentra al final de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Saca el primer elemento de la lista. Si la lista tiene elementos, se quita el
// primero de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void *lista_borrar_primero(lista_t *lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void *lista_ver_primero(const lista_t *lista);

// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la lista, cuando no está vacía.
void *lista_ver_ultimo(const lista_t* lista);

// Devuelve el largo de la lista.
// Pre: la lista fue creada.
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void *));

/* ******************************************************************
 *                DEFINICION DE LOS ITERADORES
 * *****************************************************************/

/* ******************************************************************
 *                    ITERADOR INTERNO
 * *****************************************************************/
// Permite recorrer una lista y aplica la función visitar a cada
// uno de sus elementos. 
// Pre: la lista fue creada.  
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);


/* ******************************************************************
 *                    ITERADOR EXTERNO
 * *****************************************************************/

typedef struct lista_iter lista_iter_t;

// Crea un iterador externo para el TDA lista.
// Pre: lista fue creada
// Post: devuelve un nuevo iterador a lista.
// Apunta al primer elemento de la lista.
lista_iter_t *lista_iter_crear(lista_t *lista);

// El iterador avanza al siguiente elemento de la lista.
// Devuelve true si pudo avanzar, false en caso contrario.
// Pre: el iterador fue creado.
// Post: avanza una posición en la lista.
bool lista_iter_avanzar(lista_iter_t *iter);

// Devuelve el valor del nodo actual. Devuelve
// NULL en caso de que actual lo sea.
// Pre: el iterador fue creado.
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Devuelve true si el iterador está al final, false en caso contrario.
// Pre: el iterador fue creado.
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador.
// Pre: el iterador fue creado.
void lista_iter_destruir(lista_iter_t *iter);

// Agrega un nuevo elemento entre el actual del iterador y su anterior.
// Devuelve falso en caso de error.
// Pre: el iterador fue creado.
// Post: se agregó un nuevo elemento entre el actual del iterador y su anterior.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Saca el elemento actual de la lista. Si la lista está vacía, devuelve NULL.
// Pre: el iterador fue creado.
// Post: se devolvió el valor del borrado, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void *lista_iter_borrar(lista_iter_t *iter);

/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

// Realiza pruebas sobre la implementación del alumno.
//
// Las pruebas deben emplazarse en el archivo ‘pruebas_alumno.c’, y
// solamente pueden emplear la interfaz pública tal y como aparece en cola.h
// (esto es, las pruebas no pueden acceder a los miembros del struct cola).
//
// Para la implementación de las pruebas se debe emplear la función
// print_test(), como se ha visto en TPs anteriores.
void pruebas_lista_alumno(void);

#endif // LISTA_H

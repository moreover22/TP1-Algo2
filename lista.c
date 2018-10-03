#include "lista.h"
#include "testing.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La lista está planteada como una lista de punteros genéricos. */

typedef struct nodo_lista {
	void* dato;
	struct nodo_lista* prox;
}nodo_lista_t;

struct lista {
	size_t largo;
	nodo_lista_t* prim;
	nodo_lista_t* ult;
};

// Crea un nodo con un respectivo valor.
// Post: devuelve un puntero a un nodo o NULL
// en caso de que no pueda crearlo.
nodo_lista_t* crear_nodo(void* valor) {
	nodo_lista_t* nodo = malloc(sizeof(nodo_lista_t));
	if(!nodo) return NULL;
	nodo->dato = valor;
	nodo->prox = NULL;
	return nodo;
}

/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t *lista_crear(void) {
	lista_t* lista = malloc(sizeof(lista_t));
	if(!lista) return NULL;
	lista->prim = NULL;
	lista->ult = NULL;
	lista->largo = 0;
	return lista;
}

// Devuelve verdadero o falso, según si la lista tiene o no elementos
// insertados.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista) {
	return !lista->largo;
}

// Agrega un nuevo elemento al principio de la lista. Devuelve falso en 
// caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento al principio de la lista, 
// valor se encuentra al principio de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato) {
	nodo_lista_t* nodo = crear_nodo(dato);
	if(!nodo) return false;
	if(lista_esta_vacia(lista))
		lista->ult = nodo;
	else 
		nodo->prox = lista->prim;
	lista->prim = nodo;
	lista->largo++;
	return true;
}

// Agrega un nuevo elemento al final de la lista. Devuelve falso en 
// caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento al final de la lista, 
// valor se encuentra al final de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato) {
	nodo_lista_t* nodo = crear_nodo(dato);
	if(!nodo) return false;
	if(lista_esta_vacia(lista))
		lista->prim = nodo;
	else 
		lista->ult->prox = nodo;
	lista->ult = nodo;
	lista->largo++;
	return true;
}

// Saca el primer elemento de la lista. Si la lista tiene elementos, se quita el
// primero de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void *lista_borrar_primero(lista_t *lista) {
	if(lista_esta_vacia(lista)) return NULL;
	nodo_lista_t* prim = lista->prim;
	lista->prim = prim->prox;
	if(!lista->prim)
		lista->ult = NULL;
	void* elemento = prim->dato;
	free(prim);
	lista->largo--;
	return elemento;
}

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void *lista_ver_primero(const lista_t *lista) {
	if(lista_esta_vacia(lista)) return NULL;
	return lista->prim->dato;
}

// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la lista, cuando no está vacía.
void *lista_ver_ultimo(const lista_t* lista) {
	if(lista_esta_vacia(lista)) return NULL;
	return lista->ult->dato;
}

// Devuelve el largo de la lista.
// Pre: la lista fue creada.
size_t lista_largo(const lista_t *lista) {
	return lista->largo;
}

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void *)) {
	while(!lista_esta_vacia(lista)) {
		void* elemento = lista_borrar_primero(lista);
		if(destruir_dato) destruir_dato(elemento);
	}
	free(lista);
}

/* ******************************************************************
 *                DEFINICION DE LOS ITERADORES
 * *****************************************************************/

/* ******************************************************************
 *                    ITERADOR INTERNO
 * *****************************************************************/
// Permite recorrer una lista y aplica la función visitar a cada
// uno de sus elementos. 
// Pre: la lista fue creada.  
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra) {
	if(lista_esta_vacia(lista)) return;
	nodo_lista_t* actual = lista->prim;
	while(actual && visitar(actual->dato, extra))
		actual = actual->prox;
}

/* ******************************************************************
 *                    ITERADOR EXTERNO
 * *****************************************************************/

struct lista_iter{
	lista_t* lista;
	nodo_lista_t* anterior;
	nodo_lista_t* actual;	
};
// Crea un iterador externo para el TDA lista.
// Pre: lista fue creada
// Post: devuelve un nuevo iterador a lista.
// Apunta al primer elemento de la lista.
lista_iter_t *lista_iter_crear(lista_t *lista) {
	lista_iter_t* iterador = malloc(sizeof(lista_iter_t));
	if(!iterador) return NULL;
	iterador->lista = lista;
	iterador->anterior = NULL;
	iterador->actual = lista->prim;

	return iterador;
}
// El iterador avanza al siguiente elemento de la lista.
// Devuelve true si pudo avanzar, false en caso contrario.
// Pre: el iterador fue creado.
// Post: avanza una posición en la lista.
bool lista_iter_avanzar(lista_iter_t *iter) {
	if(!iter->actual) return false;
	iter->anterior = iter->actual;
	iter->actual = iter->actual->prox;
	return true;
}

// Devuelve el valor del nodo actual. Devuelve
// NULL en caso de que actual lo sea.
// Pre: el iterador fue creado.
void *lista_iter_ver_actual(const lista_iter_t *iter) {
	if(!iter->actual) return NULL;
	return iter->actual->dato;
}

// Devuelve true si el iterador está al final, false en caso contrario.
// Pre: el iterador fue creado.
bool lista_iter_al_final(const lista_iter_t *iter) {
	return !iter->actual;
}
// Destruye el iterador.
// Pre: el iterador fue creado.
void lista_iter_destruir(lista_iter_t *iter) {
	free(iter);
}
// Agrega un nuevo elemento entre el actual del iterador y su anterior.
// Devuelve falso en caso de error.
// Pre: el iterador fue creado.
// Post: se agregó un nuevo elemento entre el actual del iterador y su anterior, 
// el actual del iterador pasa a ser el nuevo nodo.
bool lista_iter_insertar(lista_iter_t *iter, void *dato) {
	if(!iter->anterior) {
		if(!lista_insertar_primero(iter->lista, dato))
			return false;
		iter->actual = iter->lista->prim;
		return true;
	}
	if(!iter->actual) {
		if(!lista_insertar_ultimo(iter->lista, dato))
			return false;
		iter->actual = iter->lista->ult;
		return true;
	}

	nodo_lista_t* nodo = crear_nodo(dato);
	if(!nodo) return false;
	iter->anterior->prox = nodo;
	nodo->prox = iter->actual;
	iter->actual = nodo;
	iter->lista->largo++;
	return true;
}

// Saca el elemento actual de la lista. Si la lista está vacía, devuelve NULL.
// Pre: el iterador fue creado.
// Post: se devolvió el valor del borrado, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void *lista_iter_borrar(lista_iter_t *iter) {
	if(lista_esta_vacia(iter->lista) 
	|| lista_iter_al_final(iter))
		return NULL;
	void* dato;
	if(!iter->anterior) {
		dato = lista_borrar_primero(iter->lista);
		iter->actual = iter->lista->prim;
		return dato;
	}
	nodo_lista_t* eliminar = iter->actual;
	dato = eliminar->dato;
	if(!iter->actual->prox)
		iter->lista->ult = iter->anterior;
	
	iter->anterior->prox = eliminar->prox;
	iter->actual = iter->actual->prox;

	free(eliminar);
	iter->lista->largo--;

	return dato;
}
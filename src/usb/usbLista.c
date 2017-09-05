#include "usbLista.h"
#include "usbFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Lista_Inicializar(ListaEnlazada *lista) {
  if (lista) {
    lista = (ListaEnlazada *)malloc(sizeof(ListaEnlazada));
    if (!lista)
      return 0;
    ElementoLista *ancla = (ElementoLista *)malloc(sizeof(ElementoLista));
    if (!ancla)
      return 0;                 //La función empezará creando un elemento(ancla) solo si la  
    ancla->siguiente = NULL;    //lista está vacía, donde el puntero siguiente,el puntero 
    ancla->anterior = NULL;     //anterior y el objeto del elemento(ancla), apuntarán a NULL.
    ancla->objeto = NULL;
    lista->ancla = *ancla;
    lista->numeroElementos = 0;
    return 1;
  }
  return 0;
}

int Lista_InsertarFin(ListaEnlazada *lista, void *objeto) {
  // definicion de Elementos de lista
  ElementoLista *nuevo = (ElementoLista *)malloc(sizeof(ElementoLista));
  if (!nuevo)
    return 0;
  nuevo->objeto = objeto;
  if (lista->numeroElementos == 0) {
    ElementoLista *ancla = &(lista->ancla);  //La función inserterá un nuevo elemento al final de la
    ancla->anterior = nuevo;                 //lista, donde el puntero siguiente del nuevo elemento
    ancla->siguiente = nuevo;                //apuntará al elemento ancla y el puntero anterior del nuevo
    nuevo->siguiente = ancla;                //elemento apuntará al elemento(ultimo) que se encontraba al
    nuevo->anterior = ancla;                 //final de la lista. Finalmente el puntero siguiente de 
  } else {                                   //ese elemento(ultimo) y el puntero anterior del elemento ancla
    ElementoLista *ancla = &(lista->ancla);  //apuntarán al nuevo elemento.
    ElementoLista *ultimo = ancla->anterior;
    nuevo->anterior = ultimo;
    nuevo->siguiente = ancla;
    ultimo->siguiente = nuevo;
    ancla->anterior = nuevo;
  }
  lista->numeroElementos++;
  return 1;
}

void Lista_Sacar(ListaEnlazada *lista, ElementoLista *elemento){

	if(lista->numeroElementos==0){					  //La función sacará un elemento de la lista,
		return;										  //para éste proceso, los elementos anterior(tmpAnterior) 
	}												  //y siguiente(tmpSiguiente) del elemento que tenemos como
													  //parámetro deberán estar apuntándose.
	if(lista->numeroElementos==1){					  
		ElementoLista *ancla= (elemento->anterior);
		ancla->siguiente=NULL;
		ancla->anterior=NULL;
		lista->numeroElementos = 0;
		return;
	}

	ElementoLista *tmpAnterior = elemento->anterior;
	ElementoLista *tmpSiguiente = elemento->siguiente;

	tmpAnterior->siguiente=tmpSiguiente;
	tmpSiguiente->anterior=tmpAnterior;
lista->numeroElementos--;
}

ElementoLista *Lista_Primero(ListaEnlazada *lista) {
  int tamano = Lista_Conteo(lista);
  if (tamano == 0) {						 //La función retornará el elemento que está en la 
    return NULL;							 //primera posición de la lista, es decir, la que se
  }											 //encuentra después del elemento ancla.
  ElementoLista *ancla = &(lista->ancla);
  ElementoLista *primero = ancla->siguiente;
  return primero;
}

ElementoLista *Lista_Ultimo(ListaEnlazada *lista) {
  int tamano = Lista_Conteo(lista);
  if (tamano == 0) {						  //La función retornará el elemento que está en la
    return NULL;							  //última posición de la lista, es decir, la que se
  }											  //encuentra antes del elemento ancla.
  ElementoLista *ancla = &(lista->ancla);
  ElementoLista *anterior = ancla->anterior;
  return anterior;
}

int Lista_Conteo(ListaEnlazada *lista) {
  if (lista) { 
    return lista->numeroElementos;	//La función retornará el número elemento que contiene
  }									//la lista.
  return -1;
}

ElementoLista *Lista_Siguiente(ListaEnlazada *lista, ElementoLista *elemento){
	int tamano = Lista_Conteo(lista);			
  	if (tamano == 0) {							//La función retornará el elemento que está en la
    	return NULL;							//posición siguiente al elemento que tenemos como
  	}											//parámetro.
    if(elemento->siguiente!=&(lista->ancla)){
		return elemento->siguiente;
	}else{
		return NULL;
	}
}

ElementoLista *Lista_BuscarXiD(ListaEnlazada *lista, char *idProduct){
	if(lista->numeroElementos!=0){ 
  	ElementoLista *elem = NULL;
		for (elem = Lista_Primero(lista); elem != NULL; elem = Lista_Siguiente(lista, elem)) {
      struct InfoUSB *info = (struct InfoUSB *)elem->objeto;
      //printf("[COMP: %s - %s]\n",info->idProduct,idProduct);
		  if(strcmp(info->idProduct,idProduct) == 0){
		    return elem;				
		  }								
		}								
	}									
	return NULL;
}

ElementoLista *Lista_BuscarXNodo(ListaEnlazada *lista, char *nodo){
	if(lista->numeroElementos!=0){ 
  	ElementoLista *elem = NULL;
		for (elem = Lista_Primero(lista); elem != NULL; elem = Lista_Siguiente(lista, elem)) {
      struct InfoUSB *info = (struct InfoUSB *)elem->objeto;
      //printf("[COMP: %s - %s]\n",info->idProduct,idProduct);
		  if(strcmp(info->usbNodo,nodo) == 0){
		    return elem;				
		  }								
		}								
	}									
	return NULL;
}

ElementoLista *Lista_BuscarXNombre(ListaEnlazada *lista, char *nombre){
	if(lista->numeroElementos!=0){ 
  	ElementoLista *elem = NULL;
		for (elem = Lista_Primero(lista); elem != NULL; elem = Lista_Siguiente(lista, elem)) {
      struct InfoUSB *info = (struct InfoUSB *)elem->objeto;
      //printf("[COMP: %s - %s]\n",info->nombre,nombre);
		  if(strcmp(info->nombre,nombre) == 0){
		    return elem;				
		  }								
		}								
	}									
	return NULL;
}
// int main(){
//     return 0;
// }

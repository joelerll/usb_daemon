
typedef struct ElementeListaTDA{
	void *objeto;
	struct ElementeListaTDA *siguiente;
	struct ElementeListaTDA *anterior;
}ElementoLista;

typedef struct ListaEnlazadaTDA{
	int numeroElementos;
	ElementoLista ancla;
}ListaEnlazada;

ListaEnlazada listaUsb;

int Lista_Inicializar(ListaEnlazada *lista);
int Lista_InsertarFin(ListaEnlazada *lista, void *objeto);
void Lista_Sacar(ListaEnlazada *lista, ElementoLista *elemento);
ElementoLista *Lista_Primero(ListaEnlazada *lista);
ElementoLista *Lista_Ultimo(ListaEnlazada *lista);
int Lista_Conteo(ListaEnlazada *lista);
ElementoLista *Lista_Siguiente(ListaEnlazada *lista, ElementoLista *elemento);
ElementoLista *Lista_BuscarXiD(ListaEnlazada *lista, char *nodo);
ElementoLista *Lista_BuscarXNodo(ListaEnlazada *lista, char *nodo);
ElementoLista *Lista_BuscarXNombre(ListaEnlazada *lista, char *nombre);
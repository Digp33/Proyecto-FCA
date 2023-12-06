#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MX 3131
typedef int Item;
typedef struct Elemento
{
 Item dato;
 struct Elemento* siguiente;
} Nodo;
void inserPrimero (Nodo** cabeza, Item entrada);
Nodo* crearNodo (Item x);
void main ( )
{
 Item d;
 Nodo *cabeza, *ptr;
 int k;
 cabeza = NULL; /* lista vacía */
 //randomize ( );
 /* El bucle termina cuando se genera el número aleatorio 0 */
 for (d = rand()%MX; d; )
 {
	 inserPrimero (&cabeza, d);
	 d = rand()%MX;
 } /* recorre la lista para escribir los pares */
 for (k = 0, ptr = cabeza; ptr; )
 {
	 if (ptr != NULL && (ptr -> dato) % 2 == 0)
	 {
		 printf ("%d ", ptr -> dato);
		 k++;
		 printf ("\t%c", (k % 12 ? ' ' : '\n') ); /* 12 datos por línea */
 	}
 	ptr = ptr -> siguiente;
 }
 printf ("\n\n\n");
}
void inserPrimero (Nodo** cabeza, Item entrada)
{
 Nodo *nuevo ;
 nuevo = crearNodo (entrada);
 nuevo -> siguiente = *cabeza;
  *cabeza = nuevo;
}
Nodo* crearNodo (Item x)
{
 Nodo *a ;
 a = (Nodo*)malloc (sizeof (Nodo) ); /* asigna nuevo nodo */
 a -> dato = x;
 a -> siguiente = NULL;
 return a;
}
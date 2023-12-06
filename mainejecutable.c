#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h> 
#include <stdbool.h>
struct Nodo
{
  char nombreTarea[30]; 
  bool tareaRealizada;
  int prioridadTarea;
  char valor[30];
  struct Nodo *izq;
  struct Nodo *der;
};
struct ArbolBinario
{
  struct Nodo *raiz;
}; 

void inicializa_arbol(struct ArbolBinario *arbol)
{
  arbol->raiz = NULL;
}

void recorre_orden(struct Nodo *nodo)
{
  if (nodo->izq != NULL) 
  recorre_orden(nodo->izq);
  printf("*************\nNombre:%s\t tareaRealizada:%i\t prioridadTarea:%i\n",nodo->nombreTarea,nodo->tareaRealizada,nodo->prioridadTarea);
  if (nodo->der != NULL) 
  recorre_orden(nodo->der);
  system("pause");
}

struct Nodo *busca_nodo(struct ArbolBinario *arbol,char *valor)
{
  struct Nodo *p = arbol->raiz;
  for (;;)
   if (strcmp(valor,p->nombreTarea) < 0)
  {
    if (p->izq == NULL)
    break;
    else
    p = p->izq;
  }else
  if (strcmp(valor,p->nombreTarea) > 0)
  {
    if (p->der == NULL)
    break;
  else
    p = p->der;
  }
   else
    return p;
    return NULL;
}

struct Nodo *crea_nodo(char *nombreTarea,bool tareaRealizada,int prioridadTarea)
{
  struct Nodo *p = (struct Nodo *)malloc(sizeof(struct Nodo));
  fflush(stdin);
  strcat(p->valor,nombreTarea);
  strcpy(p->nombreTarea,nombreTarea);
  p->tareaRealizada=tareaRealizada;
  p->prioridadTarea = prioridadTarea;
  p->izq = NULL;
  p->der = NULL;
  return p;
}

void agrega_nodo(struct ArbolBinario *arbol,char *nombreTarea,bool tareaRealizada,int prioridadTarea)
{
  if (arbol->raiz != NULL)
  {
    struct Nodo *p = arbol->raiz;
    char valor[50];
    strcpy(valor,nombreTarea);
    for (;;)
      if (strcmp(valor,p->valor) <= 0)
      {
        if (p->izq == NULL)
        {
          p->izq = crea_nodo(nombreTarea,tareaRealizada,prioridadTarea);
          break;
        }
        else
          p = p->izq;
      }
      else
      {
        if (p->der == NULL)
        {
          p->der = crea_nodo(nombreTarea,tareaRealizada,prioridadTarea);
          break;
        }
        else
          p = p->der;
      }
    }
    else
      arbol->raiz = crea_nodo(nombreTarea,tareaRealizada,prioridadTarea);
}

int elimina_nodo(struct ArbolBinario *arbol,char *valor)
{
  struct Nodo *padre = NULL;
  struct Nodo *p = arbol->raiz;
  for(;;)
  {
      if (p != NULL)
      {
          // busca el nodo con el valor
           if (strcmp(valor,p->nombreTarea) < 0)
          {
              padre = p;
              p = p->izq;
              continue;
        }
        else
        if (strcmp(valor,p->nombreTarea) > 0)
        {
            padre = p;
            p = p->der;
            continue;
        }
        else
        {
            // se encontró el nodo p con el valor
            if (p->izq == NULL && p->der == NULL)
            {
                // p es hoja
                if (padre == NULL)
                    arbol->raiz = NULL; // no hay padre, se elimina la raíz del árbol
                else
                if (p == padre->izq)
                    padre->izq = NULL; // el nodo a eliminar es el hijo izquierdo
                else
                    padre->der = NULL; // el nodo a eliminar es el hijo derecho
                free(p);
                return 0;
            }
            else
            {
                // p no es hoja
                padre = p;
                struct Nodo *q;
                if (p->izq != NULL)
                {
                    // hay un árbol izquierdo
                    // en el árbol izquierdo se busca el nodo más a la derecha
                    q = p->izq;
                    while (q->der != NULL)
                    {
                        padre = q;
                        q = q->der;
                    }
                }
                else
                {
                    // no hay un árbol izquierdo
                    // en el árbol derecho se busca el nodo más a la izquierda
                    q = p->der;
                    while (q->izq != NULL)
                    {
                        padre = q;
                        q = q->izq;
                    }
                }
                // intercambia los valores de los nodos p y q              
                int Nedad=p->tareaRealizada;
                p->tareaRealizada=q->tareaRealizada;
                q->tareaRealizada=Nedad;
                
                int nTarea=p->prioridadTarea;
                p->prioridadTarea=q->prioridadTarea;
                q->prioridadTarea=nTarea;
                
                /*char Nnombre[]=p->nombreTarea;
                p->nombreTarea=->q->nombreTarea
                q->nombreTarea=Nnombre;*/
                char Nnombre[30];
                strcpy(Nnombre,p->nombreTarea);
        		strcpy(p->nombreTarea, q->nombreTarea);
         		strcpy(q->nombreTarea, Nnombre);
                // ahora se va a borrar el nodo p
                p = q;
                continue;
            }
        }
    }
    else
        break;
  }
  return -1; // no se encontró el nodo a eliminar
}

int main ()
{
  int i=0, j=0,n;
  struct ArbolBinario arbol;
  inicializa_arbol(&arbol);
  char nombreTarea[35];
//  char Valor[20];
  int tareaRealizada;
  int prioridadTarea;
  
  do{
    system("cls");
    printf("\nBienvenido al programa, que desea hacer?\n1.-Agregar tarea\n2.-Buscar tarea\n3.-Borrar tarea\n4.-Desplegar lista de tareas\n5.-imprimir en archivo (pendiente)\n6.-Salir \n\n\t\tOpcion: ");
    scanf("%i",&n);
    switch (n)
    {
    
    case 1://
      system("cls");
      printf("\nFavor de introducir el nombre de la tarea: ");
      fflush(stdin);
      gets(nombreTarea);
      fflush(stdin);
      fflush(stdin);
      tareaRealizada=false;
      fflush( stdin );
      printf("\nIntroduzca la prioridad de la tarea donde 1 es la opción mas importante, 2 es una tarea media y 3 es una tarea facil: ");
      fflush( stdin );
      scanf("%i",&prioridadTarea);
    //  strcat(p->valor,nombre);
      agrega_nodo(&arbol,nombreTarea,tareaRealizada,prioridadTarea);
      printf("Los datos de la tarea fueron guardados exitosamente!\n");
      system("pause");

    break;
      
    case 2:
    	system("cls");
	  struct Nodo *Auxi = (struct Nodo *)malloc(sizeof(struct Nodo));
	  fflush(stdin);
      system("cls");
      printf("Por favor, introduzca el nombre de la tarea a buscar:\n");
      fflush(stdin);
      gets(nombreTarea);
      fflush(stdin);
      Auxi=busca_nodo(&arbol,nombreTarea);
      if(Auxi!=NULL){
      printf("Los datos de la tarea son: prioridadTarea: %i. tareaRealizada: %i. nombreTarea: %s.",Auxi->prioridadTarea,Auxi->tareaRealizada,Auxi->nombreTarea);
      system("pause");
      }else{
      printf("El dato que busca no se encuentra en la lista...");
      system("pause");
    }
	break;
    
    case 3://
      system("cls");
      printf("Por favor, introduzca el nombre de la tarea a eliminar:\n");
      fflush(stdin);
      gets(nombreTarea);
      fflush(stdin);
      int Eaux=elimina_nodo(&arbol,nombreTarea);
      if(Eaux != -1)
      printf("Los datos de la tarea han sido borrados exitosamente!\n");
      else
      printf("El dato solicitado no se encuentra");
    break;
    
    case 4:
	  system("cls");
	  struct Nodo *Aux2;// = (struct Nodo *)malloc(sizeof(struct Nodo));
	  fflush(stdin); 
	  Aux2=arbol.raiz;   
      printf("Los datos de la tarea son los siguientes:\n\n");
      recorre_orden(Aux2);
    break;
    
    case 5:
    	
    	break;
    case 6://
    printf("Vuelva pronto");
    break;
    default:
    printf("Valor no valido, por favor introduzca otro que se encuentre en el menú...\n");
    }
  }while(n!=6);
  return 1;
}
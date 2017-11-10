/*******************************************/
/* 		    BUSQUEDA.C                     */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "nodo.h"
#include "listaia.h"
#include "busquedaAlum.h"

int buscaRepe(tEstado *s,Lista L1);

void dispCamino(tElemento *nodo)
{
    if (nodo->padre==NULL)
    {
        printf("\n\nInicio:\n");
        dispEstado(nodo->estado);
    }
    else
    {
        dispCamino(nodo->padre);
        dispOperador(nodo->operador);
        dispEstado(nodo->estado);
        printf("\n");
    }
}


void dispSolucion(tElemento *nodo)
{
    dispCamino(nodo);
    printf("Profundidad=%d\n",nodo->profundidad);
    printf("Coste=%d\n",nodo->costeCamino);
}


/* Crea el nodo raÌz. */
tElemento *nodoInicial()
{
    tElemento *inicial=(tElemento *) malloc(sizeof(tElemento));

    inicial->estado=estadoInicial();
    inicial->padre=NULL;
    inicial->costeCamino=0;
    inicial->profundidad=0;
    return inicial;
}


/* Expande un nodo. */
Lista expandir(tElemento *nodo)
{
    unsigned op;
    Lista sucesores = CrearLista(MAXI);
    // printf("\nLista de Sucesores de Actual: \n");
    for (op=1;op<=NUM_OPERADORES;op++)
    {
        if (esValido(op,nodo->estado))
        {
            tElemento *nuevo=(tElemento *) malloc(sizeof(tElemento));
            tEstado *s=(tEstado *) malloc(sizeof(tEstado));
            s = aplicaOperador(op,nodo->estado);
            nuevo=(tElemento *) malloc(sizeof(tElemento));
            nuevo->estado=s;
            nuevo->padre=nodo;
            nuevo->operador=op;
            nuevo->costeCamino=nodo->costeCamino + coste(op,nodo->estado);
            nuevo->profundidad=nodo->profundidad+1;
            if (!ListaLlena(sucesores)){
                InsertarUltimo((void *) nuevo,sucesores);
                //dispEstado(nuevo->estado);
            }
        }
    }
    //system("pause");
    return sucesores;
}


int busqueda()
{
    int objetivo=0;
    tElemento *Actual=(tElemento*) malloc(sizeof(tElemento));

    tElemento *Inicial=nodoInicial();
    //tEstado *Final=estadoObjetivo();

    Lista Abiertos = (Lista) CrearLista(MAXI);
    Lista Cerrados = (Lista) CrearLista(MAXI);
    Lista Sucesores;

    InsertarUltimo((void *) Inicial, Abiertos);

    while (!ListaVacia(Abiertos) && !objetivo)
    {
        Actual = (void *) ExtraerPrimero(Abiertos);
        /*printf("\n ACTUAL: \n");
        dispEstado(Actual->estado);
        system("pause");*/
        EliminarPrimero(Abiertos);
        
        int repetido = buscaRepe(Actual->estado,Cerrados);

        if(!repetido){

            objetivo = testObjetivo(Actual->estado);

            if (!objetivo)
            {
                Sucesores = expandir(Actual);
                Abiertos  = Concatenar(Abiertos, Sucesores);
                //InsertarUltimo((void*)Actual,Cerrados);
            }
        }
    }
    dispSolucion(Actual);
    return objetivo;
}


int buscaRepe(tEstado *s, Lista L1)
{
    int coincide = 0, i=0;

    while( !coincide && i < L1->Nelem )
    {
        if( iguales(s,ExtraerElem(L1,i)->estado)) coincide = 1;
        i++;
    }

    return coincide;

}





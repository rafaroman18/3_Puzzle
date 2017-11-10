/**************************************************************/
/* 		    LISTAIA.C                                         */
/*						                                      */
/* Asignatura: Inteligencia Artificial                        */
/* Funciones para manejar listas est·ticas de acuerdo         */
/*           a las necesidades de la estrategia               */
/*           de busqueda                                      */
/**************************************************************/


#include <stdlib.h>
#include <stdio.h>

#include "listaia.h"


///
Lista CrearLista (int TamMax)
{
    Lista C;
    C = (Lista) malloc(sizeof(tLista));
    if (C == NULL)
    {
        ERROR("CrearLista: No hay memoria");
    }
    else
    {
        C->elementos = (tElemento *)malloc(TamMax*sizeof(tElemento));
        if (C->elementos == NULL)
        {
            ERROR("CrearLista: No hay memoria para los elementos");
        }
        else
        {
            C->Lmax = TamMax;
            C->Nelem = 0;
            C->inicio = 0;
            C->fin =0;
        }
    }
    return C;
}


int ListaVacia (Lista C)
{
    return (C->Nelem==0);
}


int ListaLlena (Lista C)
{
    return (C->Nelem==C->Lmax);
}


//Pre: Lista C no est· vacÌa
//Post:Devuelve el primer elemento de la lista C
tElemento *ExtraerPrimero(Lista C)
{
    return (tElemento *) (C->elementos[C->inicio]);
}


//Pre: Lista C no est· vacÌa, i: es un Ìndice entre 0 y TamMax
//Post:Devuelve el elemento i-Èsimo de la lista C (no lo elimina de la lista)
tElemento *ExtraerElem(Lista C,int i)
{
    return (tElemento *) (C->elementos[i]);
}

// Elimina el primer elemento de la lista
void EliminarPrimero(Lista C)
{
    if (!ListaVacia(C)){
        C->inicio = (C->inicio+1) % C->Lmax;
        C->Nelem=C->Nelem-1;
    }
}


//Pre: Lista C no est· llena
//Post:Devuelve el elemento primero de la lista
void InsertarUltimo(tElemento *e, Lista C)
{
    (C->elementos[C->fin]) =  (tElemento ) e;
    C->Nelem=C->Nelem+1;
    if (C->fin==C->Lmax-1)
        C->fin=0;
    else
        C->fin = (C->fin+1);
}

//Pre: Lista C no est· llena
//Post:Devuelve el elemento primero de la lista
void InsertarPrimero(tElemento *e, Lista C)
{

    if (C->inicio>0)
        C->inicio = (C->inicio-1); //inserta antes que el primero
    else
        C->inicio=C->Lmax-1;

    (C->elementos[C->inicio]) = (tElemento ) e;
    C->Nelem=C->Nelem+1;
}

//Pre: Lista L1 no est· vacÌa
//Post: Devuelve L1+L2
Lista Concatenar(Lista L1,Lista L2)
{
    tElemento *e=(tElemento*) malloc(sizeof(tElemento));

    while (!ListaVacia(L2) && (!ListaLlena(L1)))
    {
        e=(tElemento*) ExtraerPrimero(L2);
        InsertarUltimo(e,L1);
        EliminarPrimero(L2);
    }
    return L1;
}

void DestruirLista(Lista C)
{
    free(C->elementos);
    free(C);
}


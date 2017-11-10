/*******************************************/
/* 		    NODO.H                         */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/
#ifndef _tElemento_
#define _tElemento_
#include "puzle.h"

typedef struct NodoBusqueda{
    tEstado *estado;
    struct NodoBusqueda *padre;
    unsigned operador;
    int costeCamino;
    int profundidad;
    int valHeuristica;
} tElementoBusqueda;

typedef tElementoBusqueda tElemento;
#endif
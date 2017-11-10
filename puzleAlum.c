/*******************************************/
/* 		      PUZLE.C                      */
/*						                   */
/* Asignatura: Inteligencia Artificial     */
/* Grado en Ingenieria Informatica - UCA   */
/*******************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "puzle.h"



tEstado *crearEstado(int puzle[N][N])
{
    tEstado *estado = (tEstado *) malloc(sizeof(tEstado));
    int i, j, ficha;

    for (i=0;i<N;i++)
        for (j=0;j<N;j++)
        {
            ficha=puzle[i][j];
            estado->celdas[i][j]=ficha;
            estado->fila[ficha]=i;
            estado->col[ficha]=j;
        }
    return estado;
}


tEstado *estadoInicial()
{
    return crearEstado(puzle_inicial);
}


tEstado *estadoObjetivo()
{
    return crearEstado(puzle_final);
}

int coste(unsigned op, tEstado *estado)
{
    return 1;
}

/* VISUALIZACI”N DE ESTADOS Y OPERADORES*/


void dispEstado(tEstado *estado)
{
    int i,j;

    for (i=0; i<N; i++)
    {
        for (j=0; j<N; j++)
            printf("%d",estado->celdas[i][j]);
        printf("\n");
    }
    printf("\n");
}


void dispOperador(unsigned op)
{
    switch(op)
    {
        case ARRIBA:    printf("Movimiento ARRIBA:\n"); break;
        case ABAJO:     printf("Movimiento ABAJO:\n"); break;
        case IZQUIERDA: printf("Movimiento IZQUIERDA:\n"); break;
        case DERECHA:   printf("Movimiento DERECHA:\n"); break;
    }
}

// FUNCIONES QUE SE HAN DE IMPLEMENTAR EN LA PRACTICA 1

// FunciÛn auxiliar para comprobar si dos puzles tienen las fichas colocadas en el mismo orden en el tablero
int iguales(tEstado *s, tEstado *t)  //
{
    //COMPLETA
    int i , j, cont;

    cont = 0;

    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            if(s->celdas[i][j]==t->celdas[i][j])
            {
                cont++;
            }
        }
    }
    return  ( cont == N*N);
}


int testObjetivo(tEstado *estado)
{

    return iguales(estado,estadoObjetivo());
}


int esValido(unsigned op, tEstado *estado)
{
    //COMPLETA
    int valido;

    switch(op)
    {
        case ARRIBA:    valido = (estado->fila[0] > 0); break;
        case ABAJO:     valido = (estado->fila[0] < N-1); break;
        case IZQUIERDA: valido = (estado->col[0] > 0); break;
        case DERECHA:   valido = (estado->col[0] < N-1); break;

    }

    return valido;
}


tEstado *aplicaOperador(unsigned op, tEstado *estado)
{
    tEstado *nuevo= (tEstado *) malloc(sizeof(tEstado));
    memcpy(nuevo, estado,sizeof(tEstado));  // Hace una copia del estado
    switch(op)
    {
        case ARRIBA:    nuevo->fila[0] = (estado->fila[0]-1); break;
        case ABAJO:     nuevo->fila[0] = (estado->fila[0]+1); break;
        case IZQUIERDA: nuevo->col[0] = (estado->col[0]-1); break;
        case DERECHA:   nuevo->col[0] = (estado->col[0]+1); break;
    }

    intercambio(nuevo,nuevo->fila[0],nuevo->col[0],estado->fila[0],estado->col[0]);

    return nuevo;
}

void intercambio (tEstado *nuevo,int fnew,int cnew,int fold,int cold)
{
    int ficha;
    ficha=nuevo->celdas[fnew][cnew];
    nuevo->celdas[fnew][cnew]=0;
    nuevo->celdas[fold][cold]=ficha;
    nuevo->col[ficha]=cold;
    nuevo->fila[ficha]=fold;
}


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
//#include "puzle.h"

int buscaRepe(tEstado *s,Lista L1);
int heuristica(tEstado *s);
Lista OrdenaLista(Lista C);
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
    Lista sucesores=CrearLista(MAXI);
    //printf("\nLista de Sucesores de Actual: \n");
    for (op=1;op<=NUM_OPERADORES;op++)
    {
        if (esValido(op,nodo->estado))
        {
            tElemento *nuevo= (tElemento *)malloc(sizeof(tElemento));
            //printf("%d",*nuevo);
            //nuevo=(tElemento *) malloc(sizeof(tElemento));
            //printf(" -> %d",nuevo);
            nuevo->estado=aplicaOperador(op, nodo->estado);
            nuevo->padre=nodo;
            nuevo->operador=op;
            nuevo->costeCamino=nodo->costeCamino + coste(op,nodo->estado);
            nuevo->profundidad=nodo->profundidad+1;
            nuevo->valHeuristica = heuristica(nuevo->estado); //guardamos el numero de piezas mal colocadas
            if (!ListaLlena(sucesores)){
                InsertarUltimo(nuevo,sucesores);
                dispEstado(nuevo->estado);
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
    tEstado *Final=estadoObjetivo();

    Lista Abiertos= (Lista) CrearLista(MAXI);
    Lista Cerrados= (Lista) CrearLista(MAXI);
    Lista Sucesores;

    InsertarPrimero(Inicial, Abiertos);

    while (!ListaVacia(Abiertos) && !objetivo)
    {

        Actual=ExtraerPrimero(Abiertos);
        EliminarPrimero(Abiertos);

        int repetido = buscaRepe(Actual->estado,Cerrados);
        if(!repetido)
        {
            //Insertamos el nodo que estamos tratando en cerrados
            //printf("\n ACTUAL: \n");
            //dispEstado(Actual->estado);
            //printf("ValHeuristica= %d \n",Actual->valHeuristica);
            //system("pause");

            objetivo=testObjetivo(Actual->estado);
            if (!objetivo)
            {
                Sucesores = expandir(Actual);
                Abiertos=Concatenar(Sucesores, Abiertos);
                Abiertos=OrdenaLista(Abiertos);
                InsertarUltimo(Actual, Cerrados);
            }

        }


    }

    dispSolucion(Actual);

    return objetivo;
}


int buscaRepe(tEstado *s, Lista L1)
{
    int repetido = 0, i = 0;

    while( !repetido && i < L1->Nelem )
    {
        tElemento *a = ExtraerElem(L1, i);
        tEstado *b = a->estado;

        if( iguales(s,b) ) repetido = 1;
        i++;
    }

    return repetido;

}
Lista OrdenaLista(Lista C)
{
    int  j, i, n = C->Nelem, H[n], O[n], Aux, Aux2;
    //system("cls");
    //printf("/nnum elem %d/n", n);
    Lista S = CrearLista(n);

    //COnvertimos el valor heuristico de cada nodo y el indice del nodo en vectores
    for(i=0; i<n; i++)
    {
        H[i] = ExtraerElem(C,i)->valHeuristica;
        O[i] = i;
    }
    // Ordenamos 0[] segun el valor heuristico
    for(i=0; i<n; i++)
    {
        for(j=n-1; j>i; j--)
        {
            if( H[j] < H[j-1] ){

                Aux = H[j-1];
                Aux2 = O[j-1];
                H[j-1] = H[j];
                O[j-1] = O[j];
                H[j] = Aux;
                O[j] = Aux2;
            }
        }

    }
    //introducimos de forma ordenada los elementos en la lista
    for(i=0; i<n; i++){
        InsertarUltimo(ExtraerElem(C,O[i]), S );
    }

    /*printf("\n ---------Sucesores ordenados------------- \n");
    for(i=0; i<n; i++)
    {
        dispEstado( ExtraerElem(S,i)->estado );
        printf("ValHeuristica= %d \n\n",ExtraerElem(S,i)->valHeuristica);
    }

    printf("\n------------------------------------ \n");

    system("pause");*/
    return S;
}
int heuristica(tEstado *s){
    int i , j, cont;

    cont = 0;

    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            if(s->celdas[i][j]==estadoObjetivo()->celdas[i][j])
            {
                cont++;
            }
        }
    }
    return  cont;
}





#include <stdio.h>
#include <stdlib.h>

#define TAM 0

struct Nodo{
    int dato;
    struct Nodo *ptrSig;
};

struct Nodo* crearNodo(int dato);
void meterNodo(struct Nodo *ptrRef, int dato);
void recorrer(struct Nodo *ptrRef);
void eliminarNodo(struct Nodo **ptrRef);
int menu();

int main(){

    struct Nodo *miPtrRef; 
    int dato;

    miPtrRef = crearNodo(-1000);

    for(;;){
        switch (menu()){

        case 1:
            printf("Ingrese un dato:\t");
            scanf("%d", &dato);
            meterNodo(miPtrRef, dato);
            break;
        
        case 2:
            eliminarNodo(&miPtrRef);
            break;
            
        case 3:
            recorrer(miPtrRef);
            break;
            
        case 4:
            exit(0);
            break;

        default:
            printf("Ingrese un numero valido.");
            break;
        }
    }

    printf("\n");

    return 0;
}

struct Nodo* crearNodo(int dato1){
    struct Nodo *ptrN;
    ptrN = (struct Nodo*) malloc(sizeof(struct Nodo));
    ptrN -> dato = dato1;
    ptrN -> ptrSig = NULL;
    return ptrN;
}

void meterNodo(struct Nodo *ptrRef, int dato){
    struct Nodo *ptrN1;
    ptrN1 = crearNodo(dato);

    if(ptrRef -> ptrSig == NULL)
        ptrRef -> ptrSig = ptrN1;
    else{
        ptrN1 -> ptrSig = ptrRef -> ptrSig;
        ptrRef -> ptrSig = ptrN1;
    }
}
    
void recorrer(struct Nodo *ptrRef){
    struct Nodo *ptrRec;
    ptrRec = ptrRef->ptrSig;
    printf("\n");
    while (ptrRec != NULL){
        printf(" %d -", ptrRec->dato);
        ptrRec = ptrRec->ptrSig;
    }
}

void eliminarNodo(struct Nodo **ptrRef) {
    if (*ptrRef != NULL && (*ptrRef)->ptrSig != NULL) {
        struct Nodo *ptrBas = (*ptrRef)->ptrSig;
        (*ptrRef)->ptrSig = ptrBas->ptrSig;
        printf("El dato recuperado es: ' %d '\n", ptrBas->dato);
        free(ptrBas);
    } else {
        printf("La lista esta vacia\n");
    }
}

int menu(){
    int eleccion;
	
	printf("\n\n1.\tIngresa un dato.\n");
	printf("2.\tSacar un dato.\n");
    printf("3.\tVisualizar.\n");
	printf("4.\tSalir\n");
	
	scanf("%d", &eleccion);
	return eleccion;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_PILA 100

// Estructura para el nodo de la pila
struct Nodo {
    char dato;
    struct Nodo *ptrSig;
};

// Funciones para la pila dinámica
struct Nodo *crearNodo(char dato);
void push(struct Nodo **ptrToTop, char dato);
char pop(struct Nodo **ptrToTop);
int isEmpty(struct Nodo *top);
char peek(struct Nodo *top);

// Funciones para la conversión infija a postfija
void conversionInfijaPostfija(char *cadenaLeida);

int esOperador(char caracter);
int gradoOperador(char caracter);
int esParentesis(char caracter);

int main() {
    char expresion[100];
    printf("Ingrese la expresion infija: ");
    fgets(expresion, sizeof(expresion), stdin);

    conversionInfijaPostfija(expresion);

    return 0;
}

void conversionInfijaPostfija(char *cadenaLeida) {
    struct Nodo *pila = NULL;
    char *ptrCadena;

    printf("Expresion infija: %s", cadenaLeida);

    for (ptrCadena = cadenaLeida; *ptrCadena != '\0'; ptrCadena++) {
        if (esParentesis(*ptrCadena)) {
            if (*ptrCadena == '(') {
                push(&pila, *ptrCadena);
            } else if (*ptrCadena == ')') {
                while (!isEmpty(pila) && peek(pila) != '(') {
                    printf("%c", pop(&pila));
                }
                if (!isEmpty(pila) && peek(pila) == '(') {
                    pop(&pila);
                }
            }
        } else if (esOperador(*ptrCadena)) {
            while (!isEmpty(pila) && gradoOperador(peek(pila)) >= gradoOperador(*ptrCadena)) {
                printf("%c", pop(&pila));
            }
            push(&pila, *ptrCadena);
        } else if (isalnum(*ptrCadena)) {
            printf("%c", *ptrCadena);
        }
    }

    while (!isEmpty(pila)) {
        printf("%c", pop(&pila));
    }
}

// Implementación de las funciones para la pila dinámica
struct Nodo *crearNodo(char dato) {
    struct Nodo *ptrNuevo = (struct Nodo *)malloc(sizeof(struct Nodo));
    if (ptrNuevo != NULL) {
        ptrNuevo->dato = dato;
        ptrNuevo->ptrSig = NULL;
    }
    return ptrNuevo;
}

void push(struct Nodo **ptrToTop, char dato) {
    struct Nodo *ptrNuevo = crearNodo(dato);
    if (ptrNuevo != NULL) {
        ptrNuevo->ptrSig = *ptrToTop;
        *ptrToTop = ptrNuevo;
    } else {
        printf("No se pudo asignar memoria para el nuevo nodo.\n");
    }
}

char pop(struct Nodo **ptrToTop) {
    char valorSacado = '\0';
    if (*ptrToTop != NULL) {
        struct Nodo *ptrTemp = *ptrToTop;
        valorSacado = (*ptrToTop)->dato;
        *ptrToTop = (*ptrToTop)->ptrSig;
        free(ptrTemp);
    }
    return valorSacado;
}

int isEmpty(struct Nodo *top) {
    return top == NULL;
}

char peek(struct Nodo *top) {
    return (top != NULL) ? top->dato : '\0';
}

// Funciones auxiliares para la conversión infija a postfija
int esOperador(char caracter) {
    return (caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/' || caracter == '^');
}

int gradoOperador(char caracter) {
    switch (caracter) {
        case '^':
            return 3;
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}

int esParentesis(char caracter) {
    return (caracter == '(' || caracter == ')');
}
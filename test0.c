#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_PILA 100
#define TAM_CADENA 100

// Estructura para el nodo de la pila
struct Nodo {
    char dato;
    struct Nodo *ptrSig;
};

char *leerCadenaDesdeArchivo(char *nombreArchivo);
void escribirEnArchivo(char caracter, char *nombreArchivo);

// Funciones para la pila dinámica
struct Nodo *crearNodo(char dato);
void pushStack(struct Nodo **ptrToTop, char dato);
char popStack(struct Nodo **ptrToTop);
int pilaVacia(struct Nodo *top);
char valorCima(struct Nodo *top);

// Funciones para la conversión infija a postfija
void conversionInfijaPostfija(char *cadenaLeida);

int esOperador(char caracter);
int gradoOperador(char caracter);
int esParentesis(char caracter);

void imprimirPila(struct Nodo *ptrCima);

int main() {

    //char expresionInfija[100];
    //printf("Ingrese la expresion infija: ");
    //fgets(expresionInfija, sizeof(expresionInfija), stdin);

    char *expresionInfija = leerCadenaDesdeArchivo("entrada.txt");

    if(expresionInfija != NULL){
        printf("\nExpresion infija leida: %s\n\n", expresionInfija);
        conversionInfijaPostfija(expresionInfija);
        free(expresionInfija);
    }else
        printf("La cadena esta vacia.");
    

    return 0;
}

void conversionInfijaPostfija(char *cadenaLeida) {
    struct Nodo *ptrPila = NULL;
    char *ptrCadena;

    //printf("Expresion infija: %s", cadenaLeida);
    //pushStack(&ptrPila, '(');

    for (ptrCadena = cadenaLeida; *ptrCadena != '\0'; ptrCadena++) {

        printf("Caracter: %c\t", *ptrCadena);

        if (esParentesis(*ptrCadena)) {

            if (*ptrCadena == '(') {
                pushStack(&ptrPila, *ptrCadena);

            } else if (*ptrCadena == ')') {
                
                printf("\tParentesis: %c \n\t\t", *ptrCadena);

                while (!pilaVacia(ptrPila) && valorCima(ptrPila) != '(') {


                    escribirEnArchivo(popStack(&ptrPila), "salida.txt");


                }
                if (!pilaVacia(ptrPila) && valorCima(ptrPila) == '(') {
                    
                    // Elimina el parentesis de abertura que queda de la pila

                    popStack(&ptrPila);
                }
            }

        } else if (esOperador(*ptrCadena)) {

            while (!pilaVacia(ptrPila) && gradoOperador(valorCima(ptrPila)) >= gradoOperador(*ptrCadena)) {


                //printf("%c", popStack(&ptrPila));
                char caracterPila = popStack(&ptrPila);
                printf("\tOperador: %c >= %c \n\t\t", caracterPila, *ptrCadena);
                // escribir en archivo
                escribirEnArchivo(caracterPila, "salida.txt");

            }
            // Se agrega el caracter que se estaba leyendo el cual hizo que los demas caracteres se salieran de la pila, a la pila xd
            pushStack(&ptrPila, *ptrCadena);



        }else{
            //printf("%c", *ptrCadena);

            // Escribir en archivo
            escribirEnArchivo(*ptrCadena, "salida.txt");

        }

        imprimirPila(ptrPila);
        //printf("Pila al momento: %s\n", ptrPila->dato);
        //printf("\t\t\t\tCima de la pila: %c\n", *ptrStack->ptrDatos);
    }

    while (!pilaVacia(ptrPila)) {
        //printf("%c", popStack(&ptrPila));

        // Escribir en archivo
        escribirEnArchivo(popStack(&ptrPila), "salida.txt");

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

void pushStack(struct Nodo **ptrCima, char dato) {
    struct Nodo *ptrNuevo = crearNodo(dato);
    if (ptrNuevo != NULL) {
        ptrNuevo->ptrSig = *ptrCima;
        *ptrCima = ptrNuevo;
    } else 
        printf("No se pudo asignar memoria\n");
}

char popStack(struct Nodo **ptrCima) {
    char valorRecuperado = '\0';
    if (*ptrCima != NULL) {
        struct Nodo *ptrTemp = *ptrCima;
        valorRecuperado = (*ptrCima)->dato;
        *ptrCima = (*ptrCima)->ptrSig;
        free(ptrTemp);
    }
    return valorRecuperado;
}

int pilaVacia(struct Nodo *ptrCima) {
    return (ptrCima == NULL) ? 1 : 0;
}

char valorCima(struct Nodo *ptrCima) {
    return (ptrCima != NULL) ? ptrCima->dato : '\0';
}

// Funciones auxiliares para la conversión infija a postfija
int esOperador(char caracter) {
    return (caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/' || caracter == '^') ? 1 : 0;
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
    return (caracter == '(') || caracter == ')' ? 1 : 0;
}

// Función que escribe en el archivo de texto
void escribirEnArchivo(char caracter, char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "a"); // Abre el archivo en modo de escritura, agregando al final del archivo

    // Verifica si el archivo se abrió correctamente
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return; // Termina la función si hay un error
    }

    // Escribe el caracter en el archivo
    fprintf(archivo, "%c", caracter);

    // Cierra el archivo
    fclose(archivo);
}

// Función para leer una cadena de texto desde un archivo
char *leerCadenaDesdeArchivo(char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r"); // "r" - indica que es archivo para lectura
    char *cadena = (char *)malloc(TAM_CADENA * sizeof(char)); // Asignación dinámica de memoria para la cadena

    // Verifica si el archivo se abrió correctamente
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return NULL;
    }

    // Lee la cadena de texto del archivo
    if (fgets(cadena, TAM_CADENA, archivo) != NULL) {
        fclose(archivo); // Cierra el archivo después de la lectura
        return cadena; // Retorna la cadena leída del archivo
    } else {
        printf("El archivo está vacío.\n");
        fclose(archivo); // Cierra el archivo si está vacío
        free(cadena); // Libera la memoria asignada para la cadena
        return NULL;
    }
}

void imprimirPila(struct Nodo *ptrCima) {
    struct Nodo *temp = ptrCima;

    char elementos[100]; // Array temporal para almacenar los elementos de la pila
    int indice = 0;

    printf("\tElementos de la pila: ");
    
    // Almacenar los elementos de la pila en el array temporal
    while (temp != NULL) {
        elementos[indice++] = temp->dato;
        temp = temp->ptrSig;
    }
    
    // Imprimir los elementos del array en orden inverso
    for (int i = indice - 1; i >= 0; i--) {
        printf("%c ", elementos[i]);
    }
    
    printf("\n");
}
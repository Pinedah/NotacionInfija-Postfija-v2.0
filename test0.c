
/*
    Pineda Hernandez Francisco
    Algoritmos y Estructuras de Datos
    Proyecto Primer Parcial
    "Algoritmo que convierte expresión aritmetica Infija a PostFija v2.0"
*/

// Importaciones necesarias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Declaración de constante para el tamaño de la cadena
#define TAM_CADENA 100

// Estructura para el nodo de la pila
struct Nodo {
    char dato;
    struct Nodo *ptrSig;
};

// Funciones para la lectura y escritura en el archivo
char *leerCadenaDesdeArchivo(char *nombreArchivo);
void escribirEnArchivo(char caracter, char *nombreArchivo);

// Funciones para la pila dinámica
struct Nodo *crearNodo(char dato);
void pushStack(struct Nodo **ptrToTop, char dato);
char popStack(struct Nodo **ptrToTop);
int pilaVacia(struct Nodo *top);
char valorCima(struct Nodo *top);
void imprimirPila(struct Nodo *ptrCima);

// Funciones para la conversión infija a postfija
void conversionInfijaPostfija(char *cadenaLeida);
int esOperador(char caracter);
int gradoOperador(char caracter);
int esParentesis(char caracter);


// Funcion MAIN
int main() {
    char *expresionInfija = leerCadenaDesdeArchivo("entrada.txt"); // Se lee la cadena desde el archivo de texto

    if(expresionInfija != NULL){ // Se verifica que la cadena no esté vacía
        printf("\nExpresion infija leida: %s\n\n", expresionInfija);
        conversionInfijaPostfija(expresionInfija); // Se llama a la función principal para hacer la conversión
        free(expresionInfija); // Se libera la memoria de la cadena leída
    }else
        printf("La cadena esta vacia.");
    
    return 0;
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

// Función que crea un nodo
struct Nodo *crearNodo(char dato) {
    struct Nodo *ptrNuevo = (struct Nodo *)malloc(sizeof(struct Nodo));
    if (ptrNuevo != NULL) {
        ptrNuevo->dato = dato;
        ptrNuevo->ptrSig = NULL;
    }
    return ptrNuevo;
}

// Función que agrega un nuevo elemento a la pila
void pushStack(struct Nodo **ptrCima, char dato) {
    struct Nodo *ptrNuevo = crearNodo(dato);
    if (ptrNuevo != NULL) {
        ptrNuevo->ptrSig = *ptrCima;
        *ptrCima = ptrNuevo;
    } else 
        printf("No se pudo asignar memoria\n");
}

// Función que saca un elemento de la pila
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

// Función que verifica si la pila está vacía
int pilaVacia(struct Nodo *ptrCima) {
    return (ptrCima == NULL) ? 1 : 0;
}

// Funcion que retorna el elemento que esté en la cima de la pila
char valorCima(struct Nodo *ptrCima) {
    return (ptrCima != NULL) ? ptrCima->dato : '\0';
}

// Función que imprime la pila de forma inversa para su correcta lectura
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

// Función que administra el algoritmo de conversión
void conversionInfijaPostfija(char *cadenaLeida) {
    struct Nodo *ptrPila = NULL; // Se crea la instancia para el primer nodo
    char *ptrCadena; // Se crea el puntero para manipular la cadena

    for (ptrCadena = cadenaLeida; *ptrCadena != '\0'; ptrCadena++) {
        printf("Caracter: %c\t", *ptrCadena); // Imprimimos que carácter estamos leyendo en ese momento

        // Caso 1. El carácter leido es un paréntesis.
        if (esParentesis(*ptrCadena)) {
            if (*ptrCadena == '(') {
                // Si es un paréntesis de apertura, lo agregamos a la pila
                pushStack(&ptrPila, *ptrCadena);

            } else if (*ptrCadena == ')') {
                // Si es un paréntesis de cerradura, lo indicamos y hacemos lo que corresponde
                printf("\tParentesis: %c \n\t\t", *ptrCadena);
                
                while (!pilaVacia(ptrPila) && valorCima(ptrPila) != '(') {
                    // Si la pila no está vacía y la cima no es un parentesis de apertura, sacamos los operadores
                    escribirEnArchivo(popStack(&ptrPila), "salida.txt");
                }
                if (!pilaVacia(ptrPila) && valorCima(ptrPila) == '(') {
                    // Elimina el parentesis de abertura que queda de la pila
                    popStack(&ptrPila);
                }
            }
        // Caso 2. El carácter leído es un operador.
        } else if (esOperador(*ptrCadena)) {

            // Mientras la pila no esté vacía
            // y el grado del operador de la cima sea >= grado del operador leído 
            // Se saca de la pila
            while (!pilaVacia(ptrPila) && gradoOperador(valorCima(ptrPila)) >= gradoOperador(*ptrCadena)) {
                
                char caracterPila = popStack(&ptrPila); // caracter auxiliar para poder imprimirlo en consola
                printf("\tOperador: %c >= %c \n\t\t", caracterPila, *ptrCadena);
                escribirEnArchivo(caracterPila, "salida.txt");
            }
            // Se agrega a la pila el carácter que se estaba leyendo (el cual hizo que los demás carácteres se salieran de la pila)
            pushStack(&ptrPila, *ptrCadena);
        // Caso 3. El carácter leído no es paréntesis ni operador, es decir, es un operando (letra o número/número decimal)
        }else{
            // Directamente se escribe en el archivo
            escribirEnArchivo(*ptrCadena, "salida.txt");

        }

        // Imprimimos la pila cada que concluye un ciclo
        imprimirPila(ptrPila);
    } // fin for

    // Una vez que termina de leer la cadena, se vacía lo que haya quedado en la pila
    while (!pilaVacia(ptrPila)) {
        escribirEnArchivo(popStack(&ptrPila), "salida.txt");
    }
}

// Función que verifica si el carácter es un operador
int esOperador(char caracter) {
    return (caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/' || caracter == '^') ? 1 : 0;
}

// Función que verifica el grado del operador
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

// función que verifica si el carácter es un paréntesis
int esParentesis(char caracter) {
    return (caracter == '(') || caracter == ')' ? 1 : 0;
}

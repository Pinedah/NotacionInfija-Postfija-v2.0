
/*
    Pineda Hernandez Francisco
    Algoritmos y Estructuras de Datos
    Proyecto Primer Parcial
    "Algoritmo que convierte expresión aritmetica Infija a PostFija"
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Declaracion de constantes para los tamaños de pila y cadena
#define TAM_PILA 100
#define TAM_CADENA 100

// Estructura para la pila
struct STACK{
    char datos[TAM_PILA]; 
    char *ptrDatos; // Puntero que manipule la pila
};

// Declaraciones de funciones
char *leerCadenaDesdeArchivo(char *nombreArchivo);
void conversionInfijaPostfija(char *cadenaLeida, struct STACK *ptrStack);
void escribirEnArchivo(char caracter, char *nombreArchivo);
int esOperador(char caracter);
int gradoOperador(char caracter);
int esParentesis(char caracter);
void pushStack(struct STACK *ptrStack, char caracter);
void popStack(struct STACK *ptrStack);

// Funcion Main
int main(){

    char *cadenaLeida = leerCadenaDesdeArchivo("entrada.txt"); // Se lee la cadena del archivo de texto

    struct STACK stack, *myPtrStack; // Instancia y puntero local de la pila
    myPtrStack = &stack; // Inicialización del puntero local a la pila
    myPtrStack->ptrDatos = myPtrStack->datos; // Inicialización del puntero de pila a pila

    if (cadenaLeida != NULL) { // Se comprueba que la cadena no esté vacía
        printf("La cadena leída del archivo es: %s\n", cadenaLeida);

        // Si no está vacía, se procede a hacer la conversión enviandola a la función conversión...
        conversionInfijaPostfija(cadenaLeida, myPtrStack);
        
        free(cadenaLeida); // Liberar la memoria asignada para la cadena
    }
    printf("\nPila Final: %s\n", myPtrStack->datos); // Se muestra en consola como terminó la pila
    printf("\t\t\t\tCima de la pila: %c\n", *myPtrStack->ptrDatos);

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

// Función para administrar todo el procedimiento de conversión infija a postfija
void conversionInfijaPostfija(char *cadenaLeida, struct STACK *ptrStack){ // Recibimos el puntero a la cadena leida y el puntero a la pila
    char *ptrCadena; // declaramos un puntero para manipular la cadena

    // Ingresamos un primer valor '(' a la pila, como el algoritmo lo indica
    *ptrStack->ptrDatos = '(';
    ptrStack->ptrDatos++;

    for(ptrCadena = cadenaLeida; *ptrCadena != '\0'; ptrCadena++){
        
        // Verificamos el primer caso. Si el caracter leido es un parentesis, entra a comparar
        if(esParentesis(*ptrCadena)){
            
            // Verificamos que tipo de parentesis es
            switch (*ptrCadena){
                case '(':
                    pushStack(ptrStack, *ptrCadena); // Si es de apertura, directamente lo agregamos a la pila
                    break;

                case ')':
                    printf("Parenteis que cierra: %c \n", *ptrCadena);
                    ptrStack->ptrDatos--; // Se decrementa para poder comparar los elementos anteriores en la pila
                    while(*ptrStack->ptrDatos != '('){ // Mientras no sea un parentesis de apertura, sacamos de la pila los operadores
                        printf("Operador anterior: %c \n", *ptrStack->ptrDatos);
                        popStack(ptrStack);
                    }
                    break;
            }

        // Verificamos el segundo caso. Si el caracter leido es un operador, entra a comparar
        }else if(esOperador(*ptrCadena)){
            
            // Si el grado del operador ANTERIOR es cero, quiere decir que lo que se leyó antes que estaba en la pila no es un operador, es decir, solo puede ser un parentesis, por lo que simplemente agrega el operador a la pila
            if(!gradoOperador(*(ptrStack->ptrDatos - 1))){
                pushStack(ptrStack, *ptrCadena);

            // Si el grado del operador Anterior es diferente de cero, entonces es un operador
            }else{

                // Si el grado del operador anterior en la pila es MENOR QUE el grado del operador que se está leyendo, entonces se escribe en la pila el que se está leyendo, pues va de forma ascendente y el algoritmo lo permite
                if(gradoOperador(*(ptrStack->ptrDatos-1)) < gradoOperador(*ptrCadena)){
                    pushStack(ptrStack, *ptrCadena); // Se ingresa en la pila el operador
                    printf("Grado menor en pila: %c < %c\n", *(ptrStack->ptrDatos - 1), *ptrCadena);

                // Si el grado del operador anterior en la pila es MAYOR QUE el grado del operador que se está leyendo, entonces entra al bucle para buscar un parentesis y sacar los operadores existentes.
                }else if(gradoOperador(*(ptrStack->ptrDatos-1)) > gradoOperador(*ptrCadena)){
                    
                    // Mientras el operador anterior sea diferente del '(', va a ir sacando los operadores
                    while (*(ptrStack->ptrDatos-1) != '('){
                        printf("Grado mayor en pila: %c > %c\n", *(ptrStack->ptrDatos - 1), *ptrCadena);

                        ptrStack->ptrDatos--; // Decrementa una vez para poder sacar de la pila el operador con el que se está comparando
                        popStack(ptrStack); // Lo saca de la pila
                        ptrStack->ptrDatos++; // Incrementa una vez para dejar el puntero donde se debe, ya que el popStack decrementa el puntero
                    }
                    pushStack(ptrStack, *ptrCadena); // Ya que saco todos los operadores que estaban antes, agrega el operador que es menor y por el cual se entro al bucle
                    
                // Si los grados no son ni mayores ni menores, entonces son iguales
                }else{
                        printf("Grado igual: %c & %c \n", *(ptrStack->ptrDatos - 1), *ptrCadena);

                        // (Mismo procedimiento que con cuando PILA > Cadena) cuando son iguales solo se debe remplazar el operador anteior y poner el nuevo en ese lugar
                        ptrStack->ptrDatos--; // Se decrementa para poder sacar el operador
                        popStack(ptrStack); // Se saca de la pila ese operador
                        ptrStack->ptrDatos++; // Se regresa a su posición 
                        pushStack(ptrStack, *ptrCadena); // Se ingresa en la pila en ese mismo lugar el operador nuevo de grado igual
                }
            }

        // Verificamos el tercer y último caso. Si el caracter leido no es un parentesis ni un operador, entonces es un operando (letra/número)
        }else{
            // Directamente se escribe en el archivo, sin pasar por la pila
            escribirEnArchivo(*ptrCadena, "expresionPostfija.txt");
            printf("\t\t\t\t\t\t\tTxt (operando):\t%c \n", *ptrCadena);
        }

        printf("Pila al momento: %s\n", ptrStack->datos); // Mostramos como va la pila al momento (recordar que aunque haya más elementos, puede que para fines reales, esos elementos ya no "existan")
        printf("\t\t\t\tCima de la pila: %c\n", *ptrStack->ptrDatos); // Mostramos la cima al momento
    }

    printf("El puntero de la pila al finalizar los calculos queda en: %c \n", *ptrStack->ptrDatos);

    // Realizamos el paso final, que es sacar todo lo que se haya quedado en la pila
    ptrStack->ptrDatos--; // Decrementamos para ir al primer valor
    while(*ptrStack->ptrDatos != '('){ // Hasta encontrar el '(' inicial
        //escribirEnArchivo(*ptrStack->ptrDatos, "expresionPostfija.txt"); // Directamente escribimos en el archivo el elemento encontrado difernte al parentesis de abertura
        popStack(ptrStack);
        //ptrStack->ptrDatos--; // Se decrementa para ir al elemento anterior
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

// Función que evalua si es o no es un operador 
int esOperador(char caracter){
    return (caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/' || caracter == '^') ? 1 : 0;
}

// Función que evalua el "grado" del caracter ingresado 
int gradoOperador(char caracter) {
    // La función es llamada dentro de un entorno en donde ya se sabe que solo hay caracteres del tipo 'Operador', por lo que no habrá más que esos caracteres evaluados, no obstante, el default devuelve 0, lo que el algoritmo entiende y respeta como un NO-operador
    switch(caracter) { // Respeta el la jerarquia de operaciones aritmeticas
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

// Función que evalua si el caracter ingresado es un parentesis o no
int esParentesis(char caracter){
    return (caracter == '(') || caracter == ')' ? 1 : 0;
}

// Función que agrega un elemento (caracter) a la pila
void pushStack(struct STACK *ptrStack, char caracter){
    *ptrStack->ptrDatos = caracter;
    ptrStack->ptrDatos++; // Incrementa el puntero de la pila para poder almacenar un elemento nuevo en la cima
}

// Función que saca algún elemento de la pila
void popStack(struct STACK *ptrStack){
    // Cada que se extraiga algún elemeto de la pila se deberá escribir en el archivo 
    escribirEnArchivo(*ptrStack->ptrDatos, "expresionPostfija.txt");
    printf("\t\t\t\t\t\t\tTxt (pila):\t%c \n", *ptrStack->ptrDatos);
    ptrStack->ptrDatos--; // Se decrementa el puntero de la pila para poder almacenar en la cima algún otro elemento
}
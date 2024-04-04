# Conversión de Expresiones Infijas a Postfijas
Este proyecto consiste en un algoritmo implementado en C que convierte una expresión aritmética en formato infijo a su equivalente en formato postfijo. La conversión se realiza mediante el uso de una pila dinámica para la manipulación de los operadores y la preservación del orden de precedencia.

# Funcionamiento del Programa
El programa lee una expresión infija desde un archivo de texto llamado "entrada.txt", realiza la conversión a formato postfijo y guarda el resultado en un archivo llamado "salida.txt". El proceso de conversión se realiza siguiendo las siguientes reglas:

Se recorre la expresión infija de izquierda a derecha.  
Si se encuentra un paréntesis de apertura '(' se agrega a la pila.  
Si se encuentra un paréntesis de cierre ')' se van sacando operadores de la pila y se agregan al resultado hasta encontrar el paréntesis de apertura correspondiente.  
Si se encuentra un operador, se sacan de la pila todos los operadores con igual o mayor precedencia y se agregan al resultado. Luego se agrega el operador actual a la pila.  
Si se encuentra un operando (letra o número), se agrega directamente al resultado.  

# Archivos
entrada.txt: Archivo de texto que contiene la expresión aritmética en formato infijo.  
salida.txt: Archivo de texto donde se guarda la expresión convertida a formato postfijo.  
ejemplos.txt: Archivo de texto que contiene ejemplos de las conversiones.  

# Compilación y Ejecución
Para compilar el programa, se debe ejecutar el siguiente comando en la terminal:

<< gcc -o conversor_expresiones conversor_expresiones.c >>
Una vez compilado, se puede ejecutar el programa con el siguiente comando:

<< conversor_expresiones >>

# Requisitos
Compilador de C compatible con el estándar C99.
Archivo de texto "entrada.txt" con la expresión aritmética en formato infijo.

# Autor
Pineda Hernandez Francisco

Notas Adicionales:
Este proyecto se realizó como parte de un proyecto del curso de Algoritmos y Estructuras de Datos. Se implementó utilizando el lenguaje de programación C y se siguió una metodología modular para facilitar la comprensión y mantenimiento del código.

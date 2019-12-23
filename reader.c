/*
* This function's objective is to read and print the stack file content.
*
* authors: Félix Aguilar Ferrer, Álvaro Bueno López, Adrián Bennasar Polzin
* date: 03/01/2020
*/

// Maximum value for an int
#define INT_MAX

// Libraries:
#include <stdio.h>
#include <limits.h>
#include "my_lib.h"

/*
* Function: Main:
* ---------------
* Primary function of the reader, here starts the reader execution.
*
*  argc: number of arguments introduced.
*  argv: char array of the arguments, the name of the executed file is stored 
*        in position 0.
*
*  returns: 0
*/

int main(int argc, char **argv)
{
    // Checks if the sintaxis is correct.
    if (argc != 2)
    {
        fprintf(stderr, "Sintaxis incorrecta: reader nombre_fichero\n");
        exit(1);
    }
    // Initializes the stack pointer and reads it from the file.
    struct my_stack *stack;
    stack = my_stack_read(argv[1]);

    // If the file does not exist.
    if (!stack)
    {
        fprintf(stderr, "No existe el fichero: %s\n", argv[1]);
        exit(1);
    }
    // Initializes the default values.
    int len = my_stack_len(stack);
    int sum = 0;
    int min = INT_MAX;
    int max = 0;
    printf("stack length: %d\n", len);

    // Process values while the stack is not empty.
    while (my_stack_len(stack))
    {
        // Obtains the data from the stack.
        int *data;
        data = my_stack_pop(stack);

        // Adds the value to the total and checks if it is max or min.
        sum += *(data);
        if (*(data) < min)
        {
            min = *(data);
        }
        if (*(data) > max)
        {
            max = *(data);
        }
        printf("%d\n", *(data));
    }
    // Shows the results of some operations performed with the stack data.
    printf("Items: %d Sum: %d Min: %d Max: %d Average: %d\n",
           len, sum, min, max, (sum / len));

    // Frees the memory that is in use by the stack.
    my_stack_purge(stack);
    return 0;
}
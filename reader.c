/*
* This function's objective is to read and print the stack file content.
*
* Authors: Aguilar Ferrer, Felix Lluis
*          Bennasar Polzin, Adrian
*          Bueno Lopez, Alvaro
*
* date: 03/01/2020
*/

// Libraries:
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "my_lib.h"

/*
* Function: main:
* ---------------
* Primary function of the reader, here starts the reader execution.
*
*  argc: number of arguments introduced.
*  argv: char array of the arguments, the name of the executed file is stored 
*        in position 0.
*
*  returns: success if execute correctly, else return failure.
*/
int main(int argc, char **argv)
{
    // Checks if the sintaxis is correct.
    if (argc != 2)
    {
        fprintf(stderr, "Sintaxis incorrecta: reader nombre_fichero\n");
        return EXIT_FAILURE;
    }
    // Initializes the stack pointer and reads it from the file.
    struct my_stack *stack;
    stack = my_stack_read(argv[1]);

    // If the file does not exist.
    if (!stack)
    {
        fprintf(stderr, "No existe el fichero: %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    // Initializes the default values.
    int len = my_stack_len(stack);
    int sum = 0;
    int min = INT_MAX;
    int max = 0;
    int avg = 0;
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
    // If stack length = 0 then skip avg and put min to 0.
    if (len)
    {
        avg = (sum / len);
    }
    else
    {
        min = 0;
    }
    // Shows the results of some operations performed with the stack data.
    printf("Items: %d Sum: %d Min: %d Max: %d Average: %d\n",
           len, sum, min, max, avg);

    // Frees the memory that is in use by the stack.
    my_stack_purge(stack);
    return EXIT_SUCCESS;
}
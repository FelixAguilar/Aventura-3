// Maximum value for an int
#define INT_MAX

// Libraries:
#include <stdio.h>
#include <limits.h>
#include "my_lib.h"

/*
* Function: Main:
* ---------------
* Primary function of the minishell, here starts the minishell execution.
*
*  argc: number of arguments introduced.
*  argv: char array of the arguments, the name of the executed file is stored 
*        in position 0.
*
*  returns: exit_success if it was executed correctly.
*/

int main(int argc, char **argv)
{

    if (argc != 2)
    {
        fprintf(stderr, "Sintaxis incorrecta: reader nombre_fichero\n");
        exit(1);
    }
    struct my_stack *stack;
    stack = my_stack_read(argv[1]);

    if (!stack)
    {
        fprintf(stderr, "No existe el fichero: %s\n", argv[1]);
        exit(1);
    }

    int len = my_stack_len(stack);
    int sum = 0;
    int min = INT_MAX;
    int max = 0;

    printf("stack length: %d\n", len);

    while (my_stack_len(stack))
    {
        int *data;
        data = my_stack_pop(stack);
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
    printf("Items: %d Sum: %d Min: %d Max: %d Average: %d\n",
           len, sum, min, max, (sum / len));

    my_stack_purge(stack);
    return 0;
}
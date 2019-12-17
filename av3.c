/*
*
* Authors: Aguilar Ferrer, Felix Lluis
*          Bennasar Polzin, Adrian
*          Bueno Lopez, Alvaro
*
* Date:    03/01/2020
*/

// Constants:
#define THREADS 10
#define NODES 10
#define ITERATIONS 1000000

// Libraries:
#include <stdio.h>
#include "my_lib.h"
#include <pthread.h>

void counter();
struct my_stack *init_stack(char *file);

int main(int argc, char **argv)
{
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    if (argc != 2)
    {
        fprintf(stderr, "Error de sintaxis: ./av3 nombre archivo\n");
        return 1;
    }
    struct my_stack *stack = init_stack(argv[1]);

    my_stack_write(stack, argv[1]);
    my_stack_purge(stack);
}

void counter()
{
    int i = ITERATIONS;

    while(i>0)
    {
        pthread_mutex_lock();
        int val = my_stack_pop(stack);
        pthread_mutex_unlock();

        pthread_mutex_lock();
        val++;
        my_stack_push(stack,val);
        i--;
        pthread_mutex_unlock();
    }
    pthread_exit();
}

struct my_stack *init_stack(char *file)
{
    struct my_stack *stack;
    stack = my_stack_read(file);

    if (stack)
    {
        if (my_stack_len(stack) != NODES)
        {
            if (my_stack_len(stack) < NODES)
            {
                while (my_stack_len(stack) != NODES)
                {
                    int *data = malloc(sizeof(int));
                    *data = 0;
                    my_stack_push(stack, data);
                }
            }
            else
            {
                while (my_stack_len(stack) != NODES)
                {
                    my_stack_pop(stack);
                }
            }
        }
    }
    else
    {
        stack = my_stack_init(sizeof(int));
        while (my_stack_len(stack) != NODES)
        {
            int *data = malloc(sizeof(int));
            *data = 0;
            my_stack_push(stack, data);
        }
    }
    return stack;
}
/*
*
* Authors: Aguilar Ferrer, Felix Lluis
*          Bennasar Polzin, Adrian
*          Bueno Lopez, Alvaro
*
* Date:    03/01/2020
*/

//#define PRINT

// Constants:
#define THREADS 10
#define NODES  10
#define ITERATIONS 1000000

// Libraries:
#include <stdio.h>
#include "my_lib.h"
#include <pthread.h>

void *counter();
struct my_stack *init_stack(char *file);

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static struct my_stack *stack;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Error de sintaxis: ./av3 nombre archivo\n");
        return 1;
    }

    printf("Threads: %d, Iterations: %d\n", THREADS, ITERATIONS);

    stack = init_stack(argv[1]);
    pthread_t thread[THREADS];

    for (int i = 0; i < THREADS; i++)
    {
        pthread_create(&thread[i],NULL, counter, NULL);
#ifdef  PRINT
        printf("El hilo %ld creado\n", thread[i]);
#endif
    }
    for (int i = 0; i < THREADS; i++)
    {
        pthread_join(thread[i], NULL);
    }

    my_stack_write(stack, argv[1]);
    //my_stack_purge(stack);
}

void *counter()
{
    int i = 0;
    while (i < ITERATIONS)
    {
        pthread_mutex_lock(&mutex);
#ifdef  PRINT
        printf("Soy el hilo %ld ejecutando pop\n", pthread_self());
#endif
        int *val = my_stack_pop(stack);
        pthread_mutex_unlock(&mutex);

        pthread_mutex_lock(&mutex);
#ifdef  PRINT
        printf("Soy el hilo %ld ejecutando push\n", pthread_self());
#endif
        *val = *val + 1;
        my_stack_push(stack, val);
        i++;
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(0);
}

struct my_stack *init_stack(char *file)
{
    struct my_stack *stack;
    stack = my_stack_read(file);
    if (stack)
    {
            printf("stack->size: %d\ninitial stack length: %d\n", stack->size, my_stack_len(stack));

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

            printf("stack->size: %d\ninitial stack length: %d\n", stack->size, my_stack_len(stack));

        while (my_stack_len(stack) != NODES)
        {
            int *data = malloc(sizeof(int));
            *data = 0;
            my_stack_push(stack, data);
        }
    }

    printf("final stack length: %d\n", my_stack_len(stack));
    return stack;
}

/*
* This contains the function to modify a stack by adding values with threads
* and save it to a file.
*
* Authors: Aguilar Ferrer, Felix Lluis
*          Bennasar Polzin, Adrian
*          Bueno Lopez, Alvaro
*
* Date:    03/01/2020
*/

// Uncomment this to print information while executing.
//#define PRINT

// Constants:
#define THREADS 10
#define NODES 10
#define ITERATIONS 1000000

// Libraries:
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "my_lib.h"

// Function headers:
void *counter();
struct my_stack *init_stack(char *file);

// Alocates memory for the stack and semafore.
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static struct my_stack *stack;

/*
* Function: main:
* ---------------
* Primary function of the av3, here starts the av3 execution.
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
        fprintf(stderr, "Error de sintaxis: ./av3 nombre archivo\n");
        return EXIT_FAILURE;
    }
    // Prints basic information.
    printf("Threads: %d, Iterations: %d\n", THREADS, ITERATIONS);

    // Creates the stack and an array for the threads id.
    stack = init_stack(argv[1]);
    pthread_t thread[THREADS];

    // Creates all threads.
    for (int i = 0; i < THREADS; i++)
    {
        pthread_create(&thread[i], NULL, counter, NULL);
        printf("%d) Thread %ld created\n", i, thread[i]);
    }
    // Waits for all threads to end.
    for (int i = 0; i < THREADS; i++)
    {
        pthread_join(thread[i], NULL);
    }
    // Save the stack into the file and purges it from memory.
    int p = my_stack_write(stack, argv[1]);
    printf("Writen elements form stack to file: %d\n", p);
    p = my_stack_purge(stack);
    printf("Released bytes: %d\n", p);
    return EXIT_SUCCESS;
}

/*
* Function: counter:
* ------------------
* This function is executed by the threads, this will obtain a value from the 
* stack, add one to it and then store it in the stack again. Before access into
* the stack checks if mutex allows it, if not then wait until it can again.
*
*  returns: void.
*/
void *counter()
{
    // Loops until executed all operations with the thread.
    int i = 0;
    while (i < ITERATIONS)
    {
        // If mutex allows, read value from the stack.
        pthread_mutex_lock(&mutex);
#ifdef PRINT
        printf("Soy el hilo %ld ejecutando pop\n", pthread_self());
#endif
        int *val = my_stack_pop(stack);
        pthread_mutex_unlock(&mutex);

        // If mutex allows, adds value to the stack.
        pthread_mutex_lock(&mutex);
#ifdef PRINT
        printf("Soy el hilo %ld ejecutando push\n", pthread_self());
#endif
        *val = *val + 1;
        my_stack_push(stack, val);
        i++;
        pthread_mutex_unlock(&mutex);
    }
    // After all operations executed then exit thread.
    pthread_exit(0);
}

/*
* Function: init_stack:
* ---------------------
* Checks if the stack exists and if it does configures it to the constants 
* defined. Else creates a new stack with the configuration created with the 
* constants.
*
*  file: Pointer to the name of the file.
*
*  returns: stack pointer.
*/
struct my_stack *init_stack(char *file)
{
    // Allocates the stack pointer and reads from the file if it has a stack.
    struct my_stack *stack;
    stack = my_stack_read(file);

    // If the stack exist, then configure it to the execution.
    if (stack)
    {
        printf("initial stack length: %d\n", my_stack_len(stack));

        // If the stack is diferent than needed corrects it.
        if (my_stack_len(stack) != NODES)
        {
            // If shorter then adds nodes.
            if (my_stack_len(stack) < NODES)
            {
                while (my_stack_len(stack) != NODES)
                {
                    int *data = malloc(sizeof(int));
                    *data = 0;
                    my_stack_push(stack, data);
                }
            }
            // If longer pops nodes.
            else
            {
                while (my_stack_len(stack) != NODES)
                {
                    my_stack_pop(stack);
                }
            }
        }
    }
    // If not creates a new stack wiht the execution configuration.
    else
    {
        stack = my_stack_init(sizeof(int));
        printf("initial stack length: %d\n", my_stack_len(stack));

        // Adds the default values to the stack.
        while (my_stack_len(stack) != NODES)
        {
            int *data = malloc(sizeof(int));
            *data = 0;
            my_stack_push(stack, data);
        }
    }
    // prints final lenght and returns the stack.
    printf("final stack length: %d\n", my_stack_len(stack));
    return stack;
}

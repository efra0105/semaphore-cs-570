//Efrain Magallon & Pingchuan Li
//masc1984 & masc2020
//CS 570, Summer 2016
//Assignment 1 - semaphores
//a1.c

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>

#include "a1.h"

//void handler(); /* Function each thread to call. */
sem_t FLAG;     /* declare the semaphore globally */

FILE *file; //creates a pointer for the shared txt file
int semError;//to detect errors in semaphore

int main (int argc, char *argv[])
{
    //int initTread; //variable initialization for number of threads
    //long x; //variable to initiate threadds
    
    /* Create a file named QUOTE.txt, in the current directory (cwd)*/
    file = fopen("QUOTE.txt", "w+");
    
    /* Write it's pid (Process ID) followed by a Carriage Return and Newline into the file. */
    /* the pid is saved on a file which is pointed to by the file pointer */
    fprintf(file, "The process id is %d.\r\n", getpid());
    /*print it's pid on the monitor */
    printf("The process id is %d.\r\n", getpid());
    /* Close the file QUOTE.txt */
    fclose(file);
    
    /* Create a semaphore named FLAG which the threads will use to manage access to the file QUOTE.txt */
    /* the pshared argument is 0, means the semaphore is shared between threads in the same process;*/
    /* initial value of the semaphore counter is 1 */
    sem_init(&FLAG, 0, 1);
    
    /* Create thread array and return code. */
    pthread_t threads[TOTAL];
    int thd[TOTAL];
    
    /* Starting each thread, raise error if thread creation failed. */
    int j;
    for ( j = 0; j < TOTAL; j++)
    {
        /* If successful, the pthread_create()creates a new thread with default attributes and returns zero.*/
        /* Otherwise, an error number is returned to indicate the error.*/
        /* pthread_create() stores the ID of the created thread in the location referenced by threads.*/
        /* The new thread starts execution by invoking function handler with the default argument*/
        thd[j] = pthread_create(&threads[j], NULL, (void *) &handler, NULL);
        if (thd[j]) /*True is represented by any numeric value not equal to 0 and false is represented by 0*/
        {
            printf("pthread_create() for thread %d return error code %d\n", j, thd[j]);
            fprintf(stderr, "Error - pthread_create() return code: %d\n", thd[j]);
            exit(-1);
        }
    }
    
    /* Waiting all 7 threads to complete their work. */
    
    for (j = 0; j < TOTAL; j++)
    {
        /*On success,pthread_join returns 0; on error, it returns an error number.*/
        pthread_join(threads[j],NULL);
    }
    
    /* Once all threads are done, destroy the semaphore and print to console. */
    /*Upon successful completion, a value of zero is returned. */
    /*Otherwise, a value of -1 is returned and errno is set to indicate the error.*/
    sem_destroy(&FLAG);
    printf("The semaphore has been successfully destroyed.\n");
    exit(0);
}

/* Function each thread to call. */
void handler ()
{
    int tid = (int)pthread_self();
    int j;
    for (j = 0; j < 7; j++)
    {
        /*locks the semaphore referenced by FLAG */
        sem_wait(&FLAG);
        printf("Thread %d is running.\n", tid);
        /*Open the file QUOTE.txt and write the thread's tid followed by "The Quote" (followed by a Carriage Return and Newline)*/
        file = fopen("QUOTE.txt", "a+");
        if ( tid % 2 == 0 )
        {
            fprintf(file,"%d. %s\r\n", tid, EVEN);
            
        }
        else
        {
            fprintf(file,"%d. %s\r\n", tid, ODD);
            
        }
        
        /*Close the file QUOTE.txt */
        
        fclose(file);
        /*Release the semaphore FLAG*/
        sem_post(&FLAG);
        /* Test if odd or even, to sleep 2 or 3 sec. */
        
        
        if ( tid % 2 == 0 )
        {
            sleep(2);
        }
        else
        {
            sleep(3);
        }
        
        
        
        
    }
    /* After 7 run, finish the thread. */
    pthread_exit(NULL);
}


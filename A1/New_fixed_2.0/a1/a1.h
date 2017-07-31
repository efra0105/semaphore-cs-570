//Efrain Magallon & Pingchuan Li
//masc1984 & masc2020
//CS 570, Summer 2016
//Assignment 1 - semaphores
//a1.h


#ifndef a1
//We use the necesary libraries to execute the program

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>



#define TOTAL 7//specifies the number of threads
#define EVEN "Controlling complexity is the essence of computer programming."//output after execution
#define ODD  "Computer science is no more about computers than astronomy is about telescopes."//output after execution

void handler();
void errorcheck (int errorcheck);




#endif /* a1_h */

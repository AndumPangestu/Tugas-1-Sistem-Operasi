#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <errno.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define SIZE 5

typedef struct elmt *address;
typedef struct elmt
{
    int value;
    address next;
} element;

typedef struct
{
    element *first, *last;
} queue;

// Inisialisasi queue.
void createqueue(queue *Q);

// Modifikasi queue.
void add(int data, queue *Q);
void del(queue *Q);

// Prosedur dan fungsi pendukung.
int isempty(queue Q);
int countelement(queue Q);

int countbuffer(queue Q);
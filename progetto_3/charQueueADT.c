#include "charQueueADT.h"
#include "charArrayQueue.h"
#include <stddef.h>
#include <stdlib.h>

/* il valore 8 può essere cambiato */
#define INITIAL_CAPACITY 8


/* Funzione ausiliaria statica per gestire il ridimensionamento e il riallineamento */
static _Bool resize(CharQueueADT q, int new_capacity) {
    char* new_a = malloc(sizeof(char) * new_capacity);
    if (new_a == NULL) return 0;
    for (size_t i = 0; i < q->size; i++) {
        new_a[i] = q->a[(q->front + i) % q->capacity];
    }
    free(q->a);
    q->a = new_a;
    q->front = 0;
    q->rear = q->size;
    q->capacity = new_capacity;
    return 1;
}

/* @brief Restituisce una coda vuota, se non trova memoria restituisce NULL */
CharQueueADT mkQueue() {
    CharQueueADT q = malloc(sizeof(struct charQueue));
    if(q==NULL){
        return NULL;
    }
    q->a = malloc(sizeof(char) * INITIAL_CAPACITY);
    if(q->a==NULL){
        free(q);
        return NULL;
    }
    q->front = 0; 
    q->rear = 0;
    q->capacity = INITIAL_CAPACITY;

    return q;
}

/* @brief Distrugge la coda, recuperando la memoria */
void dsQueue(CharQueueADT *pq) {
    if (pq != NULL && *pq != NULL) {
        free((*pq)->a);
        free(*pq);
        *pq = NULL;
    }
}
/* @brief Aggiunge un elemento in fondo alla coda */
_Bool enqueue(CharQueueADT q, const char e) {
    if (q == NULL) return 0;
    
    if (q->size == q->capacity) {
        if (!resize(q, q->capacity * 2)) return 0;
    }
    
    q->a[q->rear] = e;
    q->rear = (q->rear + 1) % q->capacity;
    q->size++;
    
    return 1;
}
/* @brief Toglie e restituisce l'elemento in testa alla coda */
_Bool dequeue(CharQueueADT q, char* res) {
    /* Se res è NULL, non possiamo restituire l'elemento, quindi falliamo */
    if (q == NULL || res == NULL || isEmpty(q)) return 0;
    
    *res = q->a[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    /* Ridimensionamento: quando size scende a capacity/4 */
    
    if (q->capacity > INITIAL_CAPACITY && q->size == q->capacity / 4) {
        resize(q, q->capacity / 2); 
        /* Se resize fallisce qui, non è critico: la coda continua a funzionare con più spazio */
    }
    
    return 1;
}
/* @brief Controlla se la coda è vuota */
_Bool isEmpty(CharQueueADT q) {
    if (q == NULL) return 1; 
    return q->size == 0; 
}
/* @brief Restituisce il numero degli elementi presenti nella coda */
int size(CharQueueADT q) {
    if (q == NULL) return 0;
    return q->size;
}
/* @brief Restituisce l'elemento nella posizione data (senza toglierlo) */
_Bool peek(CharQueueADT q, int position, char *res){
    if (q == NULL || res == NULL || position < 0 || position >= q->size) {
        return 0;
    }
    
    int real_index = (q->front + position) % q->capacity;
    *res = q->a[real_index];
    
    return 1;
}

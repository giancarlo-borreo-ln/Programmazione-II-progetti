#include "charQueueADT.h"
#include "linkedListQueue.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#define INITIAL_CAPACITY 8 /*Il valore 8 può essere cambiato*/

/*@brief Restituisce una coda vuota se non trova memoria restituisce null*/
CharQueueADT mkQueue(){
    CharQueueADT q = malloc(sizeof(*q));
    if(q == NULL) return NULL;
    
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    
    return q;
}

/*@brief Distrugge la coda, recuperando la memoria*/
void dsQueue(CharQueueADT *pq){
    if(pq != NULL && *pq != NULL){
        char garbage;

        while(isEmpty(*pq) == 0){
            dequeue(*pq, &garbage);
        }

        free(*pq);
        *pq = NULL;
    }
}

/*@brief Aggiunge un elemento in fondo alla coda, restituisce esito 0/1*/
_Bool enqueue(CharQueueADT q, const char e){
    if(q == NULL) return 0;

    ListNodePtr new_node = malloc(sizeof(*new_node));
    if(new_node == NULL) return 0;
    
    new_node->data = e;
    new_node->next = NULL;

    if(q->size == 0){
        q->front = new_node;
        q->rear = new_node;
    }else{
        q->rear->next = new_node;
        q->rear = new_node;
    }
    q->size++;
    return 1;
}

/*@brief Toglie e restituisce l'elemento in testa alla coda, restituisce eseito 0/1*/
_Bool dequeue(CharQueueADT q, char* res){
    if(q == NULL || res == NULL || q->size == 0){
        return 0;
    }

    ListNodePtr toRemove = q->front;
    *res = toRemove->data;
    
    q->front = q->front->next;
    free(toRemove);

    q->size--;

    if(q->size == 0) q->rear = NULL;

    return 1;
}

/*@brief Controlla se la coda è vuota*/
_Bool isEmpty(CharQueueADT q){
    if(q == NULL) return 1;
    return q->size == 0;
}

/*@brief Restituisce il numero degli elementi presenti nella coda*/
int size(CharQueueADT q){
    if(q == NULL) return 0;
    return q->size;
}

/*@brief Restituisce l'elemento nella posizione data (a partire dalla testa con indice zero) (senza toglierlo), restituisce sito 0/1*/
_Bool peek(CharQueueADT q, int position, char* res){
    if(q == NULL || res == NULL || q->size == 0 || position < 0) return 0;

    ListNodePtr currentPtr = q->front;

    while(position != 0){
        if(currentPtr->next == NULL) return 0;

        currentPtr = currentPtr->next;
        position--;
    }

    *res = currentPtr->data;
    return 1;
}
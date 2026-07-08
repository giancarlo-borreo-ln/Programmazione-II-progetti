#include <stdlib.h>
#include <stdbool.h>

#include "intSortedSetADT.h"
#include "intLinkedListSortedSetADT.h"

IntSortedSetADT mkSSet() {
    IntSortedSetADT ls = malloc(sizeof(*ls));

    if(ls == NULL) return NULL;

    ls -> first = NULL;
    ls -> last = NULL;

    ls -> size = 0;

    return ls;
}

_Bool dsSSet(IntSortedSetADT *ssptr) {
    if(ssptr != NULL && *ssptr != NULL){
        int garbage; 
        while(isEmptySSet(*ssptr) == 0){ 
            sset_extract(*ssptr, &garbage);
        }
        free(*ssptr);
        *ssptr = NULL;
        return 1;
    }

    return 0;

}

// aggiunge un elemento all'insieme (restituisce 0 se l'elemento era gia' presente, 1 altrimenti)
_Bool sset_add(IntSortedSetADT ss, const int elem) {
    if(ss == NULL) return 0;
    
    ListNodePtr new_node = malloc(sizeof(*new_node));
    if(new_node == NULL) return 0; 
    
    new_node->elem = elem;
    new_node->next = NULL;

    if(ss->size == 0){
        ss->first = new_node;
        ss->last = new_node;
        ss->size++; 
        return 1;
    }

    if(elem < ss->first->elem){
        new_node->next = ss->first;
        ss->first = new_node;
        ss->size++;
        return 1;
    } 
    else if(elem == ss->first->elem) {
        free(new_node);
        return 0;
    }

    ListNodePtr prev = ss->first;
    ListNodePtr curr = ss->first->next;

    while(curr != NULL && curr->elem <= elem){
        if(curr->elem == elem){
            free(new_node);
            return 0;
        }
        prev = curr;
        curr = curr->next;
    }

    if(curr == NULL) ss->last = new_node;

    new_node->next = curr;
    prev->next = new_node; 

    ss->size++;
    return 1;
}
// toglie un elemento all'insieme (restituisce 0 se l'elemento non era presente, 1 altrimenti)
_Bool sset_remove(const IntSortedSetADT ss, const int elem) {
    if(ss == NULL || ss -> size == 0){
        return 0;
    }   
    ListNodePtr prev = ss->first;
    ListNodePtr curr = ss->first->next;

    while(curr != NULL && curr->elem <= elem){
        if(curr -> elem == elem){
            //remove the elem from the linked list
            return 1;
        }

        prev = curr;
        curr = curr -> next;
    }
}
// controlla se un elemento appartiene all'insieme
_Bool sset_member(const IntSortedSetADT ss, const int elem) {
    if(ss == NULL || ss -> size == 0) return 0;

    ListNodePtr ls = malloc(sizeof(*ls));

    if(ls == NULL) return 0;

    ls = ss -> first;

    while(ls->next != NULL){
        if(ls->elem == elem) return 1;

        ls = ls->next;
    }

    free(ls);

    return 0;
}

_Bool isEmptySSet(const IntSortedSetADT ss) {
    if(ss == NULL) return 0;

    return ss -> size == 0;
}

int sset_size(const IntSortedSetADT ss) {
    if(ss == NULL) return -1; 

    return ss -> size;
}
// toglie e restituisce un elemento a caso dall'insieme, restituisce false se l'insieme è NULL oppure è vuoto
_Bool sset_extract(IntSortedSetADT ss, int *ptr) {
    if(ss == NULL || ss -> size == 0) return 0;    
    

    
}
// controlla se due insiemi sono uguali
_Bool sset_equals(const IntSortedSetADT s1, const IntSortedSetADT s2) {
    ListNodePtr ls1 = s1 -> first;
    ListNodePtr ls2 = s2 -> first;

    while(ls1 -> next != NULL || ls2 -> next != NULL){
        if(ls1 -> next == NULL || ls2 -> next == NULL){
            return 0;
        }
        if(ls1 -> elem != ls2 -> elem){
            return 0;
        }
        ls1 = ls1 -> next;
        ls2 = ls2 -> next;
    }   
    return 1;
}
// controlla se il primo insieme e' incluso nel secondo
_Bool sset_subseteq(const IntSortedSetADT s1, const IntSortedSetADT s2) {
    ListNodePtr ls1 = s1 -> first;
    ListNodePtr ls2 = s2 -> first;

    while(ls1 -> next != NULL || ls2 -> next != NULL){    
        if(ls2 -> next == NULL){
            return 0;
        }
        if(ls1 -> elem != ls2 -> elem){
            return 0;
        }
    }
    return 1;
}

_Bool sset_subset(const IntSortedSetADT s1, const IntSortedSetADT s2) {
    return false;
}

IntSortedSetADT sset_union(const IntSortedSetADT s1, const IntSortedSetADT s2) {
    return NULL; 
}

IntSortedSetADT sset_intersection(const IntSortedSetADT s1, const IntSortedSetADT s2) {
    return NULL;
}

IntSortedSetADT sset_subtraction(const IntSortedSetADT s1, const IntSortedSetADT s2) {
    return NULL;   
}

_Bool sset_min(const IntSortedSetADT ss, int *ptr) {
    return false;
}

_Bool sset_max(const IntSortedSetADT ss, int *ptr) {
    return false;
}

_Bool sset_extractMin(IntSortedSetADT ss, int *ptr) {
    return false;    
}

_Bool sset_extractMax(IntSortedSetADT ss, int *ptr) {
    return false;       
}

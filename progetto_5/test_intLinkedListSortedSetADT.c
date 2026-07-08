#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "intSortedSetADT.h"
#include "intLinkedListSortedSetADT.h"

IntSortedSetADT mkSSetv(int count, ...) {
    IntSortedSetADT set = mkSSet();

    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; ++i) {
        int num = va_arg(args, int);
        sset_add(set,num);
    }
    va_end(args);
    return set;
}

char *toString(IntSortedSetADT set) {
    if (!set) return NULL;
    char *sout = malloc(100*sizeof(char));

    ListNodePtr nptr = set->first;
    sprintf(sout, "{");
    while (nptr) {
        if (nptr == set->first)
            sprintf(sout+strlen(sout), "%d", nptr->elem);
        else
            sprintf(sout+strlen(sout), ",%d", nptr->elem);
        nptr = nptr->next;
    }

    sprintf(sout+strlen(sout), "}");

    return sout;
}

int check_mkSSet() {
    int passed = 1;
    IntSortedSetADT sptr = mkSSet();
    if (!sptr) {
        printf("FAILED - EXPECTED: not %d\n", 0);
        passed = 0;
    } else {
        printf("OK\n");
    }
    dsSSet(&sptr);
    return passed;
}

int check_dsSSet() {
    int passed = 1;
    _Bool rv;
    IntSortedSetADT sptr = mkSSet();
    
    rv = dsSSet(&sptr);
    if (!rv || sptr) {
        printf("FAILED dsSSet({})\n");
        passed=0;
    } 
    
    rv = dsSSet(NULL);
    if (rv) {
        printf("FAILED dsSSet(NULL)\n");
        passed=0;
    }
    
    if (passed) printf("OK\n");
    return passed;
}

int check_sset_add() {
    int passed=1;
    IntSortedSetADT s = mkSSet();
    
    if (sset_add(NULL, 10) != 0) { printf("FAILED on NULL\n"); passed = 0; }
    if (sset_add(s, 10) != 1) { printf("FAILED on add 10\n"); passed = 0; }
    if (sset_add(s, 10) != 0) { printf("FAILED on add dup 10\n"); passed = 0; }
    if (sset_add(s, 5) != 1) { printf("FAILED on add 5 (head)\n"); passed = 0; }
    if (sset_add(s, 20) != 1) { printf("FAILED on add 20 (tail)\n"); passed = 0; }
    
    if (passed) printf("OK\n");
    dsSSet(&s);
    return passed;
}

int check_sset_remove(){
    int passed=1;
    IntSortedSetADT s = mkSSetv(3, 10, 20, 30);
    
    if (sset_remove(NULL, 10) != 0) { printf("FAILED on NULL\n"); passed = 0; }
    if (sset_remove(s, 15) != 0) { printf("FAILED on missing elem\n"); passed = 0; }
    if (sset_remove(s, 20) != 1) { printf("FAILED on remove middle\n"); passed = 0; }
    if (sset_remove(s, 10) != 1) { printf("FAILED on remove head\n"); passed = 0; }
    if (sset_remove(s, 30) != 1) { printf("FAILED on remove tail\n"); passed = 0; }
    if (sset_remove(s, 30) != 0) { printf("FAILED on already removed\n"); passed = 0; }

    if (passed) printf("OK\n");
    dsSSet(&s);
    return passed;
}

int check_sset_member(){
    int passed=1;
    IntSortedSetADT s = mkSSetv(3, 10, 20, 30);
    
    if (sset_member(NULL, 10) != 0) { printf("FAILED on NULL\n"); passed = 0; }
    if (sset_member(s, 20) != 1) { printf("FAILED on existing elem\n"); passed = 0; }
    if (sset_member(s, 99) != 0) { printf("FAILED on missing elem\n"); passed = 0; }

    if (passed) printf("OK\n");
    dsSSet(&s);
    return passed;
}

int check_isEmptySSet(){
    int passed=1;
    IntSortedSetADT s1 = mkSSet();
    IntSortedSetADT s2 = mkSSetv(1, 10);
    
    if (isEmptySSet(NULL) != 0) { printf("FAILED on NULL\n"); passed = 0; }
    if (isEmptySSet(s1) != 1) { printf("FAILED on empty set\n"); passed = 0; }
    if (isEmptySSet(s2) != 0) { printf("FAILED on non-empty set\n"); passed = 0; }

    if (passed) printf("OK\n");
    dsSSet(&s1); dsSSet(&s2);
    return passed;
}

int check_sset_size(){
    int passed=1;
    IntSortedSetADT s1 = mkSSet();
    IntSortedSetADT s2 = mkSSetv(3, 10, 20, 30);
    
    if (sset_size(NULL) != -1) { printf("FAILED on NULL\n"); passed = 0; }
    if (sset_size(s1) != 0) { printf("FAILED on empty set\n"); passed = 0; }
    if (sset_size(s2) != 3) { printf("FAILED on non-empty set\n"); passed = 0; }

    if (passed) printf("OK\n");
    dsSSet(&s1); dsSSet(&s2);
    return passed;
}

int check_sset_extract(){
    int passed=1;
    IntSortedSetADT s = mkSSetv(2, 10, 20);
    int extracted;
    
    if (sset_extract(NULL, &extracted) != 0) { printf("FAILED on NULL\n"); passed = 0; }
    if (sset_extract(s, &extracted) != 1) { printf("FAILED on non-empty\n"); passed = 0; }
    if (sset_size(s) != 1) { printf("FAILED size did not decrease\n"); passed = 0; }
    
    sset_extract(s, &extracted); // svuota l'insieme
    if (sset_extract(s, &extracted) != 0) { printf("FAILED on empty\n"); passed = 0; }

    if (passed) printf("OK\n");
    dsSSet(&s);
    return passed;
}

int check_sset_equals(){
    int passed=1;
    IntSortedSetADT s1 = mkSSetv(3, 1, 2, 3);
    IntSortedSetADT s2 = mkSSetv(3, 1, 2, 3);
    IntSortedSetADT s3 = mkSSetv(2, 1, 2);
    
    if (sset_equals(NULL, s1) != 0 || sset_equals(s1, NULL) != 0) { printf("FAILED on NULL\n"); passed = 0; }
    if (sset_equals(s1, s2) != 1) { printf("FAILED on equal sets\n"); passed = 0; }
    if (sset_equals(s1, s3) != 0) { printf("FAILED on different sets\n"); passed = 0; }

    if (passed) printf("OK\n");
    dsSSet(&s1); dsSSet(&s2); dsSSet(&s3);
    return passed;
}

int check_sset_subseteq(){
    int passed=1;
    IntSortedSetADT s1 = mkSSetv(2, 1, 2);
    IntSortedSetADT s2 = mkSSetv(3, 1, 2, 3);
    IntSortedSetADT s3 = mkSSetv(2, 4, 5);
    
    if (sset_subseteq(NULL, s2) != 0) { printf("FAILED on NULL\n"); passed = 0; }
    if (sset_subseteq(s1, s2) != 1) { printf("FAILED on valid subset\n"); passed = 0; }
    if (sset_subseteq(s1, s1) != 1) { printf("FAILED on identical set\n"); passed = 0; }
    if (sset_subseteq(s3, s2) != 0) { printf("FAILED on not subset\n"); passed = 0; }

    if (passed) printf("OK\n");
    dsSSet(&s1); dsSSet(&s2); dsSSet(&s3);
    return passed;
}

int check_sset_subset() {
    int passed=1;
    IntSortedSetADT s1 = mkSSetv(2, 1, 2);
    IntSortedSetADT s2 = mkSSetv(3, 1, 2, 3);
    
    if (sset_subset(NULL, s2) != 0) { printf("FAILED on NULL\n"); passed = 0; }
    if (sset_subset(s1, s2) != 1) { printf("FAILED on strict subset\n"); passed = 0; }
    if (sset_subset(s1, s1) != 0) { printf("FAILED on identical set (should be false)\n"); passed = 0; }

    if (passed) printf("OK\n");
    dsSSet(&s1); dsSSet(&s2);
    return passed;
}

int check_sset_union() {
    int passed=1;
    IntSortedSetADT s1 = mkSSetv(2, 1, 2);
    IntSortedSetADT s2 = mkSSetv(2, 2, 3);
    IntSortedSetADT res = sset_union(s1, s2);
    
    if (sset_union(NULL, s2) != NULL) { printf("FAILED on NULL\n"); passed = 0; }
    if (res == NULL || sset_size(res) != 3 || !sset_member(res, 3)) { printf("FAILED on valid union\n"); passed = 0; }

    if (passed) printf("OK\n");
    dsSSet(&s1); dsSSet(&s2); dsSSet(&res);
    return passed;
}

int check_sset_intersection() {
    int passed=1;
    IntSortedSetADT s1 = mkSSetv(2, 1, 2);
    IntSortedSetADT s2 = mkSSetv(2, 2, 3);
    IntSortedSetADT res = sset_intersection(s1, s2);
    
    if (sset_intersection(NULL, s2) != NULL) { printf("FAILED on NULL\n"); passed = 0; }
    if (res == NULL || sset_size(res) != 1 || !sset_member(res, 2)) { printf("FAILED on valid intersection\n"); passed = 0; }

    if (passed) printf("OK\n");
    dsSSet(&s1); dsSSet(&s2); dsSSet(&res);
    return passed;
}

int check_sset_subtraction() {
    int passed=1;
    IntSortedSetADT s1 = mkSSetv(3, 1, 2, 3);
    IntSortedSetADT s2 = mkSSetv(2, 2, 4);
    IntSortedSetADT res = sset_subtraction(s1, s2);
    
    if (sset_subtraction(NULL, s2) != NULL) { printf("FAILED on NULL\n"); passed = 0; }
    if (res == NULL || sset_size(res) != 2 || sset_member(res, 2)) { printf("FAILED on valid subtraction\n"); passed = 0; }

    if (passed) printf("OK\n");
    dsSSet(&s1); dsSSet(&s2); dsSSet(&res);
    return passed;
}

int check_sset_min(){
    int passed=1;
    IntSortedSetADT s1 = mkSSet();
    IntSortedSetADT s2 = mkSSetv(3, 5, 10, 15);
    int val;
    
    if (sset_min(NULL, &val) != 0) { printf("FAILED on NULL\n"); passed = 0; }
    if (sset_min(s1, &val) != 0) { printf("FAILED on empty\n"); passed = 0; }
    if (sset_min(s2, &val) != 1 || val != 5) { printf("FAILED on non-empty\n"); passed = 0; }

    if (passed) printf("OK\n");
    dsSSet(&s1); dsSSet(&s2);
    return passed;
}

int check_sset_max(){
    int passed=1;
    IntSortedSetADT s1 = mkSSet();
    IntSortedSetADT s2 = mkSSetv(3, 5, 10, 15);
    int val;
    
    if (sset_max(NULL, &val) != 0) { printf("FAILED on NULL\n"); passed = 0; }
    if (sset_max(s1, &val) != 0) { printf("FAILED on empty\n"); passed = 0; }
    if (sset_max(s2, &val) != 1 || val != 15) { printf("FAILED on non-empty\n"); passed = 0; }

    if (passed) printf("OK\n");
    dsSSet(&s1); dsSSet(&s2);
    return passed;
}

int check_sset_extractMin(){
    int passed=1;
    IntSortedSetADT s = mkSSetv(3, 5, 10, 15);
    int val;
    
    if (sset_extractMin(NULL, &val) != 0) { printf("FAILED on NULL\n"); passed = 0; }
    if (sset_extractMin(s, &val) != 1 || val != 5 || sset_size(s) != 2) { printf("FAILED on non-empty\n"); passed = 0; }

    if (passed) printf("OK\n");
    dsSSet(&s);
    return passed;
}

int check_sset_extractMax(){
    int passed=1;
    IntSortedSetADT s = mkSSetv(3, 5, 10, 15);
    int val;
    
    if (sset_extractMax(NULL, &val) != 0) { printf("FAILED on NULL\n"); passed = 0; }
    if (sset_extractMax(s, &val) != 1 || val != 15 || sset_size(s) != 2) { printf("FAILED on non-empty\n"); passed = 0; }

    if (passed) printf("OK\n");
    dsSSet(&s);
    return passed;
}

int main(int argc, char *argv[]) {
  puts("BEGIN TEST intLinkedListSortedSetADT");

  printf("\nTEST mkSSet\n"); check_mkSSet();
  printf("\nTEST dsSSet\n"); check_dsSSet();
  printf("\nTEST sset_add\n"); check_sset_add();
  printf("\nTEST sset_remove\n"); check_sset_remove();
  printf("\nTEST sset_member\n"); check_sset_member();
  printf("\nTEST isEmptySSet\n"); check_isEmptySSet();
  printf("\nTEST sset_size\n"); check_sset_size();
  printf("\nTEST sset_extract\n"); check_sset_extract();
  printf("\nTEST sset_equals\n"); check_sset_equals();
  printf("\nTEST sset_subseteq\n"); check_sset_subseteq();
  printf("\nTEST sset_subset\n"); check_sset_subset();
  printf("\nTEST sset_union\n"); check_sset_union();
  printf("\nTEST sset_intersection\n"); check_sset_intersection();
  printf("\nTEST sset_subtraction\n"); check_sset_subtraction();
  printf("\nTEST sset_min\n"); check_sset_min();
  printf("\nTEST sset_max\n"); check_sset_max();
  printf("\nTEST sset_extractMin\n"); check_sset_extractMin();
  printf("\nTEST sset_extractMax\n"); check_sset_extractMax();
  
  puts("\nEND OF TESTS");
  return 0;
}

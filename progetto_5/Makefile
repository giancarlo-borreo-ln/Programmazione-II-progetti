all: test_set

test_set: test_intLinkedListSortedSetADT.o intLinkedListSortedSetADT.o
	gcc -o test_set test_intLinkedListSortedSetADT.o intLinkedListSortedSetADT.o

test_intLinkedListSortedSetADT.o: test_intLinkedListSortedSetADT.c intSortedSetADT.h intLinkedListSortedSetADT.h
	gcc -c test_intLinkedListSortedSetADT.c

intLinkedListSortedSetADT.o: intLinkedListSortedSetADT.c intSortedSetADT.h intLinkedListSortedSetADT.h
	gcc -c intLinkedListSortedSetADT.c

clean:
	rm -f *.o test_set

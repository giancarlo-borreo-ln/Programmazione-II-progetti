#include <stdbool.h>
#include <stddef.h>
#include "unity.h"
#include "charArrayQueue.h"
#include "charQueueADT.h"

/**
 * @file test_charQueue.c
 * @brief Test suite per l'ADT CharQueue.
 * @note La test suite è strutturata come black-box testing puro: 
 * non assume dettagli implementativi interni come struct, soglie di espansione/riduzione
 * o il comportamento dei puntatori dopo la free.
 */

static CharQueueADT q;

/**
 * @brief Inizializza l'ambiente di test creando una nuova coda vuota.
 */
void setUp(void) {
    q = mkQueue();
}

/**
 * @brief Pulisce l'ambiente di test distruggendo la coda.
 */
void tearDown(void) {
    if (q != NULL) {
        dsQueue(&q);
    }
}

/**
 * @brief Verifica la corretta inizializzazione di una coda vuota.
 */
void test_mkQueue(void) {
    TEST_ASSERT_NOT_NULL(q);
    TEST_ASSERT_EQUAL_INT(0, size(q));
    TEST_ASSERT_TRUE(isEmpty(q));
}

/**
 * @brief Verifica l'inserimento di un singolo elemento in fondo alla coda.
 */
void test_enqueue_one_element(void) {
    TEST_ASSERT_EQUAL_INT(1, enqueue(q, 'A'));
    TEST_ASSERT_EQUAL_INT(1, size(q));
    TEST_ASSERT_FALSE(isEmpty(q));
}

/**
 * @brief Verifica l'inserimento di più elementi base.
 */
void test_enqueue_multiple_elements(void) {
    for (size_t i = 0; i < 8; ++i) {
        TEST_ASSERT_EQUAL_INT(1, enqueue(q, ('A' + i)));
    }
    
    for (size_t j = 0; j < 8; ++j) {
        char c = '\0';
        TEST_ASSERT_EQUAL_INT(1, peek(q, j, &c));
        TEST_ASSERT_EQUAL_CHAR(('A' + j), c);
    }

    TEST_ASSERT_EQUAL_INT(8, size(q));
    TEST_ASSERT_FALSE(isEmpty(q));
}

/**
 * @brief Verifica l'inserimento di un gran numero di elementi per testare indirettamente l'espansione.
 */
void test_enqueue_growth(void) {
    for (size_t i = 0; i < 32; ++i) {
        TEST_ASSERT_EQUAL_INT(1, enqueue(q, ('A' + i)));
    }

    for (size_t j = 0; j < 32; ++j) {
        char c = '\0';
        TEST_ASSERT_EQUAL_INT(1, peek(q, j, &c));
        TEST_ASSERT_EQUAL_CHAR(('A' + j), c);
    }
    
    TEST_ASSERT_EQUAL_INT(32, size(q));
    TEST_ASSERT_FALSE(isEmpty(q));
}

/**
 * @brief Verifica la rimozione e restituzione dell'elemento in testa alla coda.
 */
void test_dequeue(void) {
    for (size_t i = 0; i < 10; ++i) {
        TEST_ASSERT_EQUAL_INT(1, enqueue(q, ('A' + i)));
    }

    char c = '\0';
    TEST_ASSERT_EQUAL_INT(1, dequeue(q, &c));

    TEST_ASSERT_EQUAL_CHAR('A', c);

    char front = '\0';
    TEST_ASSERT_EQUAL_INT(1, peek(q, 0, &front));
    TEST_ASSERT_EQUAL_CHAR('B', front);

    TEST_ASSERT_EQUAL_INT(9, size(q));
}

/**
 * @brief Verifica il corretto funzionamento del controllo di coda vuota.
 */
void test_isEmpty(void) {
    TEST_ASSERT_TRUE(isEmpty(q));

    TEST_ASSERT_EQUAL_INT(1, enqueue(q, 'A'));
    TEST_ASSERT_FALSE(isEmpty(q));

    char c = '\0';
    TEST_ASSERT_EQUAL_INT(1, dequeue(q, &c));

    TEST_ASSERT_TRUE(isEmpty(q));
}

/**
 * @brief Verifica il conteggio degli elementi presenti nella coda.
 */
void test_size(void) {
    TEST_ASSERT_EQUAL_INT(0, size(q));

    
    for (size_t i = 0; i < 10; ++i) {
        TEST_ASSERT_EQUAL_INT(1, enqueue(q, ('A' + i)));
    }

    TEST_ASSERT_EQUAL_INT(10, size(q));

    char c = '\0';
    TEST_ASSERT_EQUAL_INT(1, dequeue(q, &c));
    TEST_ASSERT_EQUAL_INT(1, dequeue(q, &c));

    TEST_ASSERT_EQUAL_INT(8, size(q));
}

/**
 * @brief Verifica la lettura di un elemento in una posizione specifica senza rimuoverlo.
 */
void test_peek(void) {
    TEST_ASSERT_EQUAL_INT(1, enqueue(q, 'A'));
    TEST_ASSERT_EQUAL_INT(1, enqueue(q, 'B'));
    TEST_ASSERT_EQUAL_INT(1, enqueue(q, 'C'));
    TEST_ASSERT_EQUAL_INT(1, enqueue(q, 'D'));
    TEST_ASSERT_EQUAL_INT(1, enqueue(q, 'E'));

    char c = '\0';
    
    TEST_ASSERT_EQUAL_INT(1, peek(q, 0, &c));
    TEST_ASSERT_EQUAL_CHAR('A', c);

    TEST_ASSERT_EQUAL_INT(1, peek(q, 2, &c));
    TEST_ASSERT_EQUAL_CHAR('C', c);

    TEST_ASSERT_EQUAL_INT(1, peek(q, 4, &c));
    TEST_ASSERT_EQUAL_CHAR('E', c);

    TEST_ASSERT_EQUAL_INT(5, size(q));

    char first_elem = '\0';
    TEST_ASSERT_EQUAL_INT(1, peek(q, 0, &first_elem));
    TEST_ASSERT_EQUAL_CHAR('A', first_elem);
}

/**
 * @brief Verifica il fallimento della funzione peek in caso di indici non validi 
 * e che la variabile non venga alterata.
 */
void test_peek_invalid(void) {
    TEST_ASSERT_EQUAL_INT(1, enqueue(q, 'X'));
    TEST_ASSERT_EQUAL_INT(1, enqueue(q, 'Y'));

    char c = 'Z';

    TEST_ASSERT_EQUAL_INT(0, peek(q, -1, &c));
    TEST_ASSERT_EQUAL_CHAR('Z', c);

    TEST_ASSERT_EQUAL_INT(0, peek(q, 2, &c));
    TEST_ASSERT_EQUAL_CHAR('Z', c);

    TEST_ASSERT_EQUAL_INT(0, peek(q, 5, &c));
    TEST_ASSERT_EQUAL_CHAR('Z', c);

    TEST_ASSERT_EQUAL_INT(2, size(q));
    
    char check_elem = '\0';
    TEST_ASSERT_EQUAL_INT(1, peek(q, 0, &check_elem));
    TEST_ASSERT_EQUAL_CHAR('X', check_elem);
    TEST_ASSERT_EQUAL_INT(1, peek(q, 1, &check_elem));
    TEST_ASSERT_EQUAL_CHAR('Y', check_elem);
}

/**
 * @brief Verifica il fallimento della funzione dequeue su una coda vuota
 * e che la variabile di destinazione non venga alterata.
 */
void test_dequeue_empty(void) {
    char c = 'X';
    
    TEST_ASSERT_EQUAL_INT(0, dequeue(q, &c));
    TEST_ASSERT_EQUAL_CHAR('X', c);
    
    TEST_ASSERT_EQUAL_INT(0, size(q));
    TEST_ASSERT_TRUE(isEmpty(q));
}

/**
 * @brief Verifica la resilienza della coda scalando massicciamente verso il basso,
 * garantendo che gli elementi rimasti siano intatti, a prescindere dalle soglie di shrink.
 */
void test_dequeue_shrink_resilience(void) {
    const size_t max_elements = 32;
    
    for (size_t i = 0; i < max_elements; ++i) {
        TEST_ASSERT_EQUAL_INT(1, enqueue(q, ('A' + i)));
    }

    char c = '\0';
    for (size_t i = 0; i < max_elements - 2; ++i) {
        TEST_ASSERT_EQUAL_INT(1, dequeue(q, &c));
    }

    TEST_ASSERT_EQUAL_INT(2, size(q));

    TEST_ASSERT_EQUAL_INT(1, peek(q, 0, &c));
    TEST_ASSERT_EQUAL_CHAR(('A' + max_elements - 2), c);
    
    TEST_ASSERT_EQUAL_INT(1, peek(q, 1, &c));
    TEST_ASSERT_EQUAL_CHAR(('A' + max_elements - 1), c);
}

/**
 * @brief Verifica la corretta gestione degli indici quando la coda avvolge l'array (wrap-around).
 * @details Con una capacità iniziale tipica (es. 8), inserendo ed estraendo sequenzialmente
 * testiamo che l'indice `rear` e `front` possano riavvolgersi correttamente all'inizio
 * dell'array mantenendo l'ordine FIFO senza errori.
 */
void test_queue_circularity(void) {
    for (size_t i = 0; i < 6; ++i) {
        TEST_ASSERT_EQUAL_INT(1, enqueue(q, ('A' + i)));
    }
    
    char c = '\0';
    for (size_t i = 0; i < 6; ++i) {
        TEST_ASSERT_EQUAL_INT(1, dequeue(q, &c));
    }
    
    for (size_t i = 0; i < 6; ++i) {
        TEST_ASSERT_EQUAL_INT(1, enqueue(q, ('a' + i)));
    }

    TEST_ASSERT_EQUAL_INT(6, size(q));

    for (size_t i = 0; i < 6; ++i) {
        TEST_ASSERT_EQUAL_INT(1, peek(q, i, &c));
        TEST_ASSERT_EQUAL_CHAR(('a' + i), c);
    }
}
int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_mkQueue);
    RUN_TEST(test_enqueue_one_element);
    RUN_TEST(test_enqueue_multiple_elements);
    RUN_TEST(test_enqueue_growth);
    RUN_TEST(test_dequeue);
    RUN_TEST(test_isEmpty);
    RUN_TEST(test_size);
    RUN_TEST(test_peek);
    RUN_TEST(test_peek_invalid);
    RUN_TEST(test_dequeue_empty);
    RUN_TEST(test_dequeue_shrink_resilience);
    RUN_TEST(test_queue_circularity);

    return UNITY_END();
}

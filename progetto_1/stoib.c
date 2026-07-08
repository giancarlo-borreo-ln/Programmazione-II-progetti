/* INSERIRE QUI EVENTUALI ALTRI #include <...> */
/* INSERT HERE MORE #include <...> IF NEEDED */
#include<stdio.h>
/* INSERIRE QUI EVENTUALI FUNZIONI AUSILIARIE */
/* INSERT HERE AUXILIARY FUNCTIONS IF NEEDED */
/**
 * Dato un carattere lo trasforma in un valore numerico intero
 * @param num: valore in ingresso che è un carattere
 */

int char_to_digit(char num, unsigned short b) {
    int val = -1;
    if (num >= '0' && num <= '9') { val = num - '0'; } 
    else if (num >= 'A' && num <= 'Z') { val = num - 'A' + 10; }
    if (val < 0 || val >= b) { return -1; }
    return val;
}
/**
 * @brief Converte una stringa in intero (data la base).
 *
 * Calcola il numero intero rappresentato dalla stringa `s` nella base `b` (tra 2 e 36):
 * − saltando gli eventuali spazi bianchi iniziali;
 * − riconoscendo l'eventuale (singolo) carattere del segno (+ o -);
 * − fermandosi al raggiungimento del primo carattere non cifra nella base data
 *   (le cifre per la base 36 sono 0,..,9,A,..,Z, invece a-z non sono cifre valide);
 * - deve essere presente almeno una cifra nella base data.
 *
 * Restituisce:
 * - 0 se uno degli argomenti non è valido, e in tal caso il valore in salvato in `r` non è significativo;
 * - altrimenti, il numero di caratteri letti dalla stringa (inclusi spazi e segni), salvando in `r` il risultato.
 * 
 * Notare che la conversione della stringa c_n ... c_2 c_1 c_0 in base b è il numero:
 * c_n * b^n + ... * c_2 * b^2 + c_1 * b + c_0.
 *
 * La funzione non si accorge di eventuali overflow numerici (restituendo in questo caso un risultato scorretto).
 *
 * @param s una stringa da convertire.
 * @param b la base (tra 2 e 36).
 * @param r l'indirizzo dell'intero dove memorizzare il risultato.
 * @return  il numero di caratteri letti dalla stringa
 *
 * NOTA: questa funzione compare negli errori di compilazione come "student_stoib"
 * NOTA: questa funzione viene testata indipendentemente dal vostro main
 * IMPORTANTE: cercate sempre di far compilare il vostro codice per poter vedere il
 * risultato dei test, anche a costo di commentare parte del codice di questa funzione
 *
 * <ENGLISH VERSION>
 *
 * @brief Converts a string to an integer (given the base).
 *
 * Computes the integer represented by the string `s` in base `b` (between 2 and 36):
 * - skipping any leading whitespace;
 * - recognizing an optional (single) sign character (+ or -);
 * - stopping at the first character that is not a valid digit in the given base
 *   (the digits for base 36 are 0,..,9,A,..,Z, while a-z are not valid digits);
 * - at least one digit in the given base must be present.
 *
 * Returns:
 * - 0 if one of the arguments is invalid, and in that case the value stored in `r` is not meaningful;
 * - otherwise, the number of characters read from the string (including whitespace and signs), storing the result in `r`.
 * 
 * Note that the conversion of string c_n ... c_2 c_1 c_0 in base b is the number:
 * c_n * b^n + ... * c_2 * b^2 + c_1 * b + c_0.
 *
 * The function does not detect possible numeric overflows (returning an incorrect result in that case).
 *
 * @param s a string to convert.
 * @param b the base (between 2 and 36).
 * @param r the address of the integer where the result is stored.
 * @return  the number of characters read from the string
 *
 * NOTE: this function appears in compilation errors as "student_stoib"
 * NOTE: this function is tested independently of your main
 * IMPORTANT: always try to make your code compile so that you can see the test
 * results, even if that means commenting out part of the code of this function
 */


int stoib(char *s, unsigned short b, int *r) {
    if (s == NULL || r == NULL){ return 0; }
    if (b < 2 || b > 36){ return 0; }

    int count = 0;
    int segno = 1;

    while (*s == ' ' || *s == '\t' || *s == '\n' || *s == '\r' || *s == '\f' || *s == '\v') {
        s++;
        count++;
    }

    if (*s == '-') { 
        segno = -1;
        s++;
        count++; }
    else if (*s == '+') { 
        s++; 
        count++; 
    }

    int res = 0, numCount = 0, digit;
    while (*s != '\0') {
        if ((digit = char_to_digit(*s, b)) == -1) { break; }
        res = res * b + digit;
        s++;
        count++;
        numCount++;
    }

    if (numCount == 0){ return 0; }

    *r = res * segno;
    return count;
}


/**
 * Invoca la funzione stoib su uno o più casi a scelta, controllando che
 * il suo effetto come risultato e argomenti rispetti la specifica corretta.
 * Può essere sufficiente anche un unico caso, se sufficientemente generale per
 * individuare quali programmi sono corretti e quali no.
 * Se la funzione è corretta, come ultima cosa deve stampare "TEST PASSED\n".
 * Se invece la funzione non risulta corretta, deve stampare "TEST FAILED\n".
 * NON STAMPARE ALTRO SU STANDARD OUTPUT.
 * Se avete necessità di fare stampe di debug, potete farle su standard error.
 *
 * NOTA: dovete invocare "stoib" e NON "student_stoib"
 * NOTA: questa funzione compare negli errori di compilazione come "student_main"
 * NOTA: il main viene testato indipendentemente dalla vostra funzione stoib
 * IMPORTANTE: cercate sempre di far compilare il vostro codice per poter vedere il
 * risultato dei test, anche a costo di commentare parte del codice di questa funzione
 *
 * <ENGLISH VERSION>
 *
 * Invokes the stoib function on one or more selected test cases, checking
 * that its effect as result and arguments respects the correct specification.
 * A single test case may be enough, if it sufficiently general to single out
 * which programs are correct and which are not.
 * If the function is correct, as the final step it must print "TEST PASSED\n".
 * If instead the function is not correct, it must print "TEST FAILED\n".
 * DO NOT PRINT ANYTHING ELSE ON STANDARD OUTPUT.
 * If you need to print debug information, use standard error.
 *
 * NOTE: you have to invoke "stoib" and NOT "student_stoib"
 * NOTE: this function appears in compilation errors as "student_main"
 * NOTE: the main is tested independently of your stoib function
 * IMPORTANT: always try to make your code compile so that you can see the test
 * results, even if that means commenting out part of the code of this function
 */


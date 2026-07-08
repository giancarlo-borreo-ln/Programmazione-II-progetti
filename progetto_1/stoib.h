#define STOIB_H

/**
 * Dato un carattere lo converte in un valore numerico intero
 * @param num: valore in ingresso che è un carattere
 */
int char_to_digit(char num);


/**
 * Converte una stringa `s` in un numero intero nella base `b`.
 * 
 * @param s: puntatore alla stringa da convertire
 * @param b: base numerica (2..36)
 * @param r: puntatore a un intero che contiene il valore restituito 
 * @return: valore intero convertito
 */
int stoib(const char *s, unsigned short b, int *r);
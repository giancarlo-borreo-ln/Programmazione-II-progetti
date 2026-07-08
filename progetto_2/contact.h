#ifndef __INCLUDE_CONTACT_H
#define __INCLUDE_CONTACT_H

/**  Un tipo di dato per i contatti telefonici e cyberspaziali
*/
typedef struct contact {
   char* name;   
   char* surname;
   char* mobile;
   char* url;
} Contact, *ContactPtr;

#include "contact.h"
/**  @brief Controlla se due stringhe sono uguali
  @param str1 la prima stringa
  @param str2 la seconda stringa
  @return false se le stringhe sono diverse true altrimenti.
*/
bool strIsEqu(char* str1, char* str2);


/** @brief Determina quale tra due stringhe è lessicograficamente maggiore.
  La funzione confronta due stringhe carattere per carattere basandosi
  sull'ordine della tabella ASCII. Se una stringa è il prefisso dell'altra,
  la stringa più lunga viene considerata maggiore.
  @param str1 Puntatore alla prima stringa (array di caratteri terminato da '\0').
  @param str2 Puntatore alla seconda stringa (array di caratteri terminato da '\0').
  @return Un puntatore alla stringa maggiore (str1 o str2).
  Restituisce NULL se le due stringhe sono esattamente identiche.
 */
char* strGreaterThan(char* str1, char* str2);

/**  @brief Controlla se due contatti hanno lo stesso nome e cognome
      @param c1 il primo  contatto 
      @param c2 il secondo contatto
      @return 1 se i due contatti sono uguali, 0 se sono diversi, -99 se qualche name o surname è NULL
*/
int contactEq(Contact c1, Contact c2);


/**  @brief Controlla se due contatti hanno lo stesso nome e cognome 
      @param pc1 il puntatore al primo contatto (assumete non NULL)
      @param pc2 il puntatore al secondo contatto (assumete non NULL)
      @return 1 se i due contatti sono uguali, 0 se sono diversi, -99 se qualche name o surname è NULL
*/
int contactEqEff(const Contact * const pc1, const Contact * const pc2);


/**  @brief Confronta due contatti per cognome rispetto all'ordine lessicografico e, se il cognome e' lo stesso, per nome
      @param c1 il primo  contatto 
      @param c2 il secondo contatto
      @return -1 se c1 minore di c2, 0 se c1 uguale a c2, 1 se c1 maggiore di c2, -99 se qualche name o surname è NULL
*/
int contactCmp(Contact c1, Contact c2);


/**  @brief Confronta due contatti per cognome rispetto all'ordine lessicografico e, se il cognome e' lo stesso, per nome
      @param pc1 il puntatore al primo  contatto (assumete non NULL)
      @param pc2 il puntatore al secondo  contatto (assumete non NULL)
      @return -1 se *pc1 minore di *pc2, 0 se *pc1 uguale a *pc2, 1 se *pc1 maggiore di *pc2, -99 se qualche name o surname è NULL
*/
int contactCmpEff(const Contact * const pc1, const Contact * const pc2);

#endif

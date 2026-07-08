#include <stdbool.h>
#include "unity.h"
#include "contact.h"
void setUp(void){}
void tearDown(void){}

/**
typedef struct contact {
   char* name;
   char* surname;
   char* mobile;
   char* url;
} Contact, *ContactPtr;
*/


// int contactEq(Contact c1, Contact c2);
void test_nome_null(void){
    Contact c1 = {NULL, "D", "+313454035779", "shortest-path.nl"};
    Contact c2 = {NULL, "C", "+1(185)3023162","sony.com"};
    TEST_ASSERT_EQUAL_INT(-99, contactEq(c1, c2)); 
}


void test_last_name_null(void){
    Contact c1 = {"E", NULL, "+313454035779", "shortest-path.nl"};
    Contact c2 = {"D", NULL, "+1(185)3023162","sony.com"};
    TEST_ASSERT_EQUAL_INT(-99, contactEq(c1, c2));
}


void test_name_or_last_name_null(void){
    Contact c1 = {"E", NULL, "+313454035779", "shortest-path.nl"};
    Contact c2 = {NULL, "C", "+1(185)3023162","sony.com"};
    TEST_ASSERT_EQUAL_INT(-99, contactEq(c1, c2));
}


void test_partial_inequality(void){
    Contact c1 = {"E", "D", "+313454035779", "shortest-path.nl"};
    Contact c2 = {"D", "E", "+313454035779", "shortest-path.nl"};
    TEST_ASSERT_EQUAL_INT(0, contactEq(c1, c2));    
}

void test_different_contacts(void){
    Contact c1 = {"E", "D", "+313454035779", "shortest-path.nl"};
    Contact c2 = {"D", "C", "+1(185)3023162","sony.com"};
    TEST_ASSERT_EQUAL_INT(0, contactEq(c1, c2));
}

void test_same_name_dif_surname(void){
    Contact c1 = {"E", "D", "+313454035779", "shortest-path.nl"};
    Contact c2 = {"E", "E", "+313454035779", "shortest-path.nl"};
    TEST_ASSERT_EQUAL_INT(0, contactEq(c1,c2)); 
}

void test_same_contacts(void){
    Contact c1 = {"E", "D", "+313454035779", "shortest-path.nl"};
    Contact c2 = {"E", "D", "+313454035779", "shortest-path.nl"};
    TEST_ASSERT_EQUAL_INT(1, contactEq(c1,c2));
}


//int contactEqEff(const Contact * const pc1, const Contact * const pc2);
void test_eff_nome_null(void) {
    Contact c1 = {NULL, "D", "+313454035779", "shortest-path.nl"};
    Contact c2 = {NULL, "C", "+1(185)3023162","sony.com"};
    TEST_ASSERT_EQUAL_INT(-99, contactEqEff(&c1, &c2));
}

void test_eff_last_name_null(void) {
    Contact c1 = {"E", NULL, "+313454035779", "shortest-path.nl"};
    Contact c2 = {"D", NULL, "+1(185)3023162","sony.com"};
    TEST_ASSERT_EQUAL_INT(-99, contactEqEff(&c1, &c2));
}

void test_eff_name_or_last_name_null(void) {
    Contact c1 = {"E", NULL, "+313454035779", "shortest-path.nl"};
    Contact c2 = {NULL, "C", "+1(185)3023162","sony.com"};
    TEST_ASSERT_EQUAL_INT(-99, contactEqEff(&c1, &c2));
}

void test_eff_partial_inequality(void) {
    Contact c1 = {"E", "D", "+313454035779", "shortest-path.nl"};
    Contact c2 = {"D", "E", "+313454035779", "shortest-path.nl"};
    TEST_ASSERT_EQUAL_INT(0, contactEqEff(&c1, &c2));
}

void test_eff_different_contacts(void) {
    Contact c1 = {"E", "D", "+313454035779", "shortest-path.nl"};
    Contact c2 = {"D", "C", "+1(185)3023162","sony.com"};
    TEST_ASSERT_EQUAL_INT(0, contactEqEff(&c1, &c2));
}

void test_eff_same_surname_dif_name(void){
    Contact c1 = {"D", "E", "+313454035779", "shortest-path.nl"};
    Contact c2 = {"J", "E", "+313454035779", "shortest-path.nl"};
    TEST_ASSERT_EQUAL_INT(0, contactEq(c1,c2)); 
}

void test_eff_same_contacts(void) {
    Contact c1 = {"E", "D", "+313454035779", "shortest-path.nl"};
    Contact c2 = {"E", "D", "+313454035779", "shortest-path.nl"};
    TEST_ASSERT_EQUAL_INT(1, contactEqEff(&c1, &c2));
}



/**  @brief Confronta due contatti per cognome rispetto all'ordine lessicografico e, se il cognome e' lo stesso, per nome
      @param c1 il primo  contatto
      @param c2 il secondo contatto
      @return -1 se c1 minore di c2, 0 se c1 uguale a c2, 1 se c1 maggiore di c2, -99 se qualche name o surname è NULL
*/

void test_nome_null_cmp(void){
    Contact c1 = {NULL, "D", "+313454035779", "shortest-path.nl"};
    Contact c2 = {NULL, "C", "+1(185)3023162","sony.com"};
    TEST_ASSERT_EQUAL_INT(-99, contactCmp(c1, c2)); 
}

void test_last_name_null_cmp(void){
    Contact c1 = {"E", NULL, "+313454035779", "shortest-path.nl"};
    Contact c2 = {"D", NULL, "+1(185)3023162","sony.com"};
    TEST_ASSERT_EQUAL_INT(-99, contactCmp(c1, c2));
}

void test_c1_minore_di_c2_cognome_diverso(void) {
    Contact c1 = {"G", "H", "+1800123456", "g.h@navy.mil"};      
    Contact c2 = {"D", "R", "+1800987654", "d.r@bell-labs.com"}; 
    TEST_ASSERT_EQUAL_INT(-1, contactCmp(c1, c2));
}

void test_c1_maggiore_di_c2_cognome_diverso(void) {
    Contact c1 = {"A", "T", "+4412345678", "a.t@bletchley.uk"};   
    Contact c2 = {"A", "L", "+4498765432", "a.l@engine.uk"};     
    TEST_ASSERT_EQUAL_INT(1, contactCmp(c1, c2));
}

void test_c1_uguale_a_c2(void) {
    Contact c1 = {"L", "T", "+358111111", "l.t@linux.org"};       
    Contact c2 = {"L", "T", "+358222222", "l.t@kernel.org"};      
    TEST_ASSERT_EQUAL_INT(0, contactCmp(c1, c2));
}

void test_cognome_uguale_c1_minore_di_c2_per_nome(void) {
    Contact c1 = {"M", "H", "+1555333333", "m.h@nasa.gov"};       
    Contact c2 = {"R", "H", "+1555444444", "r.h@example.com"};    
    TEST_ASSERT_EQUAL_INT(-1, contactCmp(c1, c2));
}

void test_cognome_uguale_c1_maggiore_di_c2_per_nome(void) {
    Contact c1 = {"D", "K", "+1555444444", "d.k@stanford.edu"};   
    Contact c2 = {"A", "K", "+1555333333", "a.k@example.com"};    
    TEST_ASSERT_EQUAL_INT(1, contactCmp(c1, c2));
}

void test_eff_same_name_dif_surname(void){
    Contact c1 = {"E", "D", "+313454035779", "shortest-path.nl"};
    Contact c2 = {"E", "E", "+313454035779", "shortest-path.nl"};
    TEST_ASSERT_EQUAL_INT(0, contactEq(c1,c2)); 
}


/**  @brief Confronta due contatti per cognome rispetto all'ordine lessicografico e, se il cognome e' lo stesso, per nome
      @param pc1 il puntatore al primo  contatto (assumete non NULL)
      @param pc2 il puntatore al secondo  contatto (assumete non NULL)
      @return -1 se *pc1 minore di *pc2, 0 se *pc1 uguale a *pc2, 1 se *pc1 maggiore di *pc2, -99 se qualche name o surname è NULL
*/

void test_contactCmpEff_nome_null(void) {
    Contact c1 = {NULL, "H", "+1800123456", "g.h@navy.mil"};
    Contact c2 = {"D", "R", "+1800987654", "d.r@bell-labs.com"};
    TEST_ASSERT_EQUAL_INT(-99, contactCmpEff(&c1, &c2));
}

void test_contactCmpEff_cognome_null(void) {
    Contact c1 = {"G", "H", "+1800123456", "g.h@navy.mil"};
    Contact c2 = {"D", NULL, "+1800987654", "d.r@bell-labs.com"};
    TEST_ASSERT_EQUAL_INT(-99, contactCmpEff(&c1, &c2));
}

void test_contactCmpEff_c1_minore_di_c2_cognome_diverso(void) {
    Contact c1 = {"G", "H", "+1800123456", "g.h@navy.mil"};
    Contact c2 = {"D", "R", "+1800987654", "d.r@bell-labs.com"};
    TEST_ASSERT_EQUAL_INT(-1, contactCmpEff(&c1, &c2));
}

void test_contactCmpEff_c1_maggiore_di_c2_cognome_diverso(void) {
    Contact c1 = {"A", "T", "+4412345678", "a.t@bletchley.uk"};
    Contact c2 = {"A", "L", "+4498765432", "a.l@engine.uk"};
    TEST_ASSERT_EQUAL_INT(1, contactCmpEff(&c1, &c2));
}

void test_contactCmpEff_c1_uguale_a_c2(void) {
    Contact c1 = {"L", "T", "+358111111", "l.t@linux.org"};
    Contact c2 = {"L", "T", "+358222222", "l.t@kernel.org"};
    TEST_ASSERT_EQUAL_INT(0, contactCmpEff(&c1, &c2));
}

void test_contactCmpEff_cognome_uguale_c1_minore_di_c2_per_nome(void) {
    Contact c1 = {"M", "H", "+1555333333", "m.h@nasa.gov"};
    Contact c2 = {"R", "H", "+1555444444", "r.h@example.com"};
    TEST_ASSERT_EQUAL_INT(-1, contactCmpEff(&c1, &c2));
}

void test_contactCmpEff_cognome_uguale_c1_maggiore_di_c2_per_nome(void) {
    Contact c1 = {"D", "K", "+1555444444", "d.k@stanford.edu"};
    Contact c2 = {"A", "K", "+1555333333", "a.k@example.com"};
    TEST_ASSERT_EQUAL_INT(1, contactCmpEff(&c1, &c2));
}


int main(void) {
    UNITY_BEGIN();

    // Test per contactEq
    RUN_TEST(test_nome_null);
    RUN_TEST(test_last_name_null);
    RUN_TEST(test_name_or_last_name_null);
    RUN_TEST(test_partial_inequality);
    RUN_TEST(test_different_contacts);
    RUN_TEST(test_same_name_dif_surname);
    RUN_TEST(test_same_contacts);
    

    // Test per contactEqEff
    RUN_TEST(test_eff_nome_null);
    RUN_TEST(test_eff_last_name_null);
    RUN_TEST(test_eff_name_or_last_name_null);
    RUN_TEST(test_eff_partial_inequality);
    RUN_TEST(test_eff_different_contacts);
    RUN_TEST(test_eff_same_name_dif_surname);
    RUN_TEST(test_eff_same_contacts);
    
    // Test per contactCmp
    RUN_TEST(test_nome_null_cmp);
    RUN_TEST(test_last_name_null_cmp);
    RUN_TEST(test_c1_minore_di_c2_cognome_diverso);
    RUN_TEST(test_c1_maggiore_di_c2_cognome_diverso);
    RUN_TEST(test_c1_uguale_a_c2);
    RUN_TEST(test_cognome_uguale_c1_minore_di_c2_per_nome);
    RUN_TEST(test_cognome_uguale_c1_maggiore_di_c2_per_nome);

    // Test per contactCmpEff
    RUN_TEST(test_contactCmpEff_nome_null);
    RUN_TEST(test_contactCmpEff_cognome_null);
    RUN_TEST(test_contactCmpEff_c1_minore_di_c2_cognome_diverso);
    RUN_TEST(test_contactCmpEff_c1_maggiore_di_c2_cognome_diverso);
    RUN_TEST(test_contactCmpEff_c1_uguale_a_c2);
    RUN_TEST(test_contactCmpEff_cognome_uguale_c1_minore_di_c2_per_nome);
    RUN_TEST(test_contactCmpEff_cognome_uguale_c1_maggiore_di_c2_per_nome);

    return UNITY_END();
}    


#include "unity.h"
#include "stoib.h"
 
void setUp(void) {}
void tearDown(void) {}
 
 
void test_s_null_restituisce_zero(void) {
    int r;
    TEST_ASSERT_EQUAL_INT(0, stoib(NULL, 10, &r));
}

void test_r_null_restituisce_zero(void) {
    TEST_ASSERT_EQUAL_INT(0, stoib("10", 10, NULL));
}
 
void test_base_0_non_valida(void) {
    int r;
    TEST_ASSERT_EQUAL_INT(0, stoib("10", 0, &r));
}
 
void test_base_1_non_valida(void) {
    int r;
    TEST_ASSERT_EQUAL_INT(0, stoib("10", 1, &r));
}
 
void test_base_37_non_valida(void) {
    int r;
    TEST_ASSERT_EQUAL_INT(0, stoib("10", 37, &r));
}
 
void test_stringa_vuota(void) {
    int r;
    TEST_ASSERT_EQUAL_INT(0, stoib("", 10, &r));
}
 
void test_solo_spazi(void) {
    int r;
    TEST_ASSERT_EQUAL_INT(0, stoib("   ", 10, &r));
}
 
void test_solo_segno_meno(void) {
    int r;
    TEST_ASSERT_EQUAL_INT(0, stoib("-", 10, &r));
}
 
void test_solo_segno_piu(void) {
    int r;
    TEST_ASSERT_EQUAL_INT(0, stoib("+", 10, &r));
}

void test_ritorno_conta_cifre(void) {
    int r;
    TEST_ASSERT_EQUAL_INT(2, stoib("42", 10, &r));
}
 
void test_ritorno_conta_segno_negativo(void) {
    int r;
    TEST_ASSERT_EQUAL_INT(4, stoib("-123", 10, &r));
}
 
void test_ritorno_conta_segno_positivo(void) {
    int r;
    TEST_ASSERT_EQUAL_INT(3, stoib("+42", 10, &r));
}
 
void test_ritorno_conta_spazi_iniziali(void) {
    int r;
    TEST_ASSERT_EQUAL_INT(3, stoib("  5", 10, &r));
}
 
void test_ritorno_conta_tab_newline(void) {
    int r;
    TEST_ASSERT_EQUAL_INT(5, stoib("\t\n 42", 10, &r));
}
 
void test_si_ferma_alla_prima_cifra_non_valida(void) {
    int r;
    TEST_ASSERT_EQUAL_INT(1, stoib("19", 8, &r));
}
 
void test_si_ferma_su_lettera_minuscola(void) {
    int r;
    TEST_ASSERT_EQUAL_INT(2, stoib("10a5", 10, &r));
}
 
void test_si_ferma_su_segno_nel_mezzo(void) {
    int r;
    TEST_ASSERT_EQUAL_INT(2, stoib("12-3", 10, &r));
}
 
void test_si_ferma_su_spazio_nel_mezzo(void) {
    int r;
    TEST_ASSERT_EQUAL_INT(2, stoib("12 34", 10, &r));
}

void test_valore_semplice_base10(void) {
    int r;
    stoib("42", 10, &r);
    TEST_ASSERT_EQUAL_INT(42, r);
}
 
void test_valore_negativo(void) {
    int r;
    stoib("-123", 10, &r);
    TEST_ASSERT_EQUAL_INT(-123, r);
}
 
void test_valore_positivo_esplicito(void) {
    int r;
    stoib("+42", 10, &r);
    TEST_ASSERT_EQUAL_INT(42, r);
}
 
void test_valore_con_spazi_iniziali(void) {
    int r;
    int c = stoib("\t\n 42", 10, &r);
    TEST_ASSERT_EQUAL_INT(5, c);
    TEST_ASSERT_EQUAL_INT(42, r);
}
 
void test_valore_base2(void) {
    int r;
    int c = stoib("1010", 2, &r);
    TEST_ASSERT_EQUAL_INT(4, c);
    TEST_ASSERT_EQUAL_INT(10, r);
}
 
void test_valore_base16(void) {
    int r;
    int c = stoib("FF", 16, &r);
    TEST_ASSERT_EQUAL_INT(2, c);
    TEST_ASSERT_EQUAL_INT(255, r);
}
 
void test_valore_base36_z(void) {
    int r;
    int c = stoib("Z", 36, &r);
    TEST_ASSERT_EQUAL_INT(1, c);
    TEST_ASSERT_EQUAL_INT(35, r);
}
 
void test_valore_zero(void) {
    int r;
    int c = stoib("0", 10, &r);
    TEST_ASSERT_EQUAL_INT(1, c);
    TEST_ASSERT_EQUAL_INT(0, r);
}
 
void test_valore_si_ferma_su_cifra_fuori_base(void) {
    int r;
    int c = stoib("19", 8, &r);
    TEST_ASSERT_EQUAL_INT(1, c);
    TEST_ASSERT_EQUAL_INT(1, r);
}
 
int main(void) {
    UNITY_BEGIN();
 
    RUN_TEST(test_s_null_restituisce_zero);
    RUN_TEST(test_r_null_restituisce_zero);
    RUN_TEST(test_base_0_non_valida);
    RUN_TEST(test_base_1_non_valida);
    RUN_TEST(test_base_37_non_valida);
    RUN_TEST(test_stringa_vuota);
    RUN_TEST(test_solo_spazi);
    RUN_TEST(test_solo_segno_meno);
    RUN_TEST(test_solo_segno_piu);
 
    RUN_TEST(test_ritorno_conta_cifre);
    RUN_TEST(test_ritorno_conta_segno_negativo);
    RUN_TEST(test_ritorno_conta_segno_positivo);
    RUN_TEST(test_ritorno_conta_spazi_iniziali);
    RUN_TEST(test_ritorno_conta_tab_newline);
    RUN_TEST(test_si_ferma_alla_prima_cifra_non_valida);
    RUN_TEST(test_si_ferma_su_lettera_minuscola);
    RUN_TEST(test_si_ferma_su_segno_nel_mezzo);
    RUN_TEST(test_si_ferma_su_spazio_nel_mezzo);
 
    RUN_TEST(test_valore_semplice_base10);
    RUN_TEST(test_valore_negativo);
    RUN_TEST(test_valore_positivo_esplicito);
    RUN_TEST(test_valore_con_spazi_iniziali);
    RUN_TEST(test_valore_base2);
    RUN_TEST(test_valore_base16);
    RUN_TEST(test_valore_base36_z);
    RUN_TEST(test_valore_zero);
    RUN_TEST(test_valore_si_ferma_su_cifra_fuori_base);
 
    return UNITY_END();
}
 

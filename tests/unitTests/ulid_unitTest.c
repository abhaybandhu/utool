#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Unity/unity.h"
#include "../../header/ulid_cmd.h"
#include "../../header/types.h"
#include "ulid_unitTest.h"

#define TESTULIDV1 "01ARZ3NDEKTSV4RRFFQ69G5FAV" // Example ULID for testing

void test_ulid_generation_single() {
    char **ulids = generate_ulid_cmd(1);
    TEST_ASSERT_NOT_NULL(ulids);
    TEST_ASSERT_NOT_NULL(ulids[0]);
    TEST_ASSERT_EQUAL_INT16(26, strlen(ulids[0]));
    free(ulids[0]);
    free(ulids);
}

void test_ulid_generation_multiple() {
    char **ulids = generate_ulid_cmd(5);
    TEST_ASSERT_NOT_NULL(ulids);
    for (int i = 0; i < 5; i++) {
        TEST_ASSERT_NOT_NULL(ulids[i]);
        TEST_ASSERT_EQUAL_INT16(26, strlen(ulids[i]));
        free(ulids[i]);
    }
    free(ulids);
}

void test_ulid_format_characters() {
    char **ulids = generate_ulid_cmd(1);
    const char *alphabet = "0123456789ABCDEFGHJKMNPQRSTVWXYZ";
    for (int i = 0; i < 26; i++) {
        TEST_ASSERT_NOT_NULL(strchr(alphabet, ulids[0][i]));
    }
    free(ulids[0]);
    free(ulids);
}

void test_ulid_uniqueness() {
    char **ulids = generate_ulid_cmd(10);
    for (int i = 0; i < 10; i++) {
        for (int j = i + 1; j < 10; j++) {
            TEST_ASSERT_NOT_EQUAL(ulids[i], ulids[j]);
        }
    }
    for (int i = 0; i < 10; i++) {
        free(ulids[i]);
    }
    free(ulids);
}

void test_ulid_null_termination() {
    char **ulids = generate_ulid_cmd(1);
    TEST_ASSERT_EQUAL_CHAR('\0', ulids[0][26]);
    free(ulids[0]);
    free(ulids);
}


int RUN_ULID_TESTS() {
    UNITY_BEGIN();
    RUN_TEST(test_ulid_generation_single);
    RUN_TEST(test_ulid_generation_multiple);
    RUN_TEST(test_ulid_format_characters);
    RUN_TEST(test_ulid_uniqueness);
    RUN_TEST(test_ulid_null_termination);
    return UNITY_END();
}

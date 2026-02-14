#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Unity/unity.h"
#include "../../header/guid_cmd.h"
#include "../../header/types.h"
#include "guid_unitTest.h"

#define TESTGUIDV7 "01842f64-6b4c-7c00-9c9f-2b2e00000001" // Example GUID for testing
#define TESTGUIDV4 "550e8400-e29b-41d4-a716-446655440000" // Example GUID for testing


void test_guid_version_4() {
    char **guids = generate_guid_v4(1);
    TEST_ASSERT_NOT_NULL(guids);
    TEST_ASSERT_GREATER_THAN(0, strlen(guids[0]));
    TEST_ASSERT_EQUAL_INT16(36, strlen(guids[0]));
    free(guids[0]);
    free(guids);
}

void test_guid_version_7() {
    char **guids = generate_guid_v7(1);
    TEST_ASSERT_NOT_NULL(guids);
    TEST_ASSERT_GREATER_THAN(0, strlen(guids[0]));
    TEST_ASSERT_EQUAL_INT16(36, strlen(guids[0]));
    free(guids[0]);
    free(guids);
}

void test_guid_multiple_count() {
    char **guids = generate_guid_v4(5);
    TEST_ASSERT_NOT_NULL(guids);
    for (int i = 0; i < 5; i++) {
        TEST_ASSERT_GREATER_THAN(0, strlen(guids[i]));
        TEST_ASSERT_EQUAL_INT16(36, strlen(guids[i]));
        free(guids[i]);
    }
    free(guids);
}

void test_valid_guid_format() {
    TEST_ASSERT_EQUAL(1, is_valid_guid_format(TESTGUIDV4));
    TEST_ASSERT_EQUAL(0, is_valid_guid_format("invalid"));
    TEST_ASSERT_EQUAL(0, is_valid_guid_format("550e8400e29b41d4a716446655440000"));
}

void test_check_guid_version() {
    TEST_ASSERT_EQUAL(VERSION_4,get_guid_version(TESTGUIDV4));
    TEST_ASSERT_EQUAL(VERSION_7,get_guid_version(TESTGUIDV7));
}

void test_check_guid_variant() {
    TEST_ASSERT_EQUAL(RFC4122, check_guid_variant(TESTGUIDV4));
}

int RUN_GUID_TESTS() {
    UNITY_BEGIN();
    RUN_TEST(test_guid_version_4);
    RUN_TEST(test_guid_version_7);
    RUN_TEST(test_guid_multiple_count);
    RUN_TEST(test_valid_guid_format);
    RUN_TEST(test_check_guid_version);
    RUN_TEST(test_check_guid_variant);
    return UNITY_END();
}

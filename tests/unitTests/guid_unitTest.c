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
    TEST_ASSERT_EQUAL(1, is_valid_guid_format(TESTGUIDV7));
    TEST_ASSERT_EQUAL(0, is_valid_guid_format("invalid"));
    TEST_ASSERT_EQUAL(0, is_valid_guid_format(NULL));
    TEST_ASSERT_EQUAL(0, is_valid_guid_format("550e8400e29b41d4a716446655440000"));
}

void test_check_guid_version() {
    TEST_ASSERT_EQUAL(VERSION_4,get_guid_version(TESTGUIDV4));
    TEST_ASSERT_EQUAL(VERSION_7,get_guid_version(TESTGUIDV7));
    TEST_ASSERT_EQUAL(MIN_VERSION,get_guid_version("xxxxxxxx-xxxx-1xxx-Nxxx-xxxxxxxxxxxx")); // Version 1 GUID
    TEST_ASSERT_EQUAL(2,get_guid_version("xxxxxxxx-xxxx-2xxx-Nxxx-xxxxxxxxxxxx")); // Vesroin 2 GUID
    TEST_ASSERT_EQUAL(3,get_guid_version("xxxxxxxx-xxxx-3xxx-Nxxx-xxxxxxxxxxxx")); // Version 3 GUID
    TEST_ASSERT_EQUAL(5,get_guid_version("xxxxxxxx-xxxx-5xxx-Nxxx-xxxxxxxxxxxx")); // Version 5 GUID
    TEST_ASSERT_EQUAL(6,get_guid_version("xxxxxxxx-xxxx-6xxx-Nxxx-xxxxxxxxxxxx")); // Version 6 GUID
    TEST_ASSERT_EQUAL(MAX_VERSION,get_guid_version("xxxxxxxx-xxxx-8xxx-Nxxx-xxxxxxxxxxxx")); // Version 8 GUID

}

void test_check_guid_variant() {
    //RFC4122
    TEST_ASSERT_EQUAL(RFC4122, check_guid_variant(TESTGUIDV4));
    TEST_ASSERT_EQUAL(RFC4122, check_guid_variant(TESTGUIDV7));
    TEST_ASSERT_EQUAL(RFC4122, check_guid_variant("xxxxxxxx-xxxx-Mxxx-bxxx-xxxxxxxxxxxx"));
    TEST_ASSERT_EQUAL(RFC4122, check_guid_variant("xxxxxxxx-xxxx-Mxxx-8xxx-xxxxxxxxxxxx"));
    //MICROSOFT
    TEST_ASSERT_EQUAL(MICROSOFT, check_guid_variant("xxxxxxxx-xxxx-Mxxx-cxxx-xxxxxxxxxxxx"));
    TEST_ASSERT_EQUAL(MICROSOFT, check_guid_variant("xxxxxxxx-xxxx-Mxxx-dxxx-xxxxxxxxxxxx"));
    //FUTURE
    TEST_ASSERT_EQUAL(FUTURE, check_guid_variant("xxxxxxxx-xxxx-Mxxx-exxx-xxxxxxxxxxxx"));
    TEST_ASSERT_EQUAL(FUTURE, check_guid_variant("xxxxxxxx-xxxx-Mxxx-fxxx-xxxxxxxxxxxx"));
    //NCS
    TEST_ASSERT_EQUAL(NCS, check_guid_variant("xxxxxxxx-xxxx-Mxxx-0xxx-xxxxxxxxxxxx"));
    TEST_ASSERT_EQUAL(NCS, check_guid_variant("xxxxxxxx-xxxx-Mxxx-7xxx-xxxxxxxxxxxx"));
    //INVALID
    TEST_ASSERT_EQUAL(INVALID, check_guid_variant("xxxxxxxx-xxxx-Mxxx-gxxx-xxxxxxxxxxxx"));
    TEST_ASSERT_EQUAL(INVALID, check_guid_variant("xxxxxxxx-xxxx-Mxxx-Zxxx-xxxxxxxxxxxx"));
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

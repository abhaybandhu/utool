
#include "Unity/unity.h"
#include "unitTests/guid_unitTest.h"
#include "unitTests/ulid_unitTest.h"

void setUp(void) {}
void tearDown(void) {}


int main(void) {
    
    int guidResult = RUN_GUID_TESTS();
    int ulidResult = RUN_ULID_TESTS();
    return guidResult && ulidResult; // Return non-zero if any test fails
}
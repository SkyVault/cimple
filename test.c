#include <stdbool.h>
#include <stdio.h>

bool test1(char* os);
bool test2(char* os);
bool test3(char* os);

#define CIMPLE_TESTS                        \
    CTEST(test1),                           \
    CTEST(test2),                           \
    CTEST(test3),

#include "cimple.h"

bool test1(char* os) {
    sprintf(os+strlen(os), "%s%s\n", CIMPLE_ARROW, "Test 1 sub text");
    return true;
}

bool test2(char* os) {
    return false;
}

bool test3(char* os) {
    return true;
}

int main() {
    printf("Cimple Version (%s)\n", CIMPLE_VERSION);
    cimpleRunTests();
    return 0;
}

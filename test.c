#include <stdbool.h>

bool test1(char* os) {
    return true;
}

bool test2(char* os) {
    return false;
}

bool test3(char* os) {
    return true;
}

#define CIMPLE_TESTS                        \
    CTEST(test1),                           \
    CTEST(test2),                           \
    CTEST(test3),

#include "cimple.h"

int main() {
    cimpleRunTests();

    return 0;
}

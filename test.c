#include <stdbool.h>
#include <stdio.h>

#define CIMPLE_TESTS                      \
    CTEST(test1)                          \
    CTEST(test2)                          \
    CTEST(test3)

#include "cimple.h"

bool test1(char* os) {
    cimp_log(os, "Test 1 is running");
    cimp_log(os, "This is the second log");
    return true;
}

bool test2(char* os) {
    cimp_log(os, "1 == 2");
    return 1 == 2;
}

bool test3(char* os) {
    cimp_log(os, "\"hello\"[2] == \"hello\"[3]");
    return "hello"[2] == "hello"[3];
}

int main() {
    printf("Cimple Version (%s)\n", CIMPLE_VERSION);
    cimpleRunTests();
    return 0;
}

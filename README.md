# cimple

A very simple, header only test library for C

## Examples

test.c:
```c
#include <stdbool.h>
#include <stdio.h>

#define CIMPLE_TESTS                      \
    CTEST(test1)                          \
    CTEST(test2)                          \
    CTEST(test3)

#include "cimple.h"

bool test1(void) {
    cimp_log("Test 1 is running");
    cimp_log("This is the second log");
    return true;
}

bool test2(void) {
    cimp_log("1 == 2");
    return 1 == 2;
}

bool test3(void) {
    cimp_log("\"hello\"[2] == \"hello\"[3]");
    return "hello"[2] == "hello"[3];
}

int main() {
    printf("Cimple Version (%s)\n", CIMPLE_VERSION);
    cimpleRunTests();
    return 0;
}
```

![see: res/output.png](res/output.png)
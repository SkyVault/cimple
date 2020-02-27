# cimple

A very simple, header only test library for C

## Examples

test.c:
```c
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
    cimp_log(os, "Test 1 is running");
    cimp_log(os, "This is the second log");
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
```

![see: res/output.png](res/output.png)
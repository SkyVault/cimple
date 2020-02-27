# cimple

A very simple, header only test library for C

## Examples

test.c:
```c
#include <stdbool.h>

bool test1(char* os) { return true; }
bool test2(char* os) { return false; }
bool test3(char* os) { return true; }

#define CIMPLE_TESTS                        \
    CTEST(test1),                           \
    CTEST(test2),                           \
    CTEST(test3),

#include "cimple.h"

int main() {
    cimpleRunTests();
    return 0;
}
```

![see: res/output.png](res/output.png)
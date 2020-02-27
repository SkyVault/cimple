#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#ifndef MACROSTR
#define MACROSTR(s) #s
#endif//MACROSTR

bool cimple_no_tests(char* os) {
    sprintf(os+strlen(os), "No tests\n");
    return false;
}

#ifndef CIMPLE_TESTS
#define CIMPLE_TESTS\
    CTEST(cimple_no_tests),
#endif//CIMPLE_TESTS

typedef bool (*cimple_test_fn)(char* os);

void cimpleRunTests(){
#define CTEST(test) { .name = MACROSTR(test), .fn = test }
    const struct { const char* name; cimple_test_fn fn; } tests[] = {
        CIMPLE_TESTS
    };
#undef CTEST

    size_t n_tests = (sizeof(tests)/sizeof(tests[0]));
    size_t succ = 0;

    char final_output[2048] = {0};

    for (size_t i = 0; i < n_tests; i++) {
        char buffer[512] = {0};
        bool result = tests[i].fn(buffer);

        const char* status = result ? "PASSED" : "FAILED";

        if (result) succ++;

        char* color = result
            ? "\033[32;1m"
            : "\033[31;1m";

        sprintf(final_output+strlen(final_output), "[%d] <%s> test: %s[%s]\033[m\n",
                (int)i + 1,
                tests[i].name,
                color,
                status);

        sprintf(final_output+strlen(final_output), "\033[36m%s\033[m", buffer);
    }

    bool passed = (n_tests == succ);

    sprintf(final_output+strlen(final_output), "Cimple tests [%s] (%d/%d) (%d%%)\n",
            (passed?"PASSED":"FAILED"),
            (int)succ,
            (int)n_tests,
            (int)((((float)succ)/(float)n_tests)*100));

    printf("%s\n", final_output);
}
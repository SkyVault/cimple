#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>

#ifndef MACROSTR
#define MACROSTR(s) #s
#endif//MACROSTR

#define CIMPLE_VERSION_PATCH "0"
#define CIMPLE_VERSION_MINOR "2"
#define CIMPLE_VERSION_MAJOR "0"
#define CIMPLE_VERSION CIMPLE_VERSION_MAJOR "." CIMPLE_VERSION_MINOR "." CIMPLE_VERSION_PATCH

#define CIMPLE_ARROW "└─> "

#ifndef CIMPLE_NO_COLOR
#define CIMPLE_NO_COLOR
    #define CIMPLE_COLOR_FAIL     "\033[31;1m"
    #define CIMPLE_COLOR_SUCC     "\033[32;1m"
    #define CIMPLE_COLOR_CLEAR    "\033[m"
    #define CIMPLE_COLOR_SUB      "\033[36m"
    #define CIMPLE_COLOR_NUMBER   "\033[33;1m"
    #define CIMPLE_COLOR_FUNC     "\033[35;1m"
#else
    #define CIMPLE_COLOR_FAIL     ""
    #define CIMPLE_COLOR_SUCC     ""
    #define CIMPLE_COLOR_CLEAR    ""
    #define CIMPLE_COLOR_SUB      ""
    #define CIMPLE_COLOR_NUMBER   ""
    #define CIMPLE_COLOR_FUNC     ""
#endif//CIMPLE_NO_COLOR

bool cimple_no_tests(char* os) {
    sprintf(os+strlen(os), "%sNo tests defined, see README.md for an example\n", CIMPLE_ARROW);
    return false;
}

#ifndef CIMPLE_TESTS
#define CIMPLE_TESTS CTEST(cimple_no_tests)
#endif//CIMPLE_TESTS

typedef bool (*cimple_test_fn)(char* os);

void cimp_log(char* os, const char* fmt, ...) {
    va_list args;
    sprintf(os+strlen(os), "%s%s", CIMPLE_COLOR_NUMBER, CIMPLE_ARROW);
    sprintf(os+strlen(os), "%s", CIMPLE_COLOR_SUB);
    sprintf(os+strlen(os), fmt, args);
    sprintf(os+strlen(os), "\n%s", CIMPLE_COLOR_CLEAR);
}

#define CTEST(test) bool test (char* os);
CIMPLE_TESTS
#undef CTEST

bool cimpleRunTests(){
#define CTEST(test) { .name = MACROSTR(test), .fn = test },
    const struct { const char* name; cimple_test_fn fn; } tests[] = {
        CIMPLE_TESTS
    };
#undef CTEST

    size_t n_tests = (sizeof(tests)/sizeof(tests[0]));
    size_t succ = 0;

    char final_output[2048] = {0};

    for (size_t i = 0; i < n_tests; i++) {
        char buffer[512] = {[0]='\0'};
        bool result = tests[i].fn(buffer);

        const char* status = result
                             ? CIMPLE_COLOR_SUCC "PASSED" CIMPLE_COLOR_CLEAR
                             : CIMPLE_COLOR_FAIL "FAILED" CIMPLE_COLOR_CLEAR;

        if (result) succ++;

        sprintf(final_output+strlen(final_output), "%s[%d] %s<%s>%s [%s]%s\n",
                CIMPLE_COLOR_NUMBER,
                (int)i + 1,
                CIMPLE_COLOR_FUNC,
                tests[i].name,
                CIMPLE_COLOR_CLEAR,
                status,
                CIMPLE_COLOR_CLEAR);

        sprintf(final_output+strlen(final_output),
                "%s%s%s",
                CIMPLE_COLOR_SUB,
                buffer,
                CIMPLE_COLOR_CLEAR);
    }

    bool passed = (n_tests == succ);

    const char* status = passed
                         ? CIMPLE_COLOR_SUCC "PASSED" CIMPLE_COLOR_CLEAR
                         : CIMPLE_COLOR_FAIL "FAILED" CIMPLE_COLOR_CLEAR;       

    sprintf(final_output+strlen(final_output), "Test results: [%s] (%d/%d) (%d%%)\n",
            status,
            (int)succ,
            (int)n_tests,
            (int)((((float)succ)/(float)n_tests)*100));

    printf("%s\n", final_output);

    return passed;
}

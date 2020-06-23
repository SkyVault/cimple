#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#ifndef MACROSTR
#define MACROSTR(s) #s
#endif//MACROSTR

#define CIMPLE_VERSION_PATCH "3"
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

void cimp_log(const char* fmt, ...);

bool cimple_no_tests(void) {
    cimp_log("%sNo tests defined, see README.md for an example\n", CIMPLE_ARROW);
    return false;
}

#ifndef CIMPLE_TESTS
#define CIMPLE_TESTS CTEST(cimple_no_tests)
#endif//CIMPLE_TESTS

typedef bool (*cimple_test_fn)(void);

static char* output_buff = NULL;

void cimp_log(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    char os[2048] = {'\0'};
    sprintf(os+strlen(os), "%s%s", CIMPLE_COLOR_SUB, CIMPLE_ARROW);
    sprintf(os+strlen(os), "%s", CIMPLE_COLOR_SUB);
    vsprintf(os+strlen(os), fmt, args);
    sprintf(os+strlen(os), "\n%s", CIMPLE_COLOR_CLEAR);

    size_t len = strlen(os);

    if (output_buff == NULL) {
        output_buff = malloc(len + 1);
        strcpy(output_buff, os);
        output_buff[len] = '\0';
    } else {
        output_buff = realloc(output_buff, strlen(output_buff) + len + 1);
        strcpy(output_buff+strlen(output_buff), os);
        output_buff[strlen(output_buff) + len] = '\0';
    }

    va_end(args);
}

#define CTEST(test) bool test (void);
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

    for (size_t i = 0; i < n_tests; i++) {
        bool result = tests[i].fn();

        const char* status = result
                             ? CIMPLE_COLOR_SUCC "PASSED" CIMPLE_COLOR_CLEAR
                             : CIMPLE_COLOR_FAIL "FAILED" CIMPLE_COLOR_CLEAR;

        if (result) succ++;

        printf("%s[%d] %s<%s>%s [%s]%s\n",
               CIMPLE_COLOR_NUMBER,
               (int)i + 1,
               CIMPLE_COLOR_FUNC,
               tests[i].name,
               CIMPLE_COLOR_CLEAR,
               status,
               CIMPLE_COLOR_CLEAR);

        printf("%s%s%s",
               CIMPLE_COLOR_SUB,
               (output_buff == NULL ? "" : output_buff),
               CIMPLE_COLOR_CLEAR);

        if (output_buff) {
            free(output_buff);
            output_buff = NULL;
        }

    }

    bool passed = (n_tests == succ);

    const char* status = passed
                         ? CIMPLE_COLOR_SUCC "PASSED" CIMPLE_COLOR_CLEAR
                         : CIMPLE_COLOR_FAIL "FAILED" CIMPLE_COLOR_CLEAR;

    printf("Test results: [%s] (%d/%d) (%d%%)\n",
            status,
            (int)succ,
            (int)n_tests,
            (int)((((float)succ)/(float)n_tests)*100));

    return passed;
}

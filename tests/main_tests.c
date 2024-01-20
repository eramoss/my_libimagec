#include <stdio.h>


typedef unsigned (*TestFunction)();

TestFunction test_suite[] = {
        
};

#define NUM_TESTS (sizeof(test_suite) / sizeof(test_suite[0]))

int main() {
    unsigned result = 0;


    for (int i = 0; i < NUM_TESTS; ++i) {
        result += test_suite[i]();
    }

    if (result == 0) {
        printf("All tests passed!\n");
    } else {
        printf("%d tests failed\n", result);
    }

    return (int) result;
}

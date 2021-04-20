#include "calc.h"

#define TABLE_SIZE 128

int is_space(char c) {
    int spaces[TABLE_SIZE] = {
        ['\t'] = 1,
        [' '] = 1,
        ['\n'] = 1,
    };
    return spaces[(int)c];
}

int calc_evaluate(const char *expr,
                  calc_result *res,
                  const calc_function *functions) {
    (void)expr;
    (void)res;
    (void)functions;
    return 0;
}

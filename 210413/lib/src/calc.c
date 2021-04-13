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

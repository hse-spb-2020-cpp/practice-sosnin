#define _CRT_SECURE_NO_WARNINGS  // Visual Studio warning suppression
#include <stdio.h>

int main(void) {
    int i = 42;
    float f = 3.141592654;
    char c = '!';
    const char *s = "How Are You";
    fprintf(stdout, "Hello world\n");
    fprintf(stdout, "%d\n", i);
    fprintf(stdout, "%.3f\n", f);
    fprintf(stdout, "%c\n", c);
    fprintf(stdout, "%s\n", s);
    fprintf(stdout, "Hello world%c %s?\n", c, s);
    return 0;
}
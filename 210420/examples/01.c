#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int buf_size = 10;
    char *buf = malloc(buf_size);
    if (!buf) {
        fprintf(stderr, "Failed to allocate\n");
        goto free_buf;
    }

    char *new_buf = realloc(buf, 2 * buf_size);
    if (!new_buf) {
        fprintf(stderr, "Failed to reallocate\n");
        goto realloc_err;
    }
    buf = new_buf;
    buf_size = 2 * buf_size;

realloc_err:
    free(buf);
free_buf:
    return 0;
}
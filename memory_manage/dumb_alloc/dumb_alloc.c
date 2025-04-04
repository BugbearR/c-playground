#include <errno.h>
#include <stddef.h>

static char *s_base = NULL;
static size_t s_base_size = 0;
static char *s_next = NULL;

void dumb_alloc_init(size_t base_size) {
    s_base = malloc(base_size);
    if (!s_base) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    s_base_size = base_size;
}

void dumb_alloc_finalize() {
    if (s_base) {
        free(s_base);
        s_base = NULL;
    }
}

void *dumb_alloc_allocate(size_t size) {
    if (!s_base) {
        errno = NOMEM;
        return NULL;
    }

    if ((s_base + s_base_size) - (s_next + size) < 0) {
        errno = NOMEM;
        return NULL;
    }

    void *ptr = s_next;
    s_next += size;
    return ptr;
}

void dumb_alloc_free(void *ptr) {
    // nothing to do :-P
}

#include <errno.h>
#include <stddef.h>

typedef struct block {
    struct block *next;
    struct block *prev;
    size_t size;
    int used;
    union {
        struct block *free_next;
        char data[1];
    };
} block_t;

static char *s_base = NULL;
static size_t s_base_size = 0;
static block_t *s_block_head = NULL;
static block_t *s_block_tail = NULL;
static block_t *s_free_block_list = NULL;

void ret_cat_alloc_init(size_t base_size) {
    s_base = malloc(base_size);
    if (!s_base) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    s_base_size = base_size;
}

void ret_cat_alloc_finalize() {
    if (s_base) {
        free(s_base);
        s_base = NULL;
    }
}

void *ret_cat_alloc_allocate(size_t size) {
    if (!s_base) {
        errno = NOMEM;
        return NULL;
    }

    block_t *prev_block = NULL;
    block_t *block = s_free_list;
    while (block) {
        if (block->size >= size) { // first-hit
            if (prev_block) {
                prev_block->next = block->next;
            } else {
                s_free_list = block->next;
            }
            return block->data;
        }
        prev_block = block;
        block = block->next;
    }

    size_t minimum_size = (sizeof(block_t) - offsetof(block_t, data));
    size_t data_size = (size < minimum_size) ? minimum_size : size;
    size_t block_size = offsetof(block_t, data) + data_size;
    if ((s_next + block_size) - (s_base + s_base_size) > 0) {
        errno = NOMEM;
        return NULL;
    }

    block = s_next;
    s_next += block_size;
    block->size = data_size;
    return block->data;
}

void ret_cat_alloc_free(void *ptr) {
    block_t *block = (block_t *)((char *)ptr - offsetof(block_t, data));
    block->next = s_free_block_list;
    s_free_block_list = block;
}

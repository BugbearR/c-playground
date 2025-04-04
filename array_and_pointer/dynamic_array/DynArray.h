#ifndef DYN_ARRAY_H_
#define DYN_ARRAY_H_

#ifdef HAVE_PRAGMA_ONCE
#pragma once
#endif

#include <stddef.h>
#include <sys/types.h>

typedef struct DynArray DynArray_t;

struct DynArray {
    void *data;
    size_t size;
    size_t capacity;
    size_t elementSize;
    void *(*allocateFn)(void *p, size_t);
    // void (*free_fn)(void *);
    // void (*copy_fn)(void *, const void *);
};

DynArray_t *DynArray_initialize(
    DynArray_t *pThis,
    size_t elementSize,
    size_t initialCapacity,
    void *(*allocateFn)(void *p, size_t));

void DynArray_finalize(DynArray_t *pThis);

/**
 * @brief Allocates memory for the dynamic array.
 * @param p Pointer to the current memory block.
 * @param size Size of the new memory block.
 */
void *DynArray_allocate(void *p, size_t size);

/**
 * @brief Resizes the dynamic array to the new capacity.
 * @param pThis Pointer to the dynamic array.
 * @param newCapacity New capacity of the dynamic array.
 * @return 0 on success, -ENOMEM on failure.
 */
int DynArray_reserve(DynArray_t *pThis, size_t newCapacity);

/**
 * @brief Resizes the dynamic array to the new size.
 * @param pThis Pointer to the dynamic array.
 * @param newSize New size of the dynamic array.
 */
int DynArray_resize(DynArray_t *pThis, size_t newSize);

void *DynArray_at(DynArray_t *pThis, size_t index);

ssize_t DynArray_size(DynArray_t *pThis);

ssize_t DynArray_capacity(DynArray_t *pThis);

void DynArray_pushBack(DynArray_t *pThis, const void *element);

void DynArray_popBack(DynArray_t *pThis);


void DynArray_clear(DynArray_t *pThis);


void DynArray_remove(DynArray_t *pThis, size_t index);

void DynArray_insert(DynArray_t *pThis, size_t index, const void *element);

void DynArray_insertArray(DynArray_t *pThis, size_t index, const void *array, size_t arraySize);

void DynArray_copy(DynArray_t *pThis, const DynArray_t *other);


#endif // DYN_ARRAY_H_

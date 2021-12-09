#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

#include "balloc.h"
#include "bitmap.h"
#include "utils.h"
#include "freelist.h"

typedef struct BallocContainer {
    FreeList *f;    // deq containing list of free memory slots
    int u;  // upper memory limit in powers of 2
    int l;  // lower memory limit in powers of 2
    int size;   // overall size of the container
    void *base; // base pointer
} *BallocContainer;

/**
 * Allocates a new buddy system
 * 
 * @param size 
 * @param l - Lower bound for memory range
 * @param u - Upper bound for memory range
 * @return Balloc 
 */
extern Balloc bnew(unsigned int size, int l, int u) {
    if (l > u)
        ERROR("Lower bound > upper bound")
    // instantiate struct and its contained items
    BallocContainer *b = (BallocContainer *) mmalloc(sizeof(BallocContainer));
    b->f = freelistnew(size, l, u);
    b->u = u;
    b->l = l;
    b->size = size;
    b->base = (void *) mmalloc(size);
    if (b->base == NULL)
        ERROR("mmalloc failed");
    return (Balloc*) b;
}

/**
 * Allocates memory in pool of size `size`
 * 
 * @param pool - Memory pool use to allocate data
 * @param size - Size of request
 * @return void* - Pointer to memory allocated in pool
 */
extern void *balloc(Balloc pool, unsigned int size) {
    if (pool == NULL)
        ERROR("pool is null");
    BallocContainer *b = (BallocContainer *) pool;
    // if request is too big, return null
    if (size > b->size)
        ERROR("Invalid balloc size requested");
    // get minimum block size needed for request
    int minSize = b->l;
    for (int i = b->l + 1; i < b->u; i++) {
        if (e2size(i) >= size) {
            minSize = i;
        } else {
            break;
        }
    }
    // allocate memory and return the pointer
    return freelistalloc(b->f, b->base, minSize, b->l);
}

/**
 * Frees the memory at offset `mem` contained in `pool`
 * 
 * @param pool - Memory pool to free data to
 * @param mem - Pointer to data to free
 */
extern void bfree(Balloc pool, void *mem) {
    //munmap? To unmap the region used up in the mmap() call?
    if (pool == NULL)
        ERROR("pool is null");
    if (mem == NULL)
        ERROR("mem is null");
    BallocContainer *b = (BallocContainer *) pool;
    // free data and store it in freelist
    freelistfree(b->f, b->base, mem, size2e(sizeof(mem)), b->l);
}

/**
 * Gets the size of memory at pointer `mem`
 * 
 * @param pool - Memory pool where data is stored
 * @param mem - Offset where data is stored
 * @return unsigned int - Size of `mem` in bytes
 */
extern unsigned int bsize(Balloc pool, void *mem) {
    if (pool == NULL)
        ERROR("pool is null");
    if (mem == NULL)
        ERROR("mem is null");
    BallocContainer *b = (BallocContainer *) pool;
    // return size of data
    return freelistsize(b->f, b->base, mem, b->l, b->u);
}

/**
 * Prints the data in `pool`
 * 
 * @param pool - Memory pool where data is stored
 */
extern void bprint(Balloc pool) {
    if (pool == NULL)
        ERROR("pool is null");
    BallocContainer *b = (BallocContainer *) pool;
    printf("%p\n", b->base);
}
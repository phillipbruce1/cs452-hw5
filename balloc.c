#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

#include "balloc.h"
#include "bitmap.h"
#include "utils.h"

typedef struct BallocContainer {
    FreeList *f;
    int u;
    int l;
    int size;
    void *base;
} *BallocContainer;

static const size_t MAX_SIZE = 128;

/**
 * @brief - Allocated a new buddy system
 * 
 * @param size 
 * @param l - Lower bound for memory range
 * @param u - Upper bound for memory range
 * @return Balloc 
 */
extern Balloc bnew(unsigned int size, int l, int u) {
    return (Balloc*) mmalloc(size);
}

/**
 * @brief - Allocates memory in pool of size `size`
 * 
 * @param pool 
 * @param size 
 * @return void* - Pointer to memory allocated in pool
 */
extern void *balloc(Balloc pool, unsigned int size) {
    // if request is too big, return null
    if (size > MAX_SIZE)
        ERROR("Invalid balloc size requested");
}

/**
 * @brief - Frees the memory `mem` contained in `pool`
 * 
 * @param pool 
 * @param mem 
 */
extern void bfree(Balloc pool, void *mem) {
    //munmap? To unmap the region used up in the mmap() call?
}

/**
 * @brief - Gets the size of memory at pointer `mem`
 * 
 * @param pool 
 * @param mem 
 * @return unsigned int - Size of `mem` in bytes
 */
extern unsigned int bsize(Balloc pool, void *mem) {
}

/**
 * @brief - Prints the data in `pool`
 * 
 * @param pool 
 */
extern void bprint(Balloc pool) {
}
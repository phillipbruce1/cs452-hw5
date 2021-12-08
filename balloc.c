#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

#include "balloc.h"
#include "bitmap.h"
#include "utils.h"

/**
 * @brief - Allocated a new buddy system
 * 
 * @param size 
 * @param l 
 * @param u 
 * @return Balloc 
 */
extern Balloc bnew(unsigned int size, int l, int u) {
    return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}

/**
 * @brief - Allocates memory in pool of size `size`
 * 
 * @param pool 
 * @param size 
 * @return void* - Pointer to memory allocated in pool
 */
extern void *balloc(Balloc pool, unsigned int size) {
}

/**
 * @brief - Frees the memory `mem` contained in `pool`
 * 
 * @param pool 
 * @param mem 
 */
extern void bfree(Balloc pool, void *mem) {
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
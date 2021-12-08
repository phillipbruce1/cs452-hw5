#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

#include "balloc.h"
#include "bitmap.h"
#include "utils.h"
#include "freelist.h"
#include "deq.h"

/**
 * Creates a new FreeList (Deq) object with one node of size `size`
 * @param size - Size of initial freelist/buddy system
 * @param l - Lower exponent bound
 * @param u - Upper exponent bound
 * @return - A new FreeList (Deq) object
 */
extern FreeList freelistnew(unsigned int size, int l, int u) {
    if (e2size(l) > size || size > e2size(u))
        return NULL;
    Deq deq = deq_new();
    deq_head_put(deq, mmalloc(size));
    return (FreeList) deq;
}

extern void *freelistalloc(FreeList f, void *base, int e, int l) {
}

extern void freelistfree(FreeList f, void *base, void *mem, int e, int l) {
}

extern int freelistsize(FreeList f, void *base, void *mem, int l, int u) {
}

extern void freelistprint(FreeList f, unsigned int size, int l, int u) {
}
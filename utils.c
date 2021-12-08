#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <sys/mman.h>

#include "balloc.h"
#include "bitmap.h"
#include "utils.h"
#include "freelist.h"
#include "deq.h"

/**
 * Wrapper for mmap - functions similar to malloc
 * mmalloc becomes base of entire buddy system
 * @param size - size of pointer requested
 * @return
 */
extern void *mmalloc(size_t size) {
    return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}

/**
 * Returns 2^e
 * @param e - Exponent to be calculated
 * @return
 */
extern unsigned int e2size(int e) {
    return pow(2, e);
}

/**
 * Returns power needed to calculate size
 * @param size - Number to be calculated
 * @return
 */
extern int size2e(unsigned int size) {
    return (int) log2f((double) size);
}

/**
 * Sets the desired bit
 * @param p - Pointer to value to be set
 * @param bit - Bit to be set
 */
extern void bitset(unsigned char *p, int bit) {
    *p = *p | 1 << bit;
}

/**
 * Clears the desired bit
 * @param p - Pointer to value to be cleared
 * @param bit - Bit to be cleared
 */
extern void bitclr(unsigned char *p, int bit) {
    *p = *p & ~(1 << bit);
}

/**
 * Inverts the desired bit
 * @param p - Pointer to value to be inverted
 * @param bit - Bit to be inverted
 */
extern void bitinv(unsigned char *p, int bit) {
    *p = *p ^ 1 << bit;
}

/**
 * Tests the desired bit
 * @param p - Pointer to value to be tested
 * @param bit - Bit to be tested
 * @return - True or false if bit is 1 or 0
 */
extern int bittst(unsigned char *p, int bit) {
    unsigned char map = 1 << bit;
    return *p & map;
}

/**
 * Sets the bit at index e
 * @param base - Base memory address
 * @param mem - Offset memory address
 * @param e - Bit to be set
 * @return - Pointer to modified data
 */
extern void *buddyset(void *base, void *mem, int e) {
    bitset((unsigned char*) (mem + base), e);
    return (void *) (mem + base);
}

/**
 * Clears the bit at index e
 * @param base - Base memory address
 * @param mem - Offset memory address
 * @param e - Bit to be cleared
 * @return - Pointer to modified data
 */
extern void *buddyclr(void *base, void *mem, int e) {
    bitclr((unsigned char*) (mem + base), e);
    return (void *) (mem + base);
}

/**
 * Inverts the bit at index e
 * @param base - Base memory address
 * @param mem - Offset memory address
 * @param e - Bit to be inverted
 * @return - Pointer to modified data
 */
extern void *buddyinv(void *base, void *mem, int e) {
    bitinv((unsigned char*) (mem + base), e);
    return (void *) (mem + base);
}

/**
 * Tests the bit at index e
 * @param base - Base memory address
 * @param mem - Offset memory address
 * @param e - Bit to be tested
 * @return - True or false if bit is 1 or 0
 */
extern int buddytst(void *base, void *mem, int e) {
    return bittst((unsigned char*) (mem + base), e);
}
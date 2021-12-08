#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "bitmap.h"
#include "utils.h"

static const int bitsperbyte=8;

/**
 * @brief - Divides up the block into smaller blocks of size d
 * 
 * @param n 
 * @param d 
 * @return int - Number of possible blocks of the minimum size d
 */
static int divup(int n, int d) {
  return (n+d-1)/d;
}

static int mapsize(unsigned int size, int e) {
  // e2size returns size of minimum block
  int blocksize=e2size(e);
  int blocks=divup(size,blocksize);
  int buddies=divup(blocks,2);
  // divup one more time to convert bits to bytes for bitmap allocation
  return divup(buddies,bitsperbyte);
}

static int bitaddr(void *base, void *mem, int e) {
  int addr=buddyclr(base,mem,e)-base;
  int blocksize=e2size(e);
  return addr/blocksize/2;
}

/**
 * @brief 
 * 
 * @param size - Size of overall block in bits
 * @param e - Resolution of bitmap/smallest possible block size in power of 2 (i.e. 1 -> 2^1 -> block size of 2)
 * @return BitMap 
 */
extern BitMap bitmapnew(unsigned int size, int e) {
  int ms=mapsize(size,e);
  BitMap b=mmalloc(ms);
  if ((long)b==-1)
    return 0;
  memset(b,0,ms);
  return b;
}

extern void bitmapset(BitMap b, void *base, void *mem, int e) {
  int offset=bitaddr(base,mem,e);
  bitset(((unsigned char *)b)+offset/bitsperbyte,offset%bitsperbyte);
}

extern void bitmapclr(BitMap b, void *base, void *mem, int e) {
  int offset=bitaddr(base,mem,e);
  bitclr(((unsigned char *)b)+offset/bitsperbyte,offset%bitsperbyte);
}

extern int bitmaptst(BitMap b, void *base, void *mem, int e) {
  int offset=bitaddr(base,mem,e);
  return bittst(((unsigned char *)b)+offset/bitsperbyte,offset%bitsperbyte);
}

extern void bitmapprint(BitMap b, unsigned int size, int e) {
  int ms=mapsize(size,e);
  int byte;
  for (byte=ms-1; byte>=0; byte--)
    printf("%02x%s",((unsigned char *)b)[byte],(byte ? " " : "\n"));
}

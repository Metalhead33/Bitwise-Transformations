#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>     /* malloc, free, rand */
#define set_bit(store,bit) store |= (1 << bit)
#define clear_bit(store,bit) store &= ~(1 << bit)
#define toggle_bit(store,bit) store ^= (1 << bit)
#define mask(store,other) store &= other
#define check_bit(store,bit) store & (1 << bit)
#define NELEMS(x)  (sizeof(x) / sizeof(x[0]))
/*Always allocate before using this!*/
void bwCompress(bool* input, unsigned char* output);
/*Always allocate before using this!*/
void bwDecompress(unsigned char* input, bool* output);
/*Only use on compressed bools*/
void bwToggle(unsigned char* input, int number, bool switched);
/*Never allocate before using this! If you did, free the pointer before that!*/
void bwMultibyteCompress(bool* input, size_t length, unsigned char** output);
/*Never allocate before using this! If you did, free the pointer before that!*/
void bwMultibyteDecompress(unsigned char* input, size_t length, bool** output);
/*Be very sure to use a legal number for it!*/
void bwMultibyteToggle(unsigned char* input, size_t number, bool switched);
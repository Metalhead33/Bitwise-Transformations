#include "bitwise.h"
#include <math.h>
void bwCompress(bool* input, unsigned char* output)
{
	unsigned char buff = 0;
	for (int j = 0; j<8; j++)
	{
		buff += input[j]; buff << 1;
	}
	*output = buff;
}

/*use it as:
unsigned char ex1;
bool[8] ex2;
bwCompress(ex2, &ex1);*/

void bwDecompress(unsigned char* input, bool* output)
{
	unsigned char buf = 0;
		for (int i = 0; i<8; i++)
		{
			buf = *input >> (8 - (i + 1));
			output[i] = buf & 1;
		}
}

void bwToggle(unsigned char* input, int number, bool switched)
{
	bool basis[8];
	bwDecompress(input, basis);
	basis[number] = switched;
	bwCompress(basis, input);
}

void bwMultibyteCompress(bool* input, size_t length, unsigned char** output)
{
	size_t array_size = (length / 8) + (length % 8 > 0);
	*output = (unsigned char*)malloc(sizeof(unsigned char) * array_size);
	size_t d = 0;
	size_t c = 0;
	for (size_t j; j < array_size; j++)
	{
		c = d;
		bool temporary[8];
		for (;d < c + 8; d++)
		{
			temporary[d - c] = input[d];
		}
		bwCompress(temporary, *output[j]);
		d += 8;
	}
}

void bwMultibyteDecompress(unsigned char* input, size_t length, bool** output)
{
	size_t array_size = (length / 8) + (length % 8 > 0);
	*output = (bool*)malloc(sizeof(bool) * array_size * 8);
	size_t total_size = array_size * 8;
	unsigned char buf;
	size_t total_buffed = 0;
	for (size_t j; j < array_size + 1; j++)
	{
		for (size_t i = 0; i < 8; i++)
		{
			buf = input[j] >> (8 - (i + 1));
			*output[total_buffed] = buf&1;
			total_buffed++;
		}
	}
}

void bwMultibyteToggle(unsigned char* input, size_t number, bool switched)
{
	size_t byte = (number / 8) + (number % 8 > 0);
	size_t to_get = number % 8;
	bool basin[8];
	bwDecompress(input[byte], basin);
	basin[to_get] = switched;
	bwCompress(basin, input[byte]);
}
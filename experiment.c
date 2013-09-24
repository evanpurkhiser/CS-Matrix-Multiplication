#include "stdio.h"
#include "stdlib.h"

#define TRIALS 4
#define MATRIX_SIZE 2048

short A[MATRIX_SIZE][MATRIX_SIZE],
      B[MATRIX_SIZE][MATRIX_SIZE],
      C[MATRIX_SIZE][MATRIX_SIZE] = {{0}};

int main(int argc, char*  argv[])
{
	// Initalize array A and B with '1's
	for (int i = 0; i < MATRIX_SIZE; ++i)
		for (int k = 0; k < MATRIX_SIZE; ++k)
			A[i][k] = B[i][k] = 1;

	// Iterate through the block sizes
	for (int block_size = 4; block_size <= 256; block_size *= 2)
	{
		// Run TRIALS number of trials for each block size
		for (int trial = 0; trial < TRIALS; ++trial)
		{
			printf("size: %d\n", block_size);
		}
	}

	return 0;
}

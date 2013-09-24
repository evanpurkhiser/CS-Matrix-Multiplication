#include "stdio.h"
#include "stdlib.h"
#include "sys/time.h"

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

	// Show headings
	for (int trial = 0; trial < TRIALS; ++trial)
		printf(" run%d ,", trial);
	puts(" avrg ");

	// Iterate through the block sizes
	for (int block_size = 4; block_size <= 256; block_size *= 2)
	{
		// Keep track of the times for this block
		time_t block_times[TRIALS];

		// Run TRIALS number of trials for each block size
		for (int trial = 0; trial < TRIALS; ++trial)
		{
			struct timeval time_start;
			gettimeofday(&time_start, NULL);


			// Do work..


			struct timeval time_end;
			gettimeofday(&time_end, NULL);

			// Keep track of the time to do statistics on
			block_times[trial] = time_end.tv_usec - time_start.tv_usec;
			printf("%06d,", (int) block_times[trial]);
		}

		int average = 0;
		for (int i = 0; i < TRIALS; ++i)
			average += (int) block_times[i];

		printf("%06d\n", average / TRIALS);
	}

	return 0;
}

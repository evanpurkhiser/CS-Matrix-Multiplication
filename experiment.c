#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "limits.h"
#include "sys/time.h"

#define TRIALS 8
#define BLOCK_MIN 256
#define BLOCK_MAX 2048
#define MATRIX_SIZE 2048

short A[MATRIX_SIZE][MATRIX_SIZE],
      B[MATRIX_SIZE][MATRIX_SIZE],
      C[MATRIX_SIZE][MATRIX_SIZE];

int min(int a, int b)
{
	return a < b ? a : b;
}

int main(int argc, char*  argv[])
{
	// Initalize array A and B with '1's
	for (int i = 0; i < MATRIX_SIZE; ++i)
		for (int k = 0; k < MATRIX_SIZE; ++k)
			A[i][k] = B[i][k] = 1;

	// Initalize our matix looping variables once
	int k, j, i, jj, kk;

	// Run TRIALS number of trials for each block size
	for (int trial = 0; trial < TRIALS; ++trial)
	{
		long long average = 0;
		long long fastest = LLONG_MAX;

		printf("Trial %d: ", trial);

		// Iterate through the block sizes
		for (int block_size = BLOCK_MIN; block_size <= BLOCK_MAX; block_size *= 2)
		{
			memset(C, 0, sizeof(C[0][0] * MATRIX_SIZE * MATRIX_SIZE));

			struct timeval time_start;
			struct timeval time_end;

			// Keep track of when we start doing work
			gettimeofday(&time_start, NULL);

			// Do block matrix multiplication
			for (k = 0; k < MATRIX_SIZE; k += block_size)
				for (j = 0; j < MATRIX_SIZE; j += block_size)
					for (i = 0; i < MATRIX_SIZE; ++i)
						for (jj = j; jj < min(j + block_size, MATRIX_SIZE); ++jj)
							for (kk = k; kk < min(k + block_size, MATRIX_SIZE); ++kk)
								C[i][jj] += A[i][kk] * B[kk][jj];

			// Keep track of when we finish our work
			gettimeofday(&time_end, NULL);

			// Keep track of the time for averaging later
			long long execution_time = 1000000LL
				* (time_end.tv_sec  - time_start.tv_sec)
				+ (time_end.tv_usec - time_start.tv_usec);

			fastest  = fastest < execution_time ? fastest : execution_time;
			average += execution_time;

			printf("%lld,", execution_time);
			fflush(stdout);
		}

		printf("%lld,%lld\n", average / TRIALS, fastest);
	}

	return 0;
}

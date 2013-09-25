# Experiments with caching - Lab 2

Evan Purkhiser

## Problem Description

In this lab we are tasked with writing a program that will execute a 'blocked
matrix multiplication' algorithm. This is a variation on normal matrix
multiplication where in you divide the matrix into smaller sub-matrices and
then calculate those matrices individually. The advantage of this method is
that you will keep the values that you need to do the matrix calculation in the
cache longer. This will speed up the calculations.

I've implemented matrix multiplication using the following algorithm. This is
very similar to what was given in the original lab handout.

	for (k = 0; k < MATRIX_SIZE; k += block_size)
		for (j = 0; j < MATRIX_SIZE; j += block_size)
			for (i = 0; i < MATRIX_SIZE; ++i)
				for (jj = j; jj < min(j + block_size, MATRIX_SIZE); ++jj)
					for (kk = k; kk < min(k + block_size, MATRIX_SIZE); ++kk)
						C[i][jj] += A[i][kk] * B[kk][jj];

As you can see, this differs from the standard matrix multiplication algorithm
in that it has an extra two loops handle setting up the block that it will be
calculating.

We also have a few variables we can specify here:

 * `MATRIX_SIZE`: This is the size of both sides of the matrix. For example, if
   `MATRIX_SIZE` was set to 512, then you would have a matrix of 512x512. For
   our experiment we will be using a matrix size of 2048x2048.

 * `block_size`: This represents the size of the block that should be
   calculated for each iteration. This should not be larger than the
   `MATRIX_SIZE`. If it is equal to the size of the matrix then the algorithm
   is no longer a blocked matrix multiplciation 

 * `A`, `B` and `C`: These are the matrices represented by a two dimensional
   array of size `MATRIX_SIZE`. both `A` and `B` are initialize with all 1s,
   and `C` is initialized to 0.

## Using `min` instead of `max`

In the sample implementation given in the original PDF handout, the function
`max` was used in place of `min`. This proved to be quite a problem during the
testing of the program. Initial experiments where the algorithm was using the
`max` function to determine the right and bottom bounds of the block to
calculate would cause the bounds to always span the entire right-bottom side of
the matrix. This caused the matrix calculation to run both inefficiently as
well as incorrectly.

This problem was solved by using `min` instead to calculate the right-bottom
bounds.

## Experiment Implementation

In our experiments we will be measuring the performance of the blocked matrix
multiplication algorithm using various `block_size`s. We can do this using the
POSIX `gettimeofday` function defined in `sys/time.h`. This function will give
us back real time (wall clock time) with microsecond resolution.

We will be running 8 trials of our experiments, for each trial we will run 4
different experiment. Our varying factor will be the `block_size`. For the
first experiment we will start with a 256 block size, for each successive
experiment we will double the block size. We continue doing this until reaching
a maximum block size of 2048 (The same size as our matrix).

### Procedure

The following command was used to execute the program

    time ./experiment

After waiting some time for the program to complete we can see the following
output in the terminal:

    real  36m32.270s
	user  36m29.686s
	sys   0m0.423s

Looking at the 'user' time (which is the time that the processor spent executing
the program _not_ including other process slices) we can see that in total it
took 36 minutes and 29 seconds  to execute all 8 trials of 4 experiments each.

### Results

| Trial   | 256      | 512      | 1024     | 2048      |
| ------- | -------- | -------- | -------- | --------- |
| Trial 0 | 51862692 | 51924947 | 51642729 | 111195982 |
| Trial 1 | 52591579 | 52564141 | 52214515 | 126408725 |
| Trial 2 | 56680496 | 57861985 | 60327945 | 152560812 |
| Trial 3 | 52757201 | 52341054 | 52909778 | 102095271 |
| Trial 4 | 52102927 | 52507276 | 58321794 | 106290925 |
| Trial 5 | 52359536 | 52779266 | 52281680 | 096682117 |
| Trial 6 | 52320941 | 52117307 | 52937892 | 107106414 |
| Trial 7 | 53086729 | 52160475 | 52650547 | 108607847 |

The times shown in the table above are recored in microseconds. I've also
calculated the average and fastest for each of the block sizes.

|          | 256      | 512      | 1024     | 2048      |
| -------- | -------- | -------- | -------- | --------- |
| Average  | 52970262 | 53032056 | 54160860 | 113868512 |
| Fastest  | 51862692 | 51924947 | 51642729 | 096682117 |

As we can see from the results, all of the block sizes seem to be fairly close
in size, the outlier being the 2048 block size. In general the first 3 block
sizes took ~53 seconds to complete, while the 2048 block size calculation took
nearly 2 minutes to complete. Let's take a look at why it turned out like that.

I ran the program on my home desktop machine. This machine uses a Intel i7
3770k quad core processor (with 4 extra virtual cores due to multi threading).
This particular CPU has 256kb of L2 cache as well as 8Mb of L3 cache. From this
we can suspect that the 2048x2048 size matrix is running out of room on the CPU
cache causing it to have to do IO with the main memory. But can we prove this?

The matrix arrays contain the `short` C type. This is a 16 bit integer.

	16 bits * 2048 * 2048 = 64 8 Megabytes

While all the data could theoretically fit into my processors 8MB L3 cache,
parts of the cache may be swapped out when other processes execute during their
time slices, thus causing the experiment process to have to read from memory.
This is in-fact what is slowing down the calculation when no blocks are used.

### Small discrepancies

It's interesting to note that for the first 3 experiments (block sizes 256, 512,
and 1024) the first trial was consistently the fastest trial. This is not true
however for the largest block size (2048) where the 5th trial is actually the
fastest. We can speculate as to why this may be, but it's most likely due to
various factors primarily including what other processes are competing for time
on the CPU.

---
Report by Evan Purkhiser - evanpurkhiser.com

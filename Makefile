
experiment: experiment.c
	gcc -Wall -std=c99 -o experiment experiment.c

all: experiment

clean:
	rm experiment

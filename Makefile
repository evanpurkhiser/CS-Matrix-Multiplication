
experiment: experiment.c
	gcc -Wall -o experiment experiment.c

all: experiment

clean:
	rm experiment

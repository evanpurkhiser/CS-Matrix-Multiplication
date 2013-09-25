### Block Matrix Multiplication Lab

This is the second lab for my Parallel Processing course during the Fall 2013
Semester. This lab involves timing the performance of a blocked matrix
multiplication algorithm using various block sizes.

#### Building and testing

A `Makefile` has been included to compile both the report and experiment
program.

To test the program simply execute the following commands

````
make
./experiement
````

Be warned, the expermiment will take around 30 minutes to fully complete.

#### Report

The report is written in markdown but may be converted to a PDF using the
`pandoc` and `texlive` packages. Ensure these packages are installed on your
macheine and execute the following command

````
make report.pdf
````

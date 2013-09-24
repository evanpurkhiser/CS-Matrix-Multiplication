experiment: experiment.c
	gcc -Wall -std=c99 -o experiment experiment.c

report.pdf: report/report.md
	pandoc report/report.md --template=report/template.tex -o report.pdf

all: experiment

clean:
	rm -f experiment report.pdf

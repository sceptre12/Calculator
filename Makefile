CFLAG=-Wall -g

clean:
	rm -f calculator calculatoroutput.txt

all: run

run: calculator

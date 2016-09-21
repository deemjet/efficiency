compile: proj3.out

proj3.out: proj3.c
	gcc -g -Wall -pedantic-errors proj3.c -o proj3.out

run: proj3.out
	./proj3.out input1.txt input2.txt; cat differencesFoundInFile1.txt differencesFoundInFile2.txt;

clean:
	rm proj3.out

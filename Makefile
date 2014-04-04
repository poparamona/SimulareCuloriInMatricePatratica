exec: serial.c paralel.c
	gcc serial.c -o serial
	gcc -fopenmp paralel.c -o paralel

clean:
	rm -f serial paralel

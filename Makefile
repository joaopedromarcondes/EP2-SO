run:
	gcc psort14582570.c -Wall -Werror -pthread -std=c11 -O
	time -v ./a.out entrada.txt saida.txt 3
	rm a.out
	
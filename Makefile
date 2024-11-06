run:
	gcc psort14582570.c 
	./a.out entrada.txt saida.txt 3
	rm a.out

time:
	gcc psort14582570.c 
	time ./a.out entrada.txt saida.txt 3
	rm a.out
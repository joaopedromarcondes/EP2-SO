run:
	gcc psort14582570.c -lpthread
	./a.out entrada.txt saida.txt 3
	rm a.out

comp:
	gcc psort14582570.c -lpthread -g

time:
	gcc psort14582570.c 
	time -p ./a.out entrada.txt saida.txt 3
	rm a.out
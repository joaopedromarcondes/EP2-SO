run:
	gcc psort14582570.c -pthread
	./a.out entrada.txt saida.txt 2
	rm a.out

comp:
	gcc psort14582570.c -pthread -std=c11 -O

time:
	gcc psort14582570.c -pthread
	time -o saida.txt -f "%e" -a ./a.out entrada.txt saida.txt 1 
	rm a.out

tempo_medio:
	gcc calcula_tempo_medio.c -o t.exe
		./t.exe
		rm t.exe


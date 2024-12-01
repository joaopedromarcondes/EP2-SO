run:
	gcc psort14582570.c -lpthread
	./a.out entrada.txt saida.txt 3
	rm a.out

comp:
	gcc psort14582570.c -lpthread 

time:
	gcc psort14582570.c -lpthread
	time -o saida.txt -f "%e" -a ./a.out entrada.txt saida.txt 3 
	rm a.out

tempo_medio:
	gcc calcula_tempo_medio.c -o t.exe
		./t.exe
		rm t.exe


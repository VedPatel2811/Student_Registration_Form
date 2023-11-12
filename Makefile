main : main.o menu.o 
	cc -o main main.o menu.o 

main.o : main.c table.h
	cc -c main.c

menu.o : menu.c table.h
	cc -c menu.c

clean : 
	rm main main.o menu.o 

#Makefile

CC=gcc
CFLAGS=-Wall -lm -lniceprint -L  .
all : lab2 bombardeo 

lab2: lab2.c funciones.c funciones.h
	$(CC) funciones.c lab2.c -o lab2 $(CFLAGS)

bombardeo: bombardeo.c funciones.c funciones.h
	$(CC) funciones.c bombardeo.c -o bombardeo $(CFLAGS)


clean:
	rm -f *.o .exe all
.PHONY : clean

run:
	./lab2 -N 35 -p 5 -c 5 -i test1_35.txt -o out1_35.txt -D

run:
#	./lab1 -N 35 -p 2 -c 5 -i test1_35.txt -o out1.txt -D
#	./lab1 -N 35 -p 2 -c 7 -i test2_35.txt -o out2.txt -D
#	./lab1 -N 30000 -p 2 -c 20000 -i test3_30000.txt -o out3.txt
#	./lab1 -N 1000000 -p 2 -c 5000 -i test4_1M.txt -o out4.txt

#	./lab1 -N 35 -i test1_35.txt -o out1.txt -D
#	./lab1 -N 35 -i test2_35.txt -o out2.txt -D
#	./lab1 -N 30000 -i test3_30000.txt -o out3.txt
#	./lab1 -N 1000000 -i test4_1M.txt -o out4.txt
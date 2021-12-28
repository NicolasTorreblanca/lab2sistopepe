#Makefile

CC=gcc
CFLAGS=-Wall -lm -lniceprint -L  .
all : lab2 bombardeo 

lab2: lab2.c funciones.c funciones.h
	$(CC) funciones.c lab2.c -o lab2 $(CFLAGS)

bombardeo: bomb.c funciones.c funciones.h
	$(CC) funciones.c bomb.c -o bomb $(CFLAGS)

clean:
	rm -f *.o .exe all
.PHONY : clean

run:
#	 ./lab2 -N 35 -p 5 -c 5 -i test1_35.txt -o out1_35.txt -D
#  ./lab2 -N 35 -p 2 -c 5 -i test1_35.txt -o out1_35.txt -D 


#  ./lab2 -N 35 -p 7 -c 7 -i test2_35.txt -o out2_35.txt -D
#  ./lab2 -N 35 -p 2 -c 7 -i test2_35.txt -o out2_35.txt -D
#  ./lab2 -N 35 -p 3 -c 7 -i test2_35.txt -o out2_35.txt -D

#  ./lab2 -N 30000 -p 20000 -c 20000 -i test3_35.txt -o out3_35.txt -D

#  ./lab2 -N 1000000 -p 5000 -c 5000 -i test4_35.txt -o out4_35.txt -D
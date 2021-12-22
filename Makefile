#Makefile

CC = gcc
CFLAGS = -Wall -lm -lniceprint
out = lab1
source = lab1.c funciones.c
objects = $(source:.c=.o)
depends = .depends
headers = funciones.h

$(out): $(objects)
	$(CC) -o $@ $^ $(CFLAGS) -L .

$(objects): 
	$(CC) -c $*.c

$(depends): $(source) $(headers)
	@$(CC) -MM $(source) > $@	

clean:
	$(RM) $(out) $(objects) $(depends)

.PHONY: clean
sinclude $(depends)

run:
#	./lab1 -N 35 -p 2 -c 5 -i test1_35.txt -o out1.txt -D
#	./lab1 -N 35 -p 2 -c 7 -i test2_35.txt -o out2.txt -D
#	./lab1 -N 30000 -p 2 -c 20000 -i test3_30000.txt -o out3.txt
#	./lab1 -N 1000000 -p 2 -c 5000 -i test4_1M.txt -o out4.txt

#	./lab1 -N 35 -i test1_35.txt -o out1.txt -D
#	./lab1 -N 35 -i test2_35.txt -o out2.txt -D
#	./lab1 -N 30000 -i test3_30000.txt -o out3.txt
#	./lab1 -N 1000000 -i test4_1M.txt -o out4.txt
OPTIONS = -Wall -Wextra -g
CC = gcc
prog : code.o teZZt.o main.o
	${CC} -o prog code.o teZZt.o main.o
code.o : code.c code.h
	${CC} ${OPTIONS} code.c -c 
main.o : code.h teZZt.h main.c 
	${CC} ${OPTIONS} main.c -c 
teZZt.o : teZZt.h teZZt.c 
	${CC} ${OPTIONS} teZZt.c -c 
clean : 
	rm -f code.o teZZt.o main.o prog

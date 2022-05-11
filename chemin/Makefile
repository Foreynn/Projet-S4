CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -g

all : main

main: main.o chemin.o
chemin.o : chemin.h trncn.h

.PHONY : clean
clean :
	rm *.o
	rm main

CC = gcc -lm
CFLAGS = -Wall -Wextra -Werror -std=c99 -g

all : main

main: main.o path_finder.o
path_finder.o : path_finder.h tile.h

.PHONY : clean
clean :
	rm *.o main

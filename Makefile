CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99

all : get_chemin

get_chemin: chemin.o
chemin.o : trncn.h

.PHONY : clean
clean :
	rm *.o

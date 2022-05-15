CC = gcc -lm
CFLAGS = -Wall -Wextra -Werror -std=c99 -g

all : main

main: project_files/pathfinding/pathfinding.o project_files/pathfinding/pf_aux.o
pathfinding.o : project_files/pathfinding/pathfinding.h project_files/pathfinding/pf_aux.h project_files/pathfinding/tile.h
pf_aux.o : project_files/pathfinding/pf_aux.h project_files/pathfinding/tile.h

.PHONY : clean
clean :
	rm project_files/pathfinding/*.o main

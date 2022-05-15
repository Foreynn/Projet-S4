# Makefile
CC = gcc
CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -std=c99 -O3 -g -rdynamic
LDFLAGS= -lm -ldl
LDLIBS = `pkg-config --libs sdl SDL_image gtk+-3.0`

SRC= pixel_operations.c preprocessing.c imgToArray.c model.c pathfinding.c pf_aux.c gui.c

OBJ= $(SRC:%.c=%.o)
DEP= ${SRC:.c=.d}
PRG= ${SRC:.c=.out}

all: rule

rule: $(SRC)
	$(CC) -o main $(CFLAGS) $^ $(LDFLAGS) $(LDLIBS)

-include ${DEP}

clean:
	rm -f *.o
	rm -f *.d
	rm -f main

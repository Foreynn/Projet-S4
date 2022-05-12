CC=gcc
CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -std=c99 -O3 -g #-fsanitize=address
LDFLAGS= -lm -ldl
LDLIBS= `pkg-config --libs sdl SDL_image`

SRC= pixel_operations.c imgToArray.c model.c main.c 

OBJ= $(SRC:%.c=%.o)
DEP= ${SRC:.c=.d}
PRG= ${SRC:.c=.out}

all: rule

rule: $(OBJ)
	$(CC) -o main.out $(CFLAGS) $^ $(LDFLAGS) $(LDLIBS)

-include ${DEP}

clean:
	rm -f *.o
	rm -f *.d
	rm -f ${PRG}
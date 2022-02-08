# Makefile
CC=gcc
CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -g -fsanitize=address
LDFLAGS= -lm -ldl
LDLIBS= `pkg-config --libs sdl SDL_image`

SRC= model_training.c model.c main.c pixel_operations.c imgToArray.c 

OBJ= $(SRC:.c=.o)
DEP= ${SRC:.c=.d}

all: model

model: main.o model.o model_training.o pixel_operations.o imgToArray.o

#$(OBJ)
#	$(CC) -o main.out $(CFLAGS) $^ $(LDFLAGS) $(LDLIBS)

-include ${DEP}

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} model

# END
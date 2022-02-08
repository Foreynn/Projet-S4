CC=gcc
CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -std=c99 -O3 -g -fsanitize=address
LDFLAGS= -lm -ldl
LDLIBS= `pkg-config --libs sdl SDL_image`

SRC= pixel_operations.c model_training.c imgToArray.c model.c main.c 

OBJ= $(SRC:%.c=%.o)
DEP= ${SRC:.c=.d}
PRG= ${SRC:.c=.out}

all: rule

rule: $(OBJ)
	$(CC) -o main.out $(CFLAGS) $^ $(LDFLAGS) $(LDLIBS)

-include ${DEP}

#%.o : %.c
#	$(CC) $(CFLAGS) -c $< -o $@ $(LDLFLAGS) $(CPPFLAGS) $(LDLIBS)

clean:
	rm -f *.o
	rm -f *.d
	rm -f ${PRG}


# Makefile
# CC= gcc
# CPPFLAGS= `pkg-config --cflags sdl` -MMD
# CFLAGS= -Wall -Wextra -fsanitize=address #-g
# LDFLAGS= -lm -ldl
# LDLIBS= `pkg-config --libs sdl SDL_image`

# all: model
# model: main.o model.o model_training.o imgToArray.o pixel_operations.o
# 	${CC} main.o model.o model_training.o imgToArray.o pixel_operations.o ${LDLIBS} -o model ${LDFLAGS}

# main.o : model.h model_training.h imgToArray.h
# model.o : model.o model_training.h
# model_training.o : model_training.h imgToArray.h
# imgToArray.o : imgToArray.h pixel_operations.h
# pixel_operations.o : pixel_operations.h

# .PHONY : clean
# clean : 
# 	rm *.o
# 	rm *.d
# 	rm *.out
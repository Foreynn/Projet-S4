# Makefile
CC=gcc
CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -lm -ldl -Wall -Wextra -g -fsanitize=address
LDFLAGS= -lm -ldl
LDLIBS= `pkg-config --libs sdl SDL_image`

all: model
model: main.o model.o model_training.o imgToArray.o pixel_operations.o

main.o : model.h model_training.h imgToArray.h
model.o : model.o model_training.h
model_training.o : model_training.h imgToArray.h
imgToArray.o : imgToArray.h pixel_operations.h
pixel_operations.o : pixel_operations.h

.PHONY : clean
clean : 
	rm *.o
	rm *.d
	rm *.out
# SRC= model_training.c model.c main.c pixel_operations.c imgToArray.c 

# OBJ= $(SRC:.c=.o)
# DEP= ${SRC:.c=.d}

# all: model

# model: main.o model.o model_training.o pixel_operations.o imgToArray.o

# #$(OBJ)
# #	$(CC) -o main.out $(CFLAGS) $^ $(LDFLAGS) $(LDLIBS)

# -include ${DEP}

# .PHONY: clean

# clean:
# 	${RM} ${OBJ}
# 	${RM} ${DEP}
# 	${RM} model

# # END
#My Makefile

CC = gcc
CPPFLAGS= `pkg-config --cflags sdl` -MMD
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl SDL_image`

all: display decoupage grayscale

decoupage: decoupage.o pixel_operations.o
display: display.o
grayscale: grayscale.o pixel_operations.o

decoupage.o: decoupage.c
pixel_operations.o: pixel_operations.c
display.o: display.c
grayscale.o: grayscale.c

clean:
	${RM} *.o
	${RM} *.d
	${RM} decoupage
	${RM} display
	${RM} grayscale
# END

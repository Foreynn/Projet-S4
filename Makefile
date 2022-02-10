all : get_chemin

get_chemin: chemin.o
chemin.o : trncn.h

.PHONY : clean
clean :
	rm *.o

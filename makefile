LIB = -lncurses
CC = gcc
RM = rm
RM += -f

install:
	$(CC) type.c -o tt $(LIB)
	chmod +x ./tt
	mv ./tt ~/bin/tt

clean:
	$(RM) ~/bin/tt 

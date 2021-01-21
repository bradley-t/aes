FILES = *.c
ARGS =  
NAME = aes

CC = gcc
CFLAGS = -g -Wall
DEBUGGER = gdb
DFLAGS =  
MCHECK = valgrind
MFLAGS = --leak-check=full

all: clean $(NAME)

$(NAME):
	$(CC) $(CFLAGS) -o $(NAME) $(FILES)
clean:
	rm -f $(NAME)
mem:
	$(MCHECK) $(MFLAGS) ./$(NAME) $(ARGS)
run:
	./$(NAME) $(ARGS)
debug:
	$(DEBUGGER) $(DFLAGS) ./$(NAME) $(ARGS)

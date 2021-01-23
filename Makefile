FILES = ./src/*.c
ARGS =  
NAME = aes
TARGET_FILEPATH = ./

CC = gcc
CFLAGS = -g -Wall
DEBUGGER = gdb
DFLAGS =  
MCHECK = valgrind
MFLAGS = --leak-check=full

all: clean $(NAME)

$(NAME): $(FILES)
	$(CC) $(CFLAGS) -o $(TARGET_FILEPATH)$(NAME) $(FILES)

clean:
	rm -f $(TARGET_FILEPATH)$(NAME)
mem:
	$(MCHECK) $(MFLAGS) $(TARGET_FILEPATH)$(NAME) $(ARGS)
debug:
	$(DEBUGGER) $(DFLAGS) $(TARGET_FILEPATH)$(NAME) $(ARGS)

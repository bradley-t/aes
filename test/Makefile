CC = gcc
CFLAGS = -g -Wall
BUILD_DIR = ../build/

clean:
	rm -f $(BUILD_DIR)test_*

test: ffArithmetic_Tests.c
	$(CC) $(CFLAGS) -o $(BUILD_DIR)test_ffArithmetic ffArithmetic_Test.c
	$(BUILD_DIR)test_ffArithmetic

	
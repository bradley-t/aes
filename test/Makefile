CC = gcc
CFLAGS = -g -Wall
BUILD_DIR = ../build/

clean:
	rm -f $(BUILD_DIR)test_*

test: ffArithmetic_Test.c keyExpansion_Test.c
	$(CC) $(CFLAGS) -o $(BUILD_DIR)test_ffArithmetic ffArithmetic_Test.c
	$(BUILD_DIR)test_ffArithmetic
	$(CC) $(CFLAGS) -o $(BUILD_DIR)test_keyExpansion keyExpansion_Test.c
	$(BUILD_DIR)test_keyExpansion

	
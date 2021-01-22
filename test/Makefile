CC = gcc
CFLAGS = -g -Wall
BUILD_DIR = ../build/
SOURCE_DIR = ../src/
SOURCE_FILES = ../src/*.c
RESOURCE = ../src/constants.c

clean:
	rm -f $(BUILD_DIR)test_*

test: ffArithmetic_Test.c keyExpansion_Test.c
	$(CC) $(CFLAGS) -o $(BUILD_DIR)test_ffArithmetic ffArithmetic_Test.c $(SOURCE_FILES)
	$(BUILD_DIR)test_ffArithmetic

	$(CC) $(CFLAGS) -o $(BUILD_DIR)test_keyExpansion keyExpansion_Test.c $(SOURCE_FILES)
	$(BUILD_DIR)test_keyExpansion

	$(CC) $(CFLAGS) -o $(BUILD_DIR)test_cipher cipher_Test.c $(SOURCE_DIR)ffArithmetic.c $(RESOURCE)
	$(BUILD_DIR)test_cipher
	
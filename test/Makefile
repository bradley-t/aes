CC = gcc
CFLAGS = -g -Wall
BUILD_DIR = ../build/
SOURCE_DIR = ../src/
SOURCE_FILES = ../src/*.c
RESOURCE = ../src/constants.c

all: ffArithmetic_Test.c keyExpansion_Test.c cipher_Test.c invCipher_Test.c $(SOURCE_FILES)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)test_ffArithmetic ffArithmetic_Test.c $(SOURCE_FILES)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)test_keyExpansion keyExpansion_Test.c $(SOURCE_FILES)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)test_cipher cipher_Test.c $(SOURCE_DIR)ffArithmetic.c $(RESOURCE)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)test_invCipher invCipher_Test.c $(SOURCE_DIR)ffArithmetic.c $(RESOURCE)

clean:
	rm -f $(BUILD_DIR)test_*

test: all
	$(BUILD_DIR)test_ffArithmetic
	$(BUILD_DIR)test_keyExpansion
	$(BUILD_DIR)test_cipher
	$(BUILD_DIR)test_invCipher
	
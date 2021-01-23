# AES Implementation
Bradley Taylor

### Compiling and Running
Running this implementation is really quite simple. It will however require gcc compiler to be already installed on your machine. First navigate to the project directory (AES). The commands for compiling and running it are:
```
make
./aes key_size cipher_key_file input_file [-d | --decrypt]

```
The allowed aes key sizes are 128, 192 and 256. The program reads both the cipher key and the input block from the files provided. if the -d option (must come at the end) is specified then it will operate in decrypt mode. The aes program writes the result to stdout, which can then be redirected to a file if desired.

Note: I used the plaintext files named key and block when using the program. You may look at them or use them with the aes program. They currently contain the key and plaintext from the first example in appendix C of the FIPS paper.

### Rescources Used
In implementing this project, the only AES rescources I used were the ones provided in the project spec.

### Test Cases
I am happy to say that my code passes all of the tests listed on the website and appendix C of the FIPS paper. You are welcome to run or examine my unit tests found in the test directory. The commands for compiling and running the unit tests are:
```
cd test
make test
```
### Auto Grader
Included is also a screenshot of the results from passing the autograder.
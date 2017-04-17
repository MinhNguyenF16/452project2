Programming language used: C++
====================================================
Program purpose: encrypting multiple blocks of text using modern block
ciphers utilizing DES and AES block ciphers in order to implement the encryption utility.

MAKE SURE YOU HAVE CRYPTO LIBRARY INSTALLED!!!
====================================================
Program instructions:
1. To compile, simply, type "make" at the terminal (without the quotes).
2. To clear all executables, type "make clean"
2. To execute, type in the ternimal this formar: ./cipher <CIPHER NAME> <KEY> <ENC/DEC> <INPUTFILE> <OUTPUT FILE>
Example: ./cipher DES 0123456789abcdef ENC file1.txt file2.txt

Available cipher names:
				– AES
				– DES

# ./cipher DES 0123456789abcdef ENC input.txt output.txt
# ./cipher DES 0123456789abcdef DEC output.txt finalout.txt
# ./cipher AES 00112233445566778899aabbccddeeff ENC input2.txt output2.txt
# ./cipher AES 00112233445566778899aabbccddeeff DEC output2.txt finalout2.txt

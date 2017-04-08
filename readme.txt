Author: Minh Nguyen (minhnguyen16@csu.fullerton.edu)
====================================================
Programming language used: C++
====================================================
Program instructions:
1. To compile, simply, type "make" at the terminal (without the quotes).
2. To clear all executables, type "make clean"
2. To execute, type in the ternimal this formar: ./cipher <CIPHER NAME> <KEY> <ENC/DEC> <INPUTFILE> <OUTPUT FILE>
Example: ./cipher DES 0123456789abcdef ENC file1.txt file2.txt

Available cipher names:
				– AES
				– DES

Cipher key formats:
				– AES : lowercase letters, 32 characters, start with a digit
				– DES : lowercase letters, 16 characters

====================================================
Extra Credit: Did not attempt
====================================================
Note:

Some minor bugs: the aes key must start with a digit not a letter, the aes and des keys must also be in lowercase letters
I also have the file output directly inside DES.cpp and AES.cpp because other methods keep having bugs that cause the file to output in hexadecimal.
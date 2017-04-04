#include <string>
#include <iostream>
#include <fstream>
#include "CipherInterface.h"
#include "DES.h"
#include "AES.h"

using namespace std;

int main(int argc, char** argv)
{
	/**
	 * TODO: Replace the code below	with your code which can SWITCH
	 * between DES and AES and encrypt files. DO NOT FORGET TO PAD
	 * THE LAST BLOCK IF NECESSARY.
	 *
	 * NOTE: due to the incomplete skeleton, the code may crash or
	 * misbehave.
	 */

	string cipherName = argv[1];
	string key = argv[2];
	string mode = argv[3];
	string inputFile = argv[4];
	string outputFile = argv[5];

	cout <<cipherName <<key <<mode <<inputFile <<outputFile <<endl;
	
	// open file and read
	ifstream readFile;
	string inputData;	

	readFile.open(inputFile.c_str());
	readFile >> inputData;
	readFile.close(); 

	cout << "Data received: "<< inputData << endl;
	cout << endl;
	
	/* Create an instance of the DES cipher */	
	CipherInterface* cipher = NULL;
	if ( cipherName == "DES")
		cipher = new DES(); // OK
	//else if ( cipherName == "AES")
	//	cipher = new AES(); // OK
		
	/* Error checks */
	if(!cipher)
	{
		fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",	
		__FILE__, __FUNCTION__, __LINE__);
		exit(-1);
	}
	
	/* Set the encryption key
	 * A valid key comprises 16 hexidecimal
	 * characters. Below is one example.
	 * Your program should take input from
	 * command line.
	 */
	cipher->setKey((unsigned char*)"0123456789abcdef");
	
	/* Perform encryption */
	//string cipherText = cipher->encrypt("hello world");
	unsigned char * ciphertext = cipher->encrypt((const unsigned char*)"BillyBob");
	
	/* Perform decryption */
	//cipher->decrypt(cipherText);	
	
	return 0;
}

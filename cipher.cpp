#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
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
	
	/*
	// open file and read
	ifstream readFile;
	string inputData;	

	readFile.open(inputFile.c_str());
	readFile >> inputData;
	readFile.close(); 

	cout << "Data received: "<< inputData << endl;
	cout << endl;
	*/

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

	
	typedef unsigned char BYTE;
	// open file and read
	//ifstream readFile;
	streampos fileSize;
    ifstream file(inputFile, ios::binary);

    // get its size:
    file.seekg(0, ios::end);
    fileSize = file.tellg();
    file.seekg(0, ios::beg);

    // read the data:
    vector<BYTE> fileData(fileSize);
    file.read((char*) &fileData[0], fileSize);
	cout << " LOL : " << fileSize << endl;

		for ( int x = 0; x<8; x++)
	{
			//writeFile << ciphertext[x];

		cout << fileData[x];
	}

	/*
	ifstream input (inputFile, ios::binary);
	vector<char> buffer((
            istreambuf_iterator<char>(input)), 
            (istreambuf_iterator<char>()));
            */

	// open file and write
	ofstream writeFile;
	writeFile.open("test.txt");

	if (mode == "ENC")
	{
		/* Perform encryption */
		//string cipherText = cipher->encrypt("hello world");
		unsigned char * ciphertext = cipher->encrypt((const unsigned char*)"BillyBob");
		//cout<< ciphertext<<endl;
		/*
		for ( int x = 0; x<8; x++)
		{
			//writeFile << ciphertext[x];

			cout << ciphertext[x];
		}
		*/
		writeFile.write((char *) ciphertext, 8);
		writeFile.close();
	}

	else if (mode == "DEC")
	{
		/* Perform decryption */

		//cipher->decrypt(cipherText);	
		//unsigned char * plaintext = cipher->decrypt(ciphertext);  // OK HERE 1
		//writeFile.write((char *)&plaintext[0], sizeof(plaintext));
		//cout << "Result: "<< plaintext << endl;
		//writeFile << (char*)&plaintext[0];
		//writeFile << plaintext;
		//writeFile.write((char *) plaintext, 8);  // works 2
		/*
		for ( int x = 0; x<sizeof(plaintext); x++)
		{
			writeFile << (char*)&plaintext[x];

			//cout << plaintext[x];
		}
		*/
		//writeFile.write((char *)&plaintext[0], 64);
		// writeFile.close();  // 3
		//cout << "Result: "<< plaintext << endl;
	}
	
	return 0;
}

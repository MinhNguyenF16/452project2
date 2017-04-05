#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include "CipherInterface.h"
#include "DES.h"
#include "AES.h"
#include <math.h>

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
    //unsigned char fileBlock[]= "";
	cout << "Filesize : " << fileSize << endl;
	//cout << fileData<< endl;
	cout << "File content : " ;
	for ( int x = 0; x<fileSize; x++)
	{
		cout << fileData[x];
	}
	cout << endl;
	file.close(); // closes file opened
	
	// see how many blocks needed 
	int blockAmount;
	if (fileSize%8 == 0)
	{
		blockAmount = fileSize/8;
	}
	else
	{
		blockAmount = fileSize/8 + 1;
	}

	vector<BYTE> dataBlock(8);
	/*
	for ( int i = 0; i<8; i++)
	{
		dataBlock[i] = fileData[i];
	}
	*/

	// open file and write
	ofstream writeFile;
	writeFile.open(outputFile);

	if (mode == "ENC")
	{
		int count = 0;
		while (count < blockAmount)
		{
			for ( int i = 0; i<8; i++)
			{
				dataBlock[i] = fileData[count*8+i];
			}
			/* Perform encryption */
			unsigned char * ciphertext = cipher->encrypt((const unsigned char*)reinterpret_cast<char*>(dataBlock.data()) );
			writeFile.write((char *) ciphertext, 8);
			count++;
		}
		writeFile.close();
	}

	else if (mode == "DEC")
	{
		int count = 0;
		while (count < blockAmount)
		{
			for ( int i = 0; i<8; i++)
			{
				dataBlock[i] = fileData[count*8+i];
			}

			/* Perform decryption */
			unsigned char * plaintext = cipher->decrypt((const unsigned char*)reinterpret_cast<char*>(dataBlock.data()) );
			writeFile.write((char *) plaintext, 8);  
			count++;
		}
		writeFile.close();  
	}
	
	return 0;
}

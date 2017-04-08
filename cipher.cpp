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
	string cipherName = argv[1];
	string key = argv[2];
	string mode = argv[3];
	string inputFile = argv[4];
	string outputFile = argv[5];

	//cout <<cipherName <<key <<mode <<inputFile <<outputFile <<endl;
	
	/* Create an instance of the DES cipher */	
	CipherInterface* cipher = NULL;
	if ( cipherName == "DES")
		cipher = new DES(); // OK
	else if ( cipherName == "AES")
		cipher = new AES(); // OK
		
	/* Error checks */
	if(!cipher)
	{
		fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",	
		__FILE__, __FUNCTION__, __LINE__);
		exit(-1);
	}
	
	const char* keyChar;
	if ( cipherName == "DES")
		keyChar= key.c_str();
	else if ( cipherName == "AES")
	{
		if (mode == "ENC")
		{
			// add 00 for ENC in AES mode
			key = "00"+key;
			//cout << "newkey: "<< key <<endl;
			keyChar = key.c_str();
		}
		else if (mode == "DEC")
		{
			// add 11 for ENC in AES mode
			key = "11"+key;
			//out << "newkey: "<< key <<endl;
			keyChar = key.c_str();
		}
	}

	// sets the key
	cipher->setKey((unsigned char*)keyChar);

	// read in the input file
	typedef unsigned char BYTE;
	streampos fileSize;

    ifstream file(inputFile, ios::in |ios::binary);
    file.seekg(0, ios::end);
    fileSize = file.tellg();
    file.seekg(0, ios::beg);

    vector<BYTE> fileData(fileSize);


    file.read((char*) &fileData[0], fileSize);

	//cout << "Filesize : " << fileSize << endl;

	cout << "File content : " ;
	for ( int x = 0; x<fileSize; x++)
	{
		cout << fileData[x];
	}
	cout << endl;
	file.close(); // closes file opened
	
	// see how many blocks needed and if padding is needed
	int blockAmount;
	bool applyPadding;
	int blockSize;

	if ( cipherName == "DES")
		blockSize = 8;
	else if ( cipherName == "AES")
		blockSize = 16;

	if (fileSize% blockSize == 0)
	{
		blockAmount = fileSize/blockSize;
		applyPadding = false;
	}
	else
	{
		blockAmount = fileSize/blockSize + 1;
		applyPadding = true;
	}

	// prepare buffer for each block
	vector<BYTE> dataBlock(blockSize);

	// clearing the file in case it exists before
	fstream clearFile;
	clearFile.open(outputFile, fstream::out | fstream::trunc);
	clearFile.close();

	if (mode == "ENC")
	{
		int count = 0;
		while (count < blockAmount)
		{	
			// apply padding if needed
			if ((applyPadding == true) && (count == blockAmount-1))
			{
				for ( int i = 0; i<blockSize; i++)
				{
					if ( i >= fileSize % blockSize)
						dataBlock[i] = 0;
					else
						dataBlock[i] = fileData[count*blockSize+i];
				}
			}
			else
			{
				for ( int i = 0; i<blockSize; i++)
				{
					dataBlock[i] = fileData[count*blockSize+i];
				}
			}

			/* Perform encryption */
			unsigned char * ciphertext; 
			ciphertext = cipher->encrypt((const unsigned char*)reinterpret_cast<char*>(dataBlock.data()), outputFile );
			
			count++;
		}
		cout << "Encryption ciphertext has been written to " << outputFile << endl;
	}

	else if (mode == "DEC")
	{
		int count = 0;
		int nullIndex= -1;
		while (count < blockAmount)
		{
			for ( int i = 0; i<blockSize; i++)
			{
				dataBlock[i] = fileData[count*blockSize+i];
			}

			// Perform decryption
			unsigned char * plaintext = cipher->decrypt((const unsigned char*)reinterpret_cast<char*>(dataBlock.data()),outputFile );
			
			count++;
		}
		cout << "Decryption plaintext has been written to " << outputFile << endl;
	}
	
	return 0;
}

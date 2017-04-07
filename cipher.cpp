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
	else if ( cipherName == "AES")
		cipher = new AES(); // OK
		
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
	const char* keyChar;
	//char buffer[17];
	if ( cipherName == "DES")
		keyChar= key.c_str();
	else if ( cipherName == "AES")
	{
		if (mode == "ENC")
		{

			key = "00"+key;
			cout << "newkey: "<< key <<endl;
			keyChar = key.c_str();
			//cout << "TEST: "<<keyChar<<endl;
			//keyChar = buffer;
		}
		else if (mode == "DEC")
		{
			//keyChar= DEC.c_str() + key.c_str();
			key = "11"+key;
			cout << "newkey: "<< key <<endl;
			keyChar = key.c_str();
		}
	}
	//strcpy(keyChar, key.c_str() );

	//cipher->setKey((unsigned char*)"0123456789abcdef");

	cipher->setKey((unsigned char*)keyChar);

	typedef unsigned char BYTE;
	// open file and read
	//ifstream readFile;
	streampos fileSize;

    ifstream file(inputFile, ios::in |ios::binary);
	//ifstream file(inputFile);
    // get its size:
    file.seekg(0, ios::end);
    fileSize = file.tellg();
    file.seekg(0, ios::beg);
    //cout<< "\n filesize"<< fileSize <<endl;

    // read the data:
    //fill(readBuffer.begin(), readBuffer.end(), 0);
    vector<BYTE> fileData(fileSize);

    //memset(fileData, 0, fileSize); // new
    file.read((char*) &fileData[0], fileSize);
    //unsigned char fileBlock[]= "";
	cout << "Filesize : " << fileSize << endl;

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

	//int bytesToPad;
	if (fileSize% blockSize == 0)
	{
		blockAmount = fileSize/blockSize;
		applyPadding = false;
	}
	else
	{
		blockAmount = fileSize/blockSize + 1;
		applyPadding = true;
		//bytesToPad = 8- (fileSize % 8);
	}

	vector<BYTE> dataBlock(blockSize);

	// open file and write
	/*
	ofstream writeFile;
	writeFile.open(outputFile);
	*/
	//writeFile.open(outputFile,ios::out | ios::binary);

	fstream clearFile;
	clearFile.open(outputFile, fstream::out | fstream::trunc);
	clearFile.close();

	if (mode == "ENC")
	{
		int count = 0;
		while (count < blockAmount)
		{	
			
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
			//string hope(reinterpret_cast<char*>(cipher->encrypt((const unsigned char*)reinterpret_cast<char*>(dataBlock.data()) ) ));
			//string hope(reinterpret_cast<char*>(ciphertext));
			//cout << "hope: "<<hope;
			//cout << "testtt: " << ciphertext <<endl;
			//unsigned char* bytes3 = new unsigned char[16];
			//bytes3 = &ciphertext[0];
			//cout << "Look: "<<bytes3[0];
			//cout << "Look: "<<*ciphertext;
			//unsigned char temp;
			//int incr = 0;
			/*
			do
			{	
				temp = *(ciphertext);
				incr++;
				cout << temp;
			}
			while (temp!='0');
			*/
			//cout << endl;
			//writeFile.write(( char *) ciphertext, blockSize);
			//writeFile << ciphertext;
			count++;
		}
		//writeFile.close();
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

			unsigned char * plaintext = cipher->decrypt((const unsigned char*)reinterpret_cast<char*>(dataBlock.data()),outputFile );
			
			/*
			if (count == blockAmount-1)
			{
				for ( int j = 0; j<blockSize; j++)
				{
					if (plaintext[j] == 0)
					{
						
						nullIndex = j;
						break;
					}
				}
				//if (nullIndex == -1)
					//writeFile.write((char *) plaintext, blockSize);  
				//else
					//writeFile.write((char *) plaintext, nullIndex);  
			}
			//else
				//writeFile.write((char *) plaintext, blockSize);  
			*/
			count++;
		}
		//writeFile.close();  
	}
	
	return 0;
}

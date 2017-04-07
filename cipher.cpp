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
	//unsigned char ENC = '0';
	//unsigned char DEC = '1';
	//unsigned char filler = NULL;

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

			key = "0"+key;
			cout << "newkey: "<< key <<endl;
			keyChar = key.c_str();
			//cout << "TEST: "<<keyChar<<endl;
			//keyChar = buffer;
		}
		else if (mode == "DEC")
		{
			//keyChar= DEC.c_str() + key.c_str();
			key = "1"+key;
			cout << "newkey: "<< key <<endl;
			keyChar = key.c_str();
		}
	}
	//strcpy(keyChar, key.c_str() );

	//cipher->setKey((unsigned char*)"0123456789abcdef");
	cipher->setKey((unsigned char*)keyChar);

	
	if (cipherName == "AES")
	{
		//unsigned char aes_input[]="helloworld123456aa";
		//unsigned char *  cipherText = cipher->encrypt((unsigned char*)"helloworld123456");
		/*
		cout << "here it is: "<< endl;
		
		for ( int y = 0; y<100; y++)
		{
			cout<<cipherText[y];
		}
		*/
		//cout << cipherText;
		//cout << "haha"<< endl;
		//unsigned char *  plainText = cipher->decrypt(cipherText);
		//cipher->decrypt(
		//(const unsigned char*)reinterpret_cast<char*>(ciphertext)) ;
	}
	
	if (cipherName == "DES")
	{
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
    //memset(fileData, 0, fileSize); // new
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
	
	// see how many blocks needed and if padding is needed
	int blockAmount;
	bool applyPadding;
	//int bytesToPad;
	if (fileSize%8 == 0)
	{
		blockAmount = fileSize/8;
		applyPadding = false;
	}
	else
	{
		blockAmount = fileSize/8 + 1;
		applyPadding = true;
		//bytesToPad = 8- (fileSize % 8);
	}

	vector<BYTE> dataBlock(8);
	//memset(dataBlock, 0, 8); // new


	// open file and write
	ofstream writeFile;
	writeFile.open(outputFile);

	if (mode == "ENC")
	{
		int count = 0;
		while (count < blockAmount)
		{	
			
			if ((applyPadding == true) && (count == blockAmount-1))
			{
				for ( int i = 0; i<8; i++)
				{
					if ( i >= fileSize%8)
						dataBlock[i] = 0;
					else
						dataBlock[i] = fileData[count*8+i];
				}
			}
			else
			{
				for ( int i = 0; i<8; i++)
				{
					dataBlock[i] = fileData[count*8+i];
				}
			}
			

			/*
			for ( int i = 0; i<8; i++)
				{
					dataBlock[i] = fileData[count*8+i];
				}
			*/

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
		int nullIndex= -1;
		while (count < blockAmount)
		{
			for ( int i = 0; i<8; i++)
			{
				dataBlock[i] = fileData[count*8+i];
			}

			/* Perform decryption */
			unsigned char * plaintext = cipher->decrypt((const unsigned char*)reinterpret_cast<char*>(dataBlock.data()) );
			
			if (count == blockAmount-1)
			{
				for ( int j = 0; j<8; j++)
				{
					if (plaintext[j] == 0)
					{
						nullIndex = j;
						break;
					}
				}
				if (nullIndex == -1)
					writeFile.write((char *) plaintext, 8);  
				else
					writeFile.write((char *) plaintext, nullIndex);  
			}
			else
				writeFile.write((char *) plaintext, 8);  
			
			count++;
		}
		writeFile.close();  
	}
	}
	
	return 0;
}

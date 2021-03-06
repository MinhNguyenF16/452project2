#include "DES.h"
#include <iostream>


/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool DES::setKey(const unsigned char* keyArray)
{
	/**
	 * First let's covert the char string
	 * into an integer byte string
	 */
	
	
	/* The key error code */
	int keyErrorCode = -1;

	/* A single byte */
	unsigned char singleByte = 0;	
	
	/* The key index */
	int keyIndex = 0;
	
	/* The DES key index */
	int desKeyIndex = 0;
		
	/* Go through the entire key character by character */
	while(desKeyIndex != 8)
	{
		/* Convert the key if the character is valid */
		if((this->des_key[desKeyIndex] = twoCharToHexByte(keyArray + keyIndex)) == 'z')
			return false;
		
		/* Go to the second pair of characters */
		keyIndex += 2;	
		
		/* Increment the index */
		++desKeyIndex;
	}
	
	fprintf(stdout, "DES KEY: ");
	
	/* Print the key */
	for(keyIndex = 0; keyIndex < 8; ++keyIndex)
		fprintf(stdout, "%x", this->des_key[keyIndex]);
	
	fprintf(stdout, "\n");	
	
	
	/* Set the encryption key */
	if ((keyErrorCode = des_set_key_checked(&des_key, this->key)) != 0)
	{	
		return false;
	}
	
	/* All is well */	
	return true;
}

/**	
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
unsigned char* DES::encrypt(const unsigned char* plaintext, string outputfile)
{

	// allow us to modify the plaintext by making a copy of it as newPlaintext
	unsigned char* newPlaintext = const_cast<unsigned char*>(plaintext);

	// create an array of 8 chars to store the ciphertext
	unsigned char ciphertext[9]; // was 9

	// create a dynamically allocated char array to store and return the ciphertext
	unsigned char* bytes = new unsigned char[8];

	DES_LONG block[2];

	// Use ctol() to convert the first 4 chars into long; store the result in block[0]
	block[0] = ctol(newPlaintext);

	//Use ctol() to convert the second 4 chars into long; store the resul in block[1]
	block[1] = ctol(newPlaintext + 4);

	//Perform des_encrypt1 in order to encrypt the block using this->key (see sample codes for details)
	des_encrypt1(block, this->key, 1); // 1 for ENCRYPTION
	memset(ciphertext, 0, 9); // was 9

	//Convert the first ciphertext long to 4 characters using ltoc()
	ltoc(block[0], ciphertext);

	//Convert the second ciphertext long to 4 characters using ltoc()
	ltoc(block[1], ciphertext + 4);

	//Save the results in the dynamically allocated char array 
	// (e.g. unsigned char* bytes = nerw unsigned char[8]).
	// Print the cipher text 
	//cout << "Ciphertext: "<< ciphertext << endl;
	bytes = ciphertext;

	// write out the data to file
	fstream writedata;
	writedata.open(outputfile, fstream::app);
	writedata << ciphertext;
	writedata.close();

	//Return the pointer to the dynamically allocated array.
	return bytes;
}

/**
 * Decrypts a string of ciphertext
 * @param ciphertext - the ciphertext
 * @return - the plaintext
 */
unsigned char* DES::decrypt(const unsigned char* ciphertext, string outputfile)
{
	//LOGIC:
	// Same logic as encrypt(), except in step 5. decrypt instead of encrypting

	//cout << "Block Content for DEC: "<< ciphertext<<endl;

	// allow us to modify the plaintext by making a copy of it as newCiphertext
	unsigned char* newCiphertext = const_cast<unsigned char*>(ciphertext);

	// create an array of 8 chars to store the plaintext
	unsigned char plaintext[9]; // was 9

	// create a dynamically allocated char array to store and return the plaintext
	unsigned char* bytes = new unsigned char[8];

	//Declate an array DES_LONG block[2];
	DES_LONG block[2];

	//Use ctol() to convert the first 4 chars into long; store the result in block[0]
	block[0] = ctol(newCiphertext);

	//Use ctol() to convert the second 4 chars into long; store the resul in block[1]
	block[1] = ctol(newCiphertext + 4);

	//Perform des_encrypt1 in order to encrypt the block using this->key (see sample codes for details)
	des_encrypt1(block, this->key, 0); // 0 for DECRYPTION
	memset(plaintext, 0, 9); // was 9

	//Convert the first plaintext long to 4 characters using ltoc()
	ltoc(block[0], plaintext);

	// Convert the second plaintext long to 4 characters using ltoc()
	ltoc(block[1], plaintext + 4);

	//8. Save the results in the dynamically allocated char array 
	// (e.g. unsigned char* bytes = nerw unsigned char[8]).
	// Print the plain text 
	//cout << "Plaintext: "<< plaintext << endl;
	bytes = plaintext;

	// write out the data to file
	fstream writedata;
	writedata.open(outputfile, fstream::app);
	writedata << plaintext;
	writedata.close();

	// Return the pointer to the dynamically allocated array.
	return bytes;

}

/**
 * Converts an array of 8 characters
 * (i.e. 4 bytes/32 bits)
 * @param c - the array of 4 characters (i.e. 1-byte per/character
 * @return - the long integer (32 bits) where each byte
 * is equivalent to one of the bytes in a character array
 */
DES_LONG DES::ctol(unsigned char *c) 
{
        /* The long integer */
	DES_LONG l;
        
	l =((DES_LONG)(*((c)++)));
        l = l | (((DES_LONG)(*((c)++)))<<8L);
        l = l | (((DES_LONG)(*((c)++)))<<16L);
        l = l | (((DES_LONG)(*((c)++)))<<24L);
        return l;
};


/** 
 * Converts a long integer (4 bytes = 32 bits)
 * into an array of 8 characters.
 * @param l - the long integer to convert
 * @param c - the character array to store the result
 */
void DES::ltoc(DES_LONG l, unsigned char *c) 
{
        *((c)++)=(unsigned char)(l&0xff);
        *((c)++)=(unsigned char)(((l)>> 8L)&0xff);
        *((c)++)=(unsigned char)(((l)>>16L)&0xff);
        *((c)++)=(unsigned char)(((l)>>24L)&0xff);
}

/**
 * Converts a character into a hexidecimal integer
 * @param character - the character to convert
 * @return - the converted character, or 'z' on error
 */
unsigned char DES::charToHex(const char& character)
{
	/* Is the first digit 0-9 ? */	
	if(character >= '0' && character <= '9')	
		/* Convert the character to hex */
		return character - '0';
	/* It the first digit a letter 'a' - 'f'? */
	else if(character >= 'a' && character <= 'f')
		/* Conver the cgaracter to hex */
		return (character - 97) + 10;	
	/* Invalid character */
	else return 'z';
}

/**
 * Converts two characters into a hex integers
 * and then inserts the integers into the higher
 * and lower bits of the byte
 * @param twoChars - two charcters representing the
 * the hexidecimal nibbles of the byte.
 * @param twoChars - the two characters
 * @return - the byte containing having the
 * valud of two characters e.g. string "ab"
 * becomes hexidecimal integer 0xab.
 */
unsigned char DES::twoCharToHexByte(const unsigned char* twoChars)
{
	/* The byte */
	unsigned char singleByte;
	
	/* The second character */
	unsigned char secondChar;

	/* Convert the first character */
	if((singleByte = charToHex(twoChars[0])) == 'z') 
	{
		/* Invalid digit */
		return 'z';
	}
	
	/* Move the newly inserted nibble from the
	 * lower to upper nibble.
	 */
	singleByte = (singleByte << 4);
	
	/* Conver the second character */
	if((secondChar = charToHex(twoChars[1])) == 'z')
		return 'z'; 
	
	/* Insert the second value into the lower nibble */	
	singleByte |= secondChar;

	return singleByte;
}



#include "AES.h"
#include <iostream>


/* AES-128 bit ECB Encryption key */
	AES_KEY enc_key, dec_key;
/**
 * Sets the key to use
 * @param key - the first byte of this represents whether
 * to encrypt or to decrypt. 00 means encrypt and any other
 * value to decrypt.  Then come the bytes of the 128-bit key
 * (should be 16 of them).
 * @return - True if the key is valid and False otherwise
 */
bool AES::setKey(const unsigned char* keyArray)
{
	/* The key error code */
	int keyErrorCode = -1;

	/* A single byte */
	unsigned char singleByte = 0;	
	
	/* The key index */
	int keyIndex = 2; // start at 2 instead of 0 to skip the first ENC/DEC byte
	
	/* The DES key index */
	int aesKeyIndex = 0;
		
	/* Go through the entire key character by character */
	while(aesKeyIndex != 16)
	{
		
		cout << "xx: "<<keyArray+2<<endl;
		/* Convert the key if the character is valid */
		if((this->aes_key[aesKeyIndex] = twoCharToHexByte(keyArray + keyIndex)) == 'z')
			{
				cout << "WARNING: Please make sure key is lower case" << endl;
				return false;
			}
		cout << "|"<<keyIndex<< "~";
		cout << aesKeyIndex<<"|";
		/* Go to the second pair of characters */
		keyIndex += 2;	
		/* Increment the index */
		++aesKeyIndex;
	}
	cout << "OFFICIAL AES KEY:";
	/* Print the key */
	for(keyIndex = 0; keyIndex < 16; ++keyIndex)
		fprintf(stdout, "%x", this->aes_key[keyIndex]);

	cout << endl;

	if (keyArray[0] == '0' )
	{
		/* Set the encryption key */
		if(AES_set_encrypt_key(aes_key, 128, &enc_key)!=0)
		{
			fprintf(stderr, "AES_set_encrypt_key() failed!\n");
			exit(-1);
		}

	}
	
	else
	{
		/* Set the decryption key */
		if(AES_set_decrypt_key(aes_key, 128, &dec_key) != 0)
		{
			fprintf(stderr, "AES_set_decrypt_key() failed!\n");
			exit(-1);
		}
	}

	return false;
	
}

/**	
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
unsigned char* AES::encrypt(const unsigned char* plainText, string outputfile)
{
	unsigned char enc_out[17]; // was 17
	memset(enc_out, 0, 17); // was 17

	// create a dynamically allocated char array to store and return the ciphertext
	unsigned char* bytes = new unsigned char[16]; // was 17


	/* Encrypt! */
	AES_ecb_encrypt(plainText, enc_out, &enc_key, AES_ENCRYPT);

	cout << "RESULT: "<< enc_out << endl;
	bytes = enc_out;
	cout << "BYTES: " << bytes<<endl;

	fstream writedata;
	writedata.open(outputfile, fstream::app);
	writedata << enc_out;
	writedata.close();
		
	return bytes;	
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
unsigned char* AES::decrypt(const unsigned char* cipherText, string outputfile)
{

	unsigned char dec_out[17];
	memset(dec_out, 0, 17);

	// create a dynamically allocated char array to store and return the ciphertext
	unsigned char* bytes2 = new unsigned char[16]; // was 17

	/* Encrypt! */
	AES_ecb_encrypt(cipherText, dec_out, &dec_key, AES_DECRYPT);

	cout << "RESULT: "<< dec_out << endl;
	bytes2 = dec_out;

	fstream writedata;
	writedata.open(outputfile, fstream::app);
	writedata << dec_out;
	writedata.close();

	return bytes2;	
}

/**
 * Converts a character into a hexidecimal integer
 * @param character - the character to convert
 * @return - the converted character, or 'z' on error
 */
unsigned char AES::charToHex(const char& character)
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
unsigned char AES::twoCharToHexByte(const unsigned char* twoChars)
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



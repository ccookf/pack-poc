/**
 * Repackages a file within a wrapper and encrypts to obfuscate its data.
 * I don't use fixed width types since I don't intend to use it on files large enough to matter.
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include "fileheader.h"
#include "encrypt.h"

int main(int argc, char* argv[])
{
	
	if (argc != 3) 
	{
		std::cout 	<< "Must supply exactly 2 arguments:\n"
					<< "input filename\n"
					<< "output filename" << std::endl;
		return 1;
	}

	char* source = argv[1];
	std::ifstream fin(source, std::ios::binary);
	if (!fin)
	{
		std::cout << "Failed to open file: " << argv[1] << std::endl;
		return 1;
	}

	Header output;
	output.key = EncryptionTools::generateKey();
	output.namelength = strlen(argv[1]);

	//Get the file size
	fin.seekg(0, std::ios::end);
	output.filelength = fin.tellg();
	fin.seekg(0, std::ios::beg);

	//Read the data into the char array
	char* data = new char[output.filelength];
	fin.read(data, output.filelength);
	fin.close();

	//Encrypt the filename & data
	for (int i = 0; i < output.namelength; i++)
		*(source + i) = EncryptionTools::parse(output.key, *(source + i));
	for (int i = 0; i < output.filelength; i++)
		*(data + i) = EncryptionTools::parse(output.key, *(data + i));

	//Output the wrapped file into the new one
	std::ofstream fout(argv[2], std::ios::binary);
	if (!fout)
	{
		std::cout << "Failed to open file: " << argv[2] << std::endl;
		return 1;
	}
	fout.write((char*) &output, sizeof(output));
	fout.write(argv[1], output.namelength); //pack the name
	fout.write(data, output.filelength); //pack the data
	fout.close();

	return 0;
}

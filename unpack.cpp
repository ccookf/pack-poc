#include <iostream>
#include <fstream>
#include "fileheader.h"
#include "encrypt.h"

int main(int argc, char* argv[])
{
	if (argc != 2) 
	{
		std::cout 	<< "Must supply exactly 1 argument:\n"
					<< "input filename" << std::endl;
		return 1;
	}

	std::ifstream fin(argv[1], std::ios::binary);
	if (!fin)
	{
		std::cout << "Failed to open file: " << argv[1] << std::endl;
		return 1;
	}

	//Read the header
	Header file;
	fin.read((char*) &file, sizeof(file));

	//Read and decrypt the filename
	char* filename = new char[file.namelength];
	fin.read(filename, file.namelength);
	for (int i = 0; i < file.namelength; i++)
		filename[i] = EncryptionTools::parse(file.key, filename[i]);
	filename[file.namelength] = '\0'; //ifstream::read() does not null terminate

	//Read the file contents
	char* data = new char[file.filelength];
	fin.read(data, file.filelength);
	for (int i = 0; i < file.filelength; i++)
		data[i] =  EncryptionTools::parse(file.key, data[i]);
	data[file.filelength] = '\0';

	//Close the input file
	fin.close();

	//Write out to a file
	std::ofstream fout(filename, std::ios::binary);
	if (!fout)
	{
		std::cout << "Failed to open file for output: " << filename << std::endl;
		return 1;
	}
	fout.write(data, file.filelength);
	fout.close();

	return 0;
}

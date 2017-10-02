#include <string>

class Header
{
public:
	char key;
	int namelength;
	int filelength; //istream::read(char*, streamsize) where streamsize is signed
};
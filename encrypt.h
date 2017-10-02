/**
 * Simple XOR encryption
 * I wrapped this in a class thinking I was going to do something more complicated,
 * but maybe I'll save that for the next iteration. Whooops.
 */
#include <iostream>
#include <cstdlib>
#include <ctime>

class EncryptionTools
{
public:
	static char generateKey();
	static char parse(char key, char data);
};

char EncryptionTools::generateKey()
{
	srand(time(NULL));
	return (char)((rand() % 256) - 128);;
}

char EncryptionTools::parse(char key, char data)
{
	return data^key;
}

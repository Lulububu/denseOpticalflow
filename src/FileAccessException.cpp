#include "../include/FileAccessException.h"

#include <iostream>
#include <string>
using namespace std;

FileAccessException::FileAccessException(string file_name_):file_name(file_name_)
{
}
FileAccessException::~FileAccessException(void)
{}

const char* FileAccessException::what() const throw()
{
	return string("Impossible d'ouvrir le fichier \"" + file_name + "\"" ).c_str();
}
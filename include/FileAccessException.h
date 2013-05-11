#pragma once
#include <exception>
#include <string>
using namespace std;

/**
 * Classe d'exception pour les problème de lecture de fichiers.
 **/

class FileAccessException :
	public exception
{
public:
	FileAccessException(string file_name_);
	~FileAccessException(void);

	virtual const char* what() const throw();

private:
	string file_name;
};


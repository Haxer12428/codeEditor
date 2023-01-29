#include "globalinclude.h"
#include "debug.h"
#include "fsystem.h"


int main()
{
	
	debug* msg = new debug();
	msg->setMessageState(debug::error, true);
	msg->setMessageState(debug::warning, true);
	msg->setMessageState(debug::message, true);

	fsystem::dir::helpers* dir = new fsystem::dir::helpers(msg);
	dir->setPath<std::string>("C:/Program Files/");


	std::vector<std::string> paths = dir->getAllRecursivePaths();

	for (std::string path : fsystem::global::helpers::getFiles(paths))
	{
		std::cout << path << std::endl;
	}

	std::cout << "Size : " << fsystem::global::helpers::formatSizeInBytes(fsystem::global::helpers::GB, dir->getSize()) << "KB" << std::endl;

	return 0; 
}
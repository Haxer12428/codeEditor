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
	dir->getAllRecursivePaths();
	
	return 0; 
}
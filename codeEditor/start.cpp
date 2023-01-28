#include "globalinclude.h"
#include "debug.h"
#include "fsystem.h"

int main()
{
	
	debug* msg = new debug();
	msg->setMessageState(debug::error, true);
	msg->setMessageState(debug::warning, true);
	msg->setMessageState(debug::message, true);

	fsystem::regular::helpers* file = new fsystem::regular::helpers(msg);
	file->setPath<std::string>("C:/c++/builder 3.0/builder 3.0/regularfile.h");

	std::vector<std::string> bf = file->getBuffer();
	for (std::string l : bf) msg->push(debug::message, l);
	

	return 0; 
}
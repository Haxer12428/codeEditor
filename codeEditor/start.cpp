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
	file->setPath<std::string>("C:/Users/jakub/Desktop/chuu.lua");

	msg->push(debug::message, "test message");

	std::cout << msg->write_to_file("C:/Users/jakub/Desktop/chuu.lua");

	return 0; 
}
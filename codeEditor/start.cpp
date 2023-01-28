#include "globalinclude.h"
#include "debug.h"
#include "fsystem.h"

int main()
{
	
	debug* msg = new debug();
	msg->setMessageState(debug::error, true);
	msg->push(debug::error, "Niga", "reason");

	fsystem::regular::helpers* file = new fsystem::regular::helpers(msg);
	std::cout << file->setPath<std::string>("niga") << std::endl;
	
	
	return 0; 
}
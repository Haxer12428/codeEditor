#include "globalinclude.h"
#include "debug.h"

int main()
{

	debug* msg = new debug();
	msg->setMessageState(debug::error, true);
	msg->push(debug::error, "Niga", "reason");

	return 0; 
}
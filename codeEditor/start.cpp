#include "globalinclude.h"
#include "debug.h"
#include "fsystem.h"
#include "smath.h"

int main()
{
	
	debug* msg = new debug();
	msg->setMessageState(debug::error, true);
	msg->setMessageState(debug::warning, true);
	msg->setMessageState(debug::message, true);

	fsystem::cache::basic::dir* cache = new fsystem::cache::basic::dir(msg);
	cache->create();

	return 0; 
}
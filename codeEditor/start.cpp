#include "globalinclude.h"
#include "debug.h"
#include "fsystem.h"
#include "smath.h"

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

int main()
{
	
	debug* msg = new debug();
	msg->setMessageState(debug::error, true);
	msg->setMessageState(debug::warning, true);
	msg->setMessageState(debug::message, true);

	fsystem::cache::basic::dir* cache = new fsystem::cache::basic::dir(msg);
	cache->create();

	fsystem::cache::basic::file* cfile = new fsystem::cache::basic::file(cache, msg);
	cfile->create();

	cfile->destory();
	cache->destory();
	return 0; 
}